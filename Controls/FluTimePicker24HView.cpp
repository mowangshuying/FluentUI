#include "FluTimePicker24HView.h"

FluTimePicker24HView::FluTimePicker24HView(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_isFirstShow(true)
{
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
    // setLayout(m_viewLayout);
    m_mainLayout->addLayout(m_viewLayout);

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

    m_viewLayout->setSpacing(0);
    m_viewLayout->addWidget(m_hourView);
    m_viewLayout->addWidget(new FluHSplitLine);
    m_viewLayout->addWidget(m_minuteView);

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

    m_mask = new FluTimePickerViewMask(m_mainView);
    m_mask->addItem("", 120, 40);
    m_mask->addItem("", 120, 40);

    setMinute(0);
    setHour(0);

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

    connect(m_hourView, &FluLoopView::visibaleMidIndexChanged, [=](int index) { m_mask->setItemText(0, m_hourView->getCurrentText()); });

    connect(m_minuteView, &FluLoopView::visibaleMidIndexChanged, [=](int index) { m_mask->setItemText(1, m_minuteView->getCurrentText()); });

    connect(m_mask, &FluTimePickerViewMask::wheelChanged, [=](int index, QWheelEvent* wheelEvent) {
        if (index == 0)
            QApplication::sendEvent(m_hourView->viewport(), wheelEvent);
        else if (index == 1)
            QApplication::sendEvent(m_minuteView->viewport(), wheelEvent);
    });

    connect(m_mask, &FluTimePickerViewMask::enterChanged, [=](int index, QEnterEvent* event) {
        // LOG_DEBUG << "index:" << index;
        if (index == 0)
            QApplication::sendEvent(m_hourView, event);
        else if (index == 1)
            QApplication::sendEvent(m_minuteView, event);
    });

    connect(m_mask, &FluTimePickerViewMask::leaveChanged, [=](int index, QEvent* event) {
        // LOG_DEBUG << "index:" << index;
        if (index == 0)
            QApplication::sendEvent(m_hourView, event);
        else if (index == 1)
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
    QWidget::showEvent(event);
    // LOG_DEBUG << "size:" << size();
    if (!m_isFirstShow)
        return;

    m_isFirstShow = false;
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
        m_okButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept, FluTheme::Light));
        m_cancelButton->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel, FluTheme::Light));

        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/light/FluTimePicker24HView.qss", this);
    }
    else
    {
        m_okButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept, FluTheme::Dark));
        m_cancelButton->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel, FluTheme::Dark));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/dark/FluTimePicker24HView.qss", this);
    }
    FluStyleSheetUtils::setQssByFileName("FluTimePicker24HView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
