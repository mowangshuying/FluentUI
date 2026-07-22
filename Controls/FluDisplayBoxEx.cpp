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
    m_titleLabel->setText(tr("A Title"));

    m_mainLayout->addWidget(m_titleLabel);

    m_bodyWidget = new QWidget;
    m_bodyWidget->setObjectName("bodyWidget");
    m_mainLayout->addWidget(m_bodyWidget, 1);

    m_bodyLayout = new QHBoxLayout;
    m_bodyWidget->setLayout(m_bodyLayout);
    m_bodyLayout->setContentsMargins(0, 0, 0, 0);
    // m_bodyLayout->setAlignment(Qt::AlignTop);

    m_bodyContentWidget = new QWidget;
    m_bodyContentLayout = new QVBoxLayout;
    m_bodyContentWidget->setLayout(m_bodyContentLayout);
    m_bodyLayout->addWidget(m_bodyContentWidget, 1);
    m_bodyContentWidget->setObjectName("bodyContentWidget");

    m_bodyRightWidget = new QWidget;
    m_bodyRightLayout = new QVBoxLayout;
    m_bodyRightWidget->setLayout(m_bodyRightLayout);
    m_bodyRightWidget->setFixedWidth(160);
    m_bodyLayout->addWidget(m_bodyRightWidget);
    m_bodyRightWidget->setObjectName("bodyRightWidget");

    m_codeExpander = new FluCodeExpander;
    m_codeExpander->setTopRadius0(true);
    m_mainLayout->addWidget(m_codeExpander);
    m_codeExpander->setObjectName("codeExpander");

    onThemeChanged();
}

void FluDisplayBoxEx::setTitle(QString title)
{
    m_titleLabel->setText(title);
}

QHBoxLayout* FluDisplayBoxEx::getBodyLayout()
{
    return m_bodyLayout;
}

QVBoxLayout* FluDisplayBoxEx::getBodyContentLayout()
{
    return m_bodyContentLayout;
}

QVBoxLayout* FluDisplayBoxEx::getBodyRightLayout()
{
    return m_bodyRightLayout;
}

FluCodeExpander* FluDisplayBoxEx::getCodeExpander()
{
    return m_codeExpander;
}

void FluDisplayBoxEx::setBodyWidgetFixedHeight(int height)
{
    m_bodyWidget->setFixedHeight(height);
}

void FluDisplayBoxEx::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluDisplayBoxEx::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluDisplayBoxEx.qss", this, FluThemeUtils::getUtils()->getTheme());
}
