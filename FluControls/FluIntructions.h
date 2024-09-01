#pragma once

#include "FluExpander.h"
#include "../FluUtils/FluUtils.h"
#include <QVBoxLayout>
#include "FluVSplitLine.h"
#include "FluLabel.h"
#include <vector>
#include <QWidget>

class FluIntructions : public FluExpander
{
    Q_OBJECT
  public:
    FluIntructions(QWidget* parent = nullptr);

    QLabel* getTitleLabel();

    void setTitleLabelText(QString text);

    void addTitleContent(QString title, QString content, bool bAdd = true);

    void addVSplitLine(bool bAdd = true);

    void resizeEvent(QResizeEvent* event);

    void paintEvent(QPaintEvent* event);

  public slots:
    virtual void onClicked();

  protected:
    FluLabel* m_titleLabel;
    QTimer* m_timer;
};
