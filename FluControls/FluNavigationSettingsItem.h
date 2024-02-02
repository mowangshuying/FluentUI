#pragma once

#include "FluNavigationItem.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include "FluRotationButton.h"
#include "../FluUtils/FluUtils.h"

class FluNavigationSettingsItem : public FluNavigationItem
{
    Q_OBJECT
  public:
    FluNavigationSettingsItem(QIcon icon, QString text, QWidget* parent = nullptr);

    FluNavigationSettingsItem(FluAwesomeType awesomeType, QString text, QWidget* parent);

    void updateAllItemsStyleSheet()
    {
        updateItemsStyleSheet();
    }

    void updateItemsStyleSheet()
    {
        style()->polish(this);
        m_indicator->style()->polish(m_indicator);
        m_icon->style()->polish(m_icon);
        m_label->style()->polish(m_label);
    }

    void updateSelected(bool b)
    {
        m_bSelected = b;
        setProperty("selected", b);
        m_indicator->setProperty("selected", b);
        m_label->setProperty("selected", b);
    }

    void clearAllItemsSelectState()
    {
        updateSelected(false);
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
        FluNavigationItem::mouseReleaseEvent(event);
        emit itemClicked();
    }

    // to enable qss
    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  signals:
    void itemClicked();
  public slots:
    void onItemClicked();
    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
    QWidget* m_indicator;
    FluRotationButton* m_icon;
    QLabel* m_label;

    bool m_bSelected;
};
