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

  public:
    FluProgressBar(QWidget* parent = nullptr);
    ~FluProgressBar();

    bool isWorking() const;
    void setWorking(bool working);

    void setValue(int value);

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

    bool m_isWorking = false;
    double m_animProgress = 0.0;
    double m_displayValue = 0.0;
    QTimer* m_indetTimer = nullptr;
    QPropertyAnimation* m_valueAnim = nullptr;
};
