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

    int getAutoH()
    {
        int nAutoH = 0;
        for (int i = 0; i < getWrap2Layout()->count(); i++)
        {
            auto widget = getWrap2Layout()->itemAt(i)->widget();
            if (widget->objectName() != "wrap2SplitLine")
            {
                auto label = (FluLabel*)widget;
                nAutoH += label->heightForWidth(m_wrap2->width() - getWrap2Layout()->contentsMargins().left() - getWrap2Layout()->contentsMargins().right());
            }
            else
            {
                nAutoH += widget->height();
            }

            nAutoH += getWrap2Layout()->spacing();
        }

        nAutoH += getWrap2Layout()->contentsMargins().top() + getWrap2Layout()->contentsMargins().bottom();
        return nAutoH;
    }

    void resizeEvent(QResizeEvent* event);

    void paintEvent(QPaintEvent* event);

  public slots:
    virtual void onClicked();

  protected:
    FluLabel* m_titleLabel;
    QTimer* m_timer;
};
