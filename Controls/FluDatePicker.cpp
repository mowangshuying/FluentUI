#include "FluDatePicker.h"
#include "FluHSplitLine.h"

FluDatePicker::FluDatePicker(QWidget* parent /*= nullptr*/) : FluDatePicker(true, parent)
{
}

FluDatePicker::FluDatePicker(bool isYMD, QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);

    m_monthButton = new QPushButton;
    m_monthButton->setText(tr("month"));
    m_monthButton->setObjectName("monthBtn");

    m_dayButton = new QPushButton;
    m_dayButton->setText(tr("day"));
    m_dayButton->setObjectName("dayBtn");

    m_yearButton = new QPushButton;
    m_yearButton->setText(tr("year"));
    m_yearButton->setObjectName("yearBtn");

    m_monthButton->setFixedWidth(140);
    m_dayButton->setFixedWidth(80);
    m_yearButton->setFixedWidth(80);

    if (!isYMD)
    {
        m_mainLayout->addWidget(m_monthButton);
        m_mainLayout->addWidget(new FluHSplitLine);
        m_mainLayout->addWidget(m_dayButton);
        m_mainLayout->addWidget(new FluHSplitLine);
        m_mainLayout->addWidget(m_yearButton);
    }
    else
    {
        m_mainLayout->addWidget(m_yearButton);
        m_mainLayout->addWidget(new FluHSplitLine);
        m_mainLayout->addWidget(m_monthButton);
        m_mainLayout->addWidget(new FluHSplitLine);
        m_mainLayout->addWidget(m_dayButton);
    }

    m_datePickerView = new FluDatePickerView(isYMD);
    // m_datePickerView->setFixedWidth(300);
    m_datePickerView->hide();

    setFixedSize(300, 30);
    connect(m_monthButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_dayButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_yearButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(this, &FluDatePicker::clicked, [=]() {
        int x = -8;
        int y = height() / 2 - 180;
        QPoint gPoint = mapToGlobal(QPoint(x, y));
        m_datePickerView->move(gPoint.x(), gPoint.y());
        m_datePickerView->show();
    });

    connect(m_datePickerView, &FluDatePickerView::clickedOk, [=]() {
        const std::vector<QString> months{tr("January"), tr("February"), tr("March"), tr("April"), tr("May"), tr("June"), tr("July"), tr("August"), tr("September"), tr("October"), tr("November"), tr("December")};

        m_monthButton->setText(months[m_datePickerView->getMonth()]);
        QString dayText = QString::asprintf("%02d", m_datePickerView->getDay() + 1);
        m_dayButton->setText(dayText);

        QString yearText = QString::asprintf("%04d", m_datePickerView->getYear() + 1924);
        m_yearButton->setText(yearText);
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
    FluStyleSheetUtils::setQssByFileName("FluDatePicker.qss", this, FluThemeUtils::getUtils()->getTheme());
}
