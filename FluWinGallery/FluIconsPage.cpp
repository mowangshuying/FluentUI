#include "FluIconsPage.h"

FluIconsPage::FluIconsPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("Icons");
    // m_subTitleLabel->setText("FluentUI::FluIcons");
    m_infoLabel->setText("With the release of Windows 11, Segoe Fluent Icons is the remmended icon font.");

    // instructions
    auto instructions = new FluIntructions;
    instructions->setTitleLabelText("Instructions on how to use Segoe Fluent Icons");
    instructions->addTitleContent("How to get the font", "On Windows 11: There's nothing you need to do, the font comes with Windows.\nOn Windows 10: Segoe Fluent Icons is not included by default on Windows 10. You can download it here.");

    instructions->addVSplitLine();

    instructions->addTitleContent(
        "How to use the font",
        "If you don't specify a FontFamily, or you specify a FontFamily that is not available on the system at runtime, the FontIcon falls back to the default font family defined by the SymbolThemeFontFamily resource.\n"
        "An icon with a 16-epx font size is the equivalent of a 16x16-epx icon, to make sizing and positioning more predictable. For optimal appearance, use these specific sizes: 16, 20, 24, 32, 40, 48, and 64. Deviating from these font "
        "sizes could lead to less crisp or blurry outcomes.\n"
        "All glyphs in Segoe Fluent Icons have the same fixed width with a consistent height and left origin point, so layering and colorization effects can be achieved by drawing glyphs directly on top of each other.");

    // instructions->addEnd();
    m_vScrollView->getMainLayout()->addWidget(instructions);

    m_vScrollView->getMainLayout()->addSpacing(15);

    m_searchLabel = new QLabel;
    m_searchLabel->setObjectName("searchLabel");
    m_searchLabel->setText("Fluent Icons Library.");
    m_vScrollView->getMainLayout()->addWidget(m_searchLabel);

    m_vScrollView->getMainLayout()->addSpacing(5);

    m_searchEdit = new FluSearchLineEdit;
    m_searchEdit->setFixedWidth(300);
    m_vScrollView->getMainLayout()->addWidget(m_searchEdit);

    auto wrapWidget = new QWidget;
    wrapWidget->setObjectName("wrapWidget");

    auto wrapLayout = new QHBoxLayout;
    wrapWidget->setLayout(wrapLayout);
    m_vScrollView->getMainLayout()->addWidget(wrapWidget, 1);

    auto wrapWidget1 = new FluFWScrollView;
    wrapWidget1->setObjectName("wrapWidget1");
    // m_vScrollView->getMainLayout()->addWidget(wrapWidget1, 1);
    wrapLayout->addWidget(wrapWidget1);

    auto wrapWidget2 = new QWidget;
    wrapWidget2->setObjectName("wrapWidget2");
    wrapWidget2->setFixedWidth(256);

    auto wrapWidget2Layout = new QVBoxLayout;
    wrapWidget2Layout->setSpacing(0);
    wrapWidget2Layout->setAlignment(Qt::AlignTop);
    //   auto wrapWidget2AwesomeTypeLayout = new QHBoxLayout;

    auto titleLabel = new QLabel;
    m_iconLabel = new QLabel;

    m_iconLabel->setFixedSize(50, 50);

    auto awesomeTypeKeyLabel = new QLabel;
    auto awesomeTypeValueLabel = new QLabel;
    // wrapWidget2AwesomeTypeLayout->addWidget(awesomeTypeKeyLabel);

    wrapWidget2Layout->addWidget(titleLabel, 0, Qt::AlignTop);
    wrapWidget2Layout->addSpacing(20);
    wrapWidget2Layout->addWidget(m_iconLabel, 0, Qt::AlignTop);
    wrapWidget2Layout->addSpacing(20);
    wrapWidget2Layout->addWidget(awesomeTypeKeyLabel, 0, Qt::AlignTop);
    wrapWidget2Layout->addSpacing(5);
    wrapWidget2Layout->addWidget(awesomeTypeValueLabel, 0, Qt::AlignTop);

    titleLabel->setObjectName("wTitleLabel");
    m_iconLabel->setObjectName("wIconLabel");
    awesomeTypeKeyLabel->setObjectName("wAwesomeTypeKeyLabel");
    awesomeTypeValueLabel->setObjectName("wAwesomeTypeValueLabel");

    titleLabel->setText("title Label");
    awesomeTypeKeyLabel->setText("awesometype key Label");
    awesomeTypeValueLabel->setText("awesometype value Label");

    wrapWidget2->setLayout(wrapWidget2Layout);
    wrapLayout->addWidget(wrapWidget2);

    //   auto flowLayout = new FluFlowLayout;
    //   wrapWidget1->setLayout(flowLayout);

    // auto wrapScrollView = new FluVScrollView;

    // wrapScrollView->getMainLayout()->addWidget(wrapWidget1);
    // m_vScrollView->getMainLayout()->addWidget(wrapScrollView, 1);

    m_sDisplayIconBox = nullptr;

    m_penColor = QColor(8, 8, 8);
    // add icons to display it!
    QMetaEnum metaEnum = QMetaEnum::fromType<FluAwesomeType>();
    for (int i = 0; i < metaEnum.keyCount(); i++)
    {
#ifdef _DEBUG
        if (i >= 512)
            continue;
#endif
        // addIcon((FluAwesomeType)metaEnum.value(i));
        auto displayIconBox = new FluDisplayIconBox((FluAwesomeType)metaEnum.value(i));
        if (i == 0)
        {
            m_sDisplayIconBox = displayIconBox;
        }

        // flowLayout->addWidget(displayIconBox);
        wrapWidget1->getMainLayout()->addWidget(displayIconBox);
        m_iconBoxMap[(FluAwesomeType)metaEnum.value(i)] = displayIconBox;

        connect(displayIconBox, &FluDisplayIconBox::clicked, [=]() {
            if (m_sDisplayIconBox != nullptr)
            {
                m_sDisplayIconBox->setSelected(false);
                m_sDisplayIconBox->style()->polish(m_sDisplayIconBox);
            }

            m_sDisplayIconBox = displayIconBox;
            displayIconBox->setSelected(true);
            displayIconBox->style()->polish(displayIconBox);

            titleLabel->setText(EnumTypeToQString(displayIconBox->getAwesomeType()));
            QPixmap pixmap = FluIconUtils::getFluentIconPixmap(displayIconBox->getAwesomeType(), m_penColor);
            pixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            m_iconLabel->setPixmap(pixmap);

            // awesomeTypeKeyLabel->setText("Enum:");
            // awesomeTypeValueLabel->setText("FluAwesomeType::" + EnumTypeToQString(displayIconBox->getAwesomeType()));
            awesomeTypeKeyLabel->setText("");
            awesomeTypeValueLabel->setText("");
        });
    }

    connect(m_searchEdit, &FluSearchLineEdit::onSearchBtnClicked, [=]() {
        QString searchText = m_searchEdit->getText();
        for (auto itMap = m_iconBoxMap.begin(); itMap != m_iconBoxMap.end(); itMap++)
        {
            QString enumString = EnumTypeToQString(itMap->first);
            if (enumString.contains(searchText))
            {
                itMap->second->show();
            }
            else
            {
                itMap->second->hide();
            }
        }
    });

    if (m_sDisplayIconBox != nullptr)
        emit m_sDisplayIconBox->clicked();

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluIconsPage.qss", this);
}

void FluIconsPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_penColor = QColor(8, 8, 8);
        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_sDisplayIconBox->getAwesomeType(), m_penColor);
        pixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        m_iconLabel->setPixmap(pixmap);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluIconsPage.qss", this);
    }
    else
    {
        m_penColor = QColor(239, 239, 239);
        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_sDisplayIconBox->getAwesomeType(), m_penColor);
        pixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        m_iconLabel->setPixmap(pixmap);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluIconsPage.qss", this);
    }
}
