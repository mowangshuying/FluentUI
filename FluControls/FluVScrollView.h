#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include "../FluUtils/FluStyleSheetUitls.h"

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
        QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluVScrollView.qss");
        setStyleSheet(qss);
    }

  protected:
    QWidget* m_contextWidget;
    QVBoxLayout* m_vMainLayout;
};
