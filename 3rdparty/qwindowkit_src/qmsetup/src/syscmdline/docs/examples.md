# Examples

## Basic

+ Acquire Program Arguments
+ Positional Argument
+ Optinal Argument And Restricted Argument
+ Option
+ Multi-argument Option
+ Multi-value Argument

### Acquire Program Arguments

The most common way to get command-line arguments is directly from the arguments of the `main` function.

```c
int main(int argc, char *argv[]);
```
If your host system is Unix, then everything is fine. However, this set of arguments from `main` is likely to cause problems on Windows because they are in ANSI encoding.

On Windows, we must call `GetCommandLineW()` to get the correct UTF-16 encoded arguments.

As a result, `syscmdline` provides a generic way to get command-line arguments that does not depend on the `main` function.

+ On Windows, it acquires arguments by calling `GetCommandLineW()` and converts the result to UTF-8 string list.

+ On Mac, it acquires arguments by calling `_NSGetArgv`.

+ On Linux, it reads the arguments from `/proc/self/cmdline`.

```c++
namespace SysCmdLine {
    std::vector<std::string> commandLineArguments();
}
```
Include `system.h` to import this function.
```c++
#include <syscmdline/system.h>
```

If you are developing a program on Windows, we recommend using this function to get command line arguments.

`syscmdline` uses UTF-8 internally to output to the console, error may occur if the ANSI-encoded arguments contain non-ASCII characters.

### Positional Argument

Simple Example of one positional argument:

```c++
#include <iostream>

#include <syscmdline/parser.h>
#include <syscmdline/system.h>

namespace SCL = SysCmdLine;

int main(int /* argc */, char * /* argv */ []) {
    SCL::Argument intArg("int", "Integer");
    intArg.setDefaultValue(0);

    SCL::Command rootCommand("square", "Display the square of the specified integer.");
    rootCommand.addArgument(intArg);
    rootCommand.addHelpOption();
    rootCommand.setHandler([](const SCL::ParseResult &result) {
        auto num = result.value("int").toInt();
        std::cout << (num * num) << std::endl;
        return 0;
    });

    SCL::Parser parser(rootCommand);
    return parser.invoke(SCL::commandLineArguments());
}
```
+ In this case, we call `addArgument` to add one positional argument.

+ The `Argument` instance is default to be required, and we set an implicit defualt value to force the parser to to accept only numeric input.

Help text:
```
Description:
    Display the square of a given integer.

Usage:
    square <int> [options]

Arguments:
    <int>    Integer

Options:
    -h, --help    Show help information
```

Test:
```sh
> ./square 32
1024
```

### Optinal Argument And Restricted Argument

Simple example of one restricted argument and one optional argument:

```c++
int main(int /* argc */, char * /* argv */ []) {
    SCL::Argument weekdayArg("weekday", "Weekday");
    weekdayArg.setExpectedValues({
        "Monday", "Tuesday",  "Wednesday", "Thursday",
        "Friday", "Saturday", "Sunday",
    });

    SCL::Argument eventArg("event", "Event to do");
    eventArg.setDefaultValue("football");
    eventArg.setRequired(false);

    SCL::Command rootCommand("work", "What to do on which day?");
    rootCommand.addArguments({weekdayArg, eventArg});
    rootCommand.addHelpOption();
    rootCommand.setHandler([](const SCL::ParseResult &result) {
        std::cout << result.value("weekday").toString() << std::endl;
        std::cout << result.value("event").toString() << std::endl;
        return 0;
    });

    SCL::Parser parser(rootCommand);
    parser.setDisplayOptions(SCL::Parser::ShowArgumentDefaultValue |
                             SCL::Parser::ShowArgumentExpectedValues);
    return parser.invoke(SCL::commandLineArguments());
}
```
+ In this case, we add a restricted argument and another required argument with default value.

+ If an argument has an expect value list, only symbols listed in it will be regarded as valid argument.

+ We also tell the parser to show default value and expect values on help list which would be hided if the flags weren't set.

<!-- We could simplify the above code by using the self-return API:
```c++
int main(int /* argc */, char * /* argv */ []) {
    SCL::Command rootCommand("work", "What to do on which day?");
    rootCommand.addArguments({
        SCL::Argument("weekday", "Weekday").expect({
            "Monday", "Tuesday",  "Wednesday", "Thursday",
            "Friday", "Saturday", "Sunday",
        }),     
        SCL::Argument("event", "Event to do", false, "football"),
    });
    rootCommand.help().action([](const SCL::ParseResult &result) {
        std::cout << result.value("weekday").toString() << std::endl;
        std::cout << result.value("event").toString() << std::endl;
        return 0;
    });

    SCL::Parser parser(rootCommand);
    parser.setDisplayOptions(SCL::Parser::ShowArgumentDefaultValue |
                             SCL::Parser::ShowArgumentExpectedValues);
    return parser.invoke(SCL::commandLineArguments());
}
``` -->

Help Text:
```
Description:
    What to do on which day?

Usage:
    work <weekday> [<event>] [options]

Arguments:
    <weekday>    Weekday [Expected: "Monday", "Tuesday", "Wednesday", ...]
    <event>      Event to do [Default: football]

Options:
    -h, --help    Show help information
```
Test:
```sh
> ./work Monday
Monday
football
```
```sh
> ./work Tuesday basketball
Tuesday
basketball
```

### Option

Simple example of a converter:
```c++
int main(int /* argc */, char * /* argv */ []) {
    SCL::Option inputOpt("--input", "Input file");
    inputOpt.addArgument(SCL::Argument("file"));
    inputOpt.setRequired(true);

    SCL::Option outputOpt("--output", "Output file");
    outputOpt.addArgument(SCL::Argument("file"));

    SCL::Command rootCommand("converter", "Convert A to B.");
    rootCommand.addOptions({inputOpt, outputOpt});
    rootCommand.addHelpOption();
    rootCommand.setHandler([](const SCL::ParseResult &result) {
        std::cout << "Input: " << result.valueForOption("--input").toString() << std::endl;
        if (result.isOptionSet("--output")) {
            std::cout << "Output: " << result.valueForOption("--output").toString() << std::endl;
        }
        return 0;
    });

    SCL::Parser parser(rootCommand);
    parser.setDisplayOptions(SCL::Parser::ShowOptionalOptionsOnUsage);
    return parser.invoke(SCL::commandLineArguments());
}
```
+ In this case, we add two single argument options `input` and `output`, and `input` is required.

+ We also tell the parser to show verbose options on usage.

Help Text:
```
Description:
    Convert A to B.

Usage:
    converter --input <file> [--output <file>] [-h]

Options:
    --input <file>     Input file
    --output <file>    Output file
    -h, --help         Show help information
```

Test:
```sh
> ./converter --input in    
Input: in
```

```sh
> ./converter --input in --output out  
Input: in
Output: out
```

### Multi-argument Option

TODO

### Multi-value Argument

TODO