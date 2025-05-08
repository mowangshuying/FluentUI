#include "argument.h"
#include "argument_p.h"

#ifdef SYSCMDLINE_ENABLE_VALIDITY_CHECK
#  include <stdexcept>
#endif

#include <algorithm>

#include "strings.h"
#include "parser.h"

#include "utils_p.h"

namespace SysCmdLine {

    ArgumentPrivate::ArgumentPrivate(std::string name, const std::string &desc, bool required,
                                     Value defaultValue)
        : SymbolPrivate(Symbol::ST_Argument, desc), name(std::move(name)), required(required),
          defaultValue(std::move(defaultValue)), number(Argument::Single) {
    }

    SymbolPrivate *ArgumentPrivate::clone() const {
        return new ArgumentPrivate(*this);
    }

    Argument::Argument() : Argument(std::string()) {
    }

    Argument::Argument(const std::string &name, const std::string &desc, bool required,
                       const Value &defaultValue)
        : Symbol(new ArgumentPrivate(name, desc, required, defaultValue)) {
    }

    std::string Argument::displayedText() const {
        Q_D2(Argument);
        std::string res = d->displayName.empty() ? ("<" + d->name + ">") : d->displayName;
        return res;
    }

    std::string Argument::helpText(Symbol::HelpPosition pos, int displayOptions,
                                   void *extra) const {
        Q_D2(Argument);
        if (auto ss = Symbol::helpText(pos, displayOptions, extra); !ss.empty()) {
            return ss;
        }

        switch (pos) {
            case Symbol::HP_Usage: {
                return displayedText() + ((d->number != Single) ? "..." : "");
            }
            case Symbol::HP_SecondColumn: {
                auto textProvider = reinterpret_cast<Parser::TextProvider>(extra);
                if (!textProvider) {
                    textProvider = Parser::defaultTextProvider();
                }

                std::string appendix;
                // Required
                if (d->required && (displayOptions & Parser::ShowArgumentIsRequired)) {
                    appendix += " [" + textProvider(Strings::Title, Strings::Required) + "]";
                }

                // Default Value
                if (d->defaultValue.type() != Value::Null &&
                    (displayOptions & Parser::ShowArgumentDefaultValue)) {
                    appendix += " [" + textProvider(Strings::Title, Strings::Default) + ": " +
                                d->defaultValue.toString() + "]";
                }

                // Expected Values
                if (!d->expectedValues.empty() &&
                    (displayOptions & Parser::ShowArgumentExpectedValues)) {
                    std::vector<std::string> values;
                    values.reserve(d->expectedValues.size());
                    for (const auto &item : d->expectedValues) {
                        switch (item.type()) {
                            case Value::String:
                                values.push_back("\"" + item.toString() + "\"");
                                break;
                            default:
                                values.push_back(item.toString());
                                break;
                        }
                    }
                    appendix += " [" + textProvider(Strings::Title, Strings::ExpectedValues) +
                                ": " + Utils::join(values, ", ") + "]";
                }
                return d->desc + appendix;
            }

            default:
                break;
        }

        return displayedText();
    }

    std::string Argument::name() const {
        Q_D2(Argument);
        return d->name;
    }

    void Argument::setName(const std::string &name) {
        Q_D(Argument);
        d->name = name;
    }

    std::string Argument::displayName() const {
        Q_D2(Argument);
        return d->displayName;
    }

    void Argument::setDisplayName(const std::string &displayName) {
        Q_D(Argument);
        d->displayName = displayName;
    }

    bool Argument::isRequired() const {
        Q_D2(Argument);
        return d->required;
    }

    void Argument::setRequired(bool required) {
        Q_D(Argument);
        d->required = required;
    }

    Value Argument::defaultValue() const {
        Q_D2(Argument);
        return d->defaultValue;
    }

    void Argument::setDefaultValue(const Value &defaultValue) {
        Q_D(Argument);
        d->defaultValue = defaultValue;
    }

    const std::vector<Value> &Argument::expectedValues() const {
        Q_D2(Argument);
        return d->expectedValues;
    }

    void Argument::setExpectedValues(const std::vector<Value> &expectedValues) {
        Q_D(Argument);
        d->expectedValues = expectedValues;
    }

    bool Argument::multiValueEnabled() const {
        Q_D2(Argument);
        return d->number != Single;
    }

    void Argument::setMultiValueEnabled(bool on) {
        Q_D(Argument);
        d->number = on ? MultiValue : Single;
    }

    Argument::Number Argument::number() const {
        Q_D2(Argument);
        return d->number;
    }

    void Argument::setNumber(Number number) {
        Q_D(Argument);
        d->number = number;
    }

    Argument::Validator Argument::validator() const {
        Q_D2(Argument);
        return d->validator;
    }

    void Argument::setValidator(const Validator &validator) {
        Q_D(Argument);
        d->validator = validator;
    }

    ArgumentHolderPrivate::ArgumentHolderPrivate(Symbol::SymbolType type, const std::string &desc)
        : SymbolPrivate(type, desc) {
    }

#ifdef SYSCMDLINE_ENABLE_VALIDITY_CHECK
    void ArgumentHolderPrivate::checkAddedArgument(const Argument &arg) const {
        const auto &d = arg.d_func();
        const auto &name = d->name;

        // Empty argument name?
        if (name.empty()) {
            throw std::runtime_error("argument doesn't have a name");
        }

        // Duplicated argument name?
        if (std::any_of(arguments.begin(), arguments.end(), [&name](const Argument &arg) {
                return arg.name() == name; //
            })) {
            throw std::runtime_error(Utils::formatText("argument name \"%1\" duplicated", {name}));
        }

        // Required argument behind optional one?
        if (!arguments.empty() && arguments.back().isOptional() && d->required) {
            throw std::runtime_error("required argument after required arguments is prohibited");
        }

        bool hasMultiValueArgument =
            std::any_of(arguments.begin(), arguments.end(), [&name](const Argument &arg) {
                return arg.multiValueEnabled(); //
            });

        if (arg.multiValueEnabled()) {
            // Multiple multi-value argument?
            if (hasMultiValueArgument) {
                throw std::runtime_error("at most one multi-value argument");
            }
            hasMultiValueArgument = true;
        } else if (hasMultiValueArgument && !d->required) {
            // Optional argument after multi-value argument?
            throw std::runtime_error("required argument after multi-value argument is prohibited");
        }

        {
            const auto &expectedValues = d->expectedValues;
            const auto &defaultValue = d->defaultValue;
            if (!expectedValues.empty()) {
                // Null expected value?
                for (size_t i = 0; i < expectedValues.size(); ++i) {
                    if (expectedValues[i].type() == Value::Null) {
                        throw std::runtime_error(
                            Utils::formatText("expected value at %1 is null", {std::to_string(i)}));
                    }
                }

                // Invalid default value?
                if (defaultValue.type() != Value::Null &&
                    std::find(expectedValues.begin(), expectedValues.end(), defaultValue) ==
                        expectedValues.end()) {
                    throw std::runtime_error(Utils::formatText(
                        "default value \"%1\" is not in expect values", {defaultValue.toString()}));
                }
            }

            const auto &validator = d->validator;
            if (validator && defaultValue.type() != Value::Null) {
                // Validator is incompatible with the default value?
                Value val;
                std::string errorMessage;
                auto res = validator(defaultValue.toString(), &val, &errorMessage);
                if (!res) {
                    throw std::runtime_error("validator is not able to handle the default value.");
                }
            }
        }

        // ...
    }
#endif

    std::string ArgumentHolder::displayedArguments(int displayOptions) const {
        Q_D2(ArgumentHolder);

        // Use C Style to traverse
        auto arguments = d->arguments.data();
        int size = int(d->arguments.size());

        std::string ss;
        int optionalIdx = size;
        for (int i = 0; i < size; ++i) {
            if (!arguments[i].isRequired()) {
                optionalIdx = i;
                break;
            }
        }

        if (optionalIdx > 0) {
            for (int i = 0; i < optionalIdx - 1; ++i) {
                ss += arguments[i].helpText(Symbol::HP_Usage, displayOptions, nullptr);
                ss += " ";
            }
            ss += arguments[optionalIdx - 1].helpText(Symbol::HP_Usage, displayOptions, nullptr);
        }

        if (optionalIdx < size) {
            if (optionalIdx > 0)
                ss += " ";
            ss += "[";
            for (int i = optionalIdx; i < size - 1; ++i) {
                ss += arguments[i].helpText(Symbol::HP_Usage, displayOptions, nullptr);
                ss += " ";
            }
            ss += arguments[size - 1].helpText(Symbol::HP_Usage, displayOptions, nullptr);
            ss += "]";
        }
        return ss;
    }

    void ArgumentHolder::addArguments(const std::vector<Argument> &arguments) {
        Q_D(ArgumentHolder);

#ifdef SYSCMDLINE_ENABLE_VALIDITY_CHECK
        for (const auto &arg : arguments) {
            d->checkAddedArgument(arg);
            d->arguments.push_back(arg);
        }
#else
        // d->arguments.insert(d->arguments.end(), arguments.begin(), arguments.end());
        d->arguments = Utils::concatVector(d->arguments, arguments);
#endif
    }

    ArgumentHolder::ArgumentHolder(ArgumentHolderPrivate *d) : Symbol(d) {
    }
}