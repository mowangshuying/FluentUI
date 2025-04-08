#pragma once

#include "FluWidget.h"
#include "../FluUtils/FluUtils.h"
#include <QHBoxLayout>
#include "FluSegmentedItem.h"
#include <QStyleOption>
#include <QPainter>
#include "FluValueObject.h"
#include <QPropertyAnimation>

class FluSegmented : public FluWidget
{
    Q_OBJECT
  public:
    FluSegmented(QWidget* parent = nullptr) : FluWidget(parent)
    {
        setFixedHeight(32);
        m_hMainLayout = new QHBoxLayout;
        m_hMainLayout->setContentsMargins(1, 1, 1, 1);
        m_hMainLayout->setSpacing(0);
        setLayout(m_hMainLayout);

        m_animation = new QPropertyAnimation;
        m_animation->setPropertyName("value");

        m_valueObject = new FluValueObject;
        m_animation->setTargetObject(m_valueObject);
        m_animation->setStartValue(0);
        m_animation->setEndValue(0);

        m_currentItem = nullptr;
        onThemeChanged();
    }

    void setCurrentItem(FluSegmentedItem* item)
    {
        if (m_currentItem != nullptr)
        {
            m_animation->setStartValue(m_currentItem->x());
            m_animation->setEndValue(item->x());
            m_animation->start();
        }

        m_currentItem = item;

        for (int i = 0; i < m_hMainLayout->layout()->count(); i++)
        {
            auto item = (FluSegmentedItem*)m_hMainLayout->layout()->itemAt(i)->widget();
            if (item != nullptr)
            {
                item->setProperty("isSelected", false);
                if (item == m_currentItem)
                {
                    item->setProperty("isSelected", true);
                }
                item->style()->polish(item);
            }
        }
        // m_currentItem->setProperty("isSelected", true);
    }

    void setCurrentItem(QString text)
    {
        for (int i = 0; i < m_hMainLayout->layout()->count(); i++)
        {
            auto item = (FluSegmentedItem*)m_hMainLayout->layout()->itemAt(i)->widget();
            if (item->text() == text)
            {
                setCurrentItem(item);
                break;
            }
        }
    }

    FluSegmentedItem getCurrentItem()
    {
        return m_currentItem;
    }

    void addWidget(FluSegmentedItem* item)
    {
        insertWidget(-1, item);
    }

    void insertWidget(int nIndex, FluSegmentedItem* item)
    {
        connect(item, &FluSegmentedItem::ItemClicked, this, &FluSegmented::onItemClicked);
        m_hMainLayout->insertWidget(nIndex, item);
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

        if (m_currentItem != nullptr)
        {
            if (FluThemeUtils::isLightTheme())
            {
                painter.setPen(Qt::transparent);
                painter.setBrush(QColor(251, 251, 251, 128));

                auto backgroundRect = m_currentItem->rect().adjusted(1, 1, -1, -1).translated(m_animation->currentValue().toFloat(), 0);
                painter.drawRoundedRect(backgroundRect, 4, 4);

                painter.setPen(Qt::NoPen);
                painter.setBrush(QColor(0, 90, 158));
                auto indicatorRect = QRect(m_animation->currentValue().toFloat() + m_currentItem->width() / 2 - 15, height() - 4, 30, 4);
                painter.drawRoundedRect(indicatorRect, 2, 2);
            }
            else if (FluThemeUtils::isDarkTheme())
            {
                painter.setPen(Qt::transparent);
                painter.setBrush(QColor(45, 45, 45, 128));

                auto backgroundRect = m_currentItem->rect().adjusted(1, 1, -1, -1).translated(m_animation->currentValue().toFloat(), 0);
                painter.drawRoundedRect(backgroundRect, 4, 4);

                painter.setPen(Qt::NoPen);
                painter.setBrush(QColor(118, 185, 237));
                auto indicatorRect = QRect(m_animation->currentValue().toFloat() + m_currentItem->width() / 2 - 15, height() - 4, 30, 4);
                painter.drawRoundedRect(indicatorRect, 2, 2);
            }
            update();
        }
    }

  public slots:
    void onItemClicked(FluSegmentedItem* item)
    {
        setCurrentItem(item);
    }

    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSegmented.qss", this);
        }
        else if (FluThemeUtils::isDarkTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSegmented.qss", this);
        }
    }

  protected:
    QHBoxLayout* m_hMainLayout;
    FluSegmentedItem* m_currentItem;

    // ani;
    FluValueObject* m_valueObject;
    QPropertyAnimation* m_animation;
};
