#pragma once

#include "FluDef.h"
#include "../Utils/FluUtils.h"
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
    FluAutoSuggestBox(bool isSearch = false, QWidget* parent = nullptr);

    void setKeys(std::vector<QString> keys);

    void setKey(QString key);

    void addKeys(std::vector<QString> keys);

    void addKey(QString key);

    void clearKeys();

    QString getText();

    void setText(QString text);

    void setPlaceholderText(QString text);

    QString getPlaceholderText();

    void setSearch(bool isSearch);
    bool getSearch();

    void hockEvent(QEvent* event);

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event);

    void setEnabled(bool enabled);
  signals:
    void searchButtonClicked();
    void currentTextChanged(QString text);
    void currentIndexChanged(int index);

  public slots:

    void onTextEdited(QString text);
    void onThemeChanged();

  protected:
    bool m_isSearch;

    std::vector<QString> m_keys;

    QLineEdit* m_lineEdit;
    QPushButton* m_searchButton;
    QHBoxLayout* m_mainLayout;

    FluCompleterMenu* m_completerMenu;
};
