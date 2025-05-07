/****************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2023 SineStriker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ****************************************************************************/

#ifndef PARSERESULT_H
#define PARSERESULT_H

#include <syscmdline/command.h>

namespace SysCmdLine {

    class Parser;

    class ParseResultPrivate;

    class SYSCMDLINE_EXPORT OptionResult {
    public:
        OptionResult();

    public:
        Option option() const;
        int indexOf(const std::string &name) const;
        int count() const;
        inline bool isSet() const;

        inline bool isArgumentSet(const Argument &arg, int n = 0) const;
        inline bool isArgumentSet(const std::string &name, int n = 0) const;
        inline bool isArgumentSet(int index, int n = 0) const;

        // Get all values of an argument
        inline std::vector<Value> allValues(const Argument &arg) const;
        inline std::vector<Value> allValues(const std::string &name) const;
        std::vector<Value> allValues(int index = 0) const;

        // Get values of multi-value argument at the option's N-th occurrence
        inline const std::vector<Value> &values(const Argument &arg, int n = 0) const;
        inline const std::vector<Value> &values(const std::string &name, int n = 0) const;
        const std::vector<Value> &values(int index = 0, int n = 0) const;

        // Get value of single-value argument at the option's N-th occurrence or its default value
        inline Value value(const Argument &arg, int n = 0) const;
        inline Value value(const std::string &name, int n = 0) const;
        Value value(int index = 0, int n = 0) const;

    private:
        inline OptionResult(const void *data);
        const void *data;

        friend class ParseResult;
    };

    inline bool OptionResult::isSet() const {
        return count() > 0;
    }

    inline bool OptionResult::isArgumentSet(const Argument &arg, int n) const {
        return !values(indexOf(arg.name()), n).empty();
    }

    inline bool OptionResult::isArgumentSet(const std::string &name, int n) const {
        return !values(indexOf(name), n).empty();
    }

    inline bool OptionResult::isArgumentSet(int index, int n) const {
        return !values(index, n).empty();
    }

    inline std::vector<Value> OptionResult::allValues(const Argument &arg) const {
        return allValues(indexOf(arg.name()));
    }

    inline std::vector<Value> OptionResult::allValues(const std::string &name) const {
        return allValues(indexOf(name));
    }

    inline const std::vector<Value> &OptionResult::values(const Argument &arg, int n) const {
        return values(indexOf(arg.name()), n);
    }

    inline const std::vector<Value> &OptionResult::values(const std::string &name, int n) const {
        return values(indexOf(name), n);
    }

    inline Value OptionResult::value(const Argument &arg, int n) const {
        return value(indexOf(arg.name()), n);
    }

    inline Value OptionResult::value(const std::string &name, int n) const {
        return value(indexOf(name), n);
    }

    inline OptionResult::OptionResult(const void *data) : data(data) {
    }

    class SYSCMDLINE_EXPORT ParseResult : public SharedBase {
        SYSCMDLINE_DECL_PRIVATE(ParseResult)
    public:
        ParseResult();

        inline bool isValid() const;

    public:
        Command rootCommand() const;
        const std::vector<std::string> &arguments() const;

        int invoke(int errCode = -1) const;
        int dispatch() const;

    public:
        enum Error {
            NoError,
            UnknownOption,
            UnknownCommand,
            MissingOptionArgument,
            MissingCommandArgument,
            TooManyArguments,
            InvalidArgumentValue,
            InvalidOptionPosition,
            MissingRequiredOption,
            OptionOccurTooMuch,
            ArgumentTypeMismatch,
            ArgumentValidateFailed,
            MutuallyExclusiveOptions,
            PriorOptionWithArguments,
            PriorOptionWithOptions,
        };

        Error error() const;
        std::string errorText() const;
        std::string correctionText() const;
        std::string cancellationToken() const;

        Command command() const;
        std::vector<Option> globalOptions() const;
        std::vector<int> commandIndexStack() const;
        int indexOfArgument(const std::string &name) const;
        int indexOfOption(const std::string &token) const;

        void showError() const;
        void showHelpText() const;
        void showMessage(const std::string &info, const std::string &warning,
                         const std::string &error) const;

    public:
        inline bool isVersionSet() const;
        inline bool isHelpSet() const;
        bool isRoleSet(Option::Role role) const;

        inline bool isArgumentSet(const Argument &arg) const;
        inline bool isArgumentSet(const std::string &name) const;
        inline bool isArgumentSet(int index) const;

        // Get values of multi-value argument
        inline const std::vector<Value> &values(const Argument &arg) const;
        inline const std::vector<Value> &values(const std::string &name) const;
        const std::vector<Value> &values(int index) const;

        // Get value of single-value argument or its default value
        inline Value value(const Argument &arg) const;
        inline Value value(const std::string &name) const;
        Value value(int index) const;

        inline bool isOptionSet(const Option &option) const;
        inline bool isOptionSet(const std::string &token) const;
        inline bool isOptionSet(int index) const;

        // Detailed result for an option
        inline OptionResult option(const Option &option) const;
        inline OptionResult option(const std::string &token) const;
        OptionResult option(int index) const;

        // Get value of single-value argument of given option or its default value
        inline Value valueForOption(const Option &option) const;
        inline Value valueForOption(const std::string &token) const;
        inline Value valueForOption(int index) const;

    protected:
        ParseResult(ParseResultPrivate *d);
        friend class Parser;
    };

    inline bool ParseResult::isValid() const {
        return d_ptr != nullptr;
    }

    inline bool ParseResult::isVersionSet() const {
        return isRoleSet(Option::Version);
    }

    inline bool ParseResult::isHelpSet() const {
        return isRoleSet(Option::Help);
    }

    inline bool ParseResult::isArgumentSet(const Argument &arg) const {
        return isArgumentSet(indexOfArgument(arg.name()));
    }

    inline bool ParseResult::isArgumentSet(const std::string &name) const {
        return isArgumentSet(indexOfArgument(name));
    }

    inline bool ParseResult::isArgumentSet(int index) const {
        return !values(index).empty();
    }

    inline const std::vector<Value> &ParseResult::values(const Argument &arg) const {
        return values(indexOfArgument(arg.name()));
    }

    inline const std::vector<Value> &ParseResult::values(const std::string &name) const {
        return values(indexOfArgument(name));
    }

    inline Value ParseResult::value(const Argument &arg) const {
        return value(indexOfArgument(arg.name()));
    }

    inline Value ParseResult::value(const std::string &name) const {
        return value(indexOfArgument(name));
    }

    inline bool ParseResult::isOptionSet(const Option &option) const {
        return this->option(indexOfOption(option.token())).count() > 0;
    }

    inline bool ParseResult::isOptionSet(const std::string &token) const {
        return option(indexOfOption(token)).count() > 0;
    }

    inline bool ParseResult::isOptionSet(int index) const {
        return option(index).count() > 0;
    }

    inline OptionResult ParseResult::option(const Option &option) const {
        return this->option(indexOfOption(option.token()));
    }

    inline OptionResult ParseResult::option(const std::string &token) const {
        return option(indexOfOption(token));
    }

    inline Value ParseResult::valueForOption(const Option &option) const {
        return this->option(indexOfOption(option.token())).value();
    }

    inline Value ParseResult::valueForOption(const std::string &token) const {
        return option(indexOfOption(token)).value();
    }

    inline Value ParseResult::valueForOption(int index) const {
        return option(index).value();
    }

}

#endif // PARSERESULT_H
