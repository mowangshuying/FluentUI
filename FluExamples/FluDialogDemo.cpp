#include "FluDialogDemo.h"
#include "../FluControls/FluDialog.h"
#include "../FluControls/FluComboBoxEx.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluLineEdit.h"

FluDialogDemo::FluDialogDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    m_contentLayout->setAlignment(Qt::AlignCenter);
    auto btn = new FluPushButton;
    btn->setText(tr("Show Dialog"));

    m_contentLayout->addWidget(btn);

    connect(btn, &FluPushButton::clicked, [=]() {
        FluDialog dlg(window());
        dlg.setWidgetFixedSize(400, 300);

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