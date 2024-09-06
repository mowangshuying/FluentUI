#pragma once

#include "FluExpander.h"
#include "../FluUtils/FluUtils.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "FluVSplitLine.h"

class FluSettingsVersionBox : public FluExpander
{
    Q_OBJECT
  public:
    FluSettingsVersionBox(QWidget* parent = nullptr);

    QLabel* getTitleLabel();

    QLabel* getInfoLabel();

    QLabel* getVersionLabel();

    QLabel* getIconLabel();

    void addVSplitLine();

    void addWidget(QWidget* widget);
  public slots:
    void onThemeChanged();

  protected:
    FluAwesomeType m_iconAwesomeType;
    QVBoxLayout* m_vLayout;

    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QLabel* m_infoLabel;
    QLabel* m_versionLabel;
};
