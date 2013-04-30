#!/usr/bin/python
#-*-coding:utf-8-*-

import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import PyQt4.Qt as qt
import ui_projectwizard
import create_project_common
import cfg



class ProjectWizardDlg(QDialog, ui_projectwizard.Ui_ProjectWizard):
    def __init__(self, parent=None):
        super(ProjectWizardDlg, self).__init__(parent)
        self.setupUi(self)
        self.setWindowFlags(qt.Qt.WindowMaximizeButtonHint|qt.Qt.WindowMinimizeButtonHint|qt.Qt.WindowCloseButtonHint)

        # 填充项目列表
        self.projectTree.setHeaderLabels([u"项目列表"])
        common = create_project_common.createProjectCommon()
        arr = common.get_project_list(cfg.cfg_project_template_path)
        rootlist = [self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree, self.projectTree]
        for one_line in arr:
            if one_line[-2:] == ":p":
                is_project = True
                one_line = one_line[:-2]
            else:
                is_project = False
            root = one_line.split("/")
            if len(root) > 0:
                rootlist[len(root)] = QTreeWidgetItem(rootlist[len(root)-1])
                rootlist[len(root)].setText(0, unicode(root[len(root)-1], "utf8"))
                rootlist[len(root)].setText(1, unicode(one_line, "utf8"))
                rootlist[len(root)].setText(2, unicode(str(is_project), "utf8"))

        self.connect(self.projectTree, SIGNAL("itemSelectionChanged()"), self.showProjectUi)

        self.projectPathEdit.setText(unicode(cfg.cfg_project_path, "utf8"))

        
    @pyqtSignature("")
    def on_selectPathButton_clicked(self):
        path = QFileDialog.getExistingDirectory(self, u"选择项目路径", cfg_project_path) 
        self.projectPathEdit.setText(path)

    @pyqtSignature("")
    def showProjectUi(self):
        common = create_project_common.createProjectCommon()
        item = self.projectTree.currentItem().text(1)
        if self.projectTree.currentItem().text(2) == "False":
            self.createProjectButton.setEnabled(False)
            common.remove_all(self)
        else:
            self.createProjectButton.setEnabled(True)
            common.show_ui(self, str(item.toUtf8()))

    @pyqtSignature("")
    def on_createProjectButton_clicked(self):
        common = create_project_common.createProjectCommon()
        common.createProject(self)

    @pyqtSignature("")
    def closeEvent(self, event):
        cfg.cfg_posx = self.x()
        cfg.cfg_posy = self.y()
        cfg.save_cfg(self)
        event.accept()

app = QApplication(sys.argv)
form = ProjectWizardDlg()
if cfg.cfg_posx!=0 and cfg.cfg_posy!=0:
    form.move(cfg.cfg_posx, cfg.cfg_posy)
form.show()

app.exec_()
