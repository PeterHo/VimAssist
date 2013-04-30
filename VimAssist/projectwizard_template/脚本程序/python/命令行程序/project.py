#!/usr/bin/python
#-*-coding:utf-8-*-

import inspect, os
from PyQt4.QtCore import *
from PyQt4.QtGui import *

def show_ui(main_dlg):
	return
	# label = QLabel("xxx")
	# label2 = QLabel("yyy")
	# main_dlg.projectUiLayout.addWidget(label, 1, 4)
	# main_dlg.projectUiLayout.addWidget(label2, 4, 1)


def createProject(main_dlg, common):
	caller_file = inspect.getfile(inspect.currentframe())
	template_path = os.path.abspath(os.path.dirname(caller_file))
	project_name = str(main_dlg.projectNameEdit.text().toUtf8())
	if len(project_name) == 0:
		return

	project_path = str(main_dlg.projectPathEdit.text().toUtf8()) + "/" + project_name + "/"
	# 创建新的工程
	for root, dirs, files in os.walk(template_path):
		# 获得并创建工程目录
		root = root + "/"
		new_project_path = project_path + root.replace(template_path, "")
		new_project_path = common.replace_keys(new_project_path, project_name)
		if not os.path.exists(new_project_path):
			os.mkdir(new_project_path)
		# 复制工程文件
		for file in files:
			if file != "project.py" and file != "project.pyc":
				# 修改文件名
				new_file_name = common.replace_keys(file, project_name)
				# 创建新文件
				fpr = open(root + file, 'r')
				fpw = open(new_project_path + new_file_name, 'w')
				# 写新文件
				for one_line in fpr:
					one_line = common.replace_keys(one_line, project_name)
					fpw.write(one_line)
				fpw.close()
				fpr.close()

	# 将工程加入到项目列表中
	common.add_project_to_list(project_path, project_name)
	# 创建vimentry文件并调用Vim将其打开
	fpw = open(project_path + project_name + ".vimentry", "w")
	fpw.close()
	os.system("gvim " + project_path + project_name + ".vimentry")
