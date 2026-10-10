#include "FluSpinBox.h"
#include "FluPMenu.h"
#include <QLineEdit>

FluSpinBox::FluSpinBox(QWidget* parent /*= nullptr*/) : QSpinBox(parent)
{
    lineEdit()->installEventFilter(this);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluSpinBox::paintEvent(QPaintEvent* event)
{
    QSpinBox::paintEvent(event);
    if (!hasFocus())
        return;

    QPainter painter(this);
    FluStyleSheetUtils::drawBottomLineIndicator(this, &painter);
}

bool FluSpinBox::eventFilter(QObject* watched, QEvent* event)
{
    // 内部 QLineEdit 的右键菜单默认是系统样式的，这里换成 FluentUI 形式的菜单
    if (watched == lineEdit() && event->type() == QEvent::ContextMenu)
    {
        auto contextEvent = static_cast<QContextMenuEvent*>(event);
        FluPMenu::execStandardContextMenu(this, lineEdit()->createStandardContextMenu(), contextEvent->globalPos());
        return true;
    }

    return QSpinBox::eventFilter(watched, event);
}

void FluSpinBox::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluSpinBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
