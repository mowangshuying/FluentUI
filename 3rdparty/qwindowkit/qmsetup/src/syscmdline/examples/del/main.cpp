#include <syscmdline/parser.h>
#include <syscmdline/system.h>

namespace zh_CN {

    static const char *error_strings[] = {
        R"(没有错误。)",
        R"(未知的选项 "%1"。)",
        R"(未知的命令或参数 "%1"。)",
        R"(选项 "%2" 缺少必选参数 "%1"。)",
        R"(缺少必选参数 "%1"。)",
        R"(参数过多。)",
        R"(参数 "%2" 被指定非法的值 "%1"。)",
        R"(选项 "%1" 出现在非法的位置，此处应为参数 "%2"。)",
        R"(缺少必选选项 "%1"。)",
        R"(选项 "%1" 出现次数过多，最多 %2 次。)",
        R"(参数 "%2" 被指定非法的值 "%1"，应为 "%3"。)",
        R"(参数 "%2" 被指定非法的值 "%1"，原因: %3)",
        R"(选项 "%1" 与 "%2" 是互斥的。)",
        R"(选项 "%1" 与其他参数不能同时指定。)",
        R"(选项 "%1" 与其他选项不能同时指定。)",
    };

    static const char *title_strings[] = {
        "错误", "用法", "简介", "参数", "选项", "命令", "必选", "默认", "合法值",
    };

    static const char *role_strings[] = {
        "", "调试模式", "显示详细信息", "显示版本信息", "显示帮助信息",
    };

    static const char *info_strings[] = {
        R"("%1" 未匹配。您是否想指定以下之一？)",
    };

    static const char **strings[] = {
        error_strings,
        title_strings,
        role_strings,
        info_strings,
    };

    static std::string provider(int category, int index) {
        return strings[category][index];
    }

}

using namespace SysCmdLine;

static int routine(const ParseResult &result) {
    auto fileValues = Value::toStringList(result.values("files"));
    u8info("将要被删除的文件：\n");
    for (const auto &item : std::as_const(fileValues)) {
        u8info("    %s\n", item.data());
    }

    bool prompt = result.isOptionSet("/P");
    bool force = result.isOptionSet("/F");
    bool subdir = result.isOptionSet("/S");
    bool quiet = result.isOptionSet("/Q");

    u8info("模式: \n");
    if (prompt) {
        u8info("    提示\n");
    }
    if (force) {
        u8info("    强制\n");
    }
    if (subdir) {
        u8info("    子文件夹\n");
    }
    if (quiet) {
        u8info("    静默\n");
    }

    return 0;
}

int main(int argc, char *argv[]) {
    SYSCMDLINE_UNUSED(argc);
    SYSCMDLINE_UNUSED(argv);

    Option promptOption({"/P", "-p"}, "删除每一个文件之前提示确认");
    Option forceOption({"/F", "-f"}, "强制删除只读文件");
    Option subdirOption({"/S", "-s"}, "删除所有子目录中的指定的文件");
    Option quietOption({"/Q", "-q"}, "安静模式。删除全局通配符时，不要求确认");

    Argument fileArg("files", "指定一个或多个文件或者目录列表");
    fileArg.setDisplayName("files");
    fileArg.setMultiValueEnabled(true);

    Command rootCommand("del", {});
    rootCommand.addArgument(fileArg);
    rootCommand.addOptions({
        promptOption,
        forceOption,
        subdirOption,
        quietOption,
    });
    rootCommand.addHelpOption(false, false, {"/?"});
    rootCommand.setHandler(routine);

    Parser parser(rootCommand);
    parser.setTextProvider(zh_CN::provider);
    parser.setDisplayOptions(Parser::ShowOptionalOptionsOnUsage | Parser::ShowArgumentIsRequired |
                             Parser::AlignAllCatalogues);
    return parser.invoke(commandLineArguments(), -1,
                         Parser::IgnoreOptionCase | Parser::AllowUnixGroupFlags);
}