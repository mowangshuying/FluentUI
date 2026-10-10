#include "FluDoubleSpinBox.h"
#include "FluPMenu.h"
#include <QLineEdit>

FluDoubleSpinBox::FluDoubleSpinBox(QWidget* parent /*= nullptr*/) : QDoubleSpinBox(parent)
{
    lineEdit()->installEventFilter(this);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluDoubleSpinBox::paintEvent(QPaintEvent* event)
{
    QDoubleSpinBox::paintEvent(event);
    if (!hasFocus())
        return;

    QPainter painter(this);
    FluStyleSheetUtils::drawBottomLineIndicator(this, &painter);
}

bool FluDoubleSpinBox::eventFilter(QObject* watched, QEvent* event)
{
    // 内部 QLineEdit 的右键菜单默认是系统样式的，这里换成 FluentUI 形式的菜单
    if (watched == lineEdit() && event->type() == QEvent::ContextMenu)
    {
        auto contextEvent = static_cast<QContextMenuEvent*>(event);
        FluPMenu::execStandardContextMenu(this, lineEdit()->createStandardContextMenu(), contextEvent->globalPos());
        return true;
    }

    return QDoubleSpinBox::eventFilter(watched, event);
}

void FluDoubleSpinBox::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluDoubleSpinBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
