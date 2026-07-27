#include "FluSplitButton.h"

FluSplitButton::FluSplitButton(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->setSpacing(0);

    m_dropDownButton = new QPushButton;
    m_textButton = new QPushButton;

    m_dropDownButton->setObjectName("dropDownBtn");
    m_dropDownButton->setIconSize(QSize(20, 20));
    m_dropDownButton->setFixedSize(30, 30);
    m_textButton->setObjectName("textBtn");

    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    m_mainLayout->addWidget(m_textButton);
    m_mainLayout->addWidget(m_dropDownButton);

    setFixedHeight(30);

    connect(m_textButton, &QPushButton::clicked, [=](bool b) { emit clicked(); });
    connect(m_dropDownButton, &QPushButton::clicked, [=](bool b) { emit clicked(); });

    onThemeChanged();
}

void FluSplitButton::setText(QString text)
{
    m_textButton->setText(text);
}

void FluSplitButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (!isEnabled())
        return;
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
    m_dropDownButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUtils::setQssByFileName("FluSplitButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluSplitButton::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    m_textButton->setEnabled(enabled);
    m_dropDownButton->setEnabled(enabled);
}
