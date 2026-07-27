#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

#include "../Utils/FluUtils.h"
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

    void setEnabled(bool enabled);
  signals:
    void onSearchButtonClicked();
  public slots:
    void onThemeChanged();

  protected:
    QLineEdit* m_edit;
    QPushButton* m_button;
    QHBoxLayout* m_layout;
};
