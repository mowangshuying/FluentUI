#pragma once

#include "FluDef.h"
#include "../FluUtils/FluUtils.h"
#include "FluWidget.h"

#include <vector>
#include "FluMenu.h"

#include <QLineEdit>
#include <QPushButton>

#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>

class FluAutoSuggestBox : public FluWidget
{
    Q_OBJECT
  public:
    FluAutoSuggestBox(QWidget* parent = nullptr);

    void setKeys(std::vector<QString> keys);

    QString getText();

    void setText(QString text);

    void setPlaceholderText(QString text);

    QString getPlaceholderText();

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void searchBtnClicked();

    void currentTextChanged(QString text);
    void currentIndexChanged(int nIndex);

  public slots:
    void onThemeChanged();

  protected:
    std::vector<QString> m_keys;

    QLineEdit* m_lineEdit;
    QHBoxLayout* m_hMainLayout;

    FluMenu* m_completerMenu;
};
