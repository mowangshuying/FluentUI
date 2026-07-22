#pragma once

#include "FluWidget.h"
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QListWidgetItem>

#include "../Utils/FluUtils.h"
#include "FluWidget.h"

#include <QStyleOption>
#include <QPainter>

class FluAmPmView : public FluWidget
{
    Q_OBJECT
  public:
    FluAmPmView(int fixedWidth = 80, QWidget* parent = nullptr);

    QString getCurrentText();

    void setAmPm(QString am, QString pm);

    bool isAm();

    void setAm(bool bAm);

    void scrollUp();

    void scrollDown();

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void wheelEvent(QWheelEvent* e);

    void keyPressEvent(QKeyEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void currentItemChanged();
  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_mainLayout;
    QListWidget* m_amPmListView;

    QPushButton* m_scrollDownButton;
    QPushButton* m_scrollUpButton;

    bool m_isAm;
    int m_fixedWidth;
};
