#include "FluHFlipView.h"
#include "FluImageBox.h"
#include <QScrollBar>

FluHFlipView::FluHFlipView(QWidget* parent /*= nullptr*/) : QScrollArea(parent)
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

    m_layout = new QHBoxLayout;
    //  m_layout->insertSpacing(0, -11);
    m_contextWidget->setLayout(m_layout);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setAlignment(Qt::AlignLeft);

    // m_layout->
    m_contextWidget->setContentsMargins(0, 0, 0, 0);

    m_contextWidget->setObjectName("contextWidget");

    m_lButton = new QPushButton(this);
    m_rButton = new QPushButton(this);
    m_lButton->setFixedSize(18, 38);
    m_rButton->setFixedSize(18, 38);

    m_lButton->setObjectName("lBtn");
    m_rButton->setObjectName("rBtn");

    m_lButton->setIconSize(QSize(15, 15));
    m_lButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidLeft)));

    m_rButton->setIconSize(QSize(15, 15));
    m_rButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidRight)));
    m_imgBoxIndex = 0;

    m_rButton->hide();
    m_lButton->hide();
    connect(m_rButton, &QPushButton::clicked, [=](bool isClicked) {
        // horizontalScrollBar()->setValue(width());
        if (m_imgBoxIndex <= m_layout->count())
        {
            m_imgBoxIndex += 1;
            hideOrShowRLButton(true);

            horizontalScrollBar()->setValue(width() * m_imgBoxIndex);
        }
    });

    connect(m_lButton, &QPushButton::clicked, [=](bool isClicked) {
        if (m_imgBoxIndex > 0)
        {
            m_imgBoxIndex -= 1;

            // m_lButton->show();
            m_rButton->show();

            hideOrShowRLButton(true);

            horizontalScrollBar()->setValue(width() * m_imgBoxIndex);
        }
    });

    // QString qss = FluStyleSheetUtils::getQssByFileName("../StyleSheet/light/FluHFlipView.qss");
    // setStyleSheet(qss);
    FluStyleSheetUtils::setQssByFileName("FluHFlipView.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluHFlipView::addPixmap(QPixmap pixmap)
{
    // LOG_DEBUG << "context widget margins:" << m_contextWidget->contentsMargins();
    auto imageBox = new FluImageBox(pixmap, m_contextWidget);
    imageBox->setFixedSize(size());
    m_layout->addWidget(imageBox, 0, Qt::AlignHCenter);
    imageBox->setObjectName("imageBox");
}

void FluHFlipView::hideOrShowRLButton(bool isEnter)
{
    if (isEnter)
    {
        m_lButton->show();
        m_rButton->show();
        if (m_imgBoxIndex == 0)
            m_lButton->hide();

        if (m_imgBoxIndex == m_layout->count() - 1)
            m_rButton->hide();
    }
    else
    {
        m_lButton->hide();
        m_rButton->hide();
    }
}

void FluHFlipView::enterEvent(QEnterEvent* event)
{
    hideOrShowRLButton(true);
}

void FluHFlipView::leaveEvent(QEvent* event)
{
    hideOrShowRLButton(false);
}

void FluHFlipView::resizeEvent(QResizeEvent* event)
{
    QScrollArea::resizeEvent(event);
    // fixed pos
    // get height
    // get width

    int h = height();
    int w = width();

    int lY = h / 2 - m_lButton->height() / 2;
    int lX = 5;

    m_lButton->move(lX, lY);

    int rX = w - m_lButton->width() - 5;
    int rY = h / 2 - m_lButton->height() / 2;
    m_rButton->move(rX, rY);
}
