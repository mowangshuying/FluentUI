#include "FluTypeographyPage.h"

FluTypeographyPage::FluTypeographyPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_titleLabel->setText(tr("Typography"));
    m_mainLayout->setAlignment(Qt::AlignTop);

    // m_subTitleLabel->setText("FluentUI::FluTypeography");

    auto typeRampLabel = new QLabel;
    typeRampLabel->setText(tr("Type ramp"));
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

    auto row1 = addARow(FluLabelStyle::CaptionTextBlockSylte, tr("Example"), tr("Variable Font"), tr("Size"), tr("Style"), 60);
    typeRampWrapLayout->addWidget(row1, Qt::AlignTop);

    auto row2 = addARow(FluLabelStyle::CaptionTextBlockSylte, tr("Caption"), tr("Text,Regular"), tr("12/16 epx"), tr("CaptionTextBlockSylte"), 60);
    typeRampWrapLayout->addWidget(row2, Qt::AlignTop);

    auto row3 = addARow(FluLabelStyle::BodyTextBlockStyle, tr("Body"), tr("Text,SemiBold"), tr("14/20 epx"), tr("BodyStrongTextBlockStyle"), 60);
    typeRampWrapLayout->addWidget(row3, Qt::AlignTop);

    auto row4 = addARow(FluLabelStyle::BodyStrongTextBlockStyle, tr("Body Strong"), tr("Text, SemiBold"), tr("14/20 epx"), tr("BodyStrongTextBlockStyle"), 60);
    typeRampWrapLayout->addWidget(row4, Qt::AlignTop);

    auto row5 = addARow(FluLabelStyle::SubTitleTextBlockStyle, tr("Subtitle"), tr("Display, SemiBold"), tr("20/28 epx"), tr("SubtitleTextBlockStyle"), 60);
    typeRampWrapLayout->addWidget(row5, Qt::AlignTop);

    auto row6 = addARow(FluLabelStyle::TitleTextBlockStyle, tr("Title"), tr("Display, SemiBold"), tr("28/36 epx"), tr("TitleTextBlockStyle"), 60);
    typeRampWrapLayout->addWidget(row6, Qt::AlignTop);

    auto row7 = addARow(FluLabelStyle::TitleLargeTextBlockStyle, tr("Title Large"), tr("Display, SemiBold"), tr("40/52 epx"), tr("TitleLargeTextBlockStyle"), 80);
    typeRampWrapLayout->addWidget(row7, Qt::AlignTop);

    auto row8 = addARow(FluLabelStyle::DisplayTextBlockStyle, tr("Display"), tr("Display, SemiBold"), tr("68/92 epx"), tr("DisplayTextBlockStyle"), 100);
    typeRampWrapLayout->addWidget(row8, Qt::AlignTop);

    auto expander = new FluCodeExpander;
    // expander->setWrap2Height(60);
    //     expander->setFixedHeight(50);
    QString code = tr("auto label = new FluLabel;label->setStyle(FluLabelStyle::CaptionTextBlockSylte);");
    expander->setCodeText(code);
    m_vScrollView->getMainLayout()->addWidget(expander);

    onThemeChanged();
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
