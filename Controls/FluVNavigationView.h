#pragma once

#include "../Utils/FluIconUtils.h"
#include "../Utils/FluLogUtils.h"
#include "../Utils/FluUtils.h"
#include "../Utils/FluStyleSheetUtils.h"
#include "FluDef.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QScrollArea>
#include <QStyleOption>
#include <QTransform>
#include <QVBoxLayout>
#include "FluWidget.h"
#include "FluVScrollView.h"
#include <QPropertyAnimation>
#include "FluValueObject.h"

class FluVNavigationItem;
class FluVNavigationIconTextItem;
class FluVNavigationMenuItem;
class FluVNavigationSearchItem;
class FluVNavigationView : public FluWidget
{
    Q_OBJECT
  public:
    FluVNavigationView(QWidget *parent = nullptr);

    void setOnlyCollapseView(bool isHideMenuAndSearch);

    void addItemToTopLayout(QWidget *item);

    void addItemToMidLayout(QWidget *item);

    void addItemToBottomLayout(QWidget *item);

    void clearAllItemsSelectState();
    void updateAllItemsStyleSheet();

    void setLong(bool b)
    {
        m_isLong = b;
    }

    bool isLong()
    {
        return m_isLong;
    }

    void setViewWidth(int width);

    int getViewWidth()
    {
        return m_viewWidth;
    }

    std::vector<FluVNavigationItem *> getAllItems();
    std::vector<QString> getAllItemsKeys();
    FluVNavigationItem *getItemByKey(QString key);

    std::vector<QString> getAllItemsTexts();
    FluVNavigationItem *getItemByText(QString text);
    void updateSearchKeys();

    void hideMenuItem();
    void showMenuItem();

    void hideSearchItem();
    void showSearchItem();

    void expandView();

    void collapseView();

    void collapseDownView();

    void resizeEvent(QResizeEvent *event);

    void paintEvent(QPaintEvent *event) override;
  signals:
    void searchKeyChanged(QString key);
    void keyChanged(QString key);
  public slots:
    void onMenuItemClicked();
    void onThemeChanged();

  protected:
    QVBoxLayout *m_layout;

    QWidget *m_topWrapWidget;
    FluVScrollView *m_midVScrollView;
    QWidget *m_bottomWrapWidget;

    QVBoxLayout *m_topWrapLayout;
    QVBoxLayout *m_bottomLayout;

    FluVNavigationMenuItem *m_menuButtonItem;
    FluVNavigationSearchItem *m_searchItem;
    bool m_isLong;

    // view width
    int m_viewWidth;

    // animation;
    QPropertyAnimation *m_animation;
    FluValueObject *m_valueObject;
};
