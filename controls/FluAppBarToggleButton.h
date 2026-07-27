#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>

#include "../Utils/FluUtils.h"

class FluAppBarToggleButton : public FluWidget
{
    Q_OBJECT
  public:
    FluAppBarToggleButton(FluAwesomeType awesomeType, QWidget* parent = nullptr);

    void updateIcon();

    void setAwesomeType(FluAwesomeType awesomeType);

    FluAwesomeType getAwesomeType();

    void setText(QString text);

    QString getText();

    void setToggled(bool isToggled);

    bool getToggled();

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);

    void setEnabled(bool enabled);
  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    bool m_isToggled;
    FluAwesomeType m_awesomeType;
    QVBoxLayout* m_mainLayout;
    QPushButton* m_iconButton;
    QLabel* m_textLabel;
};
