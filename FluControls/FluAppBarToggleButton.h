#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>

#include "../FluUtils/FluUtils.h"

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

    void setToggled(bool bToggled);

    bool getToggled();

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    bool m_bToggled;
    FluAwesomeType m_awesomeType;
    QVBoxLayout* m_vMainLayout;
    QPushButton* m_iconBtn;
    QLabel* m_textLabel;
};
