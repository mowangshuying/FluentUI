#pragma once

#include "FluWidget.h"
#include <QLabel>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QStyleOption>
#include <QPainter>
#include "../FluUtils/FluUtils.h"

#include "../FluUtils/FluStyleSheetUitls.h"
class FluHCard : public FluWidget
{
    Q_OBJECT
  public:
    FluHCard(QWidget* parent = nullptr);

    FluHCard(QPixmap icon, QString titleText, QString contextText, QWidget* parent = nullptr);

    void setKey(QString key);

    QString getKey();

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);

  signals:
    void clicked(QString key);
  public slots:
    void onThemeChanged();

  protected:
    QString m_key;
    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QLabel* m_contextLabel;
};
