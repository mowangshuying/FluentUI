#include "FluIntructions.h"
#include <QResizeEvent>

FluIntructions::FluIntructions(QWidget* parent /*= nullptr*/) : FluExpander(parent)
{
    m_wrap1->setFixedHeight(70);
    // setFixedHeight(70);
    setMinimumHeight(70);

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
    if (!m_bDown && m_expandAni->state() != QPropertyAnimation::Running)
    {
        int nAutoH = getAutoH();

        m_wrap2->setMinimumHeight(nAutoH);
        m_wrap2->setFixedHeight(nAutoH);
        setContentHeight(nAutoH);
        m_wrap1->resize(event->size().width(), m_wrap1->height());
        m_wrap1->move(0, 0);
        m_wrap2->resize(event->size().width(), nAutoH);
        m_wrap2->move(0, m_wrap1->height());

        int nX = m_wrap1->width() - m_downOrUpButton->width() - 5;
        int nY = (m_wrap1->height() - m_downOrUpButton->height()) / 2;
        m_downOrUpButton->move(nX, nY);

        return;
    }

    int nAutoH = getAutoH();
    m_wrap1->resize(event->size().width(), m_wrap1->height());
    m_wrap1->move(0, 0);
    m_wrap2->resize(event->size().width(), nAutoH);
    // LOG_DEBUG << "sizeHint height:" << m_wrap2->sizeHint().height();
    m_wrap2->move(0, m_wrap1->height() + getContentHeight() - nAutoH);

    int nX = m_wrap1->width() - m_downOrUpButton->width() - 5;
    int nY = (m_wrap1->height() - m_downOrUpButton->height()) / 2;
    m_downOrUpButton->move(nX, nY);
}

void FluIntructions::paintEvent(QPaintEvent* event)
{
    FluExpander::paintEvent(event);
}

void FluIntructions::onClicked()
{
    int nAutoH = getAutoH();
    LOG_DEBUG << "nAutoH:" << nAutoH;
    m_wrap2->setMinimumHeight(nAutoH);
    m_wrap2->setFixedHeight(nAutoH);
    if (m_bDown)
    {
        m_expandAni->setStartValue(0);
        m_expandAni->setEndValue(nAutoH);
        m_expandAni->start();

        m_downOrUpButton->setType1(FluAwesomeType::ChevronUp);
    }
    else
    {
        m_expandAni->setStartValue(nAutoH);
        m_expandAni->setEndValue(0);
        m_expandAni->start();
        m_downOrUpButton->setType1(FluAwesomeType::ChevronDown);
    }
}
