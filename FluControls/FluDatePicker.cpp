#include "FluDatePicker.h"

FluDatePicker::FluDatePicker(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(0, 0, 0, 0);
    m_hMainLayout->setSpacing(0);
    setLayout(m_hMainLayout);

    m_monthBtn = new QPushButton;
    m_monthBtn->setText(tr("month"));
    m_monthBtn->setObjectName("monthBtn");

    m_dayBtn = new QPushButton;
    m_dayBtn->setText(tr("day"));
    m_dayBtn->setObjectName("dayBtn");

    m_yearBtn = new QPushButton;
    m_yearBtn->setText(tr("year"));
    m_yearBtn->setObjectName("yearBtn");

    m_monthBtn->setFixedWidth(140);
    m_dayBtn->setFixedWidth(80);
    m_yearBtn->setFixedWidth(80);

    m_hMainLayout->addWidget(m_monthBtn);
    m_hMainLayout->addWidget(m_dayBtn);
    m_hMainLayout->addWidget(m_yearBtn);

    m_datePickerView = new FluDatePickerView;
    // m_datePickerView->setFixedWidth(300);
    m_datePickerView->hide();

    setFixedSize(300, 30);
    connect(m_monthBtn, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_dayBtn, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_yearBtn, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(this, &FluDatePicker::clicked, [=]() {
        int nX = -8;
        int nY = height() / 2 - 180;
        QPoint gPoint = mapToGlobal(QPoint(nX, nY));
        m_datePickerView->move(gPoint.x(), gPoint.y());
        m_datePickerView->show();
    });

    connect(m_datePickerView, &FluDatePickerView::clickedOk, [=]() {
        const std::vector<QString> sMonths{tr("January"), tr("February"), tr("March"), tr("April"), tr("May"), tr("June"), tr("July"), tr("August"), tr("September"), tr("October"), tr("November"), tr("December")};

        m_monthBtn->setText(sMonths[m_datePickerView->getMonth()]);
        QString sDay = QString::asprintf("%02d", m_datePickerView->getDay() + 1);
        m_dayBtn->setText(sDay);

        QString sYear = QString::asprintf("%04d", m_datePickerView->getYear() + 1924);
        m_yearBtn->setText(sYear);
    });

    onThemeChanged();
}

void FluDatePicker::mouseReleaseEvent(QMouseEvent* event)
{
    emit clicked();
}

void FluDatePicker::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluDatePicker::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluDatePicker.qss", this, FluThemeUtils::getUtils()->getTheme());
}
