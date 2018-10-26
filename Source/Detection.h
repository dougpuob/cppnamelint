#include <map>
#include <string>
#include "Config.h"

using namespace std;

namespace namelint {
class Detection {
   private:
    bool captureLowerCasePrefix(string &Name);
    bool isUpperCamelCaseString(const string &Name, vector<string> IgnorePrefixs);
    bool isLowerCamelCaseString(const string &Name, vector<string> IgnorePrefixs);
    bool isLowerSeperatedString(const string &Name, vector<string> IgnorePrefixs);
    bool isHungarianNotationString(const string &Type, const string &Name, const vector<string> &IgnorePrefixs,
                                   const map<string, string> &MappedList);

   public:
    // bool SetRule(ConfigData& const CfgData);
    bool CheckFile(const RULETYPE Rule, const string &Name);
    bool CheckFunction(const RULETYPE Rule, const string &Name, const vector<string> &IgnorePrefixs);
    bool CheckVariable(const RULETYPE Rule, const string &Type, const string &Name, const vector<string> &IgnorePrefixs,
                       const map<string, string> &MappedList);
};
}  // namespace namelint