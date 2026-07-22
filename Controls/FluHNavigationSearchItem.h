#pragma once

#include "FluHNavigationItem.h"
#include "FluSearchLineEdit.h"
#include <QHBoxLayout>
class FluHNavigationSearchItem : public FluHNavigationItem
{
    Q_OBJECT
  public:
    FluHNavigationSearchItem(QWidget* parent = nullptr);

  protected:
    QHBoxLayout* m_mainLayout;
    FluSearchLineEdit* m_searchLineEdit;
};
