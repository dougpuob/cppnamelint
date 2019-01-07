# build-flow.py
"""Build-Flow.

Usage:
  BuildFlow.py lint         <DIR>
  BuildFlow.py lint-format  <DIR>
  BuildFlow.py lint-analyze <DIR>
  BuildFlow.py path         <DIR>
  BuildFlow.py proj-create  <PATH> <OUTPUT> [BUILD]
  BuildFlow.py proj-build   <PATH>
  BuildFlow.py unittest     [FUNC]
  BuildFlow.py (-h | --help)
  BuildFlow.py (-v | --version)

Options:
  -h --help     Show this screen.
  -v --version  Show version.

"""

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

    def get_devtls_path(self):
        target_path = os.environ['CRDSWDEVTLS']
        if target_path and os.path.exists(target_path):
            return True, target_path
        return False, ''

    def get_devtls_tool_path_list(self, devtls_path):
        if not os.path.exists(devtls_path):
            return []

        devtls_path = os.path.abspath(devtls_path)

        path_list = []
        if 'Windows' == platform.system():
            if os.path.exists(os.path.join(devtls_path, '@Win32')):
                path_list.append(os.path.join(devtls_path, '@Win32/tool/7zip/18.05'))
                path_list.append(os.path.join(devtls_path, '@Win32/tool/cmake/3.12.2'))
                path_list.append(os.path.join(devtls_path, '@Win32/tool/llvm/7.0.1'))
                path_list.append(os.path.join(devtls_path, '@Win32/tool/python/3.7'))
                path_list.append(os.path.join(devtls_path, '@Win32/tool/rclone/1.45'))

        elif 'Linux' == platform.system():
            if os.exists(os.path.join(devtls_path, '@Linux')):
                print('not implement')

        elif 'Darwin' == platform.system():
            if os.exists(os.path.join(devtls_path, '@MacOS')):
                print('not implement')

        else:
            path_list = []

        return path_list

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

                    index = 0
                    for item in new_str_lines:
                        if '' == item:
                            new_str_lines.pop(index)
                            index -= 1
                        index += 1

                    for new_str in new_str_lines:
                        output = output + new_str + "\n"
        return output

    def find_files(self, root_path, ext_name_list, output_dir_list):
        root_path = os.path.abspath(root_path)
        for dirName, subdirList, fileList in os.walk(root_path, topdown=False):
            for fname in fileList:
                for extname in ext_name_list:
                    if fname.endswith(extname):
                        abspath = os.path.join(root_path, dirName, fname)
                        normpath = os.path.normpath(abspath)
                        output_dir_list.append(normpath)
                        break

    def is_ascii_string(self, input_string):
        return all(ord(c) < 128 for c in input_string)


class Lint():
    def __init__(self):
        self.name = ""

    def get_devtls_path(self):
        build_flow_utility = Utility()
        crdswdevtls_path = build_flow_utility.get_devtls_tool_path_list(os.environ['CRDSWDEVTLS'])
        return crdswdevtls_path

    def code_reformat(self, file_path, test_mode=False):
        ret_value = True
        file_path = os.path.abspath(file_path)
        print(file_path)

        style_file    = "-style=file"
        style_llvm    = "-style=llvm"
        style_google  = "-style=google"
        style_mozilla = "-style=mozilla"
        style_jsonfmt = "-style=\"{BasedOnStyle: mozilla, IndentWidth: 8}" + "\""

        new_env = os.environ
        if test_mode:
            style_target = "-style=google" # For test
            crdswdevtls  = self.get_devtls_path()
            for item in crdswdevtls:
                new_env['PATH'] = new_env['PATH'] + ';' + item
        else:
            style_target = style_file

        try:
            process = Popen(["clang-format", "-i", style_target, file_path],
                            stdin=PIPE, stdout=PIPE, stderr=PIPE, env=new_env)
            stdout, stderr = process.communicate()

            if not test_mode:
                file = open("build-flow.log", 'a')

                stdout_str = str(stdout)
                if len(stdout_str) > 5:
                    file.write(stdout_str + '\n')

                stderr_str = str(stderr)
                if len(stderr_str) > 5:
                    file.write(stderr_str + '\n')

                file.close()
        except:
            ret_value = False
            print("An exception occurred")

        return ret_value


    def code_analyze(self, file_path, test_mode=False):
        print(file_path)

        new_env = os.environ
        if test_mode:
            crdswdevtls  = self.get_devtls_path()
            ret_value    = os.path.exists(crdswdevtls)
            new_env['PATH'] = new_env['PATH'] + ';' + crdswdevtls


        process = Popen(["clang-tidy",
                         "-checks=cert*",
                         "-enable-check-profile",
                         "-header-filter=^include",
                         file_path, "--"],
                        stdin=PIPE, stdout=PIPE, stderr=PIPE, env=new_env)

        # process = Popen(["clang-tidy", "-checks=cert-*", "-enable-check-profile", file_path, "--"]) #OK
        # process = Popen(["clang-tidy", "-checks=cert-*", "-enable-check-profile", "--",  "-header-filter" ,file_path])
        # process = Popen(["clang-tidy", "-enable-check-profile", file_path])

        stdout, stderr = process.communicate()

        #if not test_mode:
           # file = open("build-flow.log", 'a')
           # file.write("================================================================================\n")
           # file.write(file_path + '\n')
           # file.write("--------------------------------------------------------------------------------\n")
           #
           # pipe_output_str = reformat_pipe_output(stdout)
           # file.write(pipe_output_str)
           # file.write("--------------------------------------------------------------------------------\n")
           #
           # pipe_output_str = reformat_pipe_output(stderr)
           # file.write(pipe_output_str)
           # file.write("--------------------------------------------------------------------------------\n")
           #
           # file.close()
           

class Build():
    def __init__(self):
        self.name = ""
        
    def create(self, cmakefile_folder, output_folder, build_type):
        output_path = os.path.abspath(os.path.join(output_folder, sys.platform))
        input_path  = os.path.abspath(cmakefile_folder)
        print("Input  = " + input_path)
        print("Output = " + output_path)

        process = Popen(["cmake", input_path, "-B"+ output_path, "-DCMAKE_BUILD_TYPE="+build_type])
        stdout, stderr = process.communicate()


def main():
    arguments = docopt(__doc__, version='build-flow 0.1a')

    output_list = []
    accepted_extname_list = [".c", ".cc", ".cpp", ".h"]

    if os.path.exists("build-flow.log"):
        os.remove("build-flow.log")

    build_flow_lint    = Lint()
    build_flow_build   = Build()
    build_flow_utility = Utility()

    if arguments['lint']:
        input_folder = arguments['<DIR>']
        print("lint command with input folder ", input_folder)

        build_flow_utility.find_files(input_folder, accepted_extname_list, output_list)
        for file_path in output_list:
            build_flow_lint.code_reformat(file_path)

    elif arguments['lint-format']:
        input_folder = arguments['<DIR>']
        print("lint-format command with input folder ", input_folder)
        build_flow_utility.find_files(input_folder, accepted_extname_list, output_list)
        for file_path in output_list:
            build_flow_lint.code_reformat(file_path)
            
    elif arguments['lint-analyze']:
        input_folder = arguments['<DIR>']
        print("lint-analyze command with input folder ", input_folder)
        build_flow_utility.find_files(input_folder, accepted_extname_list, output_list)
        for file_path in output_list:
            build_flow_lint.code_analyze(file_path)

    elif arguments['path']:
        input_folder = arguments['<DIR>']
        print("path command with input folder ", input_folder)
        build_flow_utility.find_files(input_folder, accepted_extname_list, output_list)
        for file_path in output_list:
            if not build_flow_utility.is_ascii_string(file_path):
                print(file_path)

    elif arguments['proj-create']:
        input_target_path = arguments['<PATH>']
        input_output_path = arguments['<OUTPUT>']
        
        input_build_type  = 'Release'
        if arguments['BUILD']:
            if   'RELEASE' == arguments['BUILD'].upper():
                input_build_type  = 'Release'
            elif 'DEBUG' == arguments['BUILD'].upper():
                input_build_type  = 'Debug'
        
        print("proj-create command")
        print("<PATH>    = ", input_target_path)
        print("<OUTPUT>  = ", input_output_path)
        print("[BUILD]   = ", input_build_type)
        build_flow_build.create(input_target_path, input_output_path, input_build_type)
        
    elif arguments['proj-build']:
        input_target_path = arguments['<PATH>']
        print("proj-build command")
        print("<PATH>    = ", input_target_path)

    else:
        print(arguments)


if __name__ == '__main__':
    main()
