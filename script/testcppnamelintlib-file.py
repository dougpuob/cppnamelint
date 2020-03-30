#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import unittest
import platform


from cppnamelintlib import File


class TestCppNameLint_File(unittest.TestCase):

    def test_match_specific_name(self):

        file_obj = File()

        ext_names: [] = ['.exe', '.toml']
        func = file_obj.match_specific_name
        self.assertEqual(True, func('cppnamelint.exe', 'cppnamelint', ext_names))
        self.assertEqual(True, func('cppnamelint.toml', 'cppnamelint', ext_names))
        self.assertEqual(True, func('c:\\cppnamelint.toml', 'cppnamelint', ext_names))
        self.assertEqual(True, func('c:\\a\\cppnamelint.toml', 'cppnamelint', ext_names))
        self.assertEqual(True, func('c:/a/cppnamelint.toml', 'cppnamelint', ext_names))

        self.assertEqual(False, func('cppnamelint.lib', 'cppnamelint', ext_names))
        self.assertEqual(False, func('cppnamelint.txt', 'cppnamelint', ext_names))
        self.assertEqual(False, func('cppnamelint.exe.txt', 'cppnamelint', ext_names))


    def test_match_name_all(self):

        file_obj = File()

        ext_names: [] = ['.exe', '.toml']
        func = file_obj.match_name_all
        self.assertEqual(True, func('a.exe', ext_names))
        self.assertEqual(True, func('b.toml',  ext_names))
        self.assertEqual(True, func('c:\\d.toml',  ext_names))
        self.assertEqual(True, func('c:\\a\\d.toml', ext_names))
        self.assertEqual(True, func('/etc/d.toml', ext_names))

        self.assertEqual(False, func('a.lib', ext_names))
        self.assertEqual(False, func('a:\b.lib', ext_names))

if __name__ == '__main__':
    unittest.main()

