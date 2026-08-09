#pragma once

#include "FluWidget.h"
#include "../utils/FluUtils.h"
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>
#include <QEvent>

class FluRatingControl : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(double value READ getValue WRITE setValue NOTIFY valueChanged)
  public:
    explicit FluRatingControl(QWidget* parent = nullptr);

    double getValue() const;
    void setValue(double value);

    bool isReadOnly() const;
    void setReadOnly(bool readOnly);

    bool isClearEnabled() const;
    void setClearEnabled(bool clearEnabled);

  signals:
    void valueChanged(double value);

  protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void leaveEvent(QEvent* event) override;

  public slots:
    void onThemeChanged();

  private:
    double starValueAt(const QPoint& pos) const;
    QPainterPath starPath(const QRectF& rect) const;
    void drawStar(QPainter& painter, const QRectF& rect, double fraction, const QColor& fillColor, const QColor& emptyColor) const;

    double m_value = 0.0;       // 0 ~ maxRating, step 0.5
    double m_hoverValue = -1.0; // -1 = no hover
    bool m_readOnly = false;
    bool m_clearEnabled = true;
    int m_maxRating = 5;
};