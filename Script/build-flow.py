# build-flow.py
"""Build-Flow.
Usage:
  build-flow.py lint  format   <folder>
  build-flow.py lint  analyze  <folder>
  build-flow.py check path     <folder>
  build-flow.py cmake create   <folder> <output>
  build-flow.py cmake build    <folder>
  build-flow.py (-h | --help)
  build-flow.py (-v | --version)

Options:
  -h --help     Show this screen.
  -v --version  Show version.
"""

import os
import sys
import re
from subprocess import Popen, PIPE

from docopt import docopt


def deep_explore_files(root_path, ext_name_list, output_dir_list):
    root_path = os.path.abspath(root_path)
    for dirName, subdirList, fileList in os.walk(root_path, topdown=False):
        for fname in fileList:
            for extname in ext_name_list:
                if fname.endswith(extname):
                    abspath = os.path.join(root_path, dirName, fname)
                    normpath = os.path.normpath(abspath)
                    output_dir_list.append(normpath)
                    break


def run_clang_format(file_path):
    print(file_path)

    style_file    = "-style=file"
    style_llvm    = "-style=llvm"
    style_google  = "-style=google"
    style_mozilla = "-style=mozilla"
    style_jsonfmt = "-style=\"{BasedOnStyle: mozilla, IndentWidth: 8}" + "\""

    process = Popen(["clang-format",
                     "-i",
                     style_file,
                     file_path], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    stdout, stderr = process.communicate()

    file = open("build-flow.log", 'a')

    stdout_str = str(stdout)
    if len(stdout_str) > 5:
        file.write(stdout_str + '\n')

    stderr_str = str(stderr)
    if len(stderr_str) > 5:
        file.write(stderr_str + '\n')

    file.close()


def run_clang_tidy(file_path):
    print(file_path)

    process = Popen(["clang-tidy",
                     "-checks=cert*",
                     "-enable-check-profile",
                     "-header-filter=^include",
                     file_path, "--"],
                    stdin=PIPE, stdout=PIPE, stderr=PIPE)

    # process = Popen(["clang-tidy", "-checks=cert-*", "-enable-check-profile", file_path, "--"]) #OK
    # process = Popen(["clang-tidy", "-checks=cert-*", "-enable-check-profile", "--",  "-header-filter" ,file_path])
    # process = Popen(["clang-tidy", "-enable-check-profile", file_path])

    stdout, stderr = process.communicate()

    file = open("build-flow.log", 'a')
    file.write(
        "================================================================================\n")
    file.write(file_path + '\n')
    file.write(
        "--------------------------------------------------------------------------------\n")

    if str(stdout) != "None":
        new_str_lines = str(stdout).split("\\r\\n")
        for new_str in new_str_lines:
            file.write(new_str+"\n")

    if str(stderr) != "None":
        new_str_lines = str(stderr).split("\\r\\n")
        for new_str in new_str_lines:
            file.write(new_str+"\n")

    file.close()


def run_cmake_create(cmakefile_folder, output_folder):
    output_path = os.path.abspath(os.path.join(output_folder, sys.platform))
    input_path  = os.path.abspath(cmakefile_folder)
    print("Input  = " + input_path)
    print("Output = " + output_path)

    process = Popen(["cmake", input_path, "-B"+ output_path , "-DCMAKE_BUILD_TYPE=Release"])
    stdout, stderr = process.communicate()


def run_cmake_build(folder_path):
    print(folder_path)

    process = Popen(["cmake", folder_path])
    stdout, stderr = process.communicate()


def IsAsciiString(input_string, is_err_print):
    regex = re.compile(r'[a-zA-Z0-9\\\/.\-:_\[\]~$\(\)@!#&+%&-+=]*')
    match = regex.search(input_string)
    result = input_string == match.group()
    if is_err_print and result:
        print(input_string)
    return result


def main():
    arguments = docopt(__doc__, version='build-flow 0.1a')

    output_list = []
    accepted_extname_list = [".c", ".cc", ".cpp", ".h"]

    if os.path.exists("build-flow.log"):
        os.remove("build-flow.log")

    if arguments['lint'] and arguments['format']:
        input_folder = os.path.abspath(arguments['<folder>'])
        print("lint command with input folder ", input_folder)
        deep_explore_files(input_folder, accepted_extname_list, output_list)
        for file_path in output_list:
            run_clang_format(file_path)

    elif arguments['lint'] and arguments['analyze']:
        input_folder = os.path.abspath(arguments['<folder>'])
        print("check command with input folder ", input_folder)
        deep_explore_files(input_folder, accepted_extname_list, output_list)
        for file_path in output_list:
            run_clang_tidy(file_path)

    elif arguments['check'] and arguments['path']:
        input_folder = os.path.abspath(arguments['<folder>'])
        print("path command with input folder ", input_folder)
        deep_explore_files(input_folder, accepted_extname_list, output_list)
        for file_path in output_list:
            IsAsciiString(file_path, is_err_print=True)

    elif arguments['cmake'] and arguments['create']:
        input_folder  = os.path.abspath(arguments['<folder>'])
        output_folder = os.path.abspath(arguments['<output>'])
        print("cmake command to create makefile via CMakeLists.txt ", input_folder)
        run_cmake_create(input_folder, output_folder)

    elif arguments['cmake'] and arguments['build']:
        input_folder = os.path.abspath(arguments['<folder>'])
        print("cmake command to build project", input_folder)
        run_cmake_build(input_folder)

    else:
        print(arguments)


if __name__ == '__main__':
    main()
