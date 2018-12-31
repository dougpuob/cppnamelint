#ifndef __NAMELINT_DETECTION__H__
#define __NAMELINT_DETECTION__H__

#include <map>
#include <string>
#include <vector>
#include "Config.h"

using namespace std;

namespace namelint {
class Detection {
   private:
    bool captureLowerCasePrefix(string &Name);
    bool isUpperCamelCaseString(const string &Name, vector<string> IgnorePrefixs);
    bool isLowerCamelCaseString(const string &Name, vector<string> IgnorePrefixs);
    bool isLowerSeperatedString(const string &Name, vector<string> IgnorePrefixs);
    bool isHungarianNotationString(const string &Type,
                                   const string &Name,
                                   const vector<string> &IgnorePrefixs,
                                   const map<string, string> &MappedList);
    size_t findHowManyChar(const string &InputStr, char cChar);

   public:
    bool CheckFile(const RULETYPE Rule, const string &Name);
    bool CheckFunction(const RULETYPE Rule,
                       const string &Name,
                       const vector<string> &IgnorePrefixs);
    bool CheckVariable(const RULETYPE Rule,
                       const string &Type,
                       const string &Name,
                       const vector<string> &IgnorePrefixs,
                       const map<string, string> &MappedList);
};
}  // namespace namelint

#endif