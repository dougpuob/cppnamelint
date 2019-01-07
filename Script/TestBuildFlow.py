

import os
import sys
import re
import unittest
import BuildFlow as BuildFlow
import unittest.mock as Mocker


class TestBuildFlow_Utility(unittest.TestCase):

    def test_is_ascii_string__good_cases(self):
        build_flow_utility = BuildFlow.Utility()
        self.assertEqual(True, build_flow_utility.is_ascii_string("this is an ascii string"))
        self.assertEqual(True, build_flow_utility.is_ascii_string("~!@#$%^&*()_+\\/><][{}\'\"\`"))
        self.assertEqual(True, build_flow_utility.is_ascii_string("123456789"))
        self.assertEqual(True, build_flow_utility.is_ascii_string("C:\\TestForWindowsPath"))
        self.assertEqual(True, build_flow_utility.is_ascii_string("C:\\TestFor Windows Path With Spaces"))

    def test_is_ascii_string__bad_cases(self):
        build_flow_utility = BuildFlow.Utility()
        self.assertEqual(False, build_flow_utility.is_ascii_string("中文是不可以的"))

    def test_find_files(self):
        #output_file_list   = []
        #include_ext_names  = ['.c', '.h']

        #build_flow_utility = BuildFlow.Utility()
        #build_flow_utility.find_files('.', include_ext_names, output_file_list)
        #os.walk = keeper

        #print(output_file_list)
        #self.assertEqual(True, 2 == len(output_file_list))
        #self.assertEqual(True, 'c:\\src\\abc.c' == output_file_list[0])
        #self.assertEqual(True, 'c:\\src\\abc.h' == output_file_list[1])
        return



class TestBuildFlow_Lint(unittest.TestCase):

    def test_code_reformat(self):
        sample_code = """
        void main() {
            return 0;
        }
        
        """
        text_file = open("sample_code.c", "w")
        text_file.write(sample_code)
        text_file.close()


        build_flow_lint = BuildFlow.Lint()
        build_flow_lint.code_reformat("sample_code.c", test_mode=True)

        if os.path.exists("sample_code.c"):
            os.unlink("sample_code.c")

        return

if __name__ == '__main__':
    unittest.main()