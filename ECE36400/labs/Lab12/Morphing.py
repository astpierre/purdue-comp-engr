import os
import sys
import math
import scipy
from scipy import ndimage, spatial
import imageio
import numpy as np
import matplotlib.pyplot as plt
from pprint import pprint as pp
from functools import lru_cache
from PIL import Image, ImageDraw
import PIL as pillow
from scipy.spatial import Delaunay, ConvexHull
from PIL import ImageDraw,Image,ImageFilter
from scipy.interpolate import RectBivariateSpline
import subprocess as sp

TestFolder="TestData"

def getPoints(fpath):
    with open(fpath) as f:
        lines = f.readlines()
    pts = []
    for line in lines:
        line = line.split()
        pt = np.asanyarray(line, dtype=np.float64, order='C')
        pts.append(pt)
    return np.asanyarray(pts, dtype=np.float64)

def loadTriangles(leftPointFilePath, rightPointFilePath):
    """
    =================================================================
    IN:     Full paths to the txt files containing the (x,y) coords
            of a list of points. (type: str, str)
    OUT:    Tuple of lists of instances of Triangle class (type: tuple)
    =================================================================
    """
    # Load points into a np array
    leftPoints = getPoints(leftPointFilePath)
    rightPoints = getPoints(rightPointFilePath)

    # Delaunay Triangulation on the left image
    ld = Delaunay(leftPoints)
    lTriPts = leftPoints[ld.simplices]
    rTriPts = rightPoints[ld.simplices]

    # Create instances of Triangle class for each set of points
    leftTriangles = [ Triangle(t) for t in lTriPts ]
    rightTriangles = [ Triangle(t) for t in rTriPts ]

    return tuple([leftTriangles, rightTriangles])

class Triangle:
    def __init__(self, vertices):
        if(np.dtype(type(vertices[0][0])) != np.dtype(np.float64)):
            raise ValueError("The argument must be of type 'float64' and be a 3x2 np array.")
        if not (isinstance(vertices, np.ndarray)):
            raise ValueError("Arguments must be 3x2 numpy arrays.")
        if(vertices.shape != (3,2)):
            raise ValueError("The argument must be of type 'float64' and be a 3x2 np array.")
        self.vertices = vertices

    def getPoints(self):
        x_arr = np.asanyarray([ self.vertices[0][0],
                                self.vertices[1][0],
                                self.vertices[2][0] ], dtype=np.float64)
        y_arr = np.asanyarray([ self.vertices[0][1],
                                self.vertices[1][1],
                                self.vertices[2][1] ], dtype=np.float64)

        x_min = np.amin(x_arr)
        x_max = np.amax(x_arr)
        y_min = np.amin(y_arr)
        y_max = np.amax(y_arr)

        img = Image.new('1', (1440,1080), color=0)
        imgD = ImageDraw.Draw(img)

        imgD.polygon(((x_arr[0],y_arr[0]),(x_arr[1],y_arr[1]),(x_arr[2],y_arr[2])), fill=1)

        pts = []
        coords=np.where(np.asanyarray(img, dtype=np.uint8) == [1])
        for i in range(len(list(coords[0]))):
            pts.append((int(coords[1][i]),int(coords[0][i])))

        return np.asanyarray(pts, dtype=np.float64)

class Morpher:
    def __init__(self, leftImage, leftTriangles, rightImage, rightTriangles):
        if not( isinstance(leftImage, np.ndarray) and
                isinstance(rightImage, np.ndarray) and
                isinstance(leftTriangles[0], Triangle) and
                isinstance(rightTriangles[0], Triangle) ):
            raise TypeError("Arguments must be instances of Triangle class and ndarray's.")
        self.leftImage = leftImage
        self.rightImage = rightImage
        self.leftTriangles = leftTriangles
        self.rightTriangles = rightTriangles

    def getImageAtAlpha(self, alpha):
        if(alpha > 1.0 or alpha < 0.0):
            raise ValueError("Alpha must be within range [0.0, 1.0]")

        lVertices = [ t.vertices for t in self.leftTriangles ]
        rVertices = [ t.vertices for t in self.rightTriangles ]

        self.intermediateTriangle = np.array([ v for v in lVertices ], dtype=np.float64)

        for i in range(0, len(lVertices)):
            for j in range(0, len(lVertices[i])):
                for k in range(0, len(lVertices[i][j])):
                    self.intermediateTriangle[i][j][k] =   (1 - alpha)*lVertices[i][j][k] + (alpha)*rVertices[i][j][k]

        morphedLeft = np.array(Image.new('L', (self.leftImage.shape[1], self.leftImage.shape[0]), 0))
        morphedRight = np.array(Image.new('L', (self.rightImage.shape[1], self.rightImage.shape[0]), 0))

        for i in range(0, len(self.intermediateTriangle)):
            matrixLeft = self.getAffineMatrix(lVertices[i], self.intermediateTriangle[i])
            matrixRight = self.getAffineMatrix(rVertices[i], self.intermediateTriangle[i])
            self.affineTransform(lVertices[i], self.intermediateTriangle[i], self.leftImage, morphedLeft, matrixLeft)
            self.affineTransform(rVertices[i], self.intermediateTriangle[i], self.rightImage, morphedRight, matrixRight)

        morphedImage = (1 - alpha) * morphedLeft + (alpha) * morphedRight
        return np.asanyarray(morphedImage, dtype=np.uint8)

    def getAffineMatrix(self, src, dest):
        A = np.array(   [[src[0][0], src[0][1], 1, 0, 0, 0],
                        [0, 0, 0, src[0][0], src[0][1], 1]],dtype=np.float64)
        A = np.append(A, np.array([[src[1][0], src[1][1], 1, 0, 0, 0],
                                   [0, 0, 0, src[1][0], src[1][1], 1]], dtype=np.float64), axis=0)
        A = np.append(A, np.array([[src[2][0], src[2][1], 1, 0, 0, 0],
                                   [0, 0, 0, src[2][0], src[2][1], 1]], dtype=np.float64), axis=0)
        B = np.array([[dest[0][1]], [dest[0][0]], [dest[1][1]], [dest[1][0]], [dest[2][1]], [dest[2][0]]], dtype=np.float64)

        h = np.linalg.solve(A,B)
        return np.array([[h[0], h[1], h[2]],
                         [h[3], h[4], h[5]],
                         [0, 0, 1]], dtype=np.float64)

    def get_interpolation_func(self, interpolation_func):
        self.interpolation_func = interpolation_func

    def affineTransform(self, src, dest, srcIMG, destIMG, matrixAF):
        max_x = (int)(np.max(np.transpose(src)[1])) + 1
        min_x = np.floor(np.min(np.transpose(src)[1])).astype('int')
        min_y = np.floor(np.min(np.transpose(src)[0])).astype('int')
        max_y = (int)(np.max(np.transpose(src)[0])) + 1

        unMaskedImage = srcIMG[min_x:max_x, min_y:max_y]

        self.interpolation_func = RectBivariateSpline(np.arange(min_x,max_x), np.arange(min_y,max_y), unMaskedImage, kx=1, ky=1)

        img = Image.new('L', (srcIMG.shape[1], srcIMG.shape[0]), 0)
        ImageDraw.Draw(img).polygon(( (dest[0][0], dest[0][1]),
                                      (dest[1][0], dest[1][1]),
                                      (dest[2][0], dest[2][1])), outline=255, fill=255)

        mask = np.array(img)
        invMatrixAF = np.linalg.inv(matrixAF)

        lNonZero = np.nonzero(mask)
        lNonZeroOnes = np.ones(len(lNonZero[0]))
        matrixList = np.array([lNonZero[0], lNonZero[1], lNonZeroOnes])
        source_matrix = np.matmul(invMatrixAF, matrixList)
        destIMG[lNonZero[0], lNonZero[1]] = np.round(self.interpolation_func.ev(source_matrix[1], source_matrix[0]))

if __name__ == '__main__':
    leftImagePath = os.path.join(TestFolder, "LeftGray.png")
    rightImagePath = os.path.join(TestFolder, "RightGray.png")
    leftPoints = os.path.join(TestFolder, "points.left.txt")
    rightPoints = os.path.join(TestFolder, "points.right.txt")

    (lTriangles, rTriangles) = loadTriangles(leftPoints, rightPoints)

    leftImage = np.asanyarray(imageio.imread(leftImagePath), dtype=np.uint8)
    rightImage = np.asanyarray(imageio.imread(rightImagePath), dtype=np.uint8)

    M = Morpher(leftImage, lTriangles, rightImage, rTriangles)

    imAtAlpha25 = M.getImageAtAlpha(0.25)
    imageio.imwrite("test25.png", imAtAlpha25)
    imAtAlpha50 = M.getImageAtAlpha(0.50)
    imageio.imwrite("test50.png", imAtAlpha50)
    imAtAlpha75 = M.getImageAtAlpha(0.75)
    imageio.imwrite("test75.png", imAtAlpha75)
