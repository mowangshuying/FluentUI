#include "FluInstructions.h"
#include <QResizeEvent>

FluInstructions::FluInstructions(QWidget* parent /*= nullptr*/) : FluExpander(parent)
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

QLabel* FluInstructions::getTitleLabel()
{
    return m_titleLabel;
}

void FluInstructions::setTitleLabelText(QString text)
{
    m_titleLabel->setText(text);
}

void FluInstructions::addTitleContent(QString title, QString content, bool isAdd /*= true*/)
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

void FluInstructions::addVSplitLine(bool isAdd /*= true*/)
{
    auto vSplitLine = new FluVSplitLine;
    vSplitLine->setObjectName("wrap2SplitLine");
    getWrap2Layout()->addWidget(vSplitLine);
}

void FluInstructions::resizeEvent(QResizeEvent* event)
{
    if (!m_isDown && m_expandAni->state() != QPropertyAnimation::Running)
    {
        int autoH = getAutoH();

        m_wrap2->setMinimumHeight(autoH);
        m_wrap2->setFixedHeight(autoH);
        setContentHeight(autoH);
        m_wrap1->resize(event->size().width(), m_wrap1->height());
        m_wrap1->move(0, 0);
        m_wrap2->resize(event->size().width(), autoH);
        m_wrap2->move(0, m_wrap1->height());

        int x = m_wrap1->width() - m_downOrUpButton->width() - 5;
        int y = (m_wrap1->height() - m_downOrUpButton->height()) / 2;
        m_downOrUpButton->move(x, y);

        return;
    }

    int autoH = getAutoH();
    m_wrap1->resize(event->size().width(), m_wrap1->height());
    m_wrap1->move(0, 0);
    m_wrap2->resize(event->size().width(), autoH);
    // LOG_DEBUG << "sizeHint height:" << m_wrap2->sizeHint().height();
    m_wrap2->move(0, m_wrap1->height() + getContentHeight() - autoH);

    int x = m_wrap1->width() - m_downOrUpButton->width() - 5;
    int y = (m_wrap1->height() - m_downOrUpButton->height()) / 2;
    m_downOrUpButton->move(x, y);
}

void FluInstructions::paintEvent(QPaintEvent* event)
{
    FluExpander::paintEvent(event);
}

void FluInstructions::onClicked()
{
    int autoH = getAutoH();
    LOG_DEBUG << "autoH:" << autoH;
    m_wrap2->setMinimumHeight(autoH);
    m_wrap2->setFixedHeight(autoH);
    if (m_isDown)
    {
        m_expandAni->setStartValue(0);
        m_expandAni->setEndValue(autoH);
        m_expandAni->start();

        m_downOrUpButton->setType1(FluAwesomeType::ChevronUp);
    }
    else
    {
        m_expandAni->setStartValue(autoH);
        m_expandAni->setEndValue(0);
        m_expandAni->start();
        m_downOrUpButton->setType1(FluAwesomeType::ChevronDown);
    }
}
