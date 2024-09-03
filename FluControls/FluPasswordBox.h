#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

#include "../FluUtils/FluUtils.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

class FluPasswordBox : public FluWidget
{
    Q_OBJECT
  public:
    FluPasswordBox(QWidget* parent = nullptr);

    void setMaskC(unsigned maskC);

    bool eventFilter(QObject* watched, QEvent* event);

    void resizeEvent(QResizeEvent* event)
    {
        // m_edit->resize(width() - m_btn->width() - m_hLayout->contentsMargins().left() - m_hLayout->contentsMargins().right() - 4, m_edit->height());
    }

    void paintEvent(QPaintEvent* event);

  public slots:
    void onThemeChanged();

  protected:
    QLineEdit* m_edit;
    QPushButton* m_btn;
    QHBoxLayout* m_hLayout;

    unsigned int m_maskC;
};
