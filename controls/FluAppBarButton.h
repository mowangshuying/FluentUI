#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QShortcut>
#include <QKeySequence>

#include "../Utils/FluUtils.h"

class FluAppBarButton : public FluWidget
{
    Q_OBJECT
  public:
    FluAppBarButton(FluAwesomeType awesomeType, QWidget* parent = nullptr);

    void setAwesomeType(FluAwesomeType awesomeType);

    FluAwesomeType getAwesomeType();

    void setText(QString text);

    QString getText();

    void setShortCut(QKeySequence keySequence);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);

    void setEnabled(bool enabled);
  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    FluAwesomeType m_awesomeType;
    QVBoxLayout* m_mainLayout;
    QPushButton* m_iconButton;
    QLabel* m_textLabel;

    QShortcut* m_shortCut;
};
