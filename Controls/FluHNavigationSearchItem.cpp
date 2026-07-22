#include "FluHNavigationSearchItem.h"

FluHNavigationSearchItem::FluHNavigationSearchItem(QWidget* parent /*= nullptr*/) : FluHNavigationItem(parent)
{
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    m_searchLineEdit = new FluSearchLineEdit;
    m_mainLayout->addWidget(m_searchLineEdit);
}
