#pragma once

#include "FluWidget.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QEnterEvent>
#include "../utils/FluUtils.h"

enum class TextPosition
{
    Left,
    Right,
};

enum class SwitchSize
{
    Normal,   // Default, full size
    Medium,   // 0.8x Normal
    Small,    // 0.6x Normal
};

class FluToggleSwitch : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY checkedChanged)
    Q_PROPERTY(QString text READ getText WRITE setText)
    Q_PROPERTY(QString onText READ getOnText WRITE setOnText)
    Q_PROPERTY(QString offText READ getOffText WRITE setOffText)
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)
    Q_PROPERTY(QColor fillColor READ getFillColor WRITE setFillColor)
    Q_PROPERTY(QColor fillColorOn READ getFillColorOn WRITE setFillColorOn)
    Q_PROPERTY(QColor knobColor READ getKnobColor WRITE setKnobColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    // Animation property
    Q_PROPERTY(qreal knobX READ getKnobX WRITE setKnobX)

  public:
    FluToggleSwitch(QWidget* parent = nullptr);
    FluToggleSwitch(const QString& text, QWidget* parent = nullptr);

    // -- State --
    bool isChecked() const;
    void setChecked(bool checked);
    void toggle();

    // -- Text --
    QString getText() const;
    void setText(const QString& text);
    QString getOnText() const;
    void setOnText(const QString& text);
    QString getOffText() const;
    void setOffText(const QString& text);
    void setOnOffText(const QString& onText, const QString& offText);
    bool isEmptyText() const;
    void setEmptyText(bool empty);

    // -- Layout --
    TextPosition getTextPosition() const;
    void setTextPosition(TextPosition pos);

    // -- Size --
    SwitchSize getSize() const;
    void setSize(SwitchSize size);

    // -- Colors --
    QColor getBorderColor() const;
    void setBorderColor(QColor color);
    QColor getFillColor() const;
    void setFillColor(QColor color);
    QColor getFillColorOn() const;
    void setFillColorOn(QColor color);
    QColor getKnobColor() const;
    void setKnobColor(QColor color);
    QColor getTextColor() const;
    void setTextColor(QColor color);

    // -- Animation property --
    qreal getKnobX() const;
    void setKnobX(qreal x);

    // -- Backward compatibility aliases --
    inline bool getChecked() const { return isChecked(); }

  signals:
    void checkedChanged(bool checked);
    void toggled(bool checked);

  public slots:
    void onThemeChanged() override;

  protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

  private:
    void updateSize();
    void startKnobAnimation(qreal targetX);
    int getTrackWidth() const;
    int getTrackHeight() const;
    void updateMetrics();       // Recalculate all size-dependent metrics based on m_size
    qreal scaleFactor() const;  // Get scaling factor for current size
    qreal scaleDim(int baseDim) const;  // Scale a base dimension by current size factor

  protected:
    bool m_checked = false;
    QString m_text;
    QString m_onText;
    QString m_offText;
    bool m_emptyText = true;
    TextPosition m_textPosition = TextPosition::Right;

    // Colors
    QColor m_borderColor;
    QColor m_fillColor;
    QColor m_fillColorOn;
    QColor m_knobColor;
    QColor m_textColor;

    // Animation
    qreal m_knobX = kKnobOffX;
    qreal m_knobRadius = kKnobRadius;
    QPropertyAnimation* m_knobAnimation = nullptr;

    // Size state
    SwitchSize m_size = SwitchSize::Medium;

    // Dynamic metrics (recalculated when size changes)
    qreal m_actualKnobOffX = kKnobOffX;
    qreal m_actualKnobOnX = kKnobOnX;
    qreal m_actualTrackWidth = kTrackWidth;
    qreal m_actualTrackHeight = kTrackHeight;

    // Interaction
    bool m_isHovered = false;
    bool m_isPressed = false;

    // Constants
    static constexpr int kTrackWidth = 44;
    static constexpr int kTrackHeight = 22;
    static constexpr int kKnobRadius = 7;
    static constexpr int kKnobRadiusHover = 8;
    static constexpr int kKnobOffX = kKnobRadius;
    static constexpr int kKnobOnX = kTrackWidth - kKnobRadius;
    static constexpr int kTextGap = 8;
    static constexpr int kMinHeight = kTrackHeight;
};
