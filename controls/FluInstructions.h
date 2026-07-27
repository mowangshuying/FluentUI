#pragma once

#include "FluExpander.h"
#include "../Utils/FluUtils.h"
#include <QVBoxLayout>
#include "FluVSplitLine.h"
#include "FluLabel.h"
#include <vector>
#include <QWidget>

class FluInstructions : public FluExpander
{
    Q_OBJECT
  public:
    FluInstructions(QWidget* parent = nullptr);

    QLabel* getTitleLabel();

    void setTitleLabelText(QString text);

    void addTitleContent(QString title, QString content, bool isAdd = true);

    void addVSplitLine(bool isAdd = true);

    int getAutoH()
    {
        int autoH = 0;
        for (int i = 0; i < getWrap2Layout()->count(); i++)
        {
            auto widget = getWrap2Layout()->itemAt(i)->widget();
            if (widget->objectName() != "wrap2SplitLine")
            {
                auto label = (FluLabel*)widget;
                autoH += label->heightForWidth(m_wrap2->width() - getWrap2Layout()->contentsMargins().left() - getWrap2Layout()->contentsMargins().right());
            }
            else
            {
                autoH += widget->height();
            }

            autoH += getWrap2Layout()->spacing();
        }

        autoH += getWrap2Layout()->contentsMargins().top() + getWrap2Layout()->contentsMargins().bottom();
        return autoH;
    }

    void resizeEvent(QResizeEvent* event);

    void paintEvent(QPaintEvent* event);

  public slots:
    virtual void onClicked();

  protected:
    FluLabel* m_titleLabel;
    QTimer* m_timer;
};
