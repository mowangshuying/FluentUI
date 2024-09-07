#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

#include "../FluUtils/FluUtils.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

class FluSearchLineEdit : public FluWidget
{
    Q_OBJECT
  public:
    FluSearchLineEdit(QWidget* parent = nullptr);

    QString getText();

    void setText(QString text);

    void setPlaceholderText(QString text);

    QString getPlaceholderText();

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void onSearchBtnClicked();
  public slots:
    void onThemeChanged();

  protected:
    QLineEdit* m_edit;
    QPushButton* m_btn;
    QHBoxLayout* m_hLayout;
};
