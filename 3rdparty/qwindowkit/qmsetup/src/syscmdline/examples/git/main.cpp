#include <syscmdline/parser.h>
#include <syscmdline/system.h>

using namespace SysCmdLine;

int main(int /* argc */, char * /* argv */[]) {
    Command cloneCommand("clone", "Clone a repository into a new directory");
    Command initCommand("init", "Create an empty Git repository or reinitialize an existing one");

    Command commitCommand("commit", "Record changes to the repository");
    Command mergeCommand("merge", "Join two or more development histories together");
    Command rebaseCommand("rebase", "Reapply commits on top of another base tip");

    Command rootCommand("git", "Git is a distributed version control system.");
    rootCommand.addCommands({
        cloneCommand,
        initCommand,
        commitCommand,
        mergeCommand,
        rebaseCommand,
    });
    rootCommand.addVersionOption("0.0.0.1");
    rootCommand.addHelpOption(true, true);
    rootCommand.setHandler([](const ParseResult &result) {
        u8info("%s\n", result.value("weekday").toString().data());
        u8info("%s\n", result.value("event").toString().data());
        return 0;
    });

    CommandCatalogue cc;
    cc.addCommands("start a working area", {"clone", "init"});
    cc.addCommands("grow, mark and tweak your common history", {"commit", "merge", "rebase"});
    rootCommand.setCatalogue(cc);

    Parser parser(rootCommand);
    parser.setDisplayOptions(Parser::ShowArgumentDefaultValue | Parser::ShowArgumentExpectedValues |
                             Parser::DontShowHelpOnError | Parser::AlignAllCatalogues);
    return parser.invoke(SysCmdLine::commandLineArguments());
}