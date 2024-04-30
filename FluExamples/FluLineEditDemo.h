#pragma once

#include <QLineEdit>

#include "../FluControls/FluLineEdit.h"
#include "FluDisplay9.h"
#include "../FluControls/FluSearchLineEdit.h"
#include "../FluControls/FluAutoSuggestBox.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

class FluLineEditDemo : public FluDisplay9
{
    Q_OBJECT
  public:
    FluLineEditDemo(QWidget* parent = nullptr) : FluDisplay9(parent)
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

    void paintEvent(QPaintEvent* paintEvent)
    {
        QWidget::paintEvent(paintEvent);
        QStyleOption opt;
        // opt.init(this);
        opt.initFrom(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }
};
