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

#ifndef OPTION_H
#define OPTION_H

#include <syscmdline/argument.h>

namespace SysCmdLine {

    class OptionPrivate;

    class SYSCMDLINE_EXPORT Option : public ArgumentHolder {
        SYSCMDLINE_DECL_PRIVATE(Option)
    public:
        enum Role {
            NoRole,
            Debug,
            Verbose,
            Version,
            Help,
        };

        enum PriorLevel {
            NoPrior,
            IgnoreMissingArguments,
            IgnoreMissingSymbols,
            AutoSetWhenNoSymbols,
            ExclusiveToArguments,
            ExclusiveToOptions,
            ExclusiveToAll,
        };

        enum ShortMatchRule {
            NoShortMatch,
            ShortMatchSingleLetter,
            ShortMatchSingleChar,
            ShortMatchAll,
        };

        Option();
        Option(Role role, const std::vector<std::string> &tokens = {}, const std::string &desc = {});
        Option(const std::string &token, const std::string &desc = {}, const Argument &arg = {},
               bool required = false);
        Option(const std::vector<std::string> &tokens, const std::string &desc = {},
               const Argument &arg = {}, bool required = false);
        inline Option(std::initializer_list<std::string> tokens, const std::string &desc = {},
                      const Argument &arg = {}, bool required = false);

        using Symbol::helpText;
        std::string helpText(HelpPosition pos, int displayOptions, void *extra) const override;

    public:
        Role role() const;
        void setRole(Role role);

        const std::vector<std::string> &tokens() const;
        inline std::string token() const;
        void setTokens(const std::vector<std::string> &tokens);
        inline void setToken(const std::string &token);

        bool isRequired() const;
        void setRequired(bool required);

        inline bool isOptional() const;
        inline void setOptional(bool optional);

        ShortMatchRule shortMatchRule() const;
        void setShortMatchRule(ShortMatchRule shortMatchRule);

        PriorLevel priorLevel() const;
        void setPriorLevel(PriorLevel priorLevel);

        bool isGlobal() const;
        void setGlobal(bool on);

        int maxOccurrence() const;
        void setMaxOccurrence(int max);
        inline void setUnlimitedOccurrence();

    public:
        inline Option &arg(const std::string &name, bool required = true,
                           const Value &defaultValue = {});
        inline Option &arg(const Argument &arg);
        inline Option &required(bool required = true);
        inline Option &short_match(ShortMatchRule shortMatchRule = ShortMatchAll);
        inline Option &prior(PriorLevel priorLevel);
        inline Option &global(bool global = true);
        inline Option &multi(int maxOccurrence = 0);
    };

    inline Option::Option(std::initializer_list<std::string> tokens, const std::string &desc,
                          const Argument &arg, bool required)
        : Option(std::vector<std::string>(tokens), desc, arg, required) {
    }

    inline std::string Option::token() const {
        return tokens().front();
    }

    inline void Option::setToken(const std::string &token) {
        setTokens({token});
    }

    inline bool Option::isOptional() const {
        return !isRequired();
    }

    inline void Option::setOptional(bool optional) {
        setRequired(!optional);
    }

    inline void Option::setUnlimitedOccurrence() {
        setMaxOccurrence(0);
    }

    inline Option &Option::arg(const std::string &name, bool required, const Value &defaultValue) {
        // Option's argument doesn't need a description
        addArgument(Argument(name, {}, required, defaultValue));
        return *this;
    }

    inline Option &Option::arg(const Argument &arg) {
        addArgument(arg);
        return *this;
    }

    inline Option &Option::required(bool required) {
        setRequired(required);
        return *this;
    }

    inline Option &Option::short_match(Option::ShortMatchRule shortMatchRule) {
        setShortMatchRule(shortMatchRule);
        return *this;
    }

    inline Option &Option::prior(Option::PriorLevel priorLevel) {
        setPriorLevel(priorLevel);
        return *this;
    }

    inline Option &Option::global(bool global) {
        setGlobal(global);
        return *this;
    }

    inline Option &Option::multi(int maxOccurrence) {
        setMaxOccurrence(maxOccurrence);
        return *this;
    }

}

#endif // OPTION_H
