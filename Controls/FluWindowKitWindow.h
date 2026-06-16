#pragma once

#include <QWidget>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QHoverEvent>
#include <QTimer>
#include <QScreen>
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <QWKWidgets/widgetwindowagent.h>
#include "FluWindowKitTitleBar.h"
#include "FluLabel.h"
#include "FluWindowkitButton.h"
#include "FluThemeButton.h"
#include <QMainWindow>
#include "FluMenuBar.h"
//#include <QWKWidgets/widgetwindowagent.h>
//#include "QWKWidgets/widgetwindowagent.h"

//class QWK::WidgetWindowAgent;
class FluWindowKitWindow : public QMainWindow
{
    Q_OBJECT
  public:
    FluWindowKitWindow(QWidget *parent = nullptr);

    static void emulateLeaveEvent(QWidget *widget);
  public slots:
    void onThemeChanged();

  protected:
    //QWK::WidgetWindowAgent *agent;
    FluWindowKitTitleBar *m_titleBar;

    FluMenuBar *m_menuBar;
    FluLabel *m_titleLabel;
    FluWindowkitButton *m_iconButton;

    FluThemeButton *m_themeButton;
    FluWindowkitButton *m_pinButton;
    FluWindowkitButton *m_minButton;
    FluWindowkitButton *m_maxButton;
    FluWindowkitButton *m_closeButton;
    //QVBoxLayout *m_vMainLayout;
    //QHBoxLayout *m_contentLayout;
};
