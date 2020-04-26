#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os

import unittest
import cppnamelint

from cppnamelintlib import Exec
from cppnamelintlib import File


class TestCppNameLint_Sample(unittest.TestCase):

    def setUp(self) -> None:
        file_obj = File()
        exe_name = file_obj.find_newest_exe(cppnamelint.define_exec_name, os.path.abspath('.'))
        if 0 == len(exe_name):
            exe_name = file_obj.find_newest_exe(cppnamelint.define_exec_name, os.path.abspath('..'))

        self.cppnamelint_exe_path = exe_name
        self.assertEqual(True, os.path.exists(self.cppnamelint_exe_path))


    def test_samples(self):
        found_sample_files: [] = cppnamelint.find_sample_files(cppnamelint.define_sample_dir)

        for item in found_sample_files:
            src_path = item['src']
            cfg_path = item['cfg']

            self.assertEqual(True, os.path.exists(src_path))
            self.assertEqual(True, os.path.exists(cfg_path))

            py_parser = cppnamelint.make_cmd_table()

            mock_py_args = ['check', src_path, '-cfg=' + cfg_path]
            py_args = py_parser.parse_args(mock_py_args)

            args_list: [] = cppnamelint.convert_py_args_to_exe_args(py_args)
            error_code, output_string = cppnamelint.run_util(self.cppnamelint_exe_path, args_list)

            self.assertEqual(True, 0 == error_code)
            self.assertEqual(True, '' != output_string)


if __name__ == '__main__':
    unittest.main()


