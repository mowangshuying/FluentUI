#include <iostream>
#include <syscmdline/parser.h>
using namespace SysCmdLine;
int main(int argc, char *argv[]) {
    Command cmd("mv", "move files to directory");
    cmd.addArguments({
        Argument("files", "Source files").multi(),
        Argument("dir", "Destination directory"),
    });
    cmd.addHelpOption();
    cmd.setHandler([](const ParseResult &result) -> int {
        std::cout << "[Sources]" << std::endl;
        for (const auto &item : result.values("files")) {
            std::cout << item.toString() << std::endl;
        }
        std::cout << "[Destination]" << std::endl;
        std::cout << result.value("dir").toString() << std::endl;
        return 0;
    });

    Parser parser(cmd);
    parser.setDisplayOptions(Parser::ShowOptionsHintFront);
    return parser.invoke(argc, argv);
}