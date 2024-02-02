#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluFlowLayout.h"
#include "../FluControls/FluDisplayIconBox.h"
#include "../FluControls/FluFWScrollView.h"

class FluIconsPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluIconsPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("IconsPage");
        m_infoLabel->setText("Segoe FluentIcons instructions.");

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
            if (i >= 256)
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

                awesomeTypeKeyLabel->setText("Enum:");
                awesomeTypeValueLabel->setText("FluAwesomeType::" + EnumTypeToQString(displayIconBox->getAwesomeType()));
            });
        }

        emit m_sDisplayIconBox->clicked();
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluIconsPage.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    //  void paintEvent(QPaintEvent* event)
    //   {
    //      QStyleOption opt;
    //      opt.initFrom(this);
    //      QPainter painter(this);
    //     style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    //  }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
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

  protected:
    QColor m_penColor;
    QLabel* m_iconLabel;
    FluDisplayIconBox* m_sDisplayIconBox;
};
