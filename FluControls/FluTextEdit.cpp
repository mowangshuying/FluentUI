#include "FluTextEdit.h"
#include "FluTextEditWrap.h"

FluTextEdit::FluTextEdit(QWidget* parent /*= nullptr*/) : QTextEdit(parent)
{
    m_wrap = new FluTextEditWrap(this);

    m_bAutoAdjustSize = false;

    connect(document(), &QTextDocument::contentsChanged, this, [=]() {
        if (!m_bAutoAdjustSize)
            return;

        setFixedHeight(this->document()->size().height() + 6);
    });
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTextEdit.qss", this);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}
