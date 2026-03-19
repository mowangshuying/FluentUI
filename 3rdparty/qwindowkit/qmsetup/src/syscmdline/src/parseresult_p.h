#ifndef PARSERESULT_P_H
#define PARSERESULT_P_H

#include "sharedbase_p.h"
#include "parser.h"

#include "map_p.h"

namespace SysCmdLine {

    struct ArgumentHolderData {
        int optionalArgIndex;
        int multiValueArgIndex;
        GenericMap argNameIndexes; // name -> index of argument
        int argSize;               // equal to `argumentCount()`

        ArgumentHolderData() : optionalArgIndex(-1), multiValueArgIndex(-1), argSize(0) {
        }
    };

    struct OptionData : public ArgumentHolderData {
        const Option *option;           // MUST BE SET
        std::vector<Value> **argResult; // first: occurrence, second: arg index
        int count;                      // occurrence times

        OptionData() : option(nullptr), argResult(nullptr), count(0) {
        }

        ~OptionData() {
            for (int i = 0; i < count; ++i) {
                delete[] argResult[i];
            }
            delete[] argResult;
        }

        static const OptionData &sharedNull();
    };

    struct ParseResultData2 : public ArgumentHolderData {
        std::vector<Value> *argResult;    // arg result

        OptionData *allOptionsResult;     // option result
        int allOptionsSize;               // command option count + global option count
        int globalOptionsSize;            // global option count
        GenericMap allOptionTokenIndexes; // token -> index of `allOptionsResult`

        GenericMap cmdNameIndexes;        // name -> index of command

        ~ParseResultData2() {
            delete[] allOptionsResult;
            delete[] argResult;
        }
    };

    class ParseResultPrivate : public SharedBasePrivate {
    public:
        ParseResultPrivate()
            : error(ParseResult::NoError), errorOption(nullptr), errorArgument(nullptr) {
        }

        ParseResultPrivate(const ParseResultPrivate &) = delete;
        ParseResultPrivate &operator=(const ParseResultPrivate &) = delete;

        // This is a read-only class, we can store the pointers pointing to
        // its own data, and we don't need to implement the clone method
        SharedBasePrivate *clone() const {
            return nullptr;
        }

        // parse information
        Parser parser;
        std::vector<std::string> arguments;

        // error related
        ParseResult::Error error;
        std::vector<std::string> errorPlaceholders;
        const Option *errorOption;
        const Argument *errorArgument;
        std::string cancellationToken;

        // success results
        std::vector<int> stack;
        const Command *command; // MUST BE SET

        ParseResultData2 core;

        bool roleSet[5] = {};

        std::string correctionText() const;

        std::vector<Option> globalOptions() const;

        // isMsg: mainly to display message rather than help
        void showMessage(const std::string &info, const std::string &catalogNames,
                         const std::string &symbolIndexes, bool isMsg = false) const;
    };

}

#endif // PARSERESULT_P_H
