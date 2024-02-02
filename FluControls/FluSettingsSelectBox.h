#pragma once

#include <QWidget>
#include <QLabel>
#include "FluComboBox.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"

class FluSettingsSelectBox : public QWidget
{
    Q_OBJECT
  public:
    FluSettingsSelectBox(QWidget* parent = nullptr);

    FluSettingsSelectBox(FluAwesomeType awesomeType, QWidget* parent = nullptr);

    FluComboBox* getComboBox();

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
    FluComboBox* m_comboBox;
};
