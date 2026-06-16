#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <optional>
#include <QMouseEvent>
#include <FramelessHelper/Core/framelesshelpercore_global.h>

// class ChromePalette;
class FluFrameLessTitleBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(Qt::Alignment titleLabelAlignment READ titleLabelAlignment WRITE setTitleLabelAlignment NOTIFY titleLabelAlignmentChanged FINAL)
#ifndef Q_OS_MACOS
    Q_PROPERTY(QPushButton* minimizeButton READ minimizeButton CONSTANT FINAL)
    Q_PROPERTY(QPushButton* maximizeButton READ maximizeButton CONSTANT FINAL)
    Q_PROPERTY(QPushButton* closeButton READ closeButton CONSTANT FINAL)
#endif
    Q_PROPERTY(bool extended READ isExtended WRITE setExtended NOTIFY extendedChanged FINAL)
    Q_PROPERTY(bool hideWhenClose READ isHideWhenClose WRITE setHideWhenClose NOTIFY hideWhenCloseChanged FINAL)

    Q_PROPERTY(bool titleLabelVisible READ titleLabelVisible WRITE setTitleLabelVisible NOTIFY titleLabelVisibleChanged FINAL)
    Q_PROPERTY(QSize windowIconSize READ windowIconSize WRITE setWindowIconSize NOTIFY windowIconSizeChanged FINAL)
    Q_PROPERTY(bool windowIconVisible READ windowIconVisible WRITE setWindowIconVisible NOTIFY windowIconVisibleChanged FINAL)
    Q_PROPERTY(QFont titleFont READ titleFont WRITE setTitleFont NOTIFY titleFontChanged FINAL)
  public:
    struct FontMetrics
    {
        int width = 0;
        int height = 0;
        int ascent = 0;
    };

    FluFrameLessTitleBar(QWidget* parent = nullptr);

    // private d_ptr;
    Q_NODISCARD QRect windowIconRect() const;
    Q_NODISCARD bool windowIconVisible_real() const;
    Q_NODISCARD bool isInTitleBarIconArea(const QPoint& pos) const;

    Q_NODISCARD QFont defaultFont() const;
    Q_NODISCARD FontMetrics titleLabelSize() const;
    Q_NODISCARD int titleLabelMaxWidth() const;

    Q_SLOT void updateMaximizeButton();
    Q_SLOT void updateTitleBarColor();
    Q_SLOT void updateChromeButtonColor();
    Q_SLOT void retranslateUi();

    Q_NODISCARD bool mouseEventHandler(QMouseEvent* event);

    bool eventFilter(QObject* object, QEvent* event) override;

    Q_NODISCARD Qt::Alignment titleLabelAlignment() const;
    void setTitleLabelAlignment(const Qt::Alignment value);

#ifndef Q_OS_MACOS
    Q_NODISCARD QPushButton* minimizeButton() const;
    Q_NODISCARD QPushButton* maximizeButton() const;
    Q_NODISCARD QPushButton* closeButton() const;
#endif  // Q_OS_MACOS

    Q_NODISCARD bool isExtended() const;
    void setExtended(const bool value);

    Q_NODISCARD bool isHideWhenClose() const;
    void setHideWhenClose(const bool value);

    // Q_NODISCARD ChromePalette* chromePalette() const;

    Q_NODISCARD bool titleLabelVisible() const;
    void setTitleLabelVisible(const bool value);

    Q_NODISCARD QSize windowIconSize() const;
    void setWindowIconSize(const QSize& value);

    Q_NODISCARD bool windowIconVisible() const;
    void setWindowIconVisible(const bool value);

    Q_NODISCARD QFont titleFont() const;
    void setTitleFont(const QFont& value);

    virtual void emulateLeaveEvent(QWidget* widget);

  protected:
    void paintEvent(QPaintEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

  Q_SIGNALS:
    void extendedChanged();
    void titleLabelAlignmentChanged();
    void hideWhenCloseChanged();
    void titleLabelVisibleChanged();
    void windowIconSizeChanged();
    void windowIconVisibleChanged();
    void titleFontChanged();
  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_titleBarLayout;
    QVBoxLayout* m_vSystemButtonsOuterLayout;
    QHBoxLayout* m_hSystemButtonsInnerLayout;

    //// icons;
    // QLabel* m_iconLabel;

    //// title;
    // QLabel* m_titleLabel;

    // buttons;
    QPushButton* m_minimizeButton;
    QPushButton* m_maximizeButton;
    QPushButton* m_closeButton;

    bool m_bExtended;
    Qt::Alignment m_labelAlignment = Qt::AlignLeft | Qt::AlignVCenter;
    bool m_bHideWhenClose = false;

    bool m_bTitleLabelVisible = true;
    std::optional<QSize> m_windowIconSize = std::nullopt;
    bool m_bWindowIconVisible = false;
    std::optional<QFont> m_titleFont = std::nullopt;
    bool m_closeTriggered = false;
};
