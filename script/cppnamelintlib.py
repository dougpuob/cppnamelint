#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os
import locale
import re
import subprocess

from enum import Enum


def get_locale_lang() -> str:
    ret_locale = list(locale.getdefaultlocale())
    ret_locale = list(locale.getdefaultlocale())
    if ret_locale[1] == 'cp950':
        return 'Big5'
    elif ret_locale[1] == 'cp1252':
        return 'utf8'
    else:
        return 'utf8'


class BuildType(Enum):
    DEFAULT = 0
    RELEASE = 1
    DEBUG = 2


class Cmake:
    def __init__(self):
        self.name = ""

    def run(self, project_dir: str, output_dir: str) -> int:
        if project_dir == '' or output_dir == '':
            return -1, None

        exec_obj = Exec()
        error_code, output_message = exec_obj.run('cmake', [])

        return error_code, output_message


class File:
    def __init__(self):
        self.name = ""

    def _match_all(self, intput_file_name: str, ext_name_list: []):
        ext_name_str = '|'.join(ext_name_list)
        regex_pattern = '([a-zA-Z0-9\\s~!@$#%=^&*_\\\\.\\-\\(\\):])+(' + ext_name_str + ')$'
        regex = re.compile(regex_pattern)
        matched = regex.search(intput_file_name)
        print(matched)
        return matched


    def _match_specific(self, intput_file_name: str, specific_name: str, ext_name_list: []):
        if 0 == len(ext_name_list):
            regex_pattern = '(' + specific_name + ')'
        else:
            ext_name_str = '|'.join(ext_name_list)
            regex_pattern = '(' + specific_name + ').(' + ext_name_str + ')$'

        regex = re.compile(regex_pattern)
        matched = regex.search(intput_file_name)
        print(matched)
        return matched


    def find_files(self, root_dir: str, specific_file_name: str, ext_name_list: []) -> []:
        root_dir = os.path.abspath(root_dir)

        found_files = []
        for dir_name, subdirList, fileList in os.walk(root_dir, topdown=False):
            for file_name in fileList:
                if '*' == specific_file_name:
                    is_matched = self._match_all(file_name, ext_name_list)
                else:
                    is_matched = self._match_specific(file_name, specific_file_name, ext_name_list)

                if is_matched:
                    abs_path  = os.path.join(root_dir, dir_name, file_name)
                    norm_path = os.path.normpath(abs_path)
                    found_files.append(norm_path)

        return found_files

    def get_newest_file_loc(self, files: []) -> str:
        files.sort(key=os.path.getmtime, reverse=True)

        if len(files) > 0:
            return files[0]
        else:
            return ''

    def is_exe(self, file_path: str) -> bool:
        if not os.path.isfile(file_path):
            return False

        if os.name == 'nt' and file_path.lower().endswith('.exe'):
            return True

        elif os.name == 'posix' and os.access(file_path, os.X_OK):
            return True

        return False

    def find_exe(self, file_name: str, root_dir: str) -> []:
        basename = os.path.basename(file_name)

        include_ext_names = []
        found_files: [] = self.find_files(root_dir, file_name, include_ext_names)

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

    def run(self, file_name: str, args: [], working_dir: str = '', timeout_sec=30) -> [int, str]:

        output_mix = ''
        ret_code: int = 0

        cmd_and_arg = []
        cmd_and_arg.append(file_name)
        cmd_and_arg.extend(args)

        try:
            # print(cmd_and_arg)
            process = subprocess.Popen(cmd_and_arg, \
                                       stdout=subprocess.PIPE, \
                                       stderr=subprocess.STDOUT, \
                                       universal_newlines=True)
            try:
                std_output, err_output = process.communicate(timeout=timeout_sec)
            except TimeoutExpired:
                process.kill()
                std_output, err_output = process.communicate()

            if None == std_output:
                output_mix = str(std_output)

            if None == err_output:
                output_mix = str(output_mix) + '\n' + str(err_output)

            if None == ret_code:
                ret_code = 0
            else:
                ret_code = process.returncode

        except Exception as e:
            output_mix = str(e)
            ret_code = -1000

        return ret_code, output_mix


class Str:
    def __init__(self):
        self.name = ""

    def remove_last_crlf(self, text: str):
        new_text_list = text.split('\n')
        if new_text_list[len(new_text_list) - 1] == '':
            del new_text_list[len(new_text_list) - 1]

        new_text = '\n'.join(new_text_list)
        return new_text

    def remove_all_empty_line(self, text: str):
        old_text_list: [] = text.split('\n')
        new_text_list: [] = []

        for item in old_text_list:
            if item != '':
                new_text_list.append(item)

        new_text = '\n'.join(new_text_list)
        return new_text


class Lint():
    def __init__(self):
        self.name = ""
        self.exec_obj = Exec()

    def clang_format(self, src_file_path):
        src_file_path = os.path.abspath(src_file_path)

        style_file = "-style=file"
        style_llvm = "-style=llvm"
        style_google = "-style=google"
        style_mozilla = "-style=mozilla"
        style_jsonfmt = "-style=\"{BasedOnStyle: mozilla, IndentWidth: 8}" + "\""

        style_target = style_file
        error_code, output_message = self.exec_obj.run('clang-format', ["-i", style_target, src_file_path])

        return error_code, output_message

