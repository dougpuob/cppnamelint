#include "ParseAST.h"
#include "Config.h"
#include "Detection.h"

#include <gtest/gtest.h>

using namespace namelint;

static cl::OptionCategory MyToolCategory("ClangAutoStats" /*My tool options*/);
int main(int argc, const char **argv)
{
    Config Config;
    // Config.Load("C:/working-folder/Namelint/cpp-namelint.git/Source/Config.toml");
    // const ConfigData &CfgData = Config.GetData();

    CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    Tool.setDiagnosticConsumer(new MyIgnoringDiagConsumer());

    MyFactory myFactory;
    std::unique_ptr<FrontendActionFactory> factory = newFrontendActionFactory(&myFactory);

    Tool.run(factory.get());

    ::testing::InitGoogleTest(&argc, (char **)argv);
    return RUN_ALL_TESTS();

    return 0;
}
