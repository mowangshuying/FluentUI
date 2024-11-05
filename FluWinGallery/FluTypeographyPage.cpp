#include "FluTypeographyPage.h"

FluTypeographyPage::FluTypeographyPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_titleLabel->setText("Typography");
    m_mainLayout->setAlignment(Qt::AlignTop);

    // m_subTitleLabel->setText("CppQtFluentUi888::FluTypeography");

    auto typeRampLabel = new QLabel;
    typeRampLabel->setText("Type ramp");
    typeRampLabel->setWordWrap(true);
    typeRampLabel->setObjectName("typeRampLabel");
    m_vScrollView->getMainLayout()->addWidget(typeRampLabel);

    auto typeRampWrap = new QWidget;
    typeRampWrap->setObjectName("typeRampWrap");
    m_vScrollView->getMainLayout()->addWidget(typeRampWrap);

    auto typeRampWrapLayout = new QVBoxLayout;
    typeRampWrapLayout->setAlignment(Qt::AlignTop);
    typeRampWrap->setLayout(typeRampWrapLayout);

    m_imgLabel = new QLabel;
    m_imgLabel->setObjectName("imgLabel");
    m_imgLabel->setFixedSize(740, 450);
    QPixmap pixmap = QPixmap("../res/Typography.light.png");
    pixmap = pixmap.scaled(740, 450, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_imgLabel->setPixmap(pixmap);

    auto imgLabelLayout = new QHBoxLayout;
    typeRampWrapLayout->addLayout(imgLabelLayout, Qt::AlignTop | Qt::AlignHCenter);
    imgLabelLayout->addWidget(m_imgLabel, Qt::AlignHCenter);

    auto row1 = addARow(FluLabelStyle::CaptionTextBlockSylte, "Example", "Variable Font", "Size", "Style", 60);
    typeRampWrapLayout->addWidget(row1, Qt::AlignTop);

    auto row2 = addARow(FluLabelStyle::CaptionTextBlockSylte, "Caption", "Text,Regular", "12/16 epx", "CaptionTextBlockSylte", 60);
    typeRampWrapLayout->addWidget(row2, Qt::AlignTop);

    auto row3 = addARow(FluLabelStyle::BodyTextBlockStyle, "Body", "Text,SemiBold", "14/20 epx", "BodyStrongTextBlockStyle", 60);
    typeRampWrapLayout->addWidget(row3, Qt::AlignTop);

    auto row4 = addARow(FluLabelStyle::BodyStrongTextBlockStyle, "Body Strong", "Text, SemiBold", "14/20 epx", "BodyStrongTextBlockStyle", 60);
    typeRampWrapLayout->addWidget(row4, Qt::AlignTop);

    auto row5 = addARow(FluLabelStyle::SubTitleTextBlockStyle, "Subtitle", "Display, SemiBold", "20/28 epx", "SubtitleTextBlockStyle", 60);
    typeRampWrapLayout->addWidget(row5, Qt::AlignTop);

    auto row6 = addARow(FluLabelStyle::TitleTextBlockStyle, "Title", "Display, SemiBold", "28/36 epx", "TitleTextBlockStyle", 60);
    typeRampWrapLayout->addWidget(row6, Qt::AlignTop);

    auto row7 = addARow(FluLabelStyle::TitleLargeTextBlockStyle, "Title Large", "Display, SemiBold", "40/52 epx", "TitleLargeTextBlockStyle", 80);
    typeRampWrapLayout->addWidget(row7, Qt::AlignTop);

    auto row8 = addARow(FluLabelStyle::DisplayTextBlockStyle, "Display", "Display, SemiBold", "68/92 epx", "DisplayTextBlockStyle", 100);
    typeRampWrapLayout->addWidget(row8, Qt::AlignTop);

    auto expander = new FluCodeExpander;
    // expander->setWrap2Height(60);
    //     expander->setFixedHeight(50);
    QString code;
    code += "auto label = new FluLabel;\n";
    code += "label->setStyle(FluLabelStyle::CaptionTextBlockSylte);";
    expander->setCodeText(code);
    m_vScrollView->getMainLayout()->addWidget(expander);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTypeographyPage.qss", this);
}

QWidget* FluTypeographyPage::addARow(FluLabelStyle labelStyle, QString text1, QString text2, QString text3, QString text4, int nHeight)
{
    auto label1 = new FluLabel;
    auto label2 = new FluLabel;
    auto label3 = new FluLabel;
    auto label4 = new FluLabel;

    label1->setLabelStyle(labelStyle);

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

    return labelsWrap;
}

void FluTypeographyPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        QPixmap pixmap = QPixmap("../res/Typography.light.png");
        pixmap = pixmap.scaled(740, 450, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        m_imgLabel->setPixmap(pixmap);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTypeographyPage.qss", this);
    }
    else
    {
        QPixmap pixmap = QPixmap("../res/Typography.dark.png");
        pixmap = pixmap.scaled(740, 450, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        m_imgLabel->setPixmap(pixmap);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTypeographyPage.qss", this);
    }
}
