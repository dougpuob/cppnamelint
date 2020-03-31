#include <clang/Tooling/CommonOptionsParser.h>
#include <llvm/Support/CommandLine.h>

using namespace llvm;
using namespace std;

static cl::OptionCategory CppNameLintCategory("CppNameLint options");

//==-----------------------------------------------------------------------
// Generic options
//==-----------------------------------------------------------------------
static cl::opt<string> LogFile("logfile", cl::desc("Print log message to the specific a log file."),
                               cl::value_desc("LogName"), cl::Optional,
                               cl::cat(CppNameLintCategory), cl::sub(*cl::AllSubCommands));

//==-----------------------------------------------------------------------
// SubCommand: check
//==-----------------------------------------------------------------------
static cl::SubCommand CheckSubcommand("check", "Check source with naming rules.");

static cl::opt<string> CheckInputSrc(cl::Positional, cl::desc("<input file>"), cl::Required,
                                     cl::sub(CheckSubcommand));

static cl::opt<string> CheckInputConfig("config", cl::desc("Specific your config file(.toml)."),
                                        cl::value_desc("FileName"), cl::cat(CppNameLintCategory),
                                        cl::sub(CheckSubcommand));

static cl::opt<string> CheckOutputJson("jsonout", cl::desc("Generate result to a JSON file."),
                                       cl::value_desc("FileName"), cl::cat(CppNameLintCategory),
                                       cl::sub(CheckSubcommand));

static cl::list<string> CheckIncludes("include", cl::desc("Specific header folers."),
                                      cl::value_desc("-include Dir1 -include Dir2 ..."),
                                      cl::ZeroOrMore, cl::cat(CppNameLintCategory),
                                      cl::sub(CheckSubcommand));

//==-----------------------------------------------------------------------
// SubCommand: test
//==-----------------------------------------------------------------------
static cl::SubCommand TestSubcommand("test", "Run tests.");

static cl::opt<bool> AllTest("all", cl::desc("Run all tests."), cl::cat(CppNameLintCategory),
                             cl::sub(TestSubcommand));

static cl::opt<string> UnitTest("ut", cl::desc("Run unit tests or a specifc case."),
                                cl::value_desc("unit test case name"), cl::cat(CppNameLintCategory),
                                cl::sub(TestSubcommand));

//==-----------------------------------------------------------------------
// SubCommand: DumpCfg
//==-----------------------------------------------------------------------
static cl::SubCommand DumpConfigSubcommand("dump", "Dump default config file. (TODO)");
