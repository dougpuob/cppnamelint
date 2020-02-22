#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import unittest
import platform

from cppnamelintlib import Cmake
from cppnamelintlib import Exec
from cppnamelintlib import File


class TestCppNameLint_Exec(unittest.TestCase):

    def test_run(self):
        
        exec_obj = Exec()

        output_text:str = ''
        if platform.system() == 'Windows':
            error_code, output_text = exec_obj.run('whoami', ['/?'])
            self.assertEqual(True, 0 == error_code)
            self.assertEqual(True, '' != output_text)
        # elif platform.platform() == 'Linux':
        # elif platform.platform() == 'Darwin':

        if platform.system() == 'Windows':
            found_index = output_text.find('Examples:')
            found_index = output_text.find('WHOAMI /USER /GROUPS /CLAIMS /PRIV')
            self.assertEqual(True, found_index >= 0)
        # elif platform.platform() == 'Linux':
        # elif platform.platform() == 'Darwin':
        
        

if __name__ == '__main__':
    unittest.main()

