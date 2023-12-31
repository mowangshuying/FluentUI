#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"

FluAEmptyPage::FluAEmptyPage(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    setLayout(mainLayout);

    auto textLabel = new QLabel;
    textLabel->setObjectName("textLabel");
    textLabel->setText("A Empty Page!");

    mainLayout->addWidget(textLabel);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light.qss", this);
}
