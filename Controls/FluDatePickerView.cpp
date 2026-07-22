#include "FluDatePickerView.h"
#include <QApplication>

FluDatePickerView::FluDatePickerView(QWidget* parent /*= nullptr*/) : FluDatePickerView(true, parent)
{
}

FluDatePickerView::FluDatePickerView(bool isYMD, QWidget* parent /*= nullptr*/) : FluWidget(parent), m_isFirstShow(true), m_mask(nullptr)
{
    m_isYMD = isYMD;
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    m_mainViewLayout = new QHBoxLayout;
    setLayout(m_mainViewLayout);
    m_mainViewLayout->setContentsMargins(8, 8, 8, 8);

    m_mainView = new QFrame;
    m_mainView->setObjectName("mainView");
    m_mainViewLayout->addWidget(m_mainView);

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(4, 4, 4, 4);
    m_mainLayout->setSpacing(0);
    m_mainView->setLayout(m_mainLayout);

    m_viewLayout = new QHBoxLayout;
    m_viewLayout->setSpacing(0);
    m_viewLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addLayout(m_viewLayout);

    m_monthView = new FluLoopView(140);
    m_dayView = new FluLoopView(80);
    m_yearView = new FluLoopView(80);

    m_mainView->setFixedWidth(308);
    setFixedWidth(324);

    // set month data;
    std::vector<QString> datas{tr("January"), tr("February"), tr("March"), tr("April"), tr("May"), tr("June"), tr("July"), tr("August"), tr("September"), tr("October"), tr("November"), tr("December")};
    m_monthView->setAllItems(datas);

    // set day data;
    datas.clear();
    for (int i = 0; i < 30; i++)
    {
        QString str = QString::asprintf("%02d", i + 1);
        datas.push_back(str);
    }
    m_dayView->setAllItems(datas);

    datas.clear();
    for (int i = 0; i < 200; i++)
    {
        QString str = QString::asprintf("%04d", i + 1924);
        datas.push_back(str);
    }
    m_yearView->setAllItems(datas);

    m_viewLayout->setSpacing(0);

    if (!isYMD)
    {
        m_viewLayout->addWidget(m_monthView);
        m_viewLayout->addWidget(new FluHSplitLine);
        m_viewLayout->addWidget(m_dayView);
        m_viewLayout->addWidget(new FluHSplitLine);
        m_viewLayout->addWidget(m_yearView);
    }
    else
    {
        m_viewLayout->addWidget(m_yearView);
        m_viewLayout->addWidget(new FluHSplitLine);
        m_viewLayout->addWidget(m_monthView);
        m_viewLayout->addWidget(new FluHSplitLine);
        m_viewLayout->addWidget(m_dayView);
    }

    m_buttonLayout = new QHBoxLayout;
    m_buttonLayout->setContentsMargins(4, 4, 4, 4);

    m_okButton = new QPushButton;
    m_cancelButton = new QPushButton;

    m_okButton->setObjectName("okBtn");
    m_cancelButton->setObjectName("cancelBtn");

    m_okButton->setFixedHeight(40);
    m_cancelButton->setFixedHeight(40);

    m_okButton->setIconSize(QSize(25, 25));
    m_okButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept));

    m_cancelButton->setIconSize(QSize(25, 25));
    m_cancelButton->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel));

    m_buttonLayout->addWidget(m_okButton);
    m_buttonLayout->addWidget(m_cancelButton);

    m_mainLayout->addWidget(new FluVSplitLine);
    m_mainLayout->addLayout(m_buttonLayout);

    m_mask = new FluDatePickerViewMask(m_mainView);
    if (!m_isYMD)
    {
        m_mask->addItem("", 140, 40);
        m_mask->addItem("", 80, 40);
        m_mask->addItem("", 80, 40);
    }
    else
    {
        m_mask->addItem("", 80, 40);
        m_mask->addItem("", 140, 40);
        m_mask->addItem("", 80, 40);
    }

    setDay(0);
    setMonth(0);
    setYear(0 + 100);

    setShadowEffect();
    connect(m_okButton, &QPushButton::clicked, [=]() {
        updateTime();
        emit clickedOk();
        close();
    });
    connect(m_cancelButton, &QPushButton::clicked, [=]() {
        emit clickedCancel();
        close();
    });

    connect(m_monthView, &FluLoopView::visibaleMidIndexChanged, [=](int index) {
        int days = getMonthDays(m_yearView->getVisibleMidIndex() + 1924, m_monthView->getVisibleMidIndex() + 1);
        std::vector<QString> datas;
        for (int i = 0; i < days; i++)
        {
            QString str = QString::asprintf("%02d", i + 1);
            datas.push_back(str);
        }

        m_dayView->clear();
        m_dayView->setAllItems(datas);
        m_dayView->setVisibaleMidIndex(m_dayView->getVisibleMidIndex());

        if (!m_isYMD)
            m_mask->setItemText(0, m_monthView->getCurrentText());
        else
            m_mask->setItemText(1, m_monthView->getCurrentText());
    });

    connect(m_dayView, &FluLoopView::visibaleMidIndexChanged, [=](int index) {
        if (!m_isYMD)
            m_mask->setItemText(1, m_dayView->getCurrentText());
        else
            m_mask->setItemText(2, m_dayView->getCurrentText());
    });

    connect(m_yearView, &FluLoopView::visibaleMidIndexChanged, [=](int index) {
        int days = getMonthDays(m_yearView->getVisibleMidIndex() + 1924, m_monthView->getVisibleMidIndex() + 1);
        std::vector<QString> datas;
        for (int i = 0; i < days; i++)
        {
            QString str = QString::asprintf("%02d", i + 1);
            datas.push_back(str);
        }

        m_dayView->clear();
        m_dayView->setAllItems(datas);
        m_dayView->setVisibaleMidIndex(m_dayView->getVisibleMidIndex());

        if (!m_isYMD)
            m_mask->setItemText(2, m_yearView->getCurrentText());
        else
            m_mask->setItemText(0, m_yearView->getCurrentText());
    });

    connect(m_mask, &FluDatePickerViewMask::wheelChanged, [=](int index, QWheelEvent* wheelEvent) {
        // LOG_DEBUG << "index:" << index;

        if (!m_isYMD)
        {
            if (index == 0)
                QApplication::sendEvent(m_monthView->viewport(), wheelEvent);
            else if (index == 1)
                QApplication::sendEvent(m_dayView->viewport(), wheelEvent);
            else
                QApplication::sendEvent(m_yearView->viewport(), wheelEvent);
        }
        else
        {
            if (index == 1)
                QApplication::sendEvent(m_monthView->viewport(), wheelEvent);
            else if (index == 2)
                QApplication::sendEvent(m_dayView->viewport(), wheelEvent);
            else
                QApplication::sendEvent(m_yearView->viewport(), wheelEvent);
        }
    });

    connect(m_mask, &FluDatePickerViewMask::enterChanged, [=](int index, QEnterEvent* event) {
        if (!m_isYMD)
        {
            // LOG_DEBUG << "index:" << index;
            if (index == 0)
                QApplication::sendEvent(m_monthView, event);
            else if (index == 1)
                QApplication::sendEvent(m_dayView, event);
            else
                QApplication::sendEvent(m_yearView, event);
        }
        else
        {
            // LOG_DEBUG << "index:" << index;
            if (index == 1)
                QApplication::sendEvent(m_monthView, event);
            else if (index == 2)
                QApplication::sendEvent(m_dayView, event);
            else
                QApplication::sendEvent(m_yearView, event);
        }
    });

    connect(m_mask, &FluDatePickerViewMask::leaveChanged, [=](int index, QEvent* event) {
        if (!isYMD)
        {
            // LOG_DEBUG << "index:" << index;
            if (index == 0)
                QApplication::sendEvent(m_monthView, event);
            else if (index == 1)
                QApplication::sendEvent(m_dayView, event);
            else
                QApplication::sendEvent(m_yearView, event);
        }
        else
        {
            // LOG_DEBUG << "index:" << index;
            if (index == 1)
                QApplication::sendEvent(m_monthView, event);
            else if (index == 2)
                QApplication::sendEvent(m_dayView, event);
            else
                QApplication::sendEvent(m_yearView, event);
        }
    });

    onThemeChanged();
}

int FluDatePickerView::getMonth()
{
    return m_month;
}

int FluDatePickerView::getDay()
{
    return m_day;
}

int FluDatePickerView::getYear()
{
    return m_year;
}

void FluDatePickerView::setMonth(int month)
{
    m_month = month;
    m_monthView->setVisibaleMidIndex(month);
    if (m_mask != nullptr)
    {
        if (!m_isYMD)
        {
            m_mask->setItemText(0, m_monthView->getCurrentText());
        }
        else
        {
            m_mask->setItemText(1, m_monthView->getCurrentText());
        }
    }
}

void FluDatePickerView::setDay(int day)
{
    m_day = day;
    m_dayView->setVisibaleMidIndex(day);
    if (m_mask != nullptr)
    {
        if (!m_isYMD)
        {
            m_mask->setItemText(1, m_dayView->getCurrentText());
        }
        else
        {
            m_mask->setItemText(2, m_dayView->getCurrentText());
        }
    }
    // m_mask->setItemText(1, m_dayView->getCurrentText());
    // m_hourView->scrollTo(minute);
}

void FluDatePickerView::setYear(int year)
{
    m_year = year;
    m_yearView->setVisibaleMidIndex(year);
    if (m_mask != nullptr)
    {
        if (!m_isYMD)
            m_mask->setItemText(2, m_yearView->getCurrentText());
        else
            m_mask->setItemText(0, m_yearView->getCurrentText());
    }
}

void FluDatePickerView::updateTime()
{
    m_month = m_monthView->getVisibleMidIndex();
    m_day = m_dayView->getVisibleMidIndex();
    m_year = m_yearView->getVisibleMidIndex();
}

int FluDatePickerView::getMonthDays(int year, int month)
{
    // get Month, getYear, output days;
    QDate date(year, month, 1);
    int count = 0;
    while (1)
    {
        count++;
        date = date.addDays(1);
        if (month != date.month())
        {
            break;
        }
    }
    return count;
}

void FluDatePickerView::setShadowEffect()
{
    // set shadow;
    m_shadowEffect = new QGraphicsDropShadowEffect;
    m_shadowEffect->setBlurRadius(8);
    m_shadowEffect->setOffset(0, 0);
    m_shadowEffect->setColor(QColor(0, 0, 0, 30));
    if (FluThemeUtils::isDarkTheme())
        m_shadowEffect->setColor(QColor(0, 0, 0, 80));
    m_mainView->setGraphicsEffect(m_shadowEffect);
}

void FluDatePickerView::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluDatePickerView::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    if (!m_isFirstShow)
        return;

    m_isFirstShow = false;
    m_monthView->scrollTo(m_month);
    m_dayView->scrollTo(m_day);
    m_yearView->scrollTo(m_year);
}

void FluDatePickerView::resizeEvent(QResizeEvent* event)
{
    m_mask->resize(m_mainView->width() - 8, 40);
    m_mask->move(4, 166);
}

void FluDatePickerView::onThemeChanged()
{
    m_okButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept, FluThemeUtils::getUtils()->getTheme()));
    m_cancelButton->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUtils::setQssByFileName("FluDatePickerView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
