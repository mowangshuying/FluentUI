#include "FluTimePickerAP.h"

FluTimePickerAP::FluTimePickerAP(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(0, 0, 0, 0);
    m_hMainLayout->setSpacing(0);
    setLayout(m_hMainLayout);

    m_hourBtn = new QPushButton;
    m_hourBtn->setText(tr("hour"));
    m_hourBtn->setObjectName("hourBtn");

    m_minuteBtn = new QPushButton;
    m_minuteBtn->setText(tr("minute"));
    m_minuteBtn->setObjectName("minuteBtn");

    m_apBtn = new QPushButton;
    m_apBtn->setText(tr("AM"));
    m_apBtn->setObjectName("apBtn");

    m_hourBtn->setFixedHeight(30);
    m_minuteBtn->setFixedHeight(30);
    m_apBtn->setFixedHeight(30);

    m_hMainLayout->addWidget(m_hourBtn);
    m_hMainLayout->addWidget(m_minuteBtn);
    m_hMainLayout->addWidget(m_apBtn);

    m_timerPickerApView = new FluTimePickerAPView;
    // m_timerPickerApView->setFixedWidth(240);
    m_timerPickerApView->hide();

    setFixedSize(240, 30);
    connect(m_hourBtn, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_minuteBtn, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(this, &FluTimePickerAP::clicked, [=]() {
        // get current time
        // LOG_DEBUG << "Called";
        // show FluTimerPickerView

        int nX = -8;
        int nY = height() / 2 - 180;
        QPoint gPoint = mapToGlobal(QPoint(nX, nY));
        m_timerPickerApView->move(gPoint.x(), gPoint.y());
        m_timerPickerApView->show();
    });

    connect(m_timerPickerApView, &FluTimePickerAPView::clickedOk, [=]() {
        QString sHour = QString::asprintf("%02d", m_timerPickerApView->getHour());
        m_hourBtn->setText(sHour);

        QString sMinute = QString::asprintf("%02d", m_timerPickerApView->getMinute());
        m_minuteBtn->setText(sMinute);

        QString sAmOrPm = m_timerPickerApView->isAm() ? tr("AM") : tr("PM");
        m_apBtn->setText(sAmOrPm);
    });

    onThemeChanged();
}

void FluTimePickerAP::mouseReleaseEvent(QMouseEvent* event)
{
    emit clicked();
}

void FluTimePickerAP::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluTimePickerAP::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluTimePickerAP.qss", this, FluThemeUtils::getUtils()->getTheme());
}
