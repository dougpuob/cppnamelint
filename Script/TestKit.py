#!/usr/bin/python3

import os
import sys
import re
import platform

from subprocess import Popen, PIPE


class TestKit():
    def __init__(self):
        self.name = ""

    def run_file(self, exec_file_name, arguments):
        try:

            print(exec_file_name + " (" + arguments+ ")")

            cmd_and_arg = []
            cmd_and_arg.append(exec_file_name)
            new_args = arguments.split(' ')
            cmd_and_arg.extend(new_args)
            process = Popen(cmd_and_arg, stdin=PIPE, stdout=PIPE, stderr=PIPE)
            stdout, stderr = process.communicate()


            stdout_str = self.pipe_output(str(stdout))
            stderr_str = self.pipe_output(str(stderr))
            print("errocde  = " + str(process.returncode))
            print(stdout_str)
            print(stderr_str)

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
            if os.path.isfile(file_path) and file_path.find(exec_file_name) > -1:
                if 'nt' == os.name and file_path.endswith('.exe'):
                    output_file_list.append(file_path)
                elif 'posix' == os.name and os.access(file_path, os.X_OK):
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


def mg(path, src_name, cfg_name):
    argstr = 'check ' + os.path.join(path, src_name) + ' --config=' + os.path.join(path, cfg_name)
    return argstr


def main():

    testKit = TestKit()
    exe_file = testKit.find_target_app('cppnamelint', '../Build')


    if not os.path.exists(exe_file):
        print('Failed to find executable binary file.')
        return 1

    print('exe_file = ' + exe_file)   

    # Find all source code files.
    root_path = "../Source"
    ext_name_list = [".c", ".cpp"]
    full_source_files = []
    testKit.find_files(root_path, ext_name_list, full_source_files)

    # Tick out any file in specific folder name, `Test`.
    filtered_source_files = []
    testKit.exclude_folder('Test', full_source_files, filtered_source_files)


    # Run check for self source code files.
    for file_path in filtered_source_files:
        if not os.path.basename(file_path).startswith("Test"):
            testKit.run_file(exe_file, "check " + file_path + " --config=" + os.path.abspath("../Source/Config.toml"))


    path = os.path.abspath('../Source/Test/Sample')
    testKit.run_file(exe_file, mg(path, 'Sample_01.c',   'Sample_01.toml'))
    testKit.run_file(exe_file, mg(path, 'Sample_02.c',   'Sample_02.toml'))
    testKit.run_file(exe_file, mg(path, 'Sample_03.c',   'Sample_03.toml'))
    testKit.run_file(exe_file, mg(path, 'Sample_04.cpp', 'Sample_04.toml'))

    # Run UnitTest.
    testKit.run_file(exe_file, 'test --all')


if __name__ == '__main__':
    main()
