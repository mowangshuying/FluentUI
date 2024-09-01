
#include "FluDisplayBox.h"

FluDisplayBox::FluDisplayBox(QWidget* parent /*= nullptr*/) : FluWidget(parent)
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
    //  m_bodyWidget->setFixedHeight(80);
    m_mainLayout->addWidget(m_bodyWidget, 1);

    m_vBodyLayout = new QVBoxLayout;
    m_bodyWidget->setLayout(m_vBodyLayout);
    m_vBodyLayout->setAlignment(Qt::AlignTop);

    m_codeExpander = new FluCodeExpander;
    m_codeExpander->setTopRadius0(true);
    m_mainLayout->addWidget(m_codeExpander);
    m_codeExpander->setObjectName("codeExpander");
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayBox.qss", this);
}

void FluDisplayBox::setTitle(QString title)
{
    m_titleLabel->setText(title);
}

QVBoxLayout* FluDisplayBox::getBodyLayout()
{
    return m_vBodyLayout;
}
QWidget* FluDisplayBox::getBodyWidget()
{
    return m_bodyWidget;
}

FluCodeExpander* FluDisplayBox::getCodeExpander()
{
    return m_codeExpander;
}

void FluDisplayBox::setBodyWidgetFixedHeight(int nHeight)
{
    m_bodyWidget->setFixedHeight(nHeight);
}

void FluDisplayBox::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluDisplayBox::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayBox.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDisplayBox.qss", this);
    }
}
