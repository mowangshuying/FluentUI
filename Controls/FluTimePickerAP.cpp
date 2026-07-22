#include "FluTimePickerAP.h"

FluTimePickerAP::FluTimePickerAP(QWidget* parent /*= nullptr*/) : FluWidget(parent)
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

    m_apButton = new QPushButton;
    m_apButton->setText(tr("AM"));
    m_apButton->setObjectName("apBtn");

    m_hourButton->setFixedHeight(30);
    m_minuteButton->setFixedHeight(30);
    m_apButton->setFixedHeight(30);

    m_mainLayout->addWidget(m_hourButton);
    m_mainLayout->addWidget(m_minuteButton);
    m_mainLayout->addWidget(m_apButton);

    m_timerPickerApView = new FluTimePickerAPView;
    // m_timerPickerApView->setFixedWidth(240);
    m_timerPickerApView->hide();

    setFixedSize(240, 30);
    connect(m_hourButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_minuteButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(this, &FluTimePickerAP::clicked, [=]() {
        // get current time
        // LOG_DEBUG << "Called";
        // show FluTimerPickerView

        int x = -8;
        int y = height() / 2 - 180;
        QPoint gPoint = mapToGlobal(QPoint(x, y));
        m_timerPickerApView->move(gPoint.x(), gPoint.y());
        m_timerPickerApView->show();
    });

    connect(m_timerPickerApView, &FluTimePickerAPView::clickedOk, [=]() {
        QString sHour = QString::asprintf("%02d", m_timerPickerApView->getHour());
        m_hourButton->setText(sHour);

        QString sMinute = QString::asprintf("%02d", m_timerPickerApView->getMinute());
        m_minuteButton->setText(sMinute);

        QString sAmOrPm = m_timerPickerApView->isAm() ? tr("AM") : tr("PM");
        m_apButton->setText(sAmOrPm);
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
    FluStyleSheetUtils::setQssByFileName("FluTimePickerAP.qss", this, FluThemeUtils::getUtils()->getTheme());
}
