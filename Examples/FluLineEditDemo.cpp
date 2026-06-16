#include "FluLineEditDemo.h"

FluLineEditDemo::FluLineEditDemo(QWidget* parent /*= nullptr*/) : FluDisplay16(parent)
{
    auto lineEdit = new FluLineEdit(this);
    lineEdit->setFixedSize(120, 30);
    addDemo(lineEdit);

    auto sLineEdit = new FluSearchLineEdit;
    //  sLineEdit->setFixedSize(120, 30);
    sLineEdit->setFixedSize(180, 30);
    addDemo(sLineEdit);

    auto suggestBox = new FluAutoSuggestBox;
    suggestBox->setKeys({"aa", "ab", "ac"});
    suggestBox->setFixedSize(180, 30);
    addDemo(suggestBox);
}

void FluLineEditDemo::paintEvent(QPaintEvent* paintEvent)
{
    QWidget::paintEvent(paintEvent);
    QStyleOption opt;
    // opt.init(this);
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
