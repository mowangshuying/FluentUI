#pragma once

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QEvent>
#include "../utils/FluUtils.h"

class FluToolTip : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double opacity READ getOpacity WRITE setOpacity)

  public:
    enum class Placement
    {
        Top,
        TopLeft,
        TopRight,
        Bottom,
        BottomLeft,
        BottomRight,
        Left,
        Right
    };

    FluToolTip(QWidget* parent = nullptr);
    ~FluToolTip();

    static FluToolTip* setToolTip(QWidget* parent, QWidget* target, const QString& text, Placement placement = Placement::Bottom);

    void setText(const QString& text);
    QString getText() const;

    void setPlacement(Placement placement);
    Placement getPlacement() const;

    void showToolTip();
    void hideToolTip();

    double getOpacity() const;
    void setOpacity(double opacity);

  protected:
    void paintEvent(QPaintEvent*) override;
    void onThemeChanged();
    bool eventFilter(QObject* obj, QEvent* e) override;

  private:
    void reposition();

    QString m_text;
    QWidget* m_target = nullptr;
    QTimer* m_delayTimer = nullptr;
    QTimer* m_durationTimer = nullptr;
    QPropertyAnimation* m_fadeAnim = nullptr;
    double m_opacity = 0.0;
    Placement m_placement = Placement::Bottom;
};
