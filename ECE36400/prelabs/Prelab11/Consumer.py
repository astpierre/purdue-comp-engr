#######################################################
#   Author:     Andrew
#   email:      astpier@purdue.edu
#   ID:         ee364b17
#   Date:       Thursday, March 28, 2019
#######################################################

import sys
import os
from PyQt5.QtWidgets import QMainWindow, QApplication, QFileDialog
import xml.etree.ElementTree as ET
from BasicUI import *

DataPath=os.path.expanduser('~ee364/DataFolder/Prelab11')

class Consumer(QMainWindow, Ui_MainWindow):

    def __init__(self, parent=None):

        super(Consumer, self).__init__(parent)
        self.setupUi(self)

        # Organize components by category
        self.studentData    =  [self.txtStudentName, self.txtStudentID]

        self.compNames      =  [self.txtComponentName_1,self.txtComponentName_2,
                                self.txtComponentName_3,self.txtComponentName_4,
                                self.txtComponentName_5,self.txtComponentName_6,
                                self.txtComponentName_7,self.txtComponentName_8,
                                self.txtComponentName_9,self.txtComponentName_10,
                                self.txtComponentName_11,self.txtComponentName_12,
                                self.txtComponentName_13,self.txtComponentName_14,
                                self.txtComponentName_15,self.txtComponentName_16,
                                self.txtComponentName_17,self.txtComponentName_18,
                                self.txtComponentName_19,self.txtComponentName_20]

        self.compQuantities =  [self.txtComponentCount_1,self.txtComponentCount_2,
                                self.txtComponentCount_3,self.txtComponentCount_4,
                                self.txtComponentCount_5,self.txtComponentCount_6,
                                self.txtComponentCount_7,self.txtComponentCount_8,
                                self.txtComponentCount_9,self.txtComponentCount_10,
                                self.txtComponentCount_11,self.txtComponentCount_12,
                                self.txtComponentCount_13,self.txtComponentCount_14,
                                self.txtComponentCount_15,self.txtComponentCount_16,
                                self.txtComponentCount_17,self.txtComponentCount_18,
                                self.txtComponentCount_19,self.txtComponentCount_20]

        # Initial button states [load and save]
        self.enableLoadDisableSave()

        # Connect UI components to methods
        self.btnSave.clicked.connect(self.saveData)
        self.btnClear.clicked.connect(self.clearUI)
        self.btnLoad.clicked.connect(self.loadData)

        # Assign behavior when use edits fields
        for component in self.studentData:
            component.textChanged.connect(self.enableSaveDisableLoad)
        for component in self.compNames:
            component.textChanged.connect(self.enableSaveDisableLoad)
        for component in self.compQuantities:
            component.textChanged.connect(self.enableSaveDisableLoad)
        self.cboCollege.currentIndexChanged.connect(self.enableSaveDisableLoad)
        self.chkGraduate.stateChanged.connect(self.enableSaveDisableLoad)

    def saveData(self):
        if(self.chkGraduate.isChecked()):
            isGrad="true"
        else: isGrad="false"
        target_file = open("target.xml", "w")
        target_file.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
        target_file.write("<Content>\n")
        studentName = self.txtStudentName.text()
        target_file.write("\t<StudentName graduate=\""+isGrad+"\">"+studentName+"</StudentName>\n")
        studentID = self.txtStudentID.text()
        target_file.write("\t<StudentID>"+studentID+"</StudentID>\n")
        college = self.cboCollege.itemText(self.cboCollege.currentIndex())
        target_file.write("\t<College>"+college+"</College>\n")
        target_file.write("\t<Components>\n")
        for i in range(20):
            cname = self.compNames[i].text()
            ccount = self.compQuantities[i].text()
            if(cname == ""): pass
            else:
                target_file.write("\t\t<Component name=\""+cname+"\" count=\""+ccount+"\" />\n")
        target_file.write("\t</Components>\n")
        target_file.write("</Content>\n")
        target_file.close()

    def clearUI(self):
        for component in self.studentData:
            component.clear()
        for component in self.compNames:
            component.clear()
        for component in self.compQuantities:
            component.clear()
        self.enableLoadDisableSave()
        self.chkGraduate.setChecked(False)
        self.cboCollege.setCurrentIndex(0)

    def enableSaveDisableLoad(self):
        self.btnSave.setEnabled(True)
        self.btnLoad.setEnabled(False)

    def enableLoadDisableSave(self):
        self.btnSave.setEnabled(False)
        self.btnLoad.setEnabled(True)

    def loadData(self):
        """
        *** DO NOT MODIFY THIS METHOD! ***
        Obtain a file name from a file dialog, and pass it on to the loading method. This is to facilitate automated
        testing. Invoke this method when clicking on the 'load' button.

        You must modify the method below.
        """
        filePath, _ = QFileDialog.getOpenFileName(self, caption='Open XML file ...', filter="XML files (*.xml)")

        if not filePath:
            return

        self.loadDataFromFile(filePath)

    def loadDataFromFile(self, filePath):
        """
        Handles the loading of the data from the given file name. This method will be invoked by the 'loadData' method.

        *** YOU MUST USE THIS METHOD TO LOAD DATA FILES. ***
        *** This method is required for unit tests! ***
        """
        tree = ET.parse(filePath)
        root = tree.getroot()
        idx = 0

        studentInfo = root.find("StudentName")
        isGrad = studentInfo.get("graduate")
        if isGrad == "true": self.chkGraduate.setChecked(True)
        else: self.chkGraduate.setChecked(False)
        self.txtStudentName.setText(studentInfo.text)
        studentID = root.find("StudentID").text
        self.txtStudentID.setText(studentID)
        studentCollege = root.find("College").text
        whichComboIDX = self.cboCollege.findText(studentCollege)
        self.cboCollege.setCurrentIndex(whichComboIDX)

        for comp in root.iter('Component'):
            if(idx > 19): break
            name = comp.get('name')
            count = comp.get('count')
            self.compNames[idx].setText(name)
            self.compQuantities[idx].setText(count)
            idx += 1

        self.enableSaveDisableLoad()

if __name__ == "__main__":
    currentApp = QApplication(sys.argv)
    currentForm = Consumer()
    currentForm.show()
    currentApp.exec_()
