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

    m_vLayout = new QVBoxLayout;
    //  m_hLayout->insertSpacing(0, -11);
    m_contextWidget->setLayout(m_vLayout);
    m_vLayout->setSpacing(0);
    m_vLayout->setContentsMargins(0, 0, 0, 0);
    m_vLayout->setAlignment(Qt::AlignLeft);

    // m_hLayout->
    m_contextWidget->setContentsMargins(0, 0, 0, 0);

    m_contextWidget->setObjectName("contextWidget");

    m_tBtn = new QPushButton(this);
    m_bBtn = new QPushButton(this);
    m_tBtn->setFixedSize(38, 18);
    m_bBtn->setFixedSize(38, 18);

    m_tBtn->setObjectName("tBtn");
    m_bBtn->setObjectName("bBtn");

    m_tBtn->setIconSize(QSize(15, 15));
    m_tBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp)));

    m_bBtn->setIconSize(QSize(15, 15));
    m_bBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown)));
    m_nImgBoxIndex = 0;

    m_tBtn->hide();
    m_bBtn->hide();
    connect(m_bBtn, &QPushButton::clicked, [=](bool bClicked) {
        // horizontalScrollBar()->setValue(width());
        if (m_nImgBoxIndex <= m_vLayout->count())
        {
            m_nImgBoxIndex += 1;
            hideOrShowTBBtn(true);

            verticalScrollBar()->setValue(height() * m_nImgBoxIndex);
        }
    });

    connect(m_tBtn, &QPushButton::clicked, [=](bool bClicked) {
        if (m_nImgBoxIndex > 0)
        {
            m_nImgBoxIndex -= 1;

            // m_lBtn->show();
            m_bBtn->show();

            hideOrShowTBBtn(true);

            verticalScrollBar()->setValue(height() * m_nImgBoxIndex);
        }
    });

    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluVFlipView.qss");
    setStyleSheet(qss);
}

void FluVFlipView::addPixmap(QPixmap pixmap)
{
    auto imageBox = new FluImageBox(pixmap, m_contextWidget);
    imageBox->setFixedSize(size());
    m_vLayout->addWidget(imageBox, 0, Qt::AlignHCenter);
    imageBox->setObjectName("imageBox");
}
