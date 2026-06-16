#pragma once

#include "FluRoundMenu.h"
#include <QEvent>

class FluAutoSuggestBox;
class FluCompleterMenu : public FluRoundMenu
{
    Q_OBJECT
  public:
    FluCompleterMenu(FluAutoSuggestBox* autoSuggestBox, QWidget* parent = nullptr);
    FluCompleterMenu(QString title, FluAwesomeType iconType, QWidget* parent = nullptr);

    // update actions;
    void updateActions(std::vector<QString> strs);

    void popup(QPoint pos);

  public:
    bool eventFilter(QObject* watched, QEvent* event);

  protected:
    FluAutoSuggestBox* m_autoSuggestBox;
};
