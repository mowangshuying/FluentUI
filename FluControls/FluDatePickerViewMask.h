#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include "../FluUtils/FluThemeUtils.h"
class FluDatePickerViewMaskItem
{
  public:
    FluDatePickerViewMaskItem(QString text, int width, int height);

  public:
    QString m_text;
    int m_nWidth;
    int m_nHeight;
};

class FluDatePickerViewMask : public QWidget
{
    Q_OBJECT
  public:
    FluDatePickerViewMask(QWidget* parent = nullptr);

    void setBackgroundColorEx(QColor color)
    {
        m_backgroundColorEx = color;
    }
    QColor getBackgroundColorEx()
    {
        return m_backgroundColorEx;
    }

    void setTextColorEx(QColor color)
    {
        m_textColorEx = color;
    }
    QColor getTextColorEx()
    {
        return m_textColorEx;
    }

    void addItem(QString text, int nW, int nH);

    void setItemText(int nIndex, QString text);

    void paintBackground(QPainter& painter);

    void paintText(QPainter& painter);

    // void enterEvent(QEnterEvent* event);

    // void leaveEvent(QEvent* event);

    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void enterChanged(int nIndex, QEnterEvent* event);
    void leaveChanged(int nIndex, QEvent* event);
    void wheelChanged(int nIndex, QWheelEvent* event);

  protected:
    std::vector<FluDatePickerViewMaskItem> m_items;
    int m_nCurIndex;

    QColor m_backgroundColorEx;
    QColor m_textColorEx;
};
