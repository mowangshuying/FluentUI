#include "FluEmoijsPage.h"

FluEmoijsPage::FluEmoijsPage(QWidget* parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Emoij"));
    m_infoLabel->setText(tr("Show Emoij"));

    m_searchLabel = new QLabel;
    m_searchLabel->setObjectName("searchLabel");
    m_searchLabel->setText(tr("Fluent Emoij Library."));
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

    wrapWidget2Layout->addWidget(titleLabel, 0, Qt::AlignTop);
    wrapWidget2Layout->addSpacing(20);
    wrapWidget2Layout->addWidget(m_iconLabel, 0, Qt::AlignTop);
    wrapWidget2Layout->addSpacing(20);
    wrapWidget2Layout->addWidget(awesomeTypeKeyLabel, 0, Qt::AlignTop);
    wrapWidget2Layout->addSpacing(5);
    wrapWidget2Layout->addWidget(awesomeTypeValueLabel, 0, Qt::AlignTop);

    titleLabel->setObjectName("wTitleLabel");
    m_iconLabel->setObjectName("wIconLabel");
    awesomeTypeKeyLabel->setObjectName("wEmoijTypeKeyLabel");
    awesomeTypeValueLabel->setObjectName("wEmoijTypeValueLabel");

    titleLabel->setText(tr("title Label"));
    awesomeTypeKeyLabel->setText("Emoij key Label");
    awesomeTypeValueLabel->setText("Emoij value Label");

    wrapWidget2->setLayout(wrapWidget2Layout);
    wrapLayout->addWidget(wrapWidget2);

    m_sDisplayIconBox = nullptr;

    QMetaEnum metaEnum = QMetaEnum::fromType<FluEmoijType>();
    for (int i = 0; i < metaEnum.keyCount(); i++)
    {
#ifdef _DEBUG
        if (i >= 512)
            continue;
#endif
        auto displayIconBox = new FluDisplayIconBox((FluEmoijType)metaEnum.value(i));
        if (i == 0)
        {
            m_sDisplayIconBox = displayIconBox;
        }

        // flowLayout->addWidget(displayIconBox);
        wrapWidget1->getMainLayout()->addWidget(displayIconBox);
        m_iconBoxMap[(FluEmoijType)metaEnum.value(i)] = displayIconBox;

        connect(displayIconBox, &FluDisplayIconBox::clicked, [=]() {
            if (m_sDisplayIconBox != nullptr)
            {
                m_sDisplayIconBox->setSelected(false);
                m_sDisplayIconBox->style()->polish(m_sDisplayIconBox);
            }

            m_sDisplayIconBox = displayIconBox;
            displayIconBox->setSelected(true);
            displayIconBox->style()->polish(displayIconBox);

            titleLabel->setText(EnumTypeToQString(displayIconBox->getEmoijType()));
            QPixmap pixmap = FluEmoijUtils::getSvgPixmap(displayIconBox->getEmoijType());
            pixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            m_iconLabel->setPixmap(pixmap);

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

    onThemeChanged();
}

void FluEmoijsPage::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluEmoijsPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}