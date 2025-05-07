#ifndef HELPLAYOUT_P_H
#define HELPLAYOUT_P_H

#include <utility>

#include "sharedbase_p.h"
#include "helplayout.h"

namespace SysCmdLine {

    class HelpLayoutPrivate : public SharedBasePrivate {
    public:
        HelpLayoutPrivate *clone() const {
            return new HelpLayoutPrivate(*this);
        }

        enum ItemType {
            HelpText,
            HelpList,
            Message,
            UserHelpText,
            UserHelpList,
            UserIntro,
        };

        struct ItemData {
            ItemType itemType;
            int index;
            HelpLayout::Output out;

            // Maybe
            HelpLayout::Text text;
            HelpLayout::List list;
        };

        std::vector<ItemData> itemDataList;
    };

}

#endif // HELPLAYOUT_P_H
