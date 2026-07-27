#include "FluVFlipView.h"
#include <QScrollBar>

FluVFlipView::FluVFlipView(QWidget* parent /*= nullptr*/) : QScrollArea(parent)
{
    setWidgetResizable(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedSize(400, 268);
    // resize(400, 268);
    setContentsMargins(0, 0, 0, 0);

    // LOG_DEBUG << "size:" << size();
    m_contextWidget = new QWidget(this);
    setWidget(m_contextWidget);

    // m_contextWidget->setFixedSize(size());
    // LOG_DEBUG << "contextWidget size:" << m_contextWidget->size();

    m_layout = new QVBoxLayout;
    //  m_layout->insertSpacing(0, -11);
    m_contextWidget->setLayout(m_layout);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setAlignment(Qt::AlignLeft);

    // m_layout->
    m_contextWidget->setContentsMargins(0, 0, 0, 0);

    m_contextWidget->setObjectName("contextWidget");

    m_tButton = new QPushButton(this);
    m_bottomButton = new QPushButton(this);
    m_tButton->setFixedSize(38, 18);
    m_bottomButton->setFixedSize(38, 18);

    m_tButton->setObjectName("tBtn");
    m_bottomButton->setObjectName("bBtn");

    m_tButton->setIconSize(QSize(15, 15));
    m_tButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp)));

    m_bottomButton->setIconSize(QSize(15, 15));
    m_bottomButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown)));
    m_imgBoxIndex = 0;

    m_tButton->hide();
    m_bottomButton->hide();
    connect(m_bottomButton, &QPushButton::clicked, [=](bool isClicked) {
        // horizontalScrollBar()->setValue(width());
        if (m_imgBoxIndex <= m_layout->count())
        {
            m_imgBoxIndex += 1;
            hideOrShowTBButton(true);

            verticalScrollBar()->setValue(height() * m_imgBoxIndex);
        }
    });

    connect(m_tButton, &QPushButton::clicked, [=](bool isClicked) {
        if (m_imgBoxIndex > 0)
        {
            m_imgBoxIndex -= 1;

            // m_lButton->show();
            m_bottomButton->show();

            hideOrShowTBButton(true);

            verticalScrollBar()->setValue(height() * m_imgBoxIndex);
        }
    });

    FluStyleSheetUtils::setQssByFileName("FluVFlipView.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluVFlipView::addPixmap(QPixmap pixmap)
{
    auto imageBox = new FluImageBox(pixmap, m_contextWidget);
    imageBox->setFixedSize(size());
    m_layout->addWidget(imageBox, 0, Qt::AlignHCenter);
    imageBox->setObjectName("imageBox");
}

void FluVFlipView::hideOrShowTBButton(bool isEnter)
{
    if (isEnter)
    {
        m_tButton->show();
        m_bottomButton->show();
        if (m_imgBoxIndex == 0)
            m_tButton->hide();

        if (m_imgBoxIndex == m_layout->count() - 1)
            m_bottomButton->hide();
    }
    else
    {
        m_tButton->hide();
        m_bottomButton->hide();
    }
}

void FluVFlipView::enterEvent(QEnterEvent* event)
{
    hideOrShowTBButton(true);
}

void FluVFlipView::leaveEvent(QEvent* event)
{
    hideOrShowTBButton(false);
}

void FluVFlipView::resizeEvent(QResizeEvent* event)
{
    QScrollArea::resizeEvent(event);
    int h = height();
    int w = width();

    int lX = w / 2 - m_tButton->width() / 2;
    int lY = 5;
    m_tButton->move(lX, lY);

    int rX = w / 2 - m_bottomButton->width() / 2;
    int rY = h - m_bottomButton->height() - 5;
    m_bottomButton->move(rX, rY);
}
