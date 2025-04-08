#pragma once

#include <QWidget>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QHoverEvent>
#include <QTimer>
#include <QScreen>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "FluWindowKitTitleBar.h"
#include "FluLabel.h"
#include "FluWindowkitButton.h"

class FluWindowKitWidget : public QWidget
{
    Q_OBJECT
  public:
    FluWindowKitWidget(QWidget *parent = nullptr);

    static void emulateLeaveEvent(QWidget *widget);
  public slots:
    void onThemeChanged();

  protected:
    FluWindowKitTitleBar *m_titleBar;
    FluLabel *m_titleLabel;
    FluWindowkitButton *m_iconButton;
    FluWindowkitButton *m_minButton;
    FluWindowkitButton *m_maxButton;
    FluWindowkitButton *m_closeButton;
    QVBoxLayout *m_vMainLayout;
    QHBoxLayout *m_contentLayout;
};
