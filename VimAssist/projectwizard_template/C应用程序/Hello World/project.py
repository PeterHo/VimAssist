#!/usr/bin/python
#-*-coding:utf-8-*-

import inspect, os
from PyQt4.QtCore import *
from PyQt4.QtGui import *

def show_ui(main_dlg):
	return

def get_project_sort():
	return 3

def get_project_tags():
    return "set tags+=~/.vim/capptags"

def get_call_file_path():
	return inspect.getfile(inspect.currentframe())

