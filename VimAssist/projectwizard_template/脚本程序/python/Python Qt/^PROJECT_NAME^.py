#!/usr/bin/python
#-*-coding:utf-8-*-

import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import PyQt4.Qt as qt
import ui_^PROJECTNAMEL^

class ^PROJECTNAME^Dlg(QDialog, ui_^PROJECTNAMEL^.Ui_^PROJECTNAME^):
	def __init__(self, parent=None):
		super(^PROJECTNAME^Dlg, self).__init__(parent)
		self.setupUi(self)
		self.setWindowFlags(qt.Qt.WindowMaximizeButtonHint|qt.Qt.WindowMinimizeButtonHint|qt.Qt.WindowCloseButtonHint)

	# @pyqtSignature("")
	# def on_button_clicked(self):

app = QApplication(sys.argv)
form = ^PROJECTNAME^Dlg()
form.show()

app.exec_()
