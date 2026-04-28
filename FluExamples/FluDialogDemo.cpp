#include "FluDialogDemo.h"
#include "../FluControls/FluDialog.h"
#include "../FluControls/FluComboBoxEx.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluLineEdit.h"

FluDialogDemo::FluDialogDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    /*FluDialog dlg;
    auto comboxBox = new FluComboBoxEx;
    comboxBox->addItem(tr("Option 1"));
    comboxBox->addItem(tr("Option 2"));
    comboxBox->addItem(tr("Option 3"));*/

    auto btn = new FluPushButton;
    btn->setText(tr("Show Dialog"));

    m_contentLayout->addWidget(btn);

    connect(btn, &FluPushButton::clicked, [=]() {
        FluDialog dlg(window());
        //dlg.resize(400, 300);
        dlg.getWidget()->setFixedSize(400, 300);
        //auto comboxBox = new FluComboBoxEx;
        //comboxBox->addItem(tr("Option 1"));
        //comboxBox->addItem(tr("Option 2"));
        //comboxBox->addItem(tr("Option 3"));

        {
            auto hLayout = new QHBoxLayout;
            auto label = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
            label->setFixedWidth(80);
            label->setText("httpurl:");
            auto lineEdit = new FluLineEdit;
            lineEdit->setFixedHeight(30);
            lineEdit->setPlaceholderText("Please input url");
            hLayout->addWidget(label);
            hLayout->addWidget(lineEdit);
            dlg.getContentWidgetLayout()->addLayout(hLayout);
        }

        {
            auto hLayout = new QHBoxLayout;
            auto label = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
            label->setFixedWidth(80);
            label->setText("token:");
            auto lineEdit = new FluLineEdit;
            lineEdit->setFixedHeight(30);
            lineEdit->setPlaceholderText("Please input token");
            hLayout->addWidget(label);
            hLayout->addWidget(lineEdit);
            dlg.getContentWidgetLayout()->addLayout(hLayout);
        }

        {
            auto hLayout = new QHBoxLayout;
            auto label = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
            label->setFixedWidth(80);
            label->setText("sourceLang:");

            auto comboxBox = new FluComboBoxEx;

            hLayout->addWidget(label);
            hLayout->addWidget(comboxBox);
            dlg.getContentWidgetLayout()->addLayout(hLayout);
        }

        
        {
            auto hLayout = new QHBoxLayout;
            auto label = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
            label->setFixedWidth(80);
            label->setText("destLang:");

            auto comboxBox = new FluComboBoxEx;

            hLayout->addWidget(label);
            hLayout->addWidget(comboxBox);
            dlg.getContentWidgetLayout()->addLayout(hLayout);
        }



        //dlg.getContentWidgetLayout()->addWidget(comboxBox);
        dlg.exec();
    });

}