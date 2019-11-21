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

from docopt import docopt
from cppnamelintlib import Utility
from cppnamelintlib import Helper
from cppnamelintlib import Packer


def main():
    err_code_ok = 0
    err_code_failed = 1
    err_code_invalid_input = 2
    err_code_file_not_found = 3

    ret_err_code = err_code_ok

    helper = Helper()
    utility = Utility()

    arguments = docopt(__doc__, version='cppnamelint')
    print("--includes=", arguments['--includes'])
    inc_dirs = ""

    def get_exe_file():
        exe_file_path = ''
        if os.path.exists('../Build'):
            exe_file_path = utility.find_target_app('cppnamelint', '../Build')

        if '' == exe_file_path:
            exe_file_path = utility.find_target_app('cppnamelint', '.')
            if '' == exe_file_path:
                exe_file_path = utility.find_target_app('cppnamelint', '..')
        return exe_file_path

    if arguments['check']:
        src_dir = arguments['<srcdir>']
        cfg_file = arguments['<config>']

        print('src_dir   = ' + src_dir)
        print('cfg_file  = ' + cfg_file)

        if arguments['--includes']:
            inc_dirs = arguments['--includes']

        if not os.path.exists(src_dir) or not os.path.exists(cfg_file):
            ret_err_code = err_code_invalid_input

        exe_file = get_exe_file()
        if not os.path.exists(exe_file):
            ret_err_code = err_code_file_not_found

        if ret_err_code == err_code_ok:
            # Remove previous .json file.
            utility.del_file(".", ".json")

            full_source_files = []
            if os.path.isdir(src_dir):
                # Find all source code files.
                ext_name_list = [".c", ".cpp"]
                utility.find_files(src_dir, ext_name_list, full_source_files)
            else:
                full_source_files.append(src_dir)

            # Run check for self source code files.
            for file_path in full_source_files:
                utility.run_file(exe_file, "check " + os.path.abspath(file_path) + " --config=" +
                                 os.path.abspath(cfg_file) + " --includes=" + inc_dirs)

    elif arguments['test']:
        exe_file = get_exe_file()

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
        exe_file = get_exe_file()

        if not os.path.exists(exe_file):
            print('Failed to find executable binary file.')
        else:
            print('exe_file = ' + exe_file)

            path = os.path.abspath(arguments['<sampledir>'])

            json_list = []
            add2list_func = json_list.append
            make_info_func = helper.make_test_info

            add2list_func(make_info_func(path, 'Sample01UpperCamel.c', 'Sample01UpperCamel.toml'))
            add2list_func(make_info_func(path, 'Sample02_UpperCamel.c', 'Sample02_UpperCamel.toml'))
            add2list_func(make_info_func(path, 'sample03_lower_snake.c', 'sample03_lower_snake.toml'))
            add2list_func(make_info_func(path, 'sample04_lower_snake.cpp', 'sample04_lower_snake.toml'))
            add2list_func(make_info_func(path, 'sample05HungarianNotation.cpp', 'sample05HungarianNotation.toml'))
            add2list_func(make_info_func(path, 'Sample06LowerCamel.cpp', 'Sample06LowerCamel.toml'))

            for item in json_list:
                test_argument_string = helper.make_test_argument_string(item)
                utility.run_file(exe_file, test_argument_string)

            # Run UnitTest.
            utility.run_file(exe_file, 'test --all')

    elif arguments['pack']:
        root_dir = arguments['<rootdir>']
        output_dir = arguments['<outputdir>']
        if not os.path.exists(root_dir):
            return

        packer = Packer()
        packer.make(root_dir, output_dir)

    return ret_err_code


if __name__ == '__main__':
    main()
