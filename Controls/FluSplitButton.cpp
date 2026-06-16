#include "FluSplitButton.h"

FluSplitButton::FluSplitButton(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);
    m_hMainLayout->setSpacing(0);

    m_dropDownBtn = new QPushButton;
    m_textBtn = new QPushButton;

    m_dropDownBtn->setObjectName("dropDownBtn");
    m_dropDownBtn->setIconSize(QSize(20, 20));
    m_dropDownBtn->setFixedSize(30, 30);
    m_textBtn->setObjectName("textBtn");

    m_hMainLayout->setContentsMargins(0, 0, 0, 0);

    m_hMainLayout->addWidget(m_textBtn);
    m_hMainLayout->addWidget(m_dropDownBtn);

    setFixedHeight(30);

    connect(m_textBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });
    connect(m_dropDownBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });

    onThemeChanged();
}

void FluSplitButton::setText(QString text)
{
    m_textBtn->setText(text);
}

void FluSplitButton::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    emit clicked();
}

void FluSplitButton::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluSplitButton::onThemeChanged()
{
    m_dropDownBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUitls::setQssByFileName("FluSplitButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}
