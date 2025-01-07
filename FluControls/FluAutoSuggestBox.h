#pragma once

#include "FluDef.h"
#include "../FluUtils/FluUtils.h"
#include "FluWidget.h"

#include <vector>
#include "FluMenu.h"
// #include "FluRoundMenu.h"
#include "FluCompleterMenu.h"
#include <QLineEdit>
#include <QPushButton>

#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <set>

class FluAutoSuggestBox : public FluWidget
{
    Q_OBJECT
  public:
    FluAutoSuggestBox(bool bSearch = false, QWidget* parent = nullptr);

    void setKeys(std::vector<QString> keys);

    void setKey(QString key);

    void addKeys(std::vector<QString> keys);

    void addKey(QString key);

    void clearKeys();

    QString getText();

    void setText(QString text);

    void setPlaceholderText(QString text);

    QString getPlaceholderText();

    void setSearch(bool bSearch);
    bool getSearch();

    void hockEvent(QEvent* event);

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void searchBtnClicked();
    void currentTextChanged(QString text);
    void currentIndexChanged(int nIndex);

  public slots:

    void onTextEdited(QString text);
    void onThemeChanged();

  protected:
    bool m_bSearch;

    std::vector<QString> m_keys;

    QLineEdit* m_lineEdit;
    QPushButton* m_btn;
    QHBoxLayout* m_hMainLayout;

    FluCompleterMenu* m_completerMenu;
};
