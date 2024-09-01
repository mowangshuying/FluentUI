#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "FluMenu.h"
#include <QIcon>

class FluComboBoxEx : public FluWidget
{
    Q_OBJECT
  public:
    FluComboBoxEx(QWidget* parent = nullptr);

    QPushButton* getTextBtn();

    QPushButton* getIconBtn();

    void setIcon(FluAwesomeType type);

    void setText(QString text);

    void addItem(QString text);

    void addItem(FluAwesomeType type, QString text);

    void addTextItem(QString text);

    void addIconTextItem(FluAwesomeType type, QString text);

    void mouseReleaseEvent(QMouseEvent* e);

    void paintEvent(QPaintEvent* event);
  signals:
    void clicked();
    void currentTextChanged(QString text);
    void currentIndexChanged(int nIndex);
  public slots:
    void onThemeChanged();

  protected:
    QPushButton* m_textBtn;
    QPushButton* m_iconBtn;  // dropdown button;

    FluAwesomeType m_textAwesomeType;
    //  FluAwesomeType* m_iconAwesomeType;

    QHBoxLayout* m_hMainLayout;
    FluMenu* m_menu;

    //  QString m_sText;
};
