#include "FluInfoBarDemo.h"

FluInfoBarDemo::FluInfoBarDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto infoBtn = new FluPushButton(this);
    infoBtn->setText("Clicked me! Info!");
    infoBtn->move(50, 50);

    auto sucBtn = new FluPushButton(this);
    sucBtn->setText("Clicked me! Suc!");
    sucBtn->move(50, 100);

    auto warnBtn = new FluPushButton(this);
    warnBtn->setText("Clicked me! Warn!");
    warnBtn->move(50, 150);

    auto errorBtn = new FluPushButton(this);
    errorBtn->setText("Clicked me! Error!");
    errorBtn->move(50, 200);

    connect(infoBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluShortInfoBarType::Info, "This is an informational message."); });
    connect(sucBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluShortInfoBarType::Suc, "This is an success message."); });
    connect(warnBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluShortInfoBarType::Warn, "This is an warn message."); });
    connect(errorBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluShortInfoBarType::Error, "This is an error message."); });

    resize(600, 400);
}
