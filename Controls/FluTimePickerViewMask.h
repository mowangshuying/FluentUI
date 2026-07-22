#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include "../Utils/FluThemeUtils.h"
#include <QWheelEvent>

class FluTimePickerViewMaskItem
{
  public:
    FluTimePickerViewMaskItem(QString text, int width, int height);

  public:
    QString m_text;
    int m_width;
    int m_height;
};

class FluTimePickerViewMask : public QWidget
{
    Q_OBJECT
  public:
    FluTimePickerViewMask(QWidget* parent = nullptr);

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

    void addItem(QString text, int w, int h);

    void setItemText(int index, QString text);

    void paintBackground(QPainter& painter);

    void paintText(QPainter& painter);

    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void enterChanged(int index, QEnterEvent* event);
    void leaveChanged(int index, QEvent* event);
    void wheelChanged(int index, QWheelEvent* event);

  protected:
    std::vector<FluTimePickerViewMaskItem> m_items;
    int m_curIndex;

    QColor m_backgroundColorEx;
    QColor m_textColorEx;
};
