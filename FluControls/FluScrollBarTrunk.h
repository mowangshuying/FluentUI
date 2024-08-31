#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPainter>
#include "FluScrollBarArrowButton.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

class FluScrollBarTrunk : public QWidget
{
    Q_OBJECT
  public:
    FluScrollBarTrunk(Qt::Orientation orientation = Qt::Orientation::Vertical, QWidget* parent = nullptr);

    void init(Qt::Orientation orientation);

    void initVertical(Qt::Orientation orientation);

    void initHorizontal(Qt::Orientation orientation);

    void initOpacityAnimation();

    FluScrollBarArrowButton* getPreBtn();

    FluScrollBarArrowButton* getLstBtn();

    void setHandleBackgoundColor(QColor color);

    QColor getHandleBackgoundColor();

    QPropertyAnimation* getAnimation()
    {
        return m_animation;
    }

    QGraphicsOpacityEffect* getEffect()
    {
        return m_effect;
    }

    void expandTrunk();

    void collapseTrunk();

  public:
    void drawHandleBackground(QPainter* painter);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    QColor m_handleBackgoundColor;
    FluScrollBarArrowButton* m_preBtn;
    FluScrollBarArrowButton* m_lstBtn;

    QLayout* m_Layout;

    QGraphicsOpacityEffect* m_effect;
    QPropertyAnimation* m_animation;
};
