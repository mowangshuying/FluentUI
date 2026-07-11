#include "FluWidget.h"
#include "../Utils/FluUtils.h"
#include <QStyleOption>

FluWidget::FluWidget(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_theme = FluThemeUtils::getUtils()->getTheme();

#ifdef FluCheckObjects
    FluObjectPtrUtils::getUtils()->add((int64_t)(this), this->metaObject()->className());
    LOG_DEBUG << (int64_t)(this) << "," << this->metaObject()->className();
#endif

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) {
        if (!isVisible())
            return;
#ifdef FluCheckObjects
        LOG_DEBUG << "ClassName:" << this->metaObject()->className();
#endif

        onThemeChanged();

#ifdef FluCheckObjects
        FluObjectPtrUtils::getUtils()->remove((int64_t)(this));
#endif
    });
}

  void FluWidget::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluWidget::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    if (m_theme != FluThemeUtils::getUtils()->getTheme())
    {
        onThemeChanged();
        m_theme = FluThemeUtils::getUtils()->getTheme();
    }
}
