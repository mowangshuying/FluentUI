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

#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <functional>
#include <vector>

#include <syscmdline/symbol.h>
#include <syscmdline/value.h>

namespace SysCmdLine {

    class ArgumentPrivate;

    class SYSCMDLINE_EXPORT Argument : public Symbol {
        SYSCMDLINE_DECL_PRIVATE(Argument)
    public:
        enum Number {
            Single,
            MultiValue,
            Remainder,
        };
        using Validator = std::function<bool /* result */ (
            const std::string & /* token */, Value * /* out */, std::string * /* errorMessage */)>;

        Argument();
        Argument(const std::string &name, const std::string &desc = {}, bool required = true,
                 const Value &defaultValue = {});

        std::string displayedText() const;

        using Symbol::helpText;
        std::string helpText(HelpPosition pos, int displayOptions, void *extra) const override;

    public:
        std::string name() const;
        void setName(const std::string &name);

        std::string displayName() const;
        void setDisplayName(const std::string &displayName);

        bool isRequired() const;
        void setRequired(bool required);

        inline bool isOptional() const;
        inline void setOptional(bool optional);

        Value defaultValue() const;
        void setDefaultValue(const Value &defaultValue);

        const std::vector<Value> &expectedValues() const;
        void setExpectedValues(const std::vector<Value> &expectedValues);

        bool multiValueEnabled() const;
        SYSCMDLINE_DECL_DEPRECATED void setMultiValueEnabled(bool on);

        Number number() const;
        void setNumber(Number valuePolicy);

        Validator validator() const;
        void setValidator(const Validator &validator);

    public:
        inline Argument &metavar(const std::string &metavar);
        inline Argument &required(bool required = true);
        inline Argument &default_value(const Value &value);
        inline Argument &expect(const std::vector<Value> &expectedValues);
        SYSCMDLINE_DECL_DEPRECATED inline Argument &multi(bool multiValueEnabled = true);
        inline Argument &validate(const Validator &validator);
        inline Argument &nargs(Number valuePolicy);
    };

    inline bool Argument::isOptional() const {
        return !isRequired();
    }

    inline void Argument::setOptional(bool optional) {
        setRequired(!optional);
    }

    inline Argument &Argument::metavar(const std::string &metavar) {
        setDisplayName(metavar);
        return *this;
    }

    inline Argument &Argument::required(bool required) {
        setRequired(required);
        return *this;
    }

    Argument &Argument::default_value(const Value &value) {
        setDefaultValue(value);
        return *this;
    }

    Argument &Argument::expect(const std::vector<Value> &expectedValues) {
        setExpectedValues(expectedValues);
        return *this;
    }

    inline Argument &Argument::multi(bool multiValueEnabled) {
        setMultiValueEnabled(multiValueEnabled);
        return *this;
    }

    inline Argument &Argument::validate(const Argument::Validator &validator) {
        setValidator(validator);
        return *this;
    }

    inline Argument &Argument::nargs(const Argument::Number valuePolicy) {
        setNumber(valuePolicy);
        return *this;
    }

    class ArgumentHolderPrivate;

    class SYSCMDLINE_EXPORT ArgumentHolder : public Symbol {
        SYSCMDLINE_DECL_PRIVATE(ArgumentHolder)
    public:
        std::string displayedArguments(int displayOptions) const;

    public:
        inline void addArgument(const Argument &argument);
        void addArguments(const std::vector<Argument> &arguments);

        using Symbol::helpText;

    protected:
        ArgumentHolder(ArgumentHolderPrivate *d);
    };

    inline void ArgumentHolder::addArgument(const Argument &argument) {
        addArguments({argument});
    }

}

#endif // ARGUMENT_H
