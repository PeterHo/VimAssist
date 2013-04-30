#!/usr/bin/python
#-*-coding:utf-8-*-

import inspect, os
import ConfigParser

assist_path = os.path.dirname(inspect.getfile(inspect.currentframe())) + "/"
armlib_path = os.path.realpath("~/opt/FriendlyARM/toolschain/4.5.1/lib/")
armbin_path = os.path.realpath("~/opt/FriendlyARM/toolschain/4.5.1/bin/")
config_path = assist_path + "config.ini"


def save_cfg(main_dlg):
    global config
    global config_path
    global cfg_posx
    global cfg_posy
    global cfg_project_path
    global cfg_project_template_path


    config.set("CONFIG", "project_path", cfg_project_path)
    config.set("CONFIG", "project_template_path", cfg_project_template_path)
    config.set("CONFIG", "posx", str(cfg_posx))
    config.set("CONFIG", "posy", str(cfg_posy))

    config.write(open(config_path, "w"))


config = ConfigParser.SafeConfigParser()
config.read(config_path)

cfg_posx = config.getint("CONFIG", "posx")
cfg_posy = config.getint("CONFIG", "posy")
cfg_project_path = config.get("CONFIG", "project_path")
cfg_project_template_path = config.get("CONFIG", "project_template_path")
