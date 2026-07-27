#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

#include "../Utils/FluUtils.h"
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
        // m_edit->resize(width() - m_button->width() - m_layout->contentsMargins().left() - m_layout->contentsMargins().right() - 4, m_edit->height());
    }

    void paintEvent(QPaintEvent* event);

    void setEnabled(bool enabled);

  public slots:
    void onThemeChanged();

  protected:
    QLineEdit* m_edit;
    QPushButton* m_button;
    QHBoxLayout* m_layout;

    unsigned int m_maskC;
};
