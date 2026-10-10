#include "FluTextEdit.h"
#include "FluTextEditWrap.h"
#include "FluPMenu.h"

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

void FluTextEdit::contextMenuEvent(QContextMenuEvent* event)
{
    // 用 FluentUI 形式的菜单替代 Qt 原生样式的标准右键菜单
    FluPMenu::execStandardContextMenu(this, createStandardContextMenu(), event->globalPos());
}

void FluTextEdit::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluTextEdit.qss", this, FluThemeUtils::getUtils()->getTheme());
}
