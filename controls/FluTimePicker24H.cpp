#include "FluTimePicker24H.h"

FluTimePicker24H::FluTimePicker24H(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);

    m_hourButton = new QPushButton;
    m_hourButton->setText(tr("hour"));
    m_hourButton->setObjectName("hourBtn");

    m_minuteButton = new QPushButton;
    m_minuteButton->setText(tr("minute"));
    m_minuteButton->setObjectName("minuteBtn");

    m_hourButton->setFixedHeight(30);
    m_minuteButton->setFixedHeight(30);

    m_mainLayout->addWidget(m_hourButton);
    m_mainLayout->addWidget(m_minuteButton);

    m_timerPicker24HView = new FluTimePicker24HView;
    // m_timerPicker24HView->setFixedWidth(240);
    m_timerPicker24HView->hide();

    setFixedSize(240, 30);
    connect(m_hourButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_minuteButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(this, &FluTimePicker24H::clicked, [=]() {
        // get current time
        // LOG_DEBUG << "Called";
        // show FluTimerPickerView

        int x = 0 - 8;
        int y = height() / 2 - 180;
        QPoint gPoint = mapToGlobal(QPoint(x, y));
        m_timerPicker24HView->move(gPoint.x(), gPoint.y());
        m_timerPicker24HView->show();
    });

    connect(m_timerPicker24HView, &FluTimePicker24HView::clickedOk, [=]() {
        QString sHour = QString::asprintf("%02d", m_timerPicker24HView->getHour());
        m_hourButton->setText(sHour);

        QString sMinute = QString::asprintf("%02d", m_timerPicker24HView->getMinute());
        m_minuteButton->setText(sMinute);
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
    FluStyleSheetUtils::setQssByFileName("FluTimePicker24H.qss", this, FluThemeUtils::getUtils()->getTheme());
}
