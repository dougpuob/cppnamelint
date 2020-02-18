import os
import re
import sys
import copy
import shutil
import argparse
import platform

from cppnamelintlib import Exec
from cppnamelintlib import File

define_cmd_check: str    = 'check'
define_cmd_test: str     = 'test'
define_cmd_bldgtest: str = 'bldgtest'
define_cmd_bldgpack: str = 'bldgpack'

define_exec_name: str  = 'cppnamelint'
define_build_dir: str  = '../Build'
define_sample_dir: str = '../Source/Test/Sample'

def main():
    parser = make_cmd_table()
    py_args = parser.parse_args()
    print(py_args)

    target_exe_path = os.path.join(os.path.abspath('.'), define_build_dir)
    exec_file_path = get_newest_file_path(define_exec_name, target_exe_path)
    if not os.path.exists(exec_file_path):
        print('Failed to find utility executable binary file.')
        print('exec_file_path=' + exec_file_path)
        return  -1


    error_code = 0
    #--------------------------------------------------------------------------
    if py_args.input_cmd == define_cmd_check:
        args_list :[] = convert_py_args_to_exe_args(py_args)
        error_code, output_texts = run_util(exec_file_path, args_list)
        print(output_texts)

    #--------------------------------------------------------------------------
    elif py_args.input_cmd == define_cmd_test:
        args_list :[] = convert_py_args_to_exe_args(py_args)
        error_code, output_texts = run_util(exec_file_path, args_list)
        print(output_texts)

    #--------------------------------------------------------------------------
    elif py_args.input_cmd == define_cmd_bldgtest:
        found_sample_files : [] = find_sample_files(define_sample_dir)
        error_code, output_texts = run_util_sample_files(exec_file_path, py_args, found_sample_files, True)

    #--------------------------------------------------------------------------
    elif py_args.input_cmd == define_cmd_bldgpack:
        root_dir:str = os.path.abspath('..')
        rel_dir:str  = os.path.join(os.path.abspath('.'), 'released')
        error_code   = run_pack(exec_file_path, root_dir, rel_dir)

    return error_code


def make_cmd_table():
    parser = argparse.ArgumentParser()

    parser.add_argument("-verbose" ,  action="store_true", help="increase output verbosity")
    parser.add_argument("-dbg"     ,  action="store_true", help="enable debug mode output verbosity")
    parser.add_argument('-log'     ,  required=False     , help="log file path")

    subparsers = parser.add_subparsers(dest='input_cmd')

    subparser1 = subparsers.add_parser(define_cmd_check, help="check cmd")
    subparser1.add_argument('src', help='Input source code file')
    subparser1.add_argument('-cfg'  , required=False,  help="Config file path")
    subparser1.add_argument('-json' , required=False,  help="Json result output file path")
    subparser1.add_argument('-inc'  , required=False,  help="<dir1:dir2:...>")

    subparser2 = subparsers.add_parser(define_cmd_test, help="test cmd")
    mutualgroup = subparser2.add_mutually_exclusive_group(required=False)
    mutualgroup.add_argument('-all'  , action="store_true",  help="run all tests")
    mutualgroup.add_argument('-ut'   , action="store_true",  help="run unit test only")

    subparser3 = subparsers.add_parser(define_cmd_bldgtest, help="test cmd for building this project")
    mutualgroup = subparser3.add_mutually_exclusive_group(required=False)
    mutualgroup.add_argument('-all', action="store_true", help="run all tests")
    mutualgroup.add_argument('-ut', action="store_true",  help="run unit test only")
    mutualgroup.add_argument('-it', action="store_true",  help="run integrated test only")

    subparser4 = subparsers.add_parser(define_cmd_bldgpack, help="test cmd for packing this project")
    subparser4.add_argument('dir', help='target output folder')

    return parser

#==----------------------------------------------------------------------------
# Command functions
#==----------------------------------------------------------------------------
def cmd_check():
    error_code : int = 0
    return error_code

def cmd_test():
    error_code : int = 0
    return error_code

def cmd_pack():
    error_code : int = 0
    return error_code


#==----------------------------------------------------------------------------
#
#==----------------------------------------------------------------------------
def convert_py_args_to_exe_args(py_args) -> str:

    common_args: str = ''

    #if -1 == py_args_text.find('dbg='):
    if py_args.dbg:
        common_args = common_args + ' --dbg'

    #if -1 == py_args_text.find('log='):
    if py_args.log:
        common_args = common_args + ' --logfile=' + py_args.log

    #if -1 == py_args_text.find('verbose='):
    if py_args.verbose:
        common_args = common_args + ' --verbose'

    final_cmd_str: str = ''
    specific_cmd_args: str = ''
    if py_args.input_cmd == define_cmd_check:

        if py_args.inc:
            regex = re.compile(r'<(\S+)>')
            matched = regex.search(py_args.inc)
            matched_target = matched.group(1)
            input_inc_list = matched_target.split(':')

        if py_args.src:
            specific_cmd_args = py_args.input_cmd + ' ' + py_args.src

        if py_args.cfg:
            specific_cmd_args = specific_cmd_args + ' --config=' + py_args.cfg

        if py_args.json:
            specific_cmd_args = specific_cmd_args + ' --jsonout=' + py_args.json

        if py_args.inc:
            if len(py_args.inc) > 0:
                specific_cmd_args = specific_cmd_args + ' --includes=' + '<' + ':'.join(input_inc_list) + '>'

        final_cmd_str = specific_cmd_args + common_args

    # cppnamelint test
    elif py_args.input_cmd == define_cmd_test:

        if py_args.all:
            specific_cmd_args = specific_cmd_args + ' --all'

        if py_args.ut:
            specific_cmd_args = specific_cmd_args + ' --ut'

        final_cmd_str = define_cmd_test + specific_cmd_args + common_args

    # cppnamelint bldgtest
    elif py_args.input_cmd == define_cmd_bldgtest:

        if py_args.all:
            specific_cmd_args = specific_cmd_args + ' --all'

        if py_args.ut:
            specific_cmd_args = specific_cmd_args + ' --ut'

        if py_args.it:
            specific_cmd_args = specific_cmd_args + ' --it'

        final_cmd_str = define_cmd_bldgtest + specific_cmd_args + common_args

    # cppnamelint bldgpack
    elif py_args.input_cmd == define_cmd_bldgpack:
        final_cmd_str = common_args


    final_origin  = final_cmd_str.strip()
    final_cmd_str = final_origin.split(' ')
    return final_cmd_str


def find_sample_files(start_dir: str) -> []:
    paired_list = []

    include_src_files: [] = ['.c', '.cpp']
    include_cfg_files: [] = ['.toml']

    file_obj = File()
    found_src_files = file_obj.find_files(start_dir, include_src_files)
    found_cfg_files = file_obj.find_files(start_dir, include_cfg_files)

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
    print('ExeName    = ', exec_name)
    print('ArgList    = ', arg_list)
    print('WorkingDir = ', working_dir)

    exec_obj = Exec()
    ret_code, output_text_list = exec_obj.run(exec_name, arg_list, working_dir)

    output_text = ''.join(output_text_list)
    return ret_code, output_text


def run_util_sample_files(exec_file_path, py_args, paired_samples:[], print_output:bool) -> int:
    first_error_code = 0

    mock_py_args = copy.copy(py_args)
    mock_py_args.input_cmd = define_cmd_check

    full_output_string = ''

    for paired in paired_samples:

        mock_py_args.src = paired['src']
        mock_py_args.cfg = paired['cfg']

        args_list: [] = convert_py_args_to_exe_args(mock_py_args)
        error_code, output_string = run_util(exec_file_path, args_list)

        if first_error_code == 0 and error_code != 0:
            first_error_code = error_code

        if print_output:
            full_output_string = full_output_string + '\n' + output_string
            print(output_string)

    return first_error_code, full_output_string


def run_pack(file_name:str, root_dir:str, output_dir: str) -> int:

    if os.path.exists(output_dir) and os.path.isdir(output_dir):
        shutil.rmtree(output_dir)
        os.mkdir(output_dir)
    else:
        os.mkdir(output_dir)

    file_obj = File()
    found = file_obj.find_newest_exe(file_name, root_dir)


    selected_list = [
        {'platform': 'Shared'   , 'dir': True  , 'src': 'Source/Test'          , 'dest': 'script/released/test'},
        {'platform': 'Shared'   , 'dir': False , 'src': 'Script/*.py'          , 'dest': 'script/released'},
        {'platform': 'Shared'   , 'dir': False , 'src': 'Source/*.toml'        , 'dest': 'script/released'},
        {'platform': 'Windows'  , 'dir': False , 'src': 'Script/TestWin32.cmd' , 'dest': 'script/released'},
        {'platform': 'Linux'    , 'dir': False , 'src': 'Script/TestLinux.sh'  , 'dest': 'script/released'},
        {'platform': 'Darwin'   , 'dir': False , 'src': 'Script/TestLinux.sh'  , 'dest': 'script/released'},
    ]

    for item in selected_list:
        if item['platform'] == 'Shared' or \
           item['platform'] == os.system():
            src = os.path.abspath(item['src'])
            dst = os.path.abspath(item['dest'])
            if item['dir']:
                shutil.copytree(src, dst)
            else:
                shutil.copy(src, dst)

    return 0


if __name__ == '__main__':
    ret_errcode = main()
    sys.exit(ret_errcode)

