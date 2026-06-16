#pragma once

#include "FluVNavigationItem.h"
#include "FluAutoSuggestBox.h"
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QStyleOption>
#include <QStyle>
#include <vector>

class FluVNavigationSearchItem : public FluVNavigationItem
{
    Q_OBJECT
  public:
    FluVNavigationSearchItem(QWidget* parent = nullptr);

    void hideSearchButton();

    void hideSearchEdit();

    void updateSearchKeys(std::vector<QString> keys);

    void mouseReleaseEvent(QMouseEvent* event);

    // to enable qss
    void paintEvent(QPaintEvent* event);

  signals:
    void itemClicked();
    void currentTextChanged(QString text);
  public slots:
    void onItemClicked();
    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
    FluAutoSuggestBox* m_autoSuggestBox;
    QPushButton* m_searchButton;
};
