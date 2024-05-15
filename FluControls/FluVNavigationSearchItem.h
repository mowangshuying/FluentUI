#pragma once

#include "FluVNavigationItem.h"
#include "FluSearchLineEdit.h"
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QStyleOption>
#include <QStyle>

class FluVNavigationSearchItem : public FluVNavigationItem
{
    Q_OBJECT
  public:
    FluVNavigationSearchItem(QWidget* parent = nullptr);

    void hideSearchButton()
    {
        m_searchButton->hide();
        m_searchLineEdit->show();
    }

    void hideSearchEdit()
    {
        m_searchButton->show();
        m_searchLineEdit->hide();
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
        FluVNavigationItem::mouseReleaseEvent(event);
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
    FluSearchLineEdit* m_searchLineEdit;
    QPushButton* m_searchButton;
};
