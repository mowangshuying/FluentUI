#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "../utils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include <QEnterEvent>

class FluTabBarItem : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(int tabWidth READ tabWidth WRITE setTabWidth)
  public:
    FluTabBarItem(QWidget* parent = nullptr);

    void setSelected(bool isSel);

    bool getSelected();

    void setText(QString text);

    QString getText();

    int getWidgetWidth();

    void adjustWidgetSize();

    bool getHovered() const;

    bool getPressed() const;

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
    void visualStateChanged();

  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_mainLayout;
    QPushButton* m_iconButton;
    QPushButton* m_textButton;
    QPushButton* m_closeButton;
    bool m_isSel = false;
    bool m_isHover = false;
    bool m_isPressed = false;
    QString m_text;
};
