#pragma once

#include <QWidget>
#include <QLabel>
#include "FluCodeExpander.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../FluUtils/FluUtils.h"

class FluDisplayBox : public QWidget
{
    Q_OBJECT
  public:
    FluDisplayBox(QWidget* parent = nullptr);

    void setTitle(QString title)
    {
        m_titleLabel->setText(title);
    }

    QVBoxLayout* getBodyLayout()
    {
        return m_vBodyLayout;
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
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayBox.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDisplayBox.qss", this);
        }
    }

  protected:
    QVBoxLayout* m_mainLayout;
    QLabel* m_titleLabel;
    QWidget* m_bodyWidget;
    QVBoxLayout* m_vBodyLayout;
    FluCodeExpander* m_codeExpander;
};