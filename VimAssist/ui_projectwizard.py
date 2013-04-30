# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ProjectWizard.ui'
#
# Created: Mon Apr 15 20:38:55 2013
#      by: PyQt4 UI code generator 4.10
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_ProjectWizard(object):
    def setupUi(self, ProjectWizard):
        ProjectWizard.setObjectName(_fromUtf8("ProjectWizard"))
        ProjectWizard.resize(726, 499)
        ProjectWizard.setMinimumSize(QtCore.QSize(726, 499))
        self.horizontalLayout_4 = QtGui.QHBoxLayout(ProjectWizard)
        self.horizontalLayout_4.setObjectName(_fromUtf8("horizontalLayout_4"))
        self.horizontalLayout_3 = QtGui.QHBoxLayout()
        self.horizontalLayout_3.setObjectName(_fromUtf8("horizontalLayout_3"))
        self.projectTree = QtGui.QTreeWidget(ProjectWizard)
        self.projectTree.setToolTip(_fromUtf8(""))
        self.projectTree.setStatusTip(_fromUtf8(""))
        self.projectTree.setHeaderHidden(False)
        self.projectTree.setObjectName(_fromUtf8("projectTree"))
        self.projectTree.headerItem().setText(0, _fromUtf8("1"))
        self.horizontalLayout_3.addWidget(self.projectTree)
        self.verticalLayout_3 = QtGui.QVBoxLayout()
        self.verticalLayout_3.setObjectName(_fromUtf8("verticalLayout_3"))
        self.groupBox = QtGui.QGroupBox(ProjectWizard)
        self.groupBox.setStyleSheet(_fromUtf8("QGroupBox {\n"
"    border-width:1px;\n"
"    border-style:solid;\n"
"    border-color:lightGray;\n"
"    margin-top: 0.5ex;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
"    left:25px;\n"
"    margin-left: 0px;\n"
"    padding:0 1px;\n"
"}"))
        self.groupBox.setFlat(False)
        self.groupBox.setCheckable(False)
        self.groupBox.setObjectName(_fromUtf8("groupBox"))
        self.gridLayout = QtGui.QGridLayout(self.groupBox)
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        spacerItem = QtGui.QSpacerItem(454, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem, 1, 0, 1, 1)
        self.projectUiLayout = QtGui.QGridLayout()
        self.projectUiLayout.setObjectName(_fromUtf8("projectUiLayout"))
        spacerItem1 = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.projectUiLayout.addItem(spacerItem1, 0, 0, 1, 1)
        self.gridLayout.addLayout(self.projectUiLayout, 0, 0, 1, 1)
        self.verticalLayout_3.addWidget(self.groupBox)
        self.verticalLayout = QtGui.QVBoxLayout()
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.label = QtGui.QLabel(ProjectWizard)
        self.label.setObjectName(_fromUtf8("label"))
        self.horizontalLayout.addWidget(self.label)
        self.projectPathEdit = QtGui.QLineEdit(ProjectWizard)
        self.projectPathEdit.setObjectName(_fromUtf8("projectPathEdit"))
        self.horizontalLayout.addWidget(self.projectPathEdit)
        self.selectPathButton = QtGui.QToolButton(ProjectWizard)
        self.selectPathButton.setObjectName(_fromUtf8("selectPathButton"))
        self.horizontalLayout.addWidget(self.selectPathButton)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName(_fromUtf8("horizontalLayout_2"))
        self.label_2 = QtGui.QLabel(ProjectWizard)
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.horizontalLayout_2.addWidget(self.label_2)
        self.projectNameEdit = QtGui.QLineEdit(ProjectWizard)
        self.projectNameEdit.setObjectName(_fromUtf8("projectNameEdit"))
        self.horizontalLayout_2.addWidget(self.projectNameEdit)
        self.createProjectButton = QtGui.QPushButton(ProjectWizard)
        self.createProjectButton.setObjectName(_fromUtf8("createProjectButton"))
        self.horizontalLayout_2.addWidget(self.createProjectButton)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        self.verticalLayout_3.addLayout(self.verticalLayout)
        self.horizontalLayout_3.addLayout(self.verticalLayout_3)
        self.horizontalLayout_4.addLayout(self.horizontalLayout_3)

        self.retranslateUi(ProjectWizard)
        QtCore.QMetaObject.connectSlotsByName(ProjectWizard)

    def retranslateUi(self, ProjectWizard):
        ProjectWizard.setWindowTitle(_translate("ProjectWizard", "项目向导", None))
        self.groupBox.setTitle(_translate("ProjectWizard", "项目属性", None))
        self.label.setText(_translate("ProjectWizard", "项目路径", None))
        self.selectPathButton.setText(_translate("ProjectWizard", "...", None))
        self.label_2.setText(_translate("ProjectWizard", "项目名称", None))
        self.createProjectButton.setText(_translate("ProjectWizard", "生成项目", None))

