#pragma once

#include "FluWidget.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QColor>
#include "../utils/FluUtils.h"

class FluProgressRing : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(double animValue READ getAnimValue WRITE setAnimValue)
    Q_PROPERTY(double workAngle READ getWorkAngle WRITE setWorkAngle)
    Q_PROPERTY(QColor progressColor READ getProgressColor WRITE setProgressColor)
    Q_PROPERTY(QColor trackColor READ getTrackColor WRITE setTrackColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

  public:
    FluProgressRing(QWidget* parent = nullptr);

    ~FluProgressRing();

    void paintEvent(QPaintEvent* event);

    QColor getProgressColor() const;
    void setProgressColor(const QColor& color);

    QColor getTrackColor() const;
    void setTrackColor(const QColor& color);

    QColor getTextColor() const;
    void setTextColor(const QColor& color);

    void setMinMaxValue(int minValue, int maxValue);

    void setCurValue(int curValue);

    int getCurValue();

    bool getWorking();

    void setWorking(bool isWorking);

    void setShowText(bool isShowText);

    bool getShowText();

    bool getTransparentTrack();

    void setTransparentTrack(bool isTransparentTrack);

  public slots:
    void onThemeChanged();

  protected:
    int m_minValue;
    int m_maxValue;
    int m_curValue;

    bool m_isWorking;
    bool m_isShowText;
    bool m_isTransparentTrack;

    QColor m_progressColor;
    QColor m_trackColor;
    QColor m_textColor;

    double m_animValue;
    QPropertyAnimation* m_valueAnim;

    // Indeterminate: continuous rotation angle in [0, 360) driven by QPropertyAnimation.
    double m_workAngle;
    QPropertyAnimation* m_workAngleAnim;

    // Accessors used by QPropertyAnimation.
    double getAnimValue() const
    {
        return m_animValue;
    }
    void setAnimValue(double v)
    {
        m_animValue = v;
        update();
    }
    double getWorkAngle() const
    {
        return m_workAngle;
    }
    void setWorkAngle(double v)
    {
        // 360 wraps to 0 which is the same angle, so no visual jump.
        m_workAngle = (v >= 360.0) ? v - 360.0 : v;
        update();
    }
};