#!/usr/bin/python3

"""cppnamelint.

Usage:
  cppnamelint.py check <srcdir> <config> [--includes=<dirs>] [--ignores=<paths>]
  cppnamelint.py pack  <rootdir> <outputdir>
  cppnamelint.py test  <srcdir> <config>
  cppnamelint.py test-sample <sampledir>
  cppnamelint.py (-h | --help)
  cppnamelint.py (-v | --version)
  cppnamelint.py --help     Show this screen.
  cppnamelint.py --version  Show version.

Options:
    --log=<file>     [default: cppnamelint.log]
"""

import os
import sys
import re
import platform

from subprocess import Popen, PIPE

from docopt import docopt
import shutil
import os
import sys
import re
import platform
import unittest

from subprocess import Popen, PIPE

from docopt import docopt


class Utility():
    def __init__(self):
        self.name = ""

    def is_ascii_string(self, input_string):
        return all(ord(c) < 128 for c in input_string)

    def run_file(self, exec_file_name, arguments):
        try:

            print(exec_file_name + " (" + arguments + ")")

            cmd_and_arg = []
            cmd_and_arg.append(exec_file_name)
            new_args = arguments.split(' ')
            cmd_and_arg.extend(new_args)
            process = Popen(cmd_and_arg, stdin=PIPE, stdout=PIPE, stderr=PIPE)
            stdout, stderr = process.communicate()

            stdout_str = self.pipe_output(str(stdout))
            print(stdout_str)
            # stderr_str = self.pipe_output(str(stderr))
            # print(stderr_str)

        except Exception as e:
            print(str(e))

    def find_target_app(self, file_name, build_dir):
        pure_file_name = os.path.basename(file_name)
        if len(pure_file_name.split('.')) > 1:
            pure_file_name = pure_file_name.split('.')[0]

        root_path = build_dir
        ext_name_list = []
        found_file_list = []
        self.find_files(root_path, ext_name_list, found_file_list)

        # Collect executable files.
        selected_executable_files = []
        self.select_executable_files(
            file_name, found_file_list, selected_executable_files)

        # Find the latest executable file.
        selected_executable_files.sort(key=os.path.getmtime, reverse=True)

        if len(selected_executable_files) > 0:
            return selected_executable_files[0]
        else:
            return ""

    def select_executable_files(self, exec_file_name, full_file_list, output_file_list):
        for file_path in full_file_list:
            if os.path.isfile(file_path) and os.path.basename(file_path).find(exec_file_name) > -1:
                if 'nt' == os.name and file_path.endswith('.exe'):
                    output_file_list.append(file_path)
                elif 'posix' == os.name and os.access(file_path, os.X_OK) and len(os.path.basename(file_path)) == len(exec_file_name):
                    output_file_list.append(file_path)

    def exclude_folder(self, excluded_folder_name, full_file_list, output_file_list):
        for file_path in full_file_list:
            file_path = os.path.normpath(file_path)
            sliced_folder_list = file_path.split(os.sep)

            ignore_triggered = False
            for folder_name in sliced_folder_list:
                if folder_name == excluded_folder_name:
                    ignore_triggered = True
                    break

            if ignore_triggered:
                continue

            output_file_list.append(file_path)

    def find_files(self, root_path, ext_name_list, output_file_list):
        root_path = os.path.abspath(root_path)
        for dir_name, subdirList, fileList in os.walk(root_path, topdown=False):
            for file_name in fileList:
                condition_hit = False
                if 0 == len(ext_name_list):
                    condition_hit = True
                else:
                    for ext_name in ext_name_list:
                        if file_name.endswith(ext_name):
                            condition_hit = True
                            break

                if condition_hit:
                    abs_path = os.path.join(root_path, dir_name, file_name)
                    norm_path = os.path.normpath(abs_path)
                    output_file_list.append(norm_path)

    def pipe_output(self, pipe_output):
        output = ""
        regex = re.compile(r'^b[\"|\'|`]([\S|\s|:|\\|\.|\/|\n]*)[\"|\'|`]')
        pipe_string = str(pipe_output).strip()

        if pipe_output and pipe_string != "None" and pipe_string != "":
            match = regex.search(pipe_string)
            if match:
                match_result = match.group(1)
                match_result = match_result.replace('\\r', '')
                match_result = match_result.replace('\\\\', '\\')
                if match_result:
                    new_str_lines = match_result.split("\\n")

                    for new_str in new_str_lines:
                        output = output + new_str + "\n"
        return output

    def del_file(self, dir_path, ext_name):
        dirs = os.listdir(dir_path)
        for item in dirs:
            if item.endswith(ext_name):
                os.remove(item)



class Helper():
    def __init__(self):
        self.name = ""

    def make_test_info(self, path_name, src_name, cfg_name):
        json_obj_item = {'PathName'     : path_name,
                         'FileName'     : src_name,
                         'ConfigName'   : cfg_name}
        return json_obj_item
    
    def make_test_argument_string(self, json_info):
        arugment_string = 'check ' + \
            os.path.join(json_info['PathName'], json_info['FileName']) + ' --config=' + \
            os.path.join(json_info['PathName'], json_info['ConfigName'])
        return arugment_string



class Packer():
    def __init__(self):
        self.name = ""
        self.utility = Utility()
        self.root_path = ''
        self.file_list = []

    def set_file_list(self, root_path):
        self.file_list = []

        self.root_path = os.path.abspath(root_path)

        exe_file = self.utility.find_target_app('cppnamelint', os.path.join(self.root_path, 'Build'))
        if os.path.exists(exe_file):
            self.file_list.append(self.make_file_info(False, exe_file                     , 'Script/Release'))
            self.file_list.append(self.make_file_info(False, 'Source/cppnamelint.toml'    , 'Script/Release'))
            self.file_list.append(self.make_file_info(False, 'Script/cppnamelint.py'      , 'Script/Release'))
            self.file_list.append(self.make_file_info(True , 'Source/Test'                , 'Script/Release/Test'))
            if 'Windows' == platform.system():
                self.file_list.append(self.make_file_info(False, 'Script/TestWin32.cmd'   , 'Script/Release'))
            elif 'Linux' == platform.system():
                self.file_list.append(self.make_file_info(False, 'Script/TestLinux.sh'    , 'Script/Release'))
            elif 'Darwin' == platform.system():
                self.file_list.append(self.make_file_info(False, 'Script/TestLinux.sh'    , 'Script/Release'))
            else:
                assert (False)

    def make_file_info(self, is_dir, file_name, target_dir):
        json_obj_item = {'SourcePath' : os.path.join(self.root_path, file_name),
                         'TargetDir'  : os.path.join(self.root_path, target_dir),
                         'IsDir'      : is_dir}
        return json_obj_item


    def make(self, root_path, output_dir):
        if os.path.exists(output_dir) and os.path.isdir(output_dir):
            shutil.rmtree(output_dir)
            os.mkdir(output_dir)
        else:
            os.mkdir(output_dir)

        self.set_file_list(root_path)
        for item in self.file_list:
            src = os.path.abspath(item['SourcePath'])
            dst = os.path.abspath(item['TargetDir'])
            if item['IsDir']:
                shutil.copytree(src, dst)
            else:
                shutil.copy(src, dst)



def main():

    helper  = Helper()
    utility = Utility()    

    arguments = docopt(__doc__, version='cppnamelint')
    print("--includes=", arguments['--includes'])
    inc_dirs = ""
    if arguments['check']:
        src_dir = arguments['<srcdir>']
        cfg_file = arguments['<config>']

        if arguments['--includes']:
            inc_dirs = arguments['--includes']

        if os.path.exists(src_dir) and os.path.exists(cfg_file):
            # Remove previous .json file.
            utility.del_file(".", ".json")

            # Find all source code files.
            ext_name_list = [".c", ".cpp"]
            full_source_files = []
            utility.find_files(src_dir, ext_name_list, full_source_files)

            # Tick out any file in specific folder name, `Test`.
            # filtered_source_files = []

            # Run check for self source code files.
            for file_path in full_source_files:
                utility.run_file('cppnamelint', "check " + file_path + " --config=" +
                                 os.path.abspath(cfg_file) + " --includes=" + inc_dirs)

    elif arguments['test']:
        exe_file = utility.find_target_app('cppnamelint', '.')
        if '' == exe_file:
            exe_file = utility.find_target_app('cppnamelint', '..')
            if '' == exe_file:
                exe_file = utility.find_target_app('cppnamelint', '../Build')

        if not os.path.exists(exe_file):
            print('Failed to find executable binary file.')
        else:
            print('exe_file = ' + exe_file)

            # Remove previous .json file.
            utility.del_file(".", ".json")

            # Find all source code files.
            root_path = arguments['<srcdir>']
            ext_name_list = [".c", ".cpp"]
            full_source_files = []
            utility.find_files(root_path, ext_name_list, full_source_files)

            # Tick out any file in specific folder name, `Test`.
            filtered_source_files = []
            utility.exclude_folder(
                'Test', full_source_files, filtered_source_files)

            # Run check for self source code files.
            for file_path in filtered_source_files:
                if not os.path.basename(file_path).startswith("Test"):
                    utility.run_file(exe_file, "check " + file_path +
                                     " --config=" + os.path.abspath(arguments['<config>']))

    elif arguments['test-sample']:
        exe_file = utility.find_target_app('cppnamelint', '.')
        if '' == exe_file:
            exe_file = utility.find_target_app('cppnamelint', '..')
            if '' == exe_file:
                exe_file = utility.find_target_app('cppnamelint', '../Build')

        if not os.path.exists(exe_file):
            print('Failed to find executable binary file.')
        else:
            print('exe_file = ' + exe_file)
              
            path = os.path.abspath(arguments['<sampledir>'])
            
            json_list = []
            add2list_func  = json_list.append
            make_info_func = helper.make_test_info
            
            add2list_func(make_info_func(path, 'Sample_01.c',   'Sample_01.toml'))
            add2list_func(make_info_func(path, 'Sample_02.c',   'Sample_02.toml'))
            add2list_func(make_info_func(path, 'Sample_03.c',   'Sample_03.toml'))
            add2list_func(make_info_func(path, 'Sample_04.cpp', 'Sample_04.toml'))
            
            for item in json_list:
                test_argument_string = helper.make_test_argument_string(item)
                utility.run_file(exe_file, test_argument_string)

            # Run UnitTest.
            utility.run_file(exe_file, 'test --all')

    elif arguments['pack']:
        root_dir    = arguments['<rootdir>']
        output_dir  = arguments['<outputdir>']
        if not os.path.exists(root_dir):
            return

        packer = Packer()
        packer.make(root_dir, output_dir)

    return 0

if __name__ == '__main__':
    main()
