#pragma once

#include "FluWidget.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include "../FluUtils/FluStyleSheetUitls.h"
#include "../FluUtils/FluUtils.h"

class FluVScrollView : public QScrollArea
{
    Q_OBJECT
  public:
    FluVScrollView(QWidget* parent = nullptr) : QScrollArea(parent)
    {
        setWidgetResizable(true);
        setMinimumSize(0, 0);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_contextWidget = new QWidget(this);
        setWidget(m_contextWidget);
        m_vMainLayout = new QVBoxLayout(m_contextWidget);
        m_contextWidget->setObjectName("contextWidget");

        FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluVScrollView.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    ~FluVScrollView()
    {
    }

    QVBoxLayout* getMainLayout()
    {
        return m_vMainLayout;
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluVScrollView.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/dark/FluVScrollView.qss", this);
        }
    }

  protected:
    QWidget* m_contextWidget;
    QVBoxLayout* m_vMainLayout;
};
