#pragma once

#include "FluWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include "../FluUtils/FluUtils.h"

class FluHFlipView : public QScrollArea
{
    Q_OBJECT
  public:
    FluHFlipView(QWidget* parent = nullptr);

    void addPixmap(QPixmap pixmap);

    void hideOrShowRLBtn(bool bEnter)
    {
        if (bEnter)
        {
            m_lBtn->show();
            m_rBtn->show();
            if (m_nImgBoxIndex == 0)
                m_lBtn->hide();

            if (m_nImgBoxIndex == m_hLayout->count() - 1)
                m_rBtn->hide();
        }
        else
        {
            m_lBtn->hide();
            m_rBtn->hide();
        }
    }

    void enterEvent(QEnterEvent* event)
    {
        hideOrShowRLBtn(true);
    }

    void leaveEvent(QEvent* event)
    {
        hideOrShowRLBtn(false);
    }

    void resizeEvent(QResizeEvent* event)
    {
        QScrollArea::resizeEvent(event);
        // fixed pos
        // get height
        // get width

        int nH = height();
        int nW = width();

        int nLY = nH / 2 - m_lBtn->height() / 2;
        int nLX = 5;

        m_lBtn->move(nLX, nLY);

        int nRX = nW - m_lBtn->width() - 5;
        int nRY = nH / 2 - m_lBtn->height() / 2;
        m_rBtn->move(nRX, nRY);
    }

  protected:
    QWidget* m_contextWidget;
    QHBoxLayout* m_hLayout;

    QPushButton* m_lBtn;
    QPushButton* m_rBtn;

    int m_nImgBoxIndex;
};
