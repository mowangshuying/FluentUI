#include "FluDisplayIconBox.h"

FluDisplayIconBox::FluDisplayIconBox(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_type(FluAwesomeType::None)
{
    setFixedSize(48, 48);
    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setSpacing(0);
    m_vMainLayout->setContentsMargins(5, 5, 5, 5);
    setLayout(m_vMainLayout);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(30, 30);
    m_vMainLayout->addWidget(m_iconLabel, 0, Qt::AlignHCenter);

    m_textLable = new QLabel(this);
    m_vMainLayout->addWidget(m_textLable, 0, Qt::AlignHCenter);

    m_iconLabel->setObjectName("iconLabel");
    m_textLable->setObjectName("textLabel");
    onThemeChanged();
}

FluDisplayIconBox::FluDisplayIconBox(FluAwesomeType type, QWidget* parent /*= nullptr*/) : FluDisplayIconBox(parent)
{
    m_type = type;
    QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_type, QColor(8, 8, 8), 30, 30);
    m_iconLabel->setPixmap(pixmap);
    m_textLable->setText(EnumTypeToQString(type));
}

void FluDisplayIconBox::setSelected(bool bSelected)
{
    setProperty("selected", bSelected);
    update();
}

FluAwesomeType FluDisplayIconBox::getAwesomeType()
{
    return m_type;
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
    if (FluThemeUtils::isLightTheme())
    {
        m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(m_type, QColor(8, 8, 8)));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayIconBox.qss", this);
    }
    else
    {
        m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(m_type, QColor(239, 239, 239)));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDisplayIconBox.qss", this);
    }
}
