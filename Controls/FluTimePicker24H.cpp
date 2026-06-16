#include "FluTimePicker24H.h"

FluTimePicker24H::FluTimePicker24H(QWidget* parent /*= nullptr*/) : FluWidget(parent)
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

    m_hourBtn->setFixedHeight(30);
    m_minuteBtn->setFixedHeight(30);

    m_hMainLayout->addWidget(m_hourBtn);
    m_hMainLayout->addWidget(m_minuteBtn);

    m_timerPicker24HView = new FluTimePicker24HView;
    // m_timerPicker24HView->setFixedWidth(240);
    m_timerPicker24HView->hide();

    setFixedSize(240, 30);
    connect(m_hourBtn, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_minuteBtn, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(this, &FluTimePicker24H::clicked, [=]() {
        // get current time
        // LOG_DEBUG << "Called";
        // show FluTimerPickerView

        int nX = 0 - 8;
        int nY = height() / 2 - 180;
        QPoint gPoint = mapToGlobal(QPoint(nX, nY));
        m_timerPicker24HView->move(gPoint.x(), gPoint.y());
        m_timerPicker24HView->show();
    });

    connect(m_timerPicker24HView, &FluTimePicker24HView::clickedOk, [=]() {
        QString sHour = QString::asprintf("%02d", m_timerPicker24HView->getHour());
        m_hourBtn->setText(sHour);

        QString sMinute = QString::asprintf("%02d", m_timerPicker24HView->getMinute());
        m_minuteBtn->setText(sMinute);
    });

    onThemeChanged();
}

void FluTimePicker24H::mouseReleaseEvent(QMouseEvent* event)
{
    emit clicked();
}

void FluTimePicker24H::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluTimePicker24H::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluTimePicker24H.qss", this, FluThemeUtils::getUtils()->getTheme());
}
