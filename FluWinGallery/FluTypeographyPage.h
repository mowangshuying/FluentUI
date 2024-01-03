#pragma once

#include <QWidget>
#include "FluAEmptyPage.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluExpander.h"
#include "../FluControls/FluCodeExpander.h"

// a page to display label demo
class FluTypeographyPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluTypeographyPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_titleLabel->setText("Typography");
        m_mainLayout->setAlignment(Qt::AlignTop);

        auto vScrollView = new FluVScrollView;
        vScrollView->setObjectName("vScrollView");
        m_mainLayout->addWidget(vScrollView);

        vScrollView->getMainLayout()->setAlignment(Qt::AlignTop);

        auto infoLabel = new QLabel;
        infoLabel->setWordWrap(true);
        infoLabel->setText(
            "Type helps provide structure and hierarchy to UI. The default font for Windows is Segoe UI Variable. Best practice is to use Regular weight for most text, use Semibold for titles. The minimum values should be 12px Regular, 14px "
            "Semibold.");
        infoLabel->setObjectName("infoLabel");
        vScrollView->getMainLayout()->addWidget(infoLabel);

        vScrollView->getMainLayout()->addSpacing(20);

        auto typeRampLabel = new QLabel;
        typeRampLabel->setText("Type ramp");
        typeRampLabel->setWordWrap(true);
        typeRampLabel->setObjectName("typeRampLabel");
        vScrollView->getMainLayout()->addWidget(typeRampLabel);

        auto typeRampWrap = new QWidget;
        typeRampWrap->setObjectName("typeRampWrap");
        vScrollView->getMainLayout()->addWidget(typeRampWrap);

        auto typeRampWrapLayout = new QVBoxLayout;
        typeRampWrapLayout->setAlignment(Qt::AlignTop);
        typeRampWrap->setLayout(typeRampWrapLayout);

        auto imgLabel = new QLabel;
        imgLabel->setObjectName("imgLabel");
        imgLabel->setFixedSize(740, 450);
        QPixmap pixmap = QPixmap("../res/Typography.light.png");
        pixmap = pixmap.scaled(740, 450, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        imgLabel->setPixmap(pixmap);

        auto imgLabelLayout = new QHBoxLayout;
        typeRampWrapLayout->addLayout(imgLabelLayout, Qt::AlignTop | Qt::AlignHCenter);
        imgLabelLayout->addWidget(imgLabel, Qt::AlignHCenter);

        auto row1 = addARow(FluLabelStyle::CaptionTextBlockSylte, "Example", "Variable Font", "Size", "Style", 60);
        typeRampWrapLayout->addWidget(row1, Qt::AlignTop);

        auto row2 = addARow(FluLabelStyle::CaptionTextBlockSylte, "Caption", "Text,Regular", "12/16 epx", "CaptionTextBlockSylte", 60);
        typeRampWrapLayout->addWidget(row2, Qt::AlignTop);

        auto row3 = addARow(FluLabelStyle::BodyStrongTextBlockStyle, "Body", "Text,SemiBold", "12/16 epx", "BodyStrongTextBlockStyle", 60);
        typeRampWrapLayout->addWidget(row3, Qt::AlignTop);

        auto row4 = addARow(FluLabelStyle::BodyStrongTextBlockStyle, "Body Strong", "Text, SemiBold", "12/16 epx", "BodyStrongTextBlockStyle", 60);
        typeRampWrapLayout->addWidget(row4, Qt::AlignTop);

        auto row5 = addARow(FluLabelStyle::SubTitleTextBlockStyle, "Subtitle", "Display, SemiBold", "12/16 epx", "SubtitleTextBlockStyle", 60);
        typeRampWrapLayout->addWidget(row5, Qt::AlignTop);

        auto row6 = addARow(FluLabelStyle::TitleTextBlockStyle, "Title", "Display, SemiBold", "12/16 epx", "TitleTextBlockStyle", 60);
        typeRampWrapLayout->addWidget(row6, Qt::AlignTop);

        auto row7 = addARow(FluLabelStyle::TitleLargeTextBlockStyle, "Title Large", "Display, SemiBold", "12/16 epx", "TitleLargeTextBlockStyle", 80);
        typeRampWrapLayout->addWidget(row7, Qt::AlignTop);

        auto row8 = addARow(FluLabelStyle::DisplayTextBlockStyle, "Display", "Display, SemiBold", "12/16 epx", "DisplayTextBlockStyle", 100);
        typeRampWrapLayout->addWidget(row8, Qt::AlignTop);

        auto expander = new FluCodeExpander;
        expander->setWrap2Height(60);
    //    expander->setFixedHeight(50);
        QString code;
        code += "auto label = new FluLabel;\n";
        code += "label->setStyle(FluLabelStyle::CaptionTextBlockSylte);\n";
        expander->setCode(code);
        vScrollView->getMainLayout()->addWidget(expander);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTypeographyPage.qss", this);
    }

    QWidget* addARow(FluLabelStyle labelStyle, QString text1, QString text2, QString text3, QString text4, int nHeight)
    {
        auto label1 = new FluLabel;
        auto label2 = new FluLabel;
        auto label3 = new FluLabel;
        auto label4 = new FluLabel;
        //  auto label5 = new FluLabel;

        label1->setStyle(labelStyle);

        label1->setText(text1);
        label2->setText(text2);
        label3->setText(text3);
        label4->setText(text4);

        label1->setFixedWidth(256);
        label2->setFixedWidth(120);
        label3->setFixedWidth(120);
        label4->setFixedWidth(160);

        auto labelsWrap = new QWidget;
        labelsWrap->setFixedHeight(nHeight);
        labelsWrap->setObjectName("labelsWrap");
        auto labelsWrapLayout = new QHBoxLayout;
        labelsWrapLayout->setAlignment(Qt::AlignLeft);
        labelsWrap->setLayout(labelsWrapLayout);

        labelsWrapLayout->addWidget(label1);
        labelsWrapLayout->addWidget(label2);
        labelsWrapLayout->addWidget(label3);
        labelsWrapLayout->addWidget(label4);
        //    labelsWrapLayout->addWidget(label5);

        return labelsWrap;
    }
};
