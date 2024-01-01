#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>

FluAEmptyPage::FluAEmptyPage(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    setLayout(mainLayout);

    mainLayout->setContentsMargins(35, 35, 35, 35);

    auto titleLabel = new QLabel;
    titleLabel->setObjectName("titleLabel");
    titleLabel->setText("EmptyPage - Tilte");
    mainLayout->addWidget(titleLabel);

  //  auto textLabel = new QLabel;
 //   textLabel->setObjectName("textLabel");
 //   textLabel->setText("A Empty Page!");

  //  mainLayout->addWidget(textLabel);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAEmptyPage.qss", this);
}

void FluAEmptyPage::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
