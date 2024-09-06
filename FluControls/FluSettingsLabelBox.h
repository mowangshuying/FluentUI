#pragma once

#include "FluWidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>

class FluSettingsLabelBox : public FluWidget
{
    Q_OBJECT
  public:
    FluSettingsLabelBox(QWidget* parent = nullptr);

    void setIcon(QIcon icon);

    void setTitleInfo(QString title, QString info);

    void setVersion(QString version);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_mainLayout;
    QVBoxLayout* m_vLayout;
    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QLabel* m_infoLabel;
    QLabel* m_versionLabel;
};
