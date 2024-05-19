#pragma once

#include "FluHNavigationItem.h"
#include "FluSearchLineEdit.h"
#include <QHBoxLayout>
class FluHNavigationSearchItem : public FluHNavigationItem
{
    Q_OBJECT
  public:
    FluHNavigationSearchItem(QWidget* parent = nullptr) : FluHNavigationItem(parent)
    {
        m_hMainLayout = new QHBoxLayout;
        setLayout(m_hMainLayout);
        m_hMainLayout->setContentsMargins(0, 0, 0, 0);

        m_searchLineEdit = new FluSearchLineEdit;
        m_hMainLayout->addWidget(m_searchLineEdit);
    }

  protected:
    QHBoxLayout* m_hMainLayout;
    FluSearchLineEdit* m_searchLineEdit;
};
