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

    m_hLayout = new QHBoxLayout;
    //  m_hLayout->insertSpacing(0, -11);
    m_contextWidget->setLayout(m_hLayout);
    m_hLayout->setSpacing(0);
    m_hLayout->setContentsMargins(0, 0, 0, 0);
    m_hLayout->setAlignment(Qt::AlignLeft);

    // m_hLayout->
    m_contextWidget->setContentsMargins(0, 0, 0, 0);

    m_contextWidget->setObjectName("contextWidget");

    m_lBtn = new QPushButton(this);
    m_rBtn = new QPushButton(this);
    m_lBtn->setFixedSize(18, 38);
    m_rBtn->setFixedSize(18, 38);

    m_lBtn->setObjectName("lBtn");
    m_rBtn->setObjectName("rBtn");

    m_lBtn->setIconSize(QSize(15, 15));
    m_lBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidLeft)));

    m_rBtn->setIconSize(QSize(15, 15));
    m_rBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidRight)));
    m_nImgBoxIndex = 0;

    m_rBtn->hide();
    m_lBtn->hide();
    connect(m_rBtn, &QPushButton::clicked, [=](bool bClicked) {
        // horizontalScrollBar()->setValue(width());
        if (m_nImgBoxIndex <= m_hLayout->count())
        {
            m_nImgBoxIndex += 1;
            hideOrShowRLBtn(true);

            horizontalScrollBar()->setValue(width() * m_nImgBoxIndex);
        }
    });

    connect(m_lBtn, &QPushButton::clicked, [=](bool bClicked) {
        if (m_nImgBoxIndex > 0)
        {
            m_nImgBoxIndex -= 1;

            // m_lBtn->show();
            m_rBtn->show();

            hideOrShowRLBtn(true);

            horizontalScrollBar()->setValue(width() * m_nImgBoxIndex);
        }
    });

    // QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluHFlipView.qss");
    // setStyleSheet(qss);
    FluStyleSheetUitls::setQssByFileName("FluHFlipView.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluHFlipView::addPixmap(QPixmap pixmap)
{
    // LOG_DEBUG << "context widget margins:" << m_contextWidget->contentsMargins();
    auto imageBox = new FluImageBox(pixmap, m_contextWidget);
    imageBox->setFixedSize(size());
    m_hLayout->addWidget(imageBox, 0, Qt::AlignHCenter);
    imageBox->setObjectName("imageBox");
}

void FluHFlipView::hideOrShowRLBtn(bool bEnter)
{
    if (bEnter)
    {
        m_lBtn->show();
        m_rBtn->show();
        if (m_nImgBoxIndex == 0)
            m_lBtn->hide();

        if (m_nImgBoxIndex == m_hLayout->count() - 1)
            m_rBtn->hide();
    }
    else
    {
        m_lBtn->hide();
        m_rBtn->hide();
    }
}

void FluHFlipView::enterEvent(QEnterEvent* event)
{
    hideOrShowRLBtn(true);
}

void FluHFlipView::leaveEvent(QEvent* event)
{
    hideOrShowRLBtn(false);
}

void FluHFlipView::resizeEvent(QResizeEvent* event)
{
    QScrollArea::resizeEvent(event);
    // fixed pos
    // get height
    // get width

    int nH = height();
    int nW = width();

    int nLY = nH / 2 - m_lBtn->height() / 2;
    int nLX = 5;

    m_lBtn->move(nLX, nLY);

    int nRX = nW - m_lBtn->width() - 5;
    int nRY = nH / 2 - m_lBtn->height() / 2;
    m_rBtn->move(nRX, nRY);
}
