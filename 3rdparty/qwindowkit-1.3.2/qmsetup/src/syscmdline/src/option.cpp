#include "option.h"
#include "option_p.h"

#include "utils_p.h"
#include "strings.h"
#include "parser.h"

namespace SysCmdLine {

    static std::vector<std::string> defaultTokensForRole(Option::Role role) {
        std::vector<std::string> res;
        switch (role) {
            case Option::Help:
                res = {"-h", "--help"};
                break;
            case Option::Version:
                res = {"-v", "--version"};
                break;
            case Option::Verbose:
                res = {"-V", "--verbose"};
                break;
            case Option::Debug:
                res = {"-d", "--debug"};
                break;
            default:
                break;
        }
        return res;
    }

    OptionPrivate::OptionPrivate(Option::Role role, const std::vector<std::string> &tokens,
                                 const std::string &desc, bool required)
        : ArgumentHolderPrivate(Symbol::ST_Option, desc), role(role), tokens(tokens),
          required(required), shortMatchRule(Option::NoShortMatch), priorLevel(Option::NoPrior),
          global(false), maxOccurrence(1) {
    }

    SymbolPrivate *OptionPrivate::clone() const {
        return new OptionPrivate(*this);
    }

    std::vector<Option> OptionPrivate::reorderOptions(const std::vector<Option> &options,
                                                      const std::vector<Option> &globalOptions) {
        std::vector<Option> res;
        std::vector<Option> roles;
        for (const auto &opt : options) {
            if (opt.role() == Option::NoRole) {
                res.push_back(opt);
                continue;
            }
            roles.push_back(opt);
        }

        for (const auto &opt : globalOptions) {
            if (opt.role() == Option::NoRole) {
                res.push_back(opt);
                continue;
            }
            roles.push_back(opt);
        }

        for (const auto &opt : std::as_const(roles)) {
            res.push_back(opt);
        }
        return res;
    }

    //        template <typename... Args>
    //        Option(const char *firstToken, Args &&...args, const std::string &desc)
    //            : Option(std::vector<std::string>(), desc) {
    //            std::vector<std::string> tokens;
    //            tokens.emplace_back(firstToken);
    //            (tokens.emplace_back(std::forward<Args>(args)), ...);
    //            setTokens(tokens);
    //        }

    Option::Option() : Option(NoRole, {}) {
    }

    Option::Option(Role role, const std::vector<std::string> &tokens, const std::string &desc)
        : ArgumentHolder(new OptionPrivate(
              role, tokens.empty() ? defaultTokensForRole(role) : tokens, desc, false)) {
    }

    Option::Option(const std::string &token, const std::string &desc, const Argument &arg,
                   bool required)
        : Option(std::vector<std::string>{token}, desc, arg, required) {
    }

    Option::Option(const std::vector<std::string> &tokens, const std::string &desc,
                   const Argument &arg, bool required)
        : ArgumentHolder(new OptionPrivate(NoRole, tokens, desc, required)) {
        if (!arg.d_func()->name.empty())
            addArgument(arg);
    }

    std::string Option::helpText(Symbol::HelpPosition pos, int displayOptions, void *extra) const {
        Q_D2(Option);
        if (auto ss = ArgumentHolder::helpText(pos, displayOptions, extra); !ss.empty()) {
            return ss;
        }

        switch (pos) {
            case Symbol::HP_Usage: {
                std::string appendix;
                if (!d->arguments.empty()) {
                    appendix = " " + displayedArguments(displayOptions);
                }
                return d->tokens.front() + appendix;
            }
            case Symbol::HP_ErrorText: {
                return d->tokens.front();
            }
            case Symbol::HP_FirstColumn: {
                std::string appendix;
                if (!d->arguments.empty()) {
                    appendix = " " + displayedArguments(displayOptions);
                }
                return Utils::join(d->tokens, ", ") + appendix;
            }
            case Symbol::HP_SecondColumn: {
                auto textProvider = reinterpret_cast<Parser::TextProvider>(extra);
                if (!textProvider) {
                    textProvider = Parser::defaultTextProvider();
                }

                std::string appendix;
                std::string desc = d->desc;
                if (desc.empty() && d->role != NoRole) {
                    desc = textProvider(Strings::OptionRole,
                                        static_cast<Strings::OptionRoleText>(d->role));
                }

                // Required
                if (d->required && (displayOptions & Parser::ShowOptionIsRequired)) {
                    appendix += " [" + textProvider(Strings::Title, Strings::Required) + "]";
                }
                return desc + appendix;
            }
        }
        return {};
    }

    Option::Role Option::role() const {
        Q_D2(Option);
        return d->role;
    }

    void Option::setRole(Role role) {
        Q_D(Option);
        d->role = role;
    }

    const std::vector<std::string> &Option::tokens() const {
        Q_D2(Option);
        return d->tokens;
    }

    void Option::setTokens(const std::vector<std::string> &tokens) {
        Q_D(Option);
        d->tokens = tokens;
    }

    bool Option::isRequired() const {
        Q_D2(Option);
        return d->required;
    }

    void Option::setRequired(bool required) {
        Q_D(Option);
        d->required = required;
    }

    Option::ShortMatchRule Option::shortMatchRule() const {
        Q_D2(Option);
        return d->shortMatchRule;
    }

    void Option::setShortMatchRule(ShortMatchRule shortMatchRule) {
        Q_D(Option);
        d->shortMatchRule = shortMatchRule;
    }

    Option::PriorLevel Option::priorLevel() const {
        Q_D2(Option);
        return d->priorLevel;
    }

    void Option::setPriorLevel(PriorLevel priorLevel) {
        Q_D(Option);
        d->priorLevel = priorLevel;
    }

    bool Option::isGlobal() const {
        Q_D2(Option);
        return d->global;
    }

    void Option::setGlobal(bool on) {
        Q_D(Option);
        d->global = on;
    }

    int Option::maxOccurrence() const {
        Q_D2(Option);
        return d->maxOccurrence;
    }

    void Option::setMaxOccurrence(int max) {
        Q_D(Option);
        d->maxOccurrence = max;
    }

}