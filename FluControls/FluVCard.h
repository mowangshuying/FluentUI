#pragma once

#include "FluWidget.h"
#include "../FluUtils/FluStyleSheetUitls.h"
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include "../FluUtils/FluUtils.h"

class FluVCard : public FluWidget
{
    Q_OBJECT
  public:
    FluVCard(QWidget* parent = nullptr);

    FluVCard(QPixmap icon, QString titleText, QString contextText, QWidget* parent = nullptr);

    void setIcon(QPixmap icon);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QLabel* m_contextLabel;
};
