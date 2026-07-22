#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "FluWindowKitTitleBar.h"
#include "FluLabel.h"
#include "FluWindowkitButton.h"
#include "FluThemeButton.h"

class FluWindowKitWidget : public QWidget
{
    Q_OBJECT
  public:
    FluWindowKitWidget(QWidget *parent = nullptr);

  public slots:
    void onThemeChanged();

  protected:
    FluWindowKitTitleBar *m_titleBar;
    FluLabel *m_titleLabel;
    FluWindowkitButton *m_iconButton;

    FluThemeButton *m_themeButton;
    FluWindowkitButton *m_pinButton;
    FluWindowkitButton *m_minButton;
    FluWindowkitButton *m_maxButton;
    FluWindowkitButton *m_closeButton;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_contentLayout;
};
