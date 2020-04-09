#!/usr/bin/python3
# -*- coding: UTF-8 -*-


import os
import re
import sys
import shutil
import argparse
import platform

from cppnamelintlib import Str
from cppnamelintlib import Exec
from cppnamelintlib import File
from cppnamelintlib import Lint
from cppnamelintlib import BuildType

define_cmd_check:str    = 'check'
define_cmd_test:str     = 'test'
define_cmd_format:str   = 'format'
define_cmd_chkenv:str   = 'chkenv'
define_cmd_bldgtest:str = 'bldgtest'
define_cmd_bldgpack:str = 'bldgpack'
define_cmd_bldgcfg:str  = 'bldgcfg'
define_cmd_bldgmake:str = 'bldgmake'

define_exec_name: str  = 'cppnamelint'
define_build_dir: str  = '../build'
define_sample_dir: str = '../source/test/sample'
define_cmake_name: str = 'cmake'
define_cmakelists: str = 'CMakeLists.txt'
define_cmake_msvc:str  = 'Visual Studio 15 2017'


def main(forced_argv):

    sys.argv = forced_argv

    parser = make_cmd_table()
    py_args = parser.parse_args()

    print(py_args)

    exec_file_path = get_newest_file_path(define_exec_name, '.')
    if '' == exec_file_path:
        target_exe_path = os.path.join(os.path.abspath('.'), define_build_dir)
        target_exe_path = os.path.normpath(target_exe_path)
        exec_file_path = get_newest_file_path(define_exec_name, target_exe_path)

    error_code = 0
    #--------------------------------------------------------------------------
    # python cppnamelint.py check command
    if py_args.input_cmd == define_cmd_check:
        print('Dispatched to `CHECK`')
        args_list :[] = convert_py_args_to_exe_args(py_args)
        error_code, output_texts = run_util(exec_file_path, args_list)
        print(output_texts)

    #--------------------------------------------------------------------------
    # python cppnamelint.py test command
    elif py_args.input_cmd == define_cmd_test:
        print('Dispatched to `TEST`')
        args_list: [] = convert_py_args_to_exe_args(py_args)
        error_code, output_texts = run_util(exec_file_path, args_list)
        print(output_texts)

    #--------------------------------------------------------------------------
    # python cppnamelint.py format command
    elif py_args.input_cmd == define_cmd_format:
        print('Dispatched to `FORMAT`')
        proj_dir_path = os.path.abspath(py_args.projdir)
        src_dir_path = os.path.abspath(py_args.srcdir)
        include_ext_name_list: [] = ['.c', '.cpp', '.h']
        error_code, output_texts = run_clang_format(proj_dir_path, src_dir_path, include_ext_name_list)
        print(output_texts)

    #--------------------------------------------------------------------------
    # python cppnamelint.py chkenv command
    elif py_args.input_cmd == define_cmd_chkenv:
        print('Dispatched to `CHKENV`')
        error_code_git   , output_git   = run_util('git',          ['--version'])
        error_code_cmake , output_cmake = run_util('cmake',        ['--version'])
        error_code_tidy  , output_tidy  = run_util('clang-tidy',   ['--version'])
        error_code_fmt   , output_fmt   = run_util('clang-format', ['--version'])

        str_obj = Str()
        output_git   = str_obj.remove_all_empty_line(output_git)
        output_cmake = str_obj.remove_all_empty_line(output_cmake)
        output_tidy  = str_obj.remove_all_empty_line(output_tidy)
        output_fmt   = str_obj.remove_all_empty_line(output_fmt)

        print('checking `cmake`        : (' + str(error_code_cmake) + ') ' + output_cmake)
        print('checking `git`          : (' + str(error_code_git)   + ') ' + output_git)
        print('checking `clang-tidy`   : (' + str(error_code_tidy)  + ') ' + output_tidy)
        print('checking `clang-format` : (' + str(error_code_fmt)   + ') ' + output_fmt)

        if platform.system() == 'Windows':
            error_code = error_code_git + error_code_cmake
        else:
            error_code = error_code_git + error_code_cmake + error_code_tidy + error_code_fmt

    #--------------------------------------------------------------------------
    # python cppnamelint.py bldgtest command
    elif py_args.input_cmd == define_cmd_bldgtest:
        print('Dispatched to `BLDGTEST`')
        found_sample_files: [] = find_sample_files(define_sample_dir)
        if (len(found_sample_files) == 0):
            found_sample_files: [] = find_sample_files('test/sample')
        error_code, output_texts = run_util_sample_files(exec_file_path, py_args, found_sample_files, True)

    #--------------------------------------------------------------------------
    # python cppnamelint.py bldgpack command
    elif py_args.input_cmd == define_cmd_bldgpack:
        print('Dispatched to `BLDGPACK`')
        root_dir:str    = os.path.abspath(py_args.root)
        build_dir: str  = os.path.abspath(py_args.build)
        output_dir:str  = os.path.abspath(py_args.output)
        error_code      = run_pack(define_exec_name, root_dir, build_dir, output_dir)

    #--------------------------------------------------------------------------
    # python cppnamelint.py bldgcfg command
    elif py_args.input_cmd == define_cmd_bldgcfg:
        print('Dispatched to `BLDGCFG`')
        root_dir:str    = os.path.abspath(py_args.root)
        output_dir:str  = os.path.abspath(py_args.output)

        if py_args.type.lower() == 'release':
            build_type:BuildType = BuildType.RELEASE
        elif py_args.type.lower() == 'debug':
            build_type: BuildType = BuildType.DEBUG
        else:
            build_type: BuildType = BuildType.RELEASE

        error_code, output_texts = run_cmake(root_dir, output_dir, build_type)
        print(output_texts)

    return error_code


def make_cmd_table():
    parser = argparse.ArgumentParser()

    parser.add_argument("-verbose"  ,  action="store_true"  , help="increase output verbosity")
    parser.add_argument("-dbg"      ,  action="store_true"  , help="enable debug mode output verbosity")
    parser.add_argument('-log'      ,  required=False       , help="log file path")

    subparsers = parser.add_subparsers(dest='input_cmd')

    cmd_check = subparsers.add_parser(define_cmd_check, help="check cmd")
    cmd_check.add_argument('src'    , help='Input source code file')
    cmd_check.add_argument('-cfg'   , required=False        , help="Config file path")
    cmd_check.add_argument('-json'  , required=False        , help="Json result output file path")
    cmd_check.add_argument('-inc'   , action='append'       , help='None or more include directory. (-inc Dir1 -inc Dir2 ...)', required=False)

    cmd_fmt = subparsers.add_parser(define_cmd_format, help="format cmd")
    cmd_fmt.add_argument('projdir'   , help='Project root directory(location of .clangformat).')
    cmd_fmt.add_argument('srcdir'    , help='Input source directory.')

    cmd_test = subparsers.add_parser(define_cmd_test, help="test cmd")
    cmdtest_grp = cmd_test.add_mutually_exclusive_group(required=False)
    cmdtest_grp.add_argument('-all' , action="store_true"   , help="run all tests")
    cmdtest_grp.add_argument('-ut'  , action="store_true"   , help="run unit test only")

    chk_env = subparsers.add_parser(define_cmd_chkenv, help="chkenv cmd for checking build environment")

    bldgtest = subparsers.add_parser(define_cmd_bldgtest, help="bldgtest cmd for building this project")
    bldgtest_grp = bldgtest.add_mutually_exclusive_group(required=False)
    bldgtest_grp.add_argument('-all', action="store_true"   , help="run all tests")
    bldgtest_grp.add_argument('-ut' , action="store_true"   , help="run unit test only")
    bldgtest_grp.add_argument('-it' , action="store_true"   , help="run integrated test only")

    bldgpack = subparsers.add_parser(define_cmd_bldgpack, help="bldgpack cmd for packing this project")
    bldgpack.add_argument('root'    , help='project root folder path')
    bldgpack.add_argument('build'   , help='Build directory.')
    bldgpack.add_argument('output'  , help='target released output folder path')

    bldgcfg = subparsers.add_parser(define_cmd_bldgcfg, help="bldgcfg cmd for doing config via Cmake")
    bldgcfg.add_argument('root'     , help='project root folder path')
    bldgcfg.add_argument('output'   , help='target build folder')
    bldgcfg.add_argument('type'     , help='build type(release|debug)')

    return parser


#==----------------------------------------------------------------------------
#
#==----------------------------------------------------------------------------
def convert_py_args_to_exe_args(py_args) -> str:

    common_args: str = ''

    if py_args.dbg:
        common_args = common_args + ' -dbg'

    if py_args.log:
        common_args = common_args + ' -logfile=' + py_args.log

    if py_args.verbose:
        common_args = common_args + ' -verbose'

    final_cmd_str: str = ''
    specific_cmd_args: str = ''
    if py_args.input_cmd == define_cmd_check:

        if py_args.src:
            specific_cmd_args = py_args.input_cmd + ' ' + py_args.src

        if py_args.cfg:
            specific_cmd_args = specific_cmd_args + ' -config ' + py_args.cfg

        if py_args.json:
            specific_cmd_args = specific_cmd_args + ' -jsonout ' + py_args.json

        if py_args.inc:
            for inc in py_args.inc:
                specific_cmd_args = specific_cmd_args + ' -include ' + inc

        final_cmd_str = specific_cmd_args + common_args

    # cppnamelint test
    elif py_args.input_cmd == define_cmd_test:

        if py_args.all:
            specific_cmd_args = specific_cmd_args + ' -all'

        if py_args.ut:
            specific_cmd_args = specific_cmd_args + ' -ut'

        final_cmd_str = define_cmd_test + specific_cmd_args + common_args

    # cppnamelint bldgtest
    elif py_args.input_cmd == define_cmd_bldgtest:

        if py_args.all:
            specific_cmd_args = specific_cmd_args + ' -all'

        if py_args.ut:
            specific_cmd_args = specific_cmd_args + ' -ut'

        if py_args.it:
            specific_cmd_args = specific_cmd_args + ' -it'

        final_cmd_str = define_cmd_bldgtest + specific_cmd_args + common_args

    # cppnamelint bldgpack
    elif py_args.input_cmd == define_cmd_bldgpack:
        final_cmd_str = common_args


    final_origin  = final_cmd_str.strip()
    final_cmd_str = final_origin.split(' ')
    return final_cmd_str


def find_sample_files(start_dir: str) -> []:
    paired_list = []

    include_src_files: [] = ['.c', '.cpp', '.h']
    include_cfg_files: [] = ['.toml']

    file_obj = File()
    found_src_files = file_obj.find_files(start_dir, '*', include_src_files)
    found_cfg_files = file_obj.find_files(start_dir, '*', include_cfg_files)

    for src in found_src_files:
        src_dir_name  = os.path.dirname(src)
        src_file_name = os.path.basename(src)
        src_ext_name  = ''
        for ext in include_src_files:
            if src_file_name.endswith(ext):
                src_ext_name = ext
                break

        cfg_file_name = os.path.join(src_dir_name, src_file_name.replace(src_ext_name, '.toml'))
        for cfg in found_cfg_files:
            if cfg == cfg_file_name:
                paired_list.append({'src': src,
                                    'cfg': cfg})
                break

    return paired_list


def get_newest_file_path(file_name:str, root_dir:str) ->str:
    file_obj = File()
    found = file_obj.find_newest_exe(file_name, root_dir)
    return found


def run_util(exec_name:str, arg_list:[], working_dir:str='') -> [int, str]:
    exec_obj = Exec()
    ret_code, output_text_list = exec_obj.run(exec_name, arg_list, working_dir)

    output_text = ''.join(output_text_list)
    return ret_code, output_text


def run_util_sample_files(exec_file_path, py_args, paired_samples:[], print_output:bool) -> int:
    first_error_code = 0

    sys.argv = ['prog', 'check', 'input.c', '-cfg=config.toml', '-json=output.json', '-inc=A', '-inc=B']
    parser = make_cmd_table()
    mock_py_args = parser.parse_args()

    full_output_string = ''

    for paired in paired_samples:

        mock_py_args.src = paired['src']
        mock_py_args.cfg = paired['cfg']

        args_list: [] = convert_py_args_to_exe_args(mock_py_args)
        print(args_list)
        error_code, output_string = run_util(exec_file_path, args_list)

        if first_error_code == 0 and error_code != 0:
            first_error_code = error_code

        if print_output:
            full_output_string = output_string
            print(output_string)

    return first_error_code, full_output_string


def run_pack(file_name:str, root_dir:str, build_dir:str, output_dir: str) -> int:

    root_dir   = os.path.abspath(root_dir)
    output_dir = os.path.abspath(output_dir)

    if not os.path.isdir(root_dir) and\
       not os.path.isdir(output_dir):
        return -1

    if output_dir == root_dir   or \
       output_dir == os.path.join(root_dir, '.git')   or \
       output_dir == os.path.join(root_dir, '.svn')   or \
       output_dir == os.path.join(root_dir, '.idea')  or \
       output_dir == os.path.join(root_dir, 'build')  or \
       output_dir == os.path.join(root_dir, 'doc')    or \
       output_dir == os.path.join(root_dir, 'submodule') or \
       output_dir == os.path.join(root_dir, 'script'):
        return -2

    file_obj = File()
    found_generated_binary = file_obj.find_newest_exe(file_name, build_dir)
    if '' == found_generated_binary:
        return -3

    if not os.path.exists(output_dir):
        os.mkdir(output_dir)

    selected_list = [
        {'platform': 'Shared',  'dir': True ,  'src': 'source/test'                        , 'dest': './test'},
        {'platform': 'Shared',  'dir': False,  'src': found_generated_binary               , 'dest': '.'},
        {'platform': 'Shared',  'dir': False,  'src': 'cppnamelint.toml'                   , 'dest': '.'},
        {'platform': 'Shared',  'dir': False,  'src': 'script/cppnamelint.py'              , 'dest': '.'},
        {'platform': 'Shared',  'dir': False,  'src': 'script/cppnamelintlib.py'           , 'dest': '.'},
        {'platform': 'Shared',  'dir': False,  'src': 'script/testcppnamelint.py'          , 'dest': '.'},
        {'platform': 'Shared',  'dir': False,  'src': 'script/testcppnamelint-main.py'     , 'dest': '.'},
        {'platform': 'Shared',  'dir': False,  'src': 'script/testcppnamelintlib.py'       , 'dest': '.'},
        {'platform': 'Shared',  'dir': False,  'src': 'script/testcppnamelintlib-file.py'  , 'dest': '.'},
        {'platform': 'Shared',  'dir': False,  'src': 'script/testcppnamelintlib-exec.py'  , 'dest': '.'},
        {'platform': 'Shared',  'dir': False,  'src': 'script/testcppnamelintlib-cmake.py' , 'dest': '.'},
        {'platform': 'Windows', 'dir': False , 'src': 'script/build-test-win32.ps1'        , 'dest': '.'},
        {'platform': 'Linux',   'dir': False , 'src': 'script/build-test-linux.sh'         , 'dest': '.'},
        {'platform': 'Darwin',  'dir': False , 'src': 'script/build-test-linux.sh'         , 'dest': '.'},
    ]

    for item in selected_list:
        if item['platform'] == 'Shared' or \
           item['platform'] == platform.system():

            if '' == item['src'] or '' == item['dest']:
                continue

            src = os.path.abspath(os.path.join(root_dir, item['src']))
            dst = os.path.abspath(os.path.join(output_dir, item['dest']))

            if not os.path.exists(src):
                continue

            if item['dir']:
                shutil.copytree(src, dst)
            else:
                shutil.copy(src, dst)

    return 0


def run_cmake(root_dir:str, output_dir: str, build_type:BuildType) -> int:
    error_code:int = 0

    if not os.path.exists(root_dir) or not os.path.exists(output_dir):
        return -1

    cmakelists_path = os.path.join(root_dir, define_cmakelists)
    if not os.path.exists(cmakelists_path):
        return -2

    build_type_str = ''
    if build_type == BuildType.RELEASE:
        build_type_str = 'Release'
    elif build_type == BuildType.DEBUG:
        build_type_str = 'Debug'
    else:
        build_type_str = 'Release'

    cmake_args: [] = [root_dir, '-DCMAKE_BUILD_TYPE='+build_type_str, '-B'+output_dir]
    if platform.system() == 'Windows':
        cmake_args.extend(['-G', define_cmake_msvc])

    error_code, output_texts = run_util(define_cmake_name, cmake_args)

    return error_code, output_texts



def run_clang_format(proj_dir: str, src_dir_path:str, ext_name_list: []):
    if not os.path.exists(src_dir_path):
        return -1

    lint_obj = Lint()
    file_obj = File()
    found_src_files = file_obj.find_files(src_dir_path, '*', ext_name_list)
    for path in found_src_files:
        print(path)
        error_code, output_texts = lint_obj.clang_format(path, proj_dir)
        if error_code != 0:
            break

    return error_code, output_texts

if __name__ == '__main__':
    ret_errcode = main(sys.argv)
    sys.exit(ret_errcode)

