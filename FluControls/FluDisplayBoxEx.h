#pragma once

#include "FluWidget.h"
#include <QLabel>
#include "FluCodeExpander.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../FluUtils/FluUtils.h"

class FluDisplayBoxEx : public FluWidget
{
    Q_OBJECT
  public:
    FluDisplayBoxEx(QWidget* parent = nullptr);

    void setTitle(QString title)
    {
        m_titleLabel->setText(title);
    }

    QHBoxLayout* getBodyLayout()
    {
        return m_hBodyLayout;
    }

    QVBoxLayout* getBodyContentLayout()
    {
        return m_vBodyContentLayout;
    }

    QVBoxLayout* getBodyRightLayout()
    {
        return m_vBodyRightLayout;
    }

    FluCodeExpander* getCodeExpander()
    {
        return m_codeExpander;
    }

    void setBodyWidgetFixedHeight(int nHeight)
    {
        m_bodyWidget->setFixedHeight(nHeight);
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayBoxEx.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDisplayBoxEx.qss", this);
        }
    }

  protected:
    QVBoxLayout* m_vMainLayout;
    QLabel* m_titleLabel;

    QWidget* m_bodyWidget;
    QHBoxLayout* m_hBodyLayout;

    QWidget* m_bodyContentWidget;
    QWidget* m_bodyRightWidget;

    QVBoxLayout* m_vBodyContentLayout;
    QVBoxLayout* m_vBodyRightLayout;

    FluCodeExpander* m_codeExpander;
};