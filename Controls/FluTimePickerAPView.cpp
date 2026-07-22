#include "FluTimePickerAPView.h"

FluTimePickerAPView::FluTimePickerAPView(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_isAm(true), m_hour(0), m_minute(0), m_isFirstShow(true), m_mask(nullptr)
{
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

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

    m_hourView = new FluLoopView(80);
    m_minuteView = new FluLoopView(80);
    m_ampmView = new FluAmPmView(80);

    m_mainView->setFixedWidth(248);
    setFixedWidth(264);

    // set hour data;
    std::vector<QString> datas;
    for (int i = 0; i < 12; i++)
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
    m_viewLayout->addWidget(new FluHSplitLine);
    m_viewLayout->addWidget(m_ampmView);

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
    m_mask->addItem("", 80, 40);
    m_mask->addItem("", 80, 40);
    m_mask->addItem("", 80, 40);

    setMinute(0);
    setHour(0);
    setAm(true);

    m_mask->setItemText(0, m_hourView->getCurrentText());
    m_mask->setItemText(1, m_minuteView->getCurrentText());
    m_mask->setItemText(2, m_ampmView->getCurrentText());

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

    connect(m_ampmView, &FluAmPmView::currentItemChanged, [=]() { m_mask->setItemText(2, m_ampmView->getCurrentText()); });

    connect(m_mask, &FluTimePickerViewMask::wheelChanged, [=](int index, QWheelEvent* wheelEvent) {
        if (index == 0)
            QApplication::sendEvent(m_hourView->viewport(), wheelEvent);
        else if (index == 1)
            QApplication::sendEvent(m_minuteView->viewport(), wheelEvent);
        else
            QApplication::sendEvent(m_ampmView, wheelEvent);
    });

    connect(m_mask, &FluTimePickerViewMask::enterChanged, [=](int index, QEnterEvent* event) {
        // LOG_DEBUG << "index:" << index;
        if (index == 0)
            QApplication::sendEvent(m_hourView, event);
        else if (index == 1)
            QApplication::sendEvent(m_minuteView, event);
        else
            QApplication::sendEvent(m_ampmView, event);
    });

    connect(m_mask, &FluTimePickerViewMask::leaveChanged, [=](int index, QEvent* event) {
        // LOG_DEBUG << "index:" << index;
        if (index == 0)
            QApplication::sendEvent(m_hourView, event);
        else if (index == 1)
            QApplication::sendEvent(m_minuteView, event);
        else
            QApplication::sendEvent(m_ampmView, event);
    });

    onThemeChanged();
}

int FluTimePickerAPView::getHour()
{
    return m_hour;
}

int FluTimePickerAPView::getMinute()
{
    return m_minute;
}

void FluTimePickerAPView::setHour(int hour)
{
    m_hour = hour;
    m_hourView->setVisibaleMidIndex(hour);
    // m_hourView->scrollTo(hour);
}

void FluTimePickerAPView::setMinute(int minute)
{
    m_minute = minute;
    m_minuteView->setVisibaleMidIndex(minute);
    // m_hourView->scrollTo(minute);
}

bool FluTimePickerAPView::isAm()
{
    return m_isAm;
}

void FluTimePickerAPView::setAm(bool isAm)
{
    m_isAm = isAm;
}

void FluTimePickerAPView::updateTime()
{
    m_hour = m_hourView->getVisibleMidIndex();
    m_minute = m_minuteView->getVisibleMidIndex();
    m_isAm = m_ampmView->isAm();
}

void FluTimePickerAPView::setShadowEffect()
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

void FluTimePickerAPView::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluTimePickerAPView::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    if (m_isFirstShow)
    {
        m_isFirstShow = false;
        m_hourView->scrollTo(m_hour);
        m_minuteView->scrollTo(m_minute);
    }
}

void FluTimePickerAPView::resizeEvent(QResizeEvent* event)
{
    m_mask->resize(m_mainView->width() - 8, 40);
    m_mask->move(4, 166);
}

void FluTimePickerAPView::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_okButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept, FluTheme::Light));
        m_cancelButton->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel, FluTheme::Light));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/light/FluTimePickerAPView.qss", this);
    }
    else
    {
        m_okButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Accept, FluTheme::Dark));
        m_cancelButton->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::Cancel, FluTheme::Dark));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/dark/FluTimePickerAPView.qss", this);
    }

    FluStyleSheetUtils::setQssByFileName("FluTimePickerAPView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
