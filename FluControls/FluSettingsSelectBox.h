#pragma once

#include "FluWidget.h"
#include <QLabel>
#include "FluComboBoxEx.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"

class FluSettingsSelectBox : public FluWidget
{
    Q_OBJECT
  public:
    FluSettingsSelectBox(QWidget* parent = nullptr);

    FluSettingsSelectBox(FluAwesomeType awesomeType, QWidget* parent = nullptr);

    FluComboBoxEx* getComboBox();

    void setIcon(QIcon icon);

    void setIcon(FluAwesomeType awesomeType);

    void setTitleInfo(QString title, QString info);

    void hideInfoLabel();

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_mainLayout;
    QVBoxLayout* m_vLayout;

    FluAwesomeType m_iconAwesomeType;
    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QLabel* m_infoLabel;
    FluComboBoxEx* m_comboBoxEx;
};
