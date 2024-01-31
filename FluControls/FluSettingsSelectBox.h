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

    FluComboBox* getComboBox()
    {
        return m_comboBox;
    }

    void setIcon(QIcon icon);

    void setTitleInfo(QString title, QString info);

    void hideInfoLabel()
    {
        m_infoLabel->hide();
    }

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSettingsSelectBox.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSettingsSelectBox.qss", this);
        }
    }
  protected:
    QHBoxLayout* m_mainLayout;
    QVBoxLayout* m_vLayout;
    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QLabel* m_infoLabel;
    FluComboBox* m_comboBox;
};
