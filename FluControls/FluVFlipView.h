#pragma once

#include "FluWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include "FluImageBox.h"

class FluVFlipView : public QScrollArea
{
    Q_OBJECT
  public:
    FluVFlipView(QWidget* parent = nullptr);

    void addPixmap(QPixmap pixmap);

    void hideOrShowTBBtn(bool bEnter)
    {
        if (bEnter)
        {
            m_tBtn->show();
            m_bBtn->show();
            if (m_nImgBoxIndex == 0)
                m_tBtn->hide();

            if (m_nImgBoxIndex == m_vLayout->count() - 1)
                m_bBtn->hide();
        }
        else
        {
            m_tBtn->hide();
            m_bBtn->hide();
        }
    }

    void enterEvent(QEnterEvent* event)
    {
        hideOrShowTBBtn(true);
    }

    void leaveEvent(QEvent* event)
    {
        hideOrShowTBBtn(false);
    }

    void resizeEvent(QResizeEvent* event)
    {
        QScrollArea::resizeEvent(event);
        int nH = height();
        int nW = width();

        int nLX = nW / 2 - m_tBtn->width() / 2;
        int nLY = 5;
        m_tBtn->move(nLX, nLY);

        int nRX = nW / 2 - m_bBtn->width() / 2;
        int nRY = nH - m_bBtn->height() - 5;
        m_bBtn->move(nRX, nRY);
    }

  protected:
    QWidget* m_contextWidget;
    QVBoxLayout* m_vLayout;

    QPushButton* m_tBtn;
    QPushButton* m_bBtn;

    int m_nImgBoxIndex;
};
