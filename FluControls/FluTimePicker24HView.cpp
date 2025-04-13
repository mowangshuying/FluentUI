#include "FluTimePicker24HView.h"

FluTimePicker24HView::FluTimePicker24HView(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_bFirstShow(true)
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
    // setLayout(m_hViewLayout);
    m_vMainLayout->addLayout(m_hViewLayout);

    m_hourView = new FluLoopView(120);
    m_minuteView = new FluLoopView(120);
    m_mainView->setFixedWidth(248);
    setFixedWidth(264);

    // set hour data;
    std::vector<QString> datas;
    for (int i = 0; i < 24; i++)
    {
        QString str = QString::asprintf("%02d", i);
        datas.push_back(str);
    }
    m_hourView->setAllItems(datas);

    // set minute data;
    datas.clear();
    for (int i = 0; i < 60; i++)
    {
        QString str = QString::asprintf("%02d", i);
        datas.push_back(str);
    }
    m_minuteView->setAllItems(datas);

    m_hViewLayout->setSpacing(0);
    m_hViewLayout->addWidget(m_hourView);
    m_hViewLayout->addWidget(new FluHSplitLine);
    m_hViewLayout->addWidget(m_minuteView);

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

    m_mask = new FluTimePickerViewMask(m_mainView);
    m_mask->addItem("", 120, 40);
    m_mask->addItem("", 120, 40);

    setMinute(0);
    setHour(0);

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

    connect(m_hourView, &FluLoopView::visibaleMidIndexChanged, [=](int nIndex) { m_mask->setItemText(0, m_hourView->getCurrentText()); });

    connect(m_minuteView, &FluLoopView::visibaleMidIndexChanged, [=](int nIndex) { m_mask->setItemText(1, m_minuteView->getCurrentText()); });

    connect(m_mask, &FluTimePickerViewMask::wheelChanged, [=](int nIndex, QWheelEvent* wheelEvent) {
        if (nIndex == 0)
            QApplication::sendEvent(m_hourView->viewport(), wheelEvent);
        else if (nIndex == 1)
            QApplication::sendEvent(m_minuteView->viewport(), wheelEvent);
    });

    connect(m_mask, &FluTimePickerViewMask::enterChanged, [=](int nIndex, QEnterEvent* event) {
        // LOG_DEBUG << "nIndex:" << nIndex;
        if (nIndex == 0)
            QApplication::sendEvent(m_hourView, event);
        else if (nIndex == 1)
            QApplication::sendEvent(m_minuteView, event);
    });

    connect(m_mask, &FluTimePickerViewMask::leaveChanged, [=](int nIndex, QEvent* event) {
        // LOG_DEBUG << "nIndex:" << nIndex;
        if (nIndex == 0)
            QApplication::sendEvent(m_hourView, event);
        else if (nIndex == 1)
            QApplication::sendEvent(m_minuteView, event);
    });

    onThemeChanged();
}

int FluTimePicker24HView::getHour()
{
    return m_hour;
}

int FluTimePicker24HView::getMinute()
{
    return m_minute;
}

void FluTimePicker24HView::setHour(int hour)
{
    m_hour = hour;
    m_hourView->setVisibaleMidIndex(hour);
    if (m_mask != nullptr)
        m_mask->setItemText(0, m_hourView->getCurrentText());
    // m_hourView->scrollTo(hour);
}

void FluTimePicker24HView::setMinute(int minute)
{
    m_minute = minute;
    m_minuteView->setVisibaleMidIndex(minute);
    if (m_mask != nullptr)
        m_mask->setItemText(1, m_minuteView->getCurrentText());
    // m_hourView->scrollTo(minute);
}

void FluTimePicker24HView::updateTime()
{
    m_hour = m_hourView->getVisibleMidIndex();
    m_minute = m_minuteView->getVisibleMidIndex();
}

void FluTimePicker24HView::setShadowEffect()
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

void FluTimePicker24HView::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluTimePicker24HView::showEvent(QShowEvent* event)
{
    FluWidget::showEvent(event);
    // LOG_DEBUG << "size:" << size();
    if (!m_bFirstShow)
        return;

    m_bFirstShow = false;
    m_hourView->scrollTo(m_hour);
    m_minuteView->scrollTo(m_minute);
}

void FluTimePicker24HView::resizeEvent(QResizeEvent* event)
{
    m_mask->resize(m_mainView->width() - 10, 40);
    m_mask->move(5, 166);
}

void FluTimePicker24HView::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_okBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept, FluTheme::Light));
        m_cancelBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel, FluTheme::Light));

        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTimePicker24HView.qss", this);
    }
    else
    {
        m_okBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept, FluTheme::Dark));
        m_cancelBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel, FluTheme::Dark));
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTimePicker24HView.qss", this);
    }
    FluStyleSheetUitls::setQssByFileName("FluTimePicker24HView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
