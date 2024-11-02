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
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

bool FluTextEdit::getAutoAdjustSize()
{
    return m_bAutoAdjustSize;
}

void FluTextEdit::setAutoAdjustSize(bool bAdjustSize)
{
    m_bAutoAdjustSize = bAdjustSize;
    document()->contentsChanged();
}

void FluTextEdit::paintEvent(QPaintEvent* event)
{
    QTextEdit::paintEvent(event);
    if (!hasFocus())
        return;

    QPainter painter(viewport());
    FluStyleSheetUitls::drawBottomLineIndicator(this, &painter);
}

void FluTextEdit::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTextEdit.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTextEdit.qss", this);
    }
}
