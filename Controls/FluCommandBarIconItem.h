#pragma once

#include "FluCommandBarItem.h"
#include "../Utils/FluUtils.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QStyle>
#include <QPainter>
#include "FluRoundMenu.h"

class FluCommandBarIconItem : public FluCommandBarItem
{
    Q_OBJECT
  public:
    FluCommandBarIconItem(QWidget* parent = nullptr);

    FluCommandBarIconItem(FluAwesomeType type, QWidget* parent = nullptr);

    FluRoundMenu* getRoundMenu();

    void setRoundMenu(FluRoundMenu* menu);

    void showAtBottomLeft();
    void showAtBottomRight();

    void showAtBottomCenter();

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);

    QString qssFileName() override
    {
        return "FluCommandBarIconItem.qss";
    }

  signals:
    void clicked();

  protected:
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_iconBtn;
    FluAwesomeType m_awesomeType;

    FluRoundMenu* m_roundMenu;
};
