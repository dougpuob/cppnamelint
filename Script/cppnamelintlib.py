#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import sys
import re
import platform
from subprocess import Popen, PIPE

import os
import re
import locale
import shutil
import platform

from subprocess import Popen, PIPE


def get_locale_lang() ->str:
    ret_locale = list(locale.getdefaultlocale())
    if ret_locale[1] == 'cp950':
        return 'Big5'
    elif ret_locale[1] == 'cp1252':
        return 'utf8'
    else:
        return 'utf8'


class Cmake:
    def __init__(self):
        self.name = ""

    def run(self, project_dir:str, output_dir:str) -> int:
        if project_dir == '' or output_dir =='':
            return -1, None

        exec_obj = Exec()
        error_code, output_message = exec_obj.run('cmake', [])

        return error_code, output_message



class File:
    def __init__(self):
        self.name = ""


    def find_files(self, root_dir:str, ext_name_list:[]) -> []:
        root_dir = os.path.abspath(root_dir)

        found_files = []
        for dir_name, subdirList, fileList in os.walk(root_dir, topdown=False):
            for file_name in fileList:
                is_matched = False
                if 0 == len(ext_name_list):
                    is_matched = True
                else:
                    for ext_name in ext_name_list:
                        if file_name.endswith(ext_name):
                            is_matched = True
                            break

                if is_matched:
                    abs_path = os.path.join(root_dir, dir_name, file_name)
                    norm_path = os.path.normpath(abs_path)
                    found_files.append(norm_path)

        return found_files


    def get_newest_file_loc(self, files:[]) -> str:
        files.sort(key=os.path.getmtime, reverse=True)

        if len(files) > 0:
            return files[0]
        else:
            return ''


    def is_exe(self, file_path:str) -> bool:
        if not os.path.isfile(file_path):
            return False

        if os.name == 'nt' and file_path.lower().endswith('.exe'):
            return True

        elif os.name == 'posix' and os.access(file_path, os.X_OK):
            return True

        return False


    def find_exe(self, file_name:str, root_dir:str) ->[]:
        basename = os.path.basename(file_name)

        include_ext_names = []
        found_files: [] = self.find_files(root_dir, include_ext_names)

        found_exe_files: [] = []
        if len(found_files) > 0:
            for path in found_files:
                if self.is_exe(path):
                    found_exe_files.append(path)

        return found_exe_files


    def find_newest_exe(self, file_name, dir_path) -> str:

        found_list = self.find_exe(file_name, dir_path)
        newest_file = self.get_newest_file_loc(found_list)

        return newest_file



class Exec:
    def __init__(self):
        self.name = ""


    def run(self, file_name:str, args:[], working_dir:str='') -> [int, str]:

        output_mix = ''
        ret_code: int = 0

        try:
            cmd_and_arg = []
            cmd_and_arg.append(file_name)
            cmd_and_arg.extend(args)

            process = Popen(cmd_and_arg, stdout=PIPE, stderr=PIPE, universal_newlines=True)

            if process:
                text1 = None
                text2 = None

                while '' != text1 or '' != text2:

                    text1 = process.stdout.read()
                    if text1 != "":
                        output_mix = output_mix + text1

                    text2 = process.stderr.read()
                    if text2 != "":
                        output_mix = output_mix + text2

                process.stderr.close()
                process.stdout.close()
                process.wait(10)

                ret_code = process.returncode
                if None == ret_code:
                    ret_code = 0


        except Exception as e:
            print(str(e))

        return ret_code, output_mix
