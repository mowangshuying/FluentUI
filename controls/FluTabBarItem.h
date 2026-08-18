#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "../utils/FluUtils.h"
#include <QStyleOption>
#include <QEnterEvent>

class FluTabBarItem : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(int tabWidth READ tabWidth WRITE setTabWidth)
    Q_PROPERTY(bool pressed READ getPressed WRITE setPressed)
  public:
    FluTabBarItem(QWidget* parent = nullptr);

    void setSelected(bool isSel);

    bool getSelected();

    void setText(QString text);

    QString getText();

    int getWidgetWidth();

    void adjustWidgetSize();

    bool getPressed() const;

    void setPressed(bool p);

    int tabWidth();
    void setTabWidth(int w);

    void resizeEvent(QResizeEvent* event);

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    bool eventFilter(QObject* watched, QEvent* event);

  signals:
    void clicked();
    void sizeChanged();
    void clickedCloseButton(FluTabBarItem* item);
    // Kept because FluTabView connects to it; no longer emitted (QSS handles visuals).
    void visualStateChanged();

  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_mainLayout;
    QPushButton* m_iconButton;
    QPushButton* m_textButton;
    QPushButton* m_closeButton;
    bool m_isSel = false;
    bool m_isPressed = false;
    QString m_text;
};