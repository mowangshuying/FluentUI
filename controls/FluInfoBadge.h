#pragma once

#include <QLabel>
#include "../utils/FluUtils.h"
#include <QEvent>
#include <QStyle>
#include <QPropertyAnimation>

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
    Q_PROPERTY(qreal animScale READ getAnimScale WRITE setAnimScale)

  public:
    enum class AnimState
    {
        Idle,
        Scaling,
    };

    ~FluInfoBadge();

    void setTarget(QWidget* target);
    QWidget* getTarget() const;

    QColor getBadgeColor() const;
    void setBadgeColor(QColor color);

    int getValue() const;
    void setValue(int value);

    FluInfoBadgeLevel getLevel() const;
    void setLevel(FluInfoBadgeLevel level);

    qreal getAnimScale() const;
    void setAnimScale(qreal scale);

    bool eventFilter(QObject* watched, QEvent* event) override;

    static FluInfoBadge* setInfoBadge(QWidget* parent, QWidget* target, FluInfoBadgeLevel level, int value = 0);

  public:
    void paintEvent(QPaintEvent* event) override;

  public slots:
    void onThemeChanged()
    {
        FluStyleSheetUtils::setQssByFileName("FluInfoBadge.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    void reposition();
    void updateText();
    void updateVisibility();
    void updateLevelProperty();

  private:
    FluInfoBadge(QWidget* parent = nullptr);

    QWidget* m_target = nullptr;
    QColor m_badgeColor;
    FluInfoBadgeLevel m_level = FluInfoBadgeLevel::Error;
    int m_value = 0;

    qreal m_animScale = 1.0;
    QPropertyAnimation* m_valueAnimation = nullptr;
};
