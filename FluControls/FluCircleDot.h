#pragma once

#include <QWidget>

#include "../FluUtils/FluUtils.h"
#include "FluWidget.h"
#include <QEvent>
#include <QStyleOption>
#include <QPainter>

class FluCircleDot : public FluWidget
{
    Q_OBJECT
  public:
    FluCircleDot(QWidget* parent = nullptr) : FluWidget(parent)
    {
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluInfoBadge.qss", this);

        setFixedSize(11, 11);
        onThemeChanged();
        m_target = parent;

        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    void setTopRightMargin(int nMarginTop, int nMarginRight)
    {
        m_nMarginTop = nMarginTop;
        m_nMarginRight = nMarginRight;
    }

    void moveTopRight()
    {
        int nX = m_target->width() - m_nMarginRight - width() / 2;
        int nY = m_nMarginTop - height() / 2;
        move(nX, nY);
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

    bool eventFilter(QObject* watched, QEvent* event)
    {
        if (m_target == nullptr)
            return FluWidget::eventFilter(watched, event);

        if (watched == m_target)
        {
            if (event->type() == QEvent::Resize || event->type() == QEvent::Move)
            {
                moveTopRight();
            }
        }

        return FluWidget::eventFilter(watched, event);
    }

    static void setCircleDot(QWidget* target, int nMarginTop, int nMarginRight)
    {
        if (target == nullptr)
            return;

        FluCircleDot* circleDot = new FluCircleDot(target);
        circleDot->setTopRightMargin(nMarginTop, nMarginRight);
        target->installEventFilter(circleDot);

        circleDot->moveTopRight();
    }
  public slots:

    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCircleDot.qss", this);
        }
        else if (FluThemeUtils::isDarkTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCircleDot.qss", this);
        }
    }

  protected:
    QWidget* m_target;

    int m_nMarginTop;
    int m_nMarginRight;
};
