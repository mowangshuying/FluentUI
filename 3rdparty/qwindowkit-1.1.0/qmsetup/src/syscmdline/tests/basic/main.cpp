#include <iostream>
#include <cassert>

#include <syscmdline/parser.h>
#include <syscmdline/system.h>

using namespace SysCmdLine;

int main(int argc, char *argv[]) {
    SYSCMDLINE_UNUSED(argc);
    SYSCMDLINE_UNUSED(argv);

    {
        std::cout << "[Test Simple]" << std::endl;

        Command cmd("cmd");
        cmd.addArguments({
            {"arg1"},
            {"arg2"},
        });

        {
            Parser parser(cmd);
            ParseResult res = parser.parse({"cmd", "1"});
            assert(res.error() == ParseResult::MissingCommandArgument);
        }
        std::cout << "Missing argument: OK" << std::endl;

        {
            Parser parser(cmd);
            ParseResult res = parser.parse({"cmd", "1", "2", "3"});
            assert(res.error() == ParseResult::TooManyArguments);
        }
        std::cout << "Too many argument: OK" << std::endl;

        {
            Parser parser(cmd);
            ParseResult res = parser.parse({"cmd", "1", "2"});
            assert(res.error() == ParseResult::NoError);
            assert(res.value("arg1") == "1");
            assert(res.value("arg2") == "2");
        }
        std::cout << "Get positional arguments: OK" << std::endl;
    }
    std::cout << std::endl;

    {
        std::cout << "[Test Special Argument]" << std::endl;

        Argument arg1("arg1");
        arg1.setExpectedValues({"1", "2", "3"});

        Argument arg2("arg2");
        arg2.setRequired(false);
        arg2.setDefaultValue(10);

        Command cmd("cmd");
        cmd.addArguments({
            arg1,
            arg2,
        });

        {
            Parser parser(cmd);
            ParseResult res = parser.parse({"cmd", "4"});
            assert(res.error() == ParseResult::InvalidArgumentValue);
        }
        std::cout << "Unexpected argument: OK" << std::endl;

        {
            Parser parser(cmd);
            ParseResult res = parser.parse({"cmd", "1", "str"});
            assert(res.error() == ParseResult::ArgumentTypeMismatch);
        }
        std::cout << "Argument type mismatch: OK" << std::endl;
    }
    std::cout << std::endl;

    {
        std::cout << "[Test Exclusive Option]" << std::endl;

        Option opt1("--opt1", "1");
        Option opt2("--opt2", "2");

        Command cmd("cmd");
        cmd.addOptions({opt1, opt2}, "1");

        {
            Parser parser(cmd);
            ParseResult res = parser.parse({"cmd", "--opt1", "--opt2"});
            assert(res.error() == ParseResult::MutuallyExclusiveOptions);
        }
        std::cout << "Mutually exclusive options: OK" << std::endl;
    }
    std::cout << std::endl;

    {
        std::cout << "[Test Short Option]" << std::endl;
    }

    return 0;
}