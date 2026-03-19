#include <syscmdline/parser.h>
#include <syscmdline/system.h>

using namespace SysCmdLine;

int main(int /* argc */, char * /* argv */[]) {
    Option linkDirOption({"-L", "--linkdir"}, "Add link directory");
    linkDirOption.setShortMatchRule(Option::ShortMatchSingleChar);
    linkDirOption.addArgument(Argument("dir"));
    linkDirOption.setUnlimitedOccurrence();

    Option includeDirOption({"-I", "--includedir"}, "Add include directory");
    includeDirOption.setShortMatchRule(Option::ShortMatchSingleChar);
    includeDirOption.addArgument(Argument("dir"));
    includeDirOption.setUnlimitedOccurrence();

    Command rootCommand("gcc", "GNU C/C++ Compiler");
    rootCommand.addOptions({
        linkDirOption,
        includeDirOption,
    });
    rootCommand.addVersionOption("0.0.0.1");
    rootCommand.addHelpOption(true, true);
    rootCommand.setHandler([](const ParseResult &result) {
        u8info("Link directories:\n");
        for (const auto &item : result.option("-L").allValues())
            u8info("    %s\n", item.toString().data());
        u8info("Include directories:\n");
        for (const auto &item : result.option("-I").allValues())
            u8info("    %s\n", item.toString().data());
        return 0;
    });

    Parser parser(rootCommand);
    return parser.invoke(commandLineArguments());
}