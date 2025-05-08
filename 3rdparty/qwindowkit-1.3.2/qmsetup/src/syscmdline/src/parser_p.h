#ifndef PARSER_P_H
#define PARSER_P_H

#include "sharedbase_p.h"
#include "parser.h"

namespace SysCmdLine {

    class ParserPrivate : public SharedBasePrivate {
    public:
        ParserPrivate();
        ParserPrivate *clone() const;

        Command rootCommand;
        std::string prologue, epilogue;
        int displayOptions;

        int sizeConfig[3] = {
            4,
            4,
            80,
        };

        Parser::TextProvider textProvider;

        inline std::string indent() const {
            return std::string(sizeConfig[Parser::ST_Indent], ' ');
        }

        inline std::string spacing() const {
            return std::string(sizeConfig[Parser::ST_Spacing], ' ');
        }
    };

}

#endif // PARSER_P_H
