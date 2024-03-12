#include "FluDisplayBoxEx.h"

FluDisplayBoxEx::FluDisplayBoxEx(QWidget* parent /*= nullptr*/)
{
    m_mainLayout = new QVBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(8, 8, 8, 8);
    m_mainLayout->setSpacing(0);

    m_titleLabel = new QLabel;
    m_titleLabel->setFixedHeight(30);
    m_titleLabel->setWordWrap(true);
    m_titleLabel->setObjectName("titleLabel");
    m_titleLabel->setText("A Title");

    m_mainLayout->addWidget(m_titleLabel);

    m_bodyWidget = new QWidget;
    m_bodyWidget->setObjectName("bodyWidget");
    m_mainLayout->addWidget(m_bodyWidget, 1);

    m_hBodyLayout = new QHBoxLayout;
    m_bodyWidget->setLayout(m_hBodyLayout);
    m_hBodyLayout->setContentsMargins(0, 0, 0, 0);
    // m_hBodyLayout->setAlignment(Qt::AlignTop);

    m_bodyContentWidget = new QWidget;
    m_vBodyContentLayout = new QVBoxLayout;
    m_bodyContentWidget->setLayout(m_vBodyContentLayout);
    m_hBodyLayout->addWidget(m_bodyContentWidget, 1);
    m_bodyContentWidget->setObjectName("bodyContentWidget");

    m_bodyRightWidget = new QWidget;
    m_vBodyRightLayout = new QVBoxLayout;
    m_bodyRightWidget->setLayout(m_vBodyRightLayout);
    m_bodyRightWidget->setFixedWidth(160);
    m_hBodyLayout->addWidget(m_bodyRightWidget);
    m_bodyRightWidget->setObjectName("bodyRightWidget");

    m_codeExpander = new FluCodeExpander;
    m_mainLayout->addWidget(m_codeExpander);
    m_codeExpander->setObjectName("codeExpander");
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayBoxEx.qss", this);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
}
