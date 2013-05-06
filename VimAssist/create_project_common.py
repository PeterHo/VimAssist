#!/usr/bin/python
#-*-coding:utf-8-*-

import sys, os
import cfg

mod = None

class createProjectCommon():
    def get_project_list(self, startPath):
        arr = []

        for root, dirs, files in os.walk(startPath):
            strDir = root.replace(startPath, '')
            if len(strDir) > 0 and strDir.find("^SUB^") == -1:

                if strDir[0] == "/":
                    path = strDir[1:]
                else:
                    path = strDir

                if files:
                    path = path + ":p"

                arr.append(path)

        return arr

    def remove_all(self, main_dlg):
        for i in range(main_dlg.projectUiLayout.count()):
            if main_dlg.projectUiLayout.itemAt(i).widget() != None:
                main_dlg.projectUiLayout.itemAt(i).widget().close()

    def show_ui(self, main_dlg, project_path):
        global mod
        self.remove_all(main_dlg)

        dirname = cfg.cfg_project_template_path + "/" + project_path
        filename = "project"

        if sys.modules.has_key(filename):
            del sys.modules[filename]
        sys.path.insert(0, dirname)
        mod = __import__(filename)
        del sys.path[0]
        mod.show_ui(main_dlg)

    def replace_keys(self, one_line, project_name):
        one_line = one_line.replace("^PROJECTNAME^", project_name)
        one_line = one_line.replace("^PROJECTNAMEL^", project_name.lower())
        one_line = one_line.replace("^PROJECTNAMEU^", project_name.upper())
        one_line = one_line.replace("^SUB^", "")
        one_line = one_line.replace("^ARMLIBPATH^", cfg.armlib_path)
        one_line = one_line.replace("^ARMBINPATH^", cfg.armbin_path)
        return one_line

    def copy_file(self, oldfile, newfile, project_name):
        fpr = open(oldfile, 'r')
        fpw = open(newfile, 'w')
        for one_line in fpr:
            one_line = self.replace_keys(one_line, project_name)
            fpw.write(one_line)
        fpw.close()
        fpr.close()

    def createProject(self, main_dlg):
        global mod

        # 获取路径,文件名等信息
        caller_file = mod.get_call_file_path()
        template_path = os.path.abspath(os.path.dirname(caller_file))
        project_name = str(main_dlg.projectNameEdit.text().toUtf8())
        project_path = str(main_dlg.projectPathEdit.text().toUtf8()) + "/" + project_name + "/"
        if len(project_name) == 0:
            return

        # 创建新的工程
        for root, dirs, files in os.walk(template_path):
            # 获得并创建工程目录
            root = root + "/"
            new_project_path = project_path + root.replace(template_path, "")
            new_project_path = self.replace_keys(new_project_path, project_name)
            if not os.path.exists(new_project_path):
                os.mkdir(new_project_path)
            # 复制工程文件
            for file in files:
                if file != "project.py" and file != "project.pyc":
                    # 修改文件名
                    new_file_name = self.replace_keys(file, project_name)
                    # 创建新文件
                    self.copy_file(root+file, new_project_path + new_file_name, project_name)

        # 判断是否需要建立CMakeLists.txt
        if mod.get_project_sort() == 3:
            if not os.path.isfile(project_path + "CMakeLists.txt"):
                self.copy_file(cfg.assist_path + "CMakeLists_CApp.txt", project_path + "CMakeLists.txt", project_name)
        elif mod.get_project_sort() == 4:
            if not os.path.isfile(project_path + "CMakeLists.txt"):
                self.copy_file(cfg.assist_path + "CMakeLists_CPPApp.txt", project_path + "CMakeLists.txt", project_name)

        # 创建.vimprj目录以及项目文件
        os.mkdir(project_path + ".vimprj")
        fpw = open(project_path + ".vimprj/" + "common.vim", "w")
        fpw.write("cs add ./.vimprj/cscope.out\n")
        fpw.write(mod.get_project_tags())
        fpw.write("\n")
        fpw.close()

        # gen vim script and exit
        fpw = open(cfg.assist_path + "prj.vim_", "w")
        fpw.write(":call nerdtree#closeTreeIfOpen()\n")
        fpw.write(":call g:NERDTreeCreator.CreatePrimary(\'" + project_path + "\')\n")
        fpw.write(":call nerdtree#bookmarkNode(\'" + project_name + "\')\n")
        fpw.close()

        os._exit(1)
