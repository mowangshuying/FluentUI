#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include "../FluUtils/FluThemeUtils.h"

class FluTimePickerViewMaskItem
{
  public:
    FluTimePickerViewMaskItem(QString text, int width, int height)
    {
        m_text = text;
        m_nWidth = width;
        m_nHeight = height;
    }

  public:
    QString m_text;
    int m_nWidth;
    int m_nHeight;
};

class FluTimePickerViewMask : public QWidget
{
  public:
    FluTimePickerViewMask(QWidget* parent = nullptr) : QWidget(parent)
    {
    }

    void addItem(QString text, int nW, int nH)
    {
        FluTimePickerViewMaskItem item(text, nW, nH);
        m_items.push_back(item);
    }

    void setItemText(int nIndex, QString text)
    {
        m_items[nIndex].m_text = text;
    }

    void paintBackground(QPainter& painter)
    {
        QColor backgroundColor;
        if (FluThemeUtils::isLightTheme())
        {
            backgroundColor = QColor(0, 90, 158);
        }
        else if (FluThemeUtils::isDarkTheme())
        {
            backgroundColor = QColor(118, 185, 237);
        }

        painter.setPen(Qt::NoPen);
        painter.setBrush(backgroundColor);
        painter.drawRoundedRect(rect().adjusted(4, 0, -4, 0), 4, 4);
    }

    void paintText(QPainter& painter)
    {
        QColor textColor;
        if (FluThemeUtils::isLightTheme())
            textColor = Qt::white;
        else if (FluThemeUtils::isDarkTheme())
            textColor = Qt::black;

        painter.setPen(textColor);

        int nX = 0;
        int nY = 0;
        for (auto item : m_items)
        {
            painter.drawText(QRect(nX, nY, item.m_nWidth, item.m_nHeight), Qt::AlignCenter, item.m_text);
            nX += item.m_nWidth;
        }
    }

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
        painter.setPen(Qt::NoPen);

        paintBackground(painter);

        paintText(painter);
    }

  protected:
    std::vector<FluTimePickerViewMaskItem> m_items;
};
