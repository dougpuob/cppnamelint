#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import unittest
import cppnamelint


class TestCppNameLint(unittest.TestCase):

    def test_convert_py_args_to_exe_args_sample_check(self):
        # [sample for check]
        # cppnamelint.py -log=MyLog.log -dbg check MySource.c -cfg=MyConfig.toml -json=MyJson.json
        mock_argv = ['-log=MyLog.log', '-dbg', 'check' , 'MySource.c', '-cfg=MyConfig.toml', '-json=MyJson.json', '-inc=<MyDir1:MyDir2:MyDir3>']
        py_parser = cppnamelint.make_cmd_table()
        py_args = py_parser.parse_args(mock_argv)

        args_list: [] = cppnamelint.convert_py_args_to_exe_args(py_args)
        self.assertEqual(True, len(mock_argv) == len(args_list))
        self.assertEqual(args_list[0], 'check')
        self.assertEqual(args_list[1], 'MySource.c')
        self.assertEqual(args_list[2], '--config=MyConfig.toml')
        self.assertEqual(args_list[3], '--jsonout=MyJson.json')
        self.assertEqual(args_list[4], '--includes=<MyDir1:MyDir2:MyDir3>')
        self.assertEqual(args_list[5], '--dbg')
        self.assertEqual(args_list[6], '--logfile=MyLog.log')

        return

    def test_convert_py_args_to_exe_args_test(self):
        # [sample for `test`]
        # cppnamelint.py -log=MyLog.log -dbg test -all
        mock_argv = ['-log=MyLog.log', '-dbg', 'test' , '-all']
        py_parser = cppnamelint.make_cmd_table()
        py_args = py_parser.parse_args(mock_argv)

        args_list: [] = cppnamelint.convert_py_args_to_exe_args(py_args)
        self.assertEqual(True, len(mock_argv) == len(args_list))
        self.assertEqual(args_list[0], 'test')
        self.assertEqual(args_list[1], '--all')
        self.assertEqual(args_list[2], '--dbg')
        self.assertEqual(args_list[3], '--logfile=MyLog.log')

        return


if __name__ == '__main__':
    unittest.main()


