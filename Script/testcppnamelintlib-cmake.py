#!/usr/bin/python3
# -*- coding: UTF-8 -*-


import unittest

from cppnamelintlib import Cmake
from cppnamelintlib import Exec
from cppnamelintlib import File


class TestCmake(unittest.TestCase):

    def test_run(self):
        cmake_obj = Cmake()
        error_code, output_message = cmake_obj.run('','')
        self.assertEqual(True, 0 != error_code)

if __name__ == '__main__':
    unittest.main()
