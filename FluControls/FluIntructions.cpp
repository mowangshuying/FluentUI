#include "FluIntructions.h"

FluIntructions::FluIntructions(QWidget* parent /*= nullptr*/) : FluExpander(parent)
{
    m_wrap1->setFixedHeight(70);
    setFixedHeight(70);

    m_titleLabel = new FluLabel;
    m_titleLabel->setObjectName("wrap1TitleLabel");
    m_titleLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
    m_titleLabel->setWordWrap(true);

    getWrap1Layout()->addWidget(m_titleLabel);
    getWrap1Layout()->setContentsMargins(15, 0, 15, 0);
    getWrap2Layout()->setContentsMargins(15, 15, 15, 15);
    getWrap2Layout()->setAlignment(Qt::AlignTop);
    getWrap2Layout()->setSpacing(5);
}

QLabel* FluIntructions::getTitleLabel()
{
    return m_titleLabel;
}

void FluIntructions::setTitleLabelText(QString text)
{
    m_titleLabel->setText(text);
}

void FluIntructions::addTitleContent(QString title, QString content, bool bAdd /*= true*/)
{
    auto titleLabel = new FluLabel(this);
    titleLabel->setObjectName("wrap2TitleLabel");
    titleLabel->setWordWrap(true);
    auto contentLabel = new FluLabel(this);
    contentLabel->setObjectName("wrap2ContentLabel");
    contentLabel->setWordWrap(true);
    titleLabel->setLabelStyle(FluLabelStyle::BodyStrongTextBlockStyle);
    contentLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);

    titleLabel->setText(title);
    contentLabel->setText(content);

    titleLabel->adjustSize();
    contentLabel->adjustSize();

    getWrap2Layout()->addWidget(titleLabel, 0, Qt::AlignTop);
    getWrap2Layout()->addWidget(contentLabel, 0, Qt::AlignTop);
}

void FluIntructions::addVSplitLine(bool bAdd /*= true*/)
{
    auto vSplitLine = new FluVSplitLine;
    vSplitLine->setObjectName("wrap2SplitLine");
    getWrap2Layout()->addWidget(vSplitLine);
}

void FluIntructions::resizeEvent(QResizeEvent* event)
{
    FluExpander::resizeEvent(event);
    if (m_bDown)
        return;

    if (m_expandAni->state() == QPropertyAnimation::Running)
        return;

    int nAutoH = 0;
    for (int i = 0; i < getWrap2Layout()->count(); i++)
    {
        auto widget = getWrap2Layout()->itemAt(i)->widget();
        if (widget->objectName() != "wrap2SplitLine")
        {
            auto label = (FluLabel*)widget;
            nAutoH += label->heightForWidth(m_wrap2->width() - getWrap2Layout()->contentsMargins().left() - getWrap2Layout()->contentsMargins().right());
        }
        else
        {
            nAutoH += widget->height();
        }

        nAutoH += getWrap2Layout()->spacing();
    }

    nAutoH += getWrap2Layout()->contentsMargins().top() + getWrap2Layout()->contentsMargins().bottom();
    m_wrap2->setFixedHeight(nAutoH);
    setFixedHeight(m_wrap1->height() + m_wrap2->height());
}

void FluIntructions::paintEvent(QPaintEvent* event)
{
    FluExpander::paintEvent(event);
}

void FluIntructions::onClicked()
{
    int nAutoH = 0;
    for (int i = 0; i < getWrap2Layout()->count(); i++)
    {
        auto widget = getWrap2Layout()->itemAt(i)->widget();
        if (widget->objectName() != "wrap2SplitLine")
        {
            auto label = (FluLabel*)widget;
            nAutoH += label->heightForWidth(m_wrap2->width() - getWrap2Layout()->contentsMargins().left() - getWrap2Layout()->contentsMargins().right());
        }
        else
        {
            nAutoH += widget->height();
        }

        nAutoH += getWrap2Layout()->spacing();
    }

    nAutoH += getWrap2Layout()->contentsMargins().top() + getWrap2Layout()->contentsMargins().bottom();
    m_wrap2->setFixedHeight(nAutoH);
    if (m_bDown)
    {
        m_expandAni->setStartValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), 0));
        m_expandAni->setEndValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), nAutoH));
        m_expandAni->start();

        m_downOrUpButton->setType1(FluAwesomeType::ChevronUp);
    }
    else
    {
        m_expandAni->setStartValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), nAutoH));
        m_expandAni->setEndValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), 0));
        m_expandAni->start();
        m_downOrUpButton->setType1(FluAwesomeType::ChevronDown);
    }
}
