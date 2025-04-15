#include "FluDatePickerView.h"
#include <QApplication>

FluDatePickerView::FluDatePickerView(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_bFirstShow(true), m_mask(nullptr)
{
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    m_hMainViewLayout = new QHBoxLayout;
    setLayout(m_hMainViewLayout);
    m_hMainViewLayout->setContentsMargins(8, 8, 8, 8);

    m_mainView = new QFrame;
    m_mainView->setObjectName("mainView");
    m_hMainViewLayout->addWidget(m_mainView);

    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setContentsMargins(4, 4, 4, 4);
    m_vMainLayout->setSpacing(0);
    m_mainView->setLayout(m_vMainLayout);

    m_hViewLayout = new QHBoxLayout;
    m_hViewLayout->setSpacing(0);
    m_hViewLayout->setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->addLayout(m_hViewLayout);

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

    m_hViewLayout->setSpacing(0);
    m_hViewLayout->addWidget(m_monthView);
    m_hViewLayout->addWidget(new FluHSplitLine);
    m_hViewLayout->addWidget(m_dayView);
    m_hViewLayout->addWidget(new FluHSplitLine);
    m_hViewLayout->addWidget(m_yearView);

    m_hBtnLayout = new QHBoxLayout;
    m_hBtnLayout->setContentsMargins(4, 4, 4, 4);

    m_okBtn = new QPushButton;
    m_cancelBtn = new QPushButton;

    m_okBtn->setObjectName("okBtn");
    m_cancelBtn->setObjectName("cancelBtn");

    m_okBtn->setFixedHeight(40);
    m_cancelBtn->setFixedHeight(40);

    m_okBtn->setIconSize(QSize(25, 25));
    m_okBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept));

    m_cancelBtn->setIconSize(QSize(25, 25));
    m_cancelBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel));

    m_hBtnLayout->addWidget(m_okBtn);
    m_hBtnLayout->addWidget(m_cancelBtn);

    m_vMainLayout->addWidget(new FluVSplitLine);
    m_vMainLayout->addLayout(m_hBtnLayout);

    m_mask = new FluDatePickerViewMask(m_mainView);
    m_mask->addItem("", 140, 40);
    m_mask->addItem("", 80, 40);
    m_mask->addItem("", 80, 40);

    setDay(0);
    setMonth(0);
    setYear(0 + 100);

    setShadowEffect();
    connect(m_okBtn, &QPushButton::clicked, [=]() {
        updateTime();
        emit clickedOk();
        close();
    });
    connect(m_cancelBtn, &QPushButton::clicked, [=]() {
        emit clickedCancel();
        close();
    });

    connect(m_monthView, &FluLoopView::visibaleMidIndexChanged, [=](int nIndex) {
        int nDays = getMonthDays(m_yearView->getVisibleMidIndex() + 1924, m_monthView->getVisibleMidIndex() + 1);
        std::vector<QString> datas;
        for (int i = 0; i < nDays; i++)
        {
            QString str = QString::asprintf("%02d", i + 1);
            datas.push_back(str);
        }

        m_dayView->clear();
        m_dayView->setAllItems(datas);
        m_dayView->setVisibaleMidIndex(m_dayView->getVisibleMidIndex());
        m_mask->setItemText(0, m_monthView->getCurrentText());
    });

    connect(m_dayView, &FluLoopView::visibaleMidIndexChanged, [=](int nIndex) { m_mask->setItemText(1, m_dayView->getCurrentText()); });

    connect(m_yearView, &FluLoopView::visibaleMidIndexChanged, [=](int nIndex) {
        int nDays = getMonthDays(m_yearView->getVisibleMidIndex() + 1924, m_monthView->getVisibleMidIndex() + 1);
        std::vector<QString> datas;
        for (int i = 0; i < nDays; i++)
        {
            QString str = QString::asprintf("%02d", i + 1);
            datas.push_back(str);
        }

        m_dayView->clear();
        m_dayView->setAllItems(datas);
        m_dayView->setVisibaleMidIndex(m_dayView->getVisibleMidIndex());
        m_mask->setItemText(2, m_yearView->getCurrentText());
    });

    connect(m_mask, &FluDatePickerViewMask::wheelChanged, [=](int nIndex, QWheelEvent* wheelEvent) {
        // LOG_DEBUG << "nIndex:" << nIndex;
        if (nIndex == 0)
            QApplication::sendEvent(m_monthView->viewport(), wheelEvent);
        else if (nIndex == 1)
            QApplication::sendEvent(m_dayView->viewport(), wheelEvent);
        else
            QApplication::sendEvent(m_yearView->viewport(), wheelEvent);
    });

    connect(m_mask, &FluDatePickerViewMask::enterChanged, [=](int nIndex, QEnterEvent* event) {
        // LOG_DEBUG << "nIndex:" << nIndex;
        if (nIndex == 0)
            QApplication::sendEvent(m_monthView, event);
        else if (nIndex == 1)
            QApplication::sendEvent(m_dayView, event);
        else
            QApplication::sendEvent(m_yearView, event);
    });

    connect(m_mask, &FluDatePickerViewMask::leaveChanged, [=](int nIndex, QEvent* event) {
        // LOG_DEBUG << "nIndex:" << nIndex;
        if (nIndex == 0)
            QApplication::sendEvent(m_monthView, event);
        else if (nIndex == 1)
            QApplication::sendEvent(m_dayView, event);
        else
            QApplication::sendEvent(m_yearView, event);
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
        m_mask->setItemText(0, m_monthView->getCurrentText());
    // m_hourView->scrollTo(hour);
}

void FluDatePickerView::setDay(int day)
{
    m_day = day;
    m_dayView->setVisibaleMidIndex(day);
    if (m_mask != nullptr)
        m_mask->setItemText(1, m_dayView->getCurrentText());
    // m_hourView->scrollTo(minute);
}

void FluDatePickerView::setYear(int year)
{
    m_year = year;
    m_yearView->setVisibaleMidIndex(year);
    if (m_mask != nullptr)
        m_mask->setItemText(2, m_yearView->getCurrentText());
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
    FluWidget::showEvent(event);
    if (!m_bFirstShow)
        return;

    m_bFirstShow = false;
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
    m_okBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept, FluThemeUtils::getUtils()->getTheme()));
    m_cancelBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUitls::setQssByFileName("FluDatePickerView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
