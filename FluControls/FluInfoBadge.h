#pragma once

#include <QLabel>
#include "../FluUtils/FluUtils.h"
#include <QEvent>
#include <QStyle>

enum class FluInfoBadgeLevel
{
    Info,
    Suc,
    Warn,
    Error,
};

class FluInfoBadge : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor badgeColor READ getBadgeColor WRITE setBadgeColor)
  public:
    FluInfoBadge(QWidget* parent = nullptr);

    void setParent(QWidget* parent);

    void setTarget(QWidget* target);

    QWidget* getTarget();

    QColor getBadgeColor();

    void setBadgeColor(QColor color);

    void setLevel(FluInfoBadgeLevel level)
    {
        m_level = level;
        QString levelString;
        switch (level)
        {
            case FluInfoBadgeLevel::Info:
                levelString = "Info";
                break;
            case FluInfoBadgeLevel::Suc:
                levelString = "Suc";
                break;
            case FluInfoBadgeLevel::Warn:
                levelString = "Warn";
                break;
            case FluInfoBadgeLevel::Error:
                levelString = "Error";
                break;
            default:
                break;
        }
        setProperty("level", levelString);
        style()->polish(this);
    }

    bool eventFilter(QObject* watched, QEvent* event);

    static void setInfoBadge(QWidget* parent, QWidget* target, FluInfoBadgeLevel level, int nVlaue = 0);

  public:
    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged()
    {
        FluStyleSheetUitls::setQssByFileName("FluInfoBadge.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    QWidget* m_parent;
    QWidget* m_target;

    QColor m_badgeColor;
    FluInfoBadgeLevel m_level;
};
