

import os
import sys
import re
import unittest
import cppnamelint as cppnamelint
import unittest.mock as Mocker


class TestCppNameLint(unittest.TestCase):

    def test_main_cmd_pack(self):
        target_py_file    = ''
        target_cmd_name   = 'pack'
        target_cmd_param1 = os.path.abspath('..')
        target_cmd_param2 = os.path.abspath('./Release')
        sys.argv = [target_py_file, target_cmd_name , target_cmd_param1, target_cmd_param2]
        ret_code = cppnamelint.main()
        self.assertEqual(True, 0 == ret_code)

        return


if __name__ == '__main__':
    unittest.main()