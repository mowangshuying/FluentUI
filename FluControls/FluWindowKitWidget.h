#pragma once

#include <QWidget>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QHoverEvent>
#include <QTimer>
#include <QScreen>
#include <QVBoxLayout>
#include <QHBoxLayout>

class FluWindowKitWidget : public QWidget
{
  public:
    FluWindowKitWidget(QWidget *parent = nullptr);

    static void emulateLeaveEvent(QWidget *widget);

  protected:
    QVBoxLayout *m_vMainLayout;
    QHBoxLayout *m_contentLayout;
};
