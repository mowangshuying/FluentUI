#include "FluDisplayIconBox.h"

FluDisplayIconBox::FluDisplayIconBox(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_awesomeType(FluAwesomeType::None)
{
    setFixedSize(48, 48);
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setSpacing(0);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    setLayout(m_mainLayout);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(30, 30);
    m_mainLayout->addWidget(m_iconLabel, 0, Qt::AlignHCenter);

    m_textLable = new QLabel(this);
    m_mainLayout->addWidget(m_textLable, 0, Qt::AlignHCenter);

    m_iconLabel->setObjectName("iconLabel");
    m_textLable->setObjectName("textLabel");

    m_useAwesomeType = true;
    onThemeChanged();
}

FluDisplayIconBox::FluDisplayIconBox(FluAwesomeType type, QWidget* parent /*= nullptr*/) : FluDisplayIconBox(parent)
{
    m_awesomeType = type;
    QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_awesomeType, FluThemeUtils::getUtils()->getTheme());
    m_iconLabel->setPixmap(pixmap);
    m_textLable->setText(EnumTypeToQString(type));
}

FluDisplayIconBox::FluDisplayIconBox(FluEmoijType type, QWidget* parent) : FluDisplayIconBox(parent)
{
    m_emoijType = type;
    setUseAwesomeType(false);
    m_iconLabel->setPixmap(FluEmoijUtils::getSvgPixmap(type));
}

void FluDisplayIconBox::setSelected(bool isSelected)
{
    setProperty("selected", isSelected);
    update();
}

FluAwesomeType FluDisplayIconBox::getAwesomeType()
{
    return m_awesomeType;
}

FluEmoijType FluDisplayIconBox::getEmoijType()
{
    return m_emoijType;
}

void FluDisplayIconBox::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    emit clicked();
}

void FluDisplayIconBox::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluDisplayIconBox::onThemeChanged()
{
    if (m_useAwesomeType)
        m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
    else
        m_iconLabel->setPixmap(FluEmoijUtils::getSvgPixmap(m_emoijType));

    FluStyleSheetUtils::setQssByFileName("FluDisplayIconBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
