#######################################################
#   Author:     Andrew St. Pierre
#   email:      astpier@purdue.edu
#   ID:         ee364b17
#   Date:       Wednesday, April 17, 2019
#######################################################
import sys
import os
import re
import scipy
import numpy as np
from enum import Enum
from scipy import ndimage, spatial
from scipy.spatial import Delaunay
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from MorphingGUI import *
from Morphing import *

DataPath=os.path.expanduser("TestData/")
def enum(*sequential, **named):
    enums = dict(zip(sequential, range(len(sequential))), **named)
    return type('Enum', (), enums)

class MorphingApp(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MorphingApp, self).__init__(parent)
        self.setupUi(self)

        # Class member variables
        self.states = enum("INIT", "LOADED", "POINTSELECTION_NOPRIOR", "POINTSELECTION_PRIOR", "POINTSELECTION_MIXED")
        self.state = self.states.INIT
        self.startLoaded = False
        self.endLoaded = False
        self.initiallyDisabled = [  self.alphaSlider,
                                    self.alphaLabel,
                                    self.blendImagesPB,
                                    self.trianglesCheckBox,
                                 ]
        self.userAddedPoint = 0
        self.editStack = []
        self.startImagePointsFile = ""
        self.endImagePointsFile = ""
        self.alphaValue = 0.00
        self.imageDimensions = [0,0]
        self.pointsInImages = 0

        # Connect UI components to methods
        self.loadStartImagePB.clicked.connect(self.loadStartImage)
        self.loadEndImagePB.clicked.connect(self.loadEndImage)
        self.startImageView.mousePressEvent = self.startImageClicked
        self.endImageView.mousePressEvent = self.endImageClicked
        self.centralwidget.mousePressEvent = self.somethingClicked
        self.alphaSlider.valueChanged.connect(self.alphaSliderMoved)
        self.trianglesCheckBox.stateChanged.connect(self.delaunayTrianglesDisplay)
        self.keyPressEvent = self.undoHelper
        self.blendImagesPB.clicked.connect(self.blendImages)

        # Initialize the GUI to have some widgets disabled
        for item in self.initiallyDisabled:
            item.setDisabled(True)
    def blendImages(self):
        startingPoints = getPoints(self.startImagePointsFile)
        endingPoints = getPoints(self.endImagePointsFile)
        ld = Delaunay(startingPoints)
        startTriPts = startingPoints[ld.simplices]
        endTriPts = endingPoints[ld.simplices]
        intermediateTriangle = np.array([ v for v in startTriPts ], dtype=np.float64)
        for i in range(0, len(startTriPts)):
            for j in range(0, len(startTriPts[i])):
                for k in range(0, len(startTriPts[i][j])):
                    intermediateTriangle[i][j][k] =   (1 - self.alphaValue)*startTriPts[i][j][k] + (self.alphaValue)*endTriPts[i][j][k]

        morphedLeft = np.array(Image.new('L', (self.startImage.shape[1], self.startImage.shape[0]), 0))
        morphedRight = np.array(Image.new('L', (self.endImage.shape[1], self.endImage.shape[0]), 0))

        for i in range(0, len(intermediateTriangle)):
            matrixLeft = self.getAffineMatrix(startTriPts[i], intermediateTriangle[i])
            matrixRight = self.getAffineMatrix(endTriPts[i], intermediateTriangle[i])
            self.affineTransform(startTriPts[i], intermediateTriangle[i], self.startImage, morphedLeft, matrixLeft)
            self.affineTransform(endTriPts[i], intermediateTriangle[i], self.endImage, morphedRight, matrixRight)
        morphedImage = np.asanyarray((1 - self.alphaValue) * morphedLeft + (self.alphaValue) * morphedRight, dtype=np.uint8)
        imName = "alpha"+str(self.alphaValue)+".png"
        imageio.imwrite(imName, morphedImage)
        self.blendScene = QGraphicsScene()
        self.blendImageView.setScene(self.blendScene)
        self.blendScene.addPixmap(self.scaleThis(QPixmap(imName)))
    def delaunayTrianglesDisplay(self):
        # Clean both displays, then reload points
        startSceneItems = self.startScene.items()
        endSceneItems = self.endScene.items()
        for item in startSceneItems:
            if("QGraphicsPolygonItem" in str(type(item))):
                self.startScene.removeItem(item)
        for item in endSceneItems:
            if("QGraphicsPolygonItem" in str(type(item))):
                self.endScene.removeItem(item)
        # If checked, look and see if there are >= 3 pts
        if(self.trianglesCheckBox.isChecked()):
            if(self.pointsInImages < 3): return
            pen = QPen(QtCore.Qt.cyan) # Default
            if(self.state == self.states.POINTSELECTION_PRIOR):
                pen = QPen(QtCore.Qt.red)
            elif(self.state == self.states.POINTSELECTION_NOPRIOR):
                pen = QPen(QtCore.Qt.blue)
            elif(self.state == self.states.POINTSELECTION_MIXED):
                pen = QPen(QtCore.Qt.cyan)
            startingPoints = getPoints(self.startImagePointsFile)
            endingPoints = getPoints(self.endImagePointsFile)
            ld = Delaunay(startingPoints)
            startTriPts = startingPoints[ld.simplices]
            endTriPts = endingPoints[ld.simplices]
            for tri in startTriPts:
                a = self.startImageView.mapToScene(QPoint(self.scalePoint(number=tri[0][0], axis="x"), self.scalePoint(number=tri[0][1], axis="y")))
                b = self.startImageView.mapToScene(QPoint(self.scalePoint(number=tri[1][0], axis="x"), self.scalePoint(number=tri[1][1], axis="y")))
                c = self.startImageView.mapToScene(QPoint(self.scalePoint(number=tri[2][0], axis="x"), self.scalePoint(number=tri[2][1], axis="y")))
                dTri = QPolygonF([a,b,c])
                self.startScene.addPolygon(dTri, pen)
            for tri in endTriPts:
                a = self.endImageView.mapToScene(QPoint(self.scalePoint(number=tri[0][0], axis="x"), self.scalePoint(number=tri[0][1], axis="y")))
                b = self.endImageView.mapToScene(QPoint(self.scalePoint(number=tri[1][0], axis="x"), self.scalePoint(number=tri[1][1], axis="y")))
                c = self.endImageView.mapToScene(QPoint(self.scalePoint(number=tri[2][0], axis="x"), self.scalePoint(number=tri[2][1], axis="y")))
                dTri = QPolygonF([a,b,c])
                self.endScene.addPolygon(dTri, pen)
        else:
            startSceneItems = self.startScene.items()
            endSceneItems = self.endScene.items()
            for item in startSceneItems:
                if("QGraphicsPolygonItem" in str(type(item))):
                    self.startScene.removeItem(item)
            for item in endSceneItems:
                if("QGraphicsPolygonItem" in str(type(item))):
                    self.endScene.removeItem(item)
    def alphaSliderMoved(self):
        self.alphaValue = float(self.alphaSlider.value())/100.00
        self.alphaLabel.setNum(self.alphaValue)
    def undoHelper(self, event):
        if(event.key() == QtCore.Qt.Key_Backspace):
            oldTask = self.undo()
    def undo(self):
        try:
            task = self.editStack.pop()
        except IndexError:
            return
        if(task[0] == "START"):
            self.startScene.removeItem(self.startScene.items()[0])
            self.userAddedPoint = 0
        if(task[0] == "END"):
            self.endScene.removeItem(self.endScene.items()[0])
            self.userAddedPoint = 1
        return task
    def somethingClicked(self, event=None):
        # If the userAddedPoint state == 2 (left and right selected)
        if(self.userAddedPoint == 2):
            self.userAddedPoint = 0
            taskUndone1 = self.undo()
            taskUndone2 = self.undo()
            if(self.state == self.states.POINTSELECTION_PRIOR):
                self.state = self.states.POINTSELECTION_MIXED
            self.addPointToFile(img="START", xy=[taskUndone2[1][0], taskUndone2[1][1]])
            self.addPointToFile(img="END", xy=[taskUndone1[1][0], taskUndone1[1][1]])
            self.addDot("END", taskUndone1[1], "GREEN")
            self.addDot("START", taskUndone2[1], "GREEN")
            self.delaunayTrianglesDisplay()
    def startImageClicked(self, event):
        if(not self.startLoaded or not self.endLoaded): return
        x = event.pos().x()
        y = event.pos().y()
        scenePoint = self.startImageView.mapToScene(QPoint(float(x),float(y)))
        if(self.userAddedPoint == 0):
            self.addDot("START", [scenePoint.x(), scenePoint.y()], "BLUE")
            self.editStack.append(["START", [scenePoint.x(), scenePoint.y()], "BLUE"])
            self.userAddedPoint = 1
        elif self.userAddedPoint == 2:
            self.somethingClicked()
            self.addDot("START", [scenePoint.x(), scenePoint.y()], "BLUE")
            self.editStack.append(["START", [scenePoint.x(), scenePoint.y()], "BLUE"])
            self.userAddedPoint = 1
    def endImageClicked(self, event):
        if(not self.startLoaded or not self.endLoaded): return
        x = event.pos().x()
        y = event.pos().y()
        scenePoint = self.endImageView.mapToScene(QPoint(float(x),float(y)))
        if(self.userAddedPoint == 1):
            self.addDot("END", [scenePoint.x(), scenePoint.y()], "BLUE")
            self.editStack.append(["END", [scenePoint.x(), scenePoint.y()], "BLUE"])
            self.userAddedPoint = 2
    def addPointToFile(self, img, xy=[], remove=False):
        if(remove == True):
            if(img == "START"):
                with open(self.startImagePointsFile, "a+") as f:
                    f.seek(0, os.SEEK_END)
                    while f.tell() and f.read(1) != "\n":
                        f.seek(-2, os.SEEK_CUR)
                    f.truncate()
            elif(img == "END"):
                with open(self.endImagePointsFile, "a+") as f:
                    f.seek(0, os.SEEK_END)
                    while f.tell() and f.read(1) != "\n":
                        f.seek(-2, os.SEEK_CUR)
                    f.truncate()

        elif(img == "START"):
            self.pointsInImages += 1
            with open(self.startImagePointsFile, "a+") as f:
                x_scaled = self.scalePoint(number=float(xy[0]), axis="x", reverse=True)
                y_scaled = self.scalePoint(number=float(xy[1]), axis="y", reverse=True)
                f.write(f"{x_scaled}  {y_scaled}\n")
        elif(img == "END"):
            with open(self.endImagePointsFile, "a+") as f:
                x_scaled = self.scalePoint(float(xy[0]), "x", reverse=True)
                y_scaled = self.scalePoint(float(xy[1]), "y", reverse=True)
                f.write(f"{x_scaled}  {y_scaled}\n")
        else:
            raise ValueError("Usage: addPointToFile(img=['START','END'], xy=[x,y])")
        return
    def addDot(self, img, point, color="RED", userAdded=True):
        if(color == "RED"):
            pen = QPen(QtCore.Qt.red)
            brush = QBrush(QtCore.Qt.red)
        elif(color == "BLUE"):
            pen = QPen(QtCore.Qt.blue)
            brush = QBrush(QtCore.Qt.blue)
        elif(color == "GREEN"):
            pen = QPen(QtCore.Qt.green)
            brush = QBrush(QtCore.Qt.green)
        if(userAdded):
            if(img == "START"):
                self.startScene.addEllipse(max(point[0]-3,0), point[1]-3, 6, 6, pen, brush)
            elif(img == "END"):
                self.endScene.addEllipse(max(point[0]-3,0), point[1]-3, 6, 6, pen, brush)
        else:
            if(img == "START"):
                self.startScene.addEllipse(max(point[0]-3,0), point[1]-3, 5, 5, pen, brush)
            elif(img == "END"):
                self.endScene.addEllipse(max(point[0]-3,0), point[1]-3, 5, 5, pen, brush)
    def loadStartImage(self):
        filePath, _ = QFileDialog.getOpenFileName(self, caption="Open Start Image ...", filter="Image files (*.png *.jpg)")
        if not filePath:
            return
        self.loadStartImageFromFile(filePath)
    def loadStartImageFromFile(self, filePath):
        # Find the size of the image
        with Image.open(filePath) as img:
            w, h = img.size
        print(f"{w}x{h}")
        self.imageDimensions = [w, h]
        # Create a scene and add scaled pixmap to the scene
        self.startImage = np.asanyarray(imageio.imread(filePath), dtype=np.uint8)
        self.startScene = QGraphicsScene()
        self.startImageView.setScene(self.startScene)
        self.startScene.addPixmap(self.scaleThis(QPixmap(filePath)))
        self.startScene.setSceneRect(0,0,self.startImageView.width(), self.startImageView.height())
        self.startLoaded = True
        # Check for a points file...
        self.startImagePointsFile = filePath+".txt"
        if(os.path.isfile(self.startImagePointsFile)):
            print("Found file containing point correspondences.")
            with open(self.startImagePointsFile, "r") as f:
                lines = f.readlines()
            for line in lines:
                self.pointsInImages += 1
                line = line.split()
                x = self.scalePoint(float(line[0].strip(" ")), "x")
                y = self.scalePoint(float(line[1].strip(" ")), "y")
                self.addDot("START", [x,y], userAdded=False)
            if(self.endLoaded):
                self.state = self.states.POINTSELECTION_PRIOR
                for item in self.initiallyDisabled:
                    item.setEnabled(True)
        else:
            print("File containing point correspondences not found...")
            with open(self.startImagePointsFile, "w") as f:
                print("Created a new points file for start image.")
            if(self.endLoaded):
                self.state = self.states.POINTSELECTION_NOPRIOR
                for item in self.initiallyDisabled:
                    item.setEnabled(True)
    def loadEndImage(self):
        filePath, _ = QFileDialog.getOpenFileName(self, caption="Open End Image ...", filter="Image files (*.png *.jpg)")

        if not filePath:
            return

        self.loadEndImageFromFile(filePath)
    def loadEndImageFromFile(self, filePath):
        # Find the size of the image
        with Image.open(filePath) as img:
            w, h = img.size
        print(f"{w}x{h}")
        # Create a scene and add scaled pixmap to the scene
        self.endImage = np.asanyarray(imageio.imread(filePath), dtype=np.uint8)
        self.endScene = QGraphicsScene()
        self.endImageView.setScene(self.endScene)
        self.endScene.addPixmap(self.scaleThis(QPixmap(filePath)))
        self.endScene.setSceneRect(0,0,self.endImageView.width(), self.endImageView.height())
        self.endLoaded = True
        # Check for a points file...
        self.endImagePointsFile = filePath+".txt"
        if(os.path.isfile(self.endImagePointsFile)):
            print("Found file containing point correspondences.")
            with open(self.endImagePointsFile, "r") as f:
                lines = f.readlines()
            for line in lines:
                line = line.split()
                x = self.scalePoint(float(line[0].strip(" ")), "x")
                y = self.scalePoint(float(line[1].strip(" ")), "y")
                self.addDot("END", [x,y], userAdded=False)
            if(self.startLoaded):
                self.state = self.states.POINTSELECTION_PRIOR
                for item in self.initiallyDisabled:
                    item.setEnabled(True)
        else:
            print("File containing point correspondences not found.")
            with open(self.endImagePointsFile, "w") as f:
                print("Created a new points file for end image.")
            if(self.startLoaded):
                self.state = self.states.POINTSELECTION_NOPRIOR
                for item in self.initiallyDisabled:
                    item.setEnabled(True)
        if(self.trianglesCheckBox.isChecked()):
            self.delaunayTrianglesDisplay()
    def scaleThis(self, object, x=400, y=300):
        return object.scaled(x, y, QtCore.Qt.KeepAspectRatio, QtCore.Qt.SmoothTransformation)
    def scalePoint( self, number, axis, reverse=False, x_0_range=[0,1440], y_0_range=[0,1080],  x_f_range=[0,400], y_f_range=[0,300] ):
        if x_0_range[1] != self.imageDimensions[1] or y_0_range[1] != self.imageDimensions[0]:
            x_0_range = [0, self.imageDimensions[0]]
            y_0_range = [0, self.imageDimensions[1]]
        if(reverse == True):
            if(axis=="x"):
                return ((number-x_f_range[0]) / (x_f_range[1]-x_f_range[0])) * (x_0_range[1]-x_0_range[0]) + x_0_range[0]
            if(axis=="y"):
                return ((number-y_f_range[0]) / (y_f_range[1]-y_f_range[0])) * (y_0_range[1]-y_0_range[0]) + y_0_range[0]
        else:
            if(axis=="x"):
                return ((number-x_0_range[0]) / (x_0_range[1]-x_0_range[0])) * (x_f_range[1]-x_f_range[0]) + x_f_range[0]
            if(axis=="y"):
                return ((number-y_0_range[0]) / (y_0_range[1]-y_0_range[0])) * (y_f_range[1]-y_f_range[0]) + y_f_range[0]
        raise ValueError("Please provide a number and either X or Y axis.")
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

if __name__ == "__main__":
    currentApp = QApplication(sys.argv)
    currentForm = MorphingApp()
    currentForm.show()
    currentApp.exec_()
