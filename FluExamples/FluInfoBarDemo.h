#pragma once

#include "../FluControls/FluShortInfoBar.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluInfoBarMgr.h"

class FluInfoBarDemo : public QWidget
{
    // Q_OBJECT
  public:
    FluInfoBarDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        // auto vLayout = new QVBoxLayout;
        // setLayout(vLayout);

        //  vLayout->setContentsMargins(20, 20, 20, 20);

        //  auto sInfoBar1 = new FluShortInfoBar(FluShortInfoBarType::Info);
        //  vLayout->addWidget(sInfoBar1);

        //  auto sInfoBar2 = new FluShortInfoBar(FluShortInfoBarType::Suc);
        //  vLayout->addWidget(sInfoBar2);

        //  auto sInfoBar3 = new FluShortInfoBar(FluShortInfoBarType::Warn);
        //   vLayout->addWidget(sInfoBar3);

        //  auto sInfoBar4 = new FluShortInfoBar(FluShortInfoBarType::Error);
        //    vLayout->addWidget(sInfoBar4);

        auto clickBtn = new FluPushButton(this);
        clickBtn->setText("Clicked me!");
        // clickBtn->move(300 - clickBtn->width() / 2, 200 - clickBtn->height() / 2);

        connect(clickBtn, &FluPushButton::clicked, [=]() {
            FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Info, this);
            FluInfoBarMgr::getInstance()->addInfoBar(this, sInfoBar);
        });

        resize(600, 400);
        clickBtn->move(300 - clickBtn->width() / 2, 200 - clickBtn->height() / 2);
    }
};
