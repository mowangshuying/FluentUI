#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QShortcut>
#include <QKeySequence>

#include "../FluUtils/FluUtils.h"

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
  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    FluAwesomeType m_awesomeType;
    QVBoxLayout* m_vMainLayout;
    QPushButton* m_iconBtn;
    QLabel* m_textLabel;

    QShortcut* m_shortCut;
};
