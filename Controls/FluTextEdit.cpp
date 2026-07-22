#include "FluTextEdit.h"
#include "FluTextEditWrap.h"

FluTextEdit::FluTextEdit(QWidget* parent /*= nullptr*/) : QTextEdit(parent)
{
    m_wrap = new FluTextEditWrap(this);

    m_isAutoAdjustSize = false;
    m_delegate = new FluScrollDelegate(this);

    connect(document(), &QTextDocument::contentsChanged, this, [=]() {
        if (!m_isAutoAdjustSize)
            return;

        setFixedHeight(this->document()->size().height() + 6);
    });
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

bool FluTextEdit::getAutoAdjustSize()
{
    return m_isAutoAdjustSize;
}

void FluTextEdit::setAutoAdjustSize(bool isAdjustSize)
{
    m_isAutoAdjustSize = isAdjustSize;
    document()->contentsChanged();
}

void FluTextEdit::paintEvent(QPaintEvent* event)
{
    QTextEdit::paintEvent(event);
    if (!hasFocus())
        return;

    QPainter painter(viewport());
    FluStyleSheetUtils::drawBottomLineIndicator(this, &painter);
}

void FluTextEdit::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluTextEdit.qss", this, FluThemeUtils::getUtils()->getTheme());
}
