#pragma once

#include "FluWidget.h"
// #include <QScrollArea>
#include <QVBoxLayout>
#include "../utils/FluStyleSheetUtils.h"
#include "../utils/FluUtils.h"
#include "FluScrollArea.h"

class FluVScrollView : public FluScrollArea
{
    Q_OBJECT
  public:
    FluVScrollView(QWidget* parent = nullptr);

    ~FluVScrollView();

    QVBoxLayout* getMainLayout();

    void addWidget(QWidget* widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
    void addSpacing(int size);
    void setAlignment(Qt::Alignment alignment);

  public slots:
    void onThemeChanged();

  protected:
    QWidget* m_contextWidget;
    QVBoxLayout* m_mainLayout;
};
