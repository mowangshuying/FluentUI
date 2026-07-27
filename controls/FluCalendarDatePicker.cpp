#include "FluCalendarDatePicker.h"

FluCalendarDatePicker::FluCalendarDatePicker(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    m_mainLayout = new QHBoxLayout;
    m_textButton = new QPushButton;
    m_iconButton = new QPushButton;

    m_textButton->setObjectName("textButton");
    m_iconButton->setObjectName("iconButton");

    setLayout(m_mainLayout);

    setFixedSize(120, 30);
    m_textButton->setText(tr("Pick a date"));

    m_iconButton->setIconSize(QSize(20, 20));
    m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Calendar));
    m_iconButton->setFixedWidth(30);

    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addWidget(m_textButton);
    m_mainLayout->addWidget(m_iconButton);

    m_calendarView = new FluCalendarView(window());
    m_calendarView->setWindowFlag(Qt::Popup);

    connect(m_calendarView, &FluCalendarView::selectedDate, [=](QDate date) {
        QString dateText = QString::asprintf("%d/%d/%d", date.month(), date.day(), date.year());
        m_textButton->setText(dateText);
        // LOG_DEBUG << date;
        m_calendarView->hide();

        emit selectedDate(date);
    });

    connect(this, &FluCalendarDatePicker::clicked, [=]() { onClicked(); });
    connect(m_textButton, &QPushButton::clicked, [=]() { onClicked(); });
    connect(m_iconButton, &QPushButton::clicked, [=]() { onClicked(); });

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

QDate FluCalendarDatePicker::getCurDate()
{
    return m_calendarView->getCurDate();
}

void FluCalendarDatePicker::setCurDate(QDate date)
{
    m_calendarView->setCurDate(date);

    emit m_calendarView->selectedDate(date);
}

void FluCalendarDatePicker::onClicked()
{
    // the pos
    int x = width() / 2;
    int y = height() + 5;

    // LOG_DEBUG << "x:" << x << ",y:" << y;
    // LOG_DEBUG << m_calendarView->width();
    QPoint gPoint = mapToGlobal(QPoint(x, y));
    // LOG_DEBUG << gPoint;
    m_calendarView->move(gPoint.x() - m_calendarView->width() / 2, gPoint.y());
    m_calendarView->show();
}

void FluCalendarDatePicker::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Calendar));
    }
    else
    {
        m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Calendar, FluTheme::Dark));
    }

    FluStyleSheetUtils::setQssByFileName("FluCalendarDatePicker.qss", this, FluThemeUtils::getUtils()->getTheme());
}
