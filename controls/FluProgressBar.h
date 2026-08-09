#pragma once

#include <QProgressBar>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QTimer>

#include "../utils/FluUtils.h"

class FluProgressBar : public QProgressBar
{
    Q_OBJECT
    Q_PROPERTY(double animProgress READ getAnimProgress WRITE setAnimProgress)
    Q_PROPERTY(double determinateOpacity READ getDeterminateOpacity WRITE setDeterminateOpacity)

  public:
    enum class State { Normal, Paused, Error };

    FluProgressBar(QWidget* parent = nullptr);
    ~FluProgressBar();

    bool isWorking() const;
    void setWorking(bool working);

    void setValue(int value);

    void setState(State state);
    State getState() const;

  protected:
    void paintEvent(QPaintEvent* event) override;

  protected:
    void onThemeChanged();

  private:
    double getAnimProgress() const
    {
        return m_animProgress;
    }
    void setAnimProgress(double v)
    {
        m_animProgress = v;
        update();
    }

    double getDeterminateOpacity() const;
    void setDeterminateOpacity(double v);

    bool m_isWorking = false;
    double m_animProgress = 0.0;
    double m_displayValue = 0.0;
    QTimer* m_indetTimer = nullptr;
    QPropertyAnimation* m_valueAnim = nullptr;

    State m_state = State::Normal;

    // Indeterminate dual chunks (WinUI3 spec)
    double m_chunk1Pos = 0.0;  // [0, 1] normalized position
    double m_chunk2Pos = 0.0;  // [0, 1] normalized position
    int m_animCycle = 0;       // animation cycle counter

    // State transition fade
    double m_determinateOpacity = 1.0;
    double m_indeterminateOpacity = 0.0;
    QPropertyAnimation* m_fadeAnim = nullptr;
};
