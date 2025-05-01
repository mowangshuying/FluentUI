#include "FluMessageBox.h"
#include <QThread>

FluMessageBox::FluMessageBox(QString title, QString info, QWidget* parent) : QDialog(parent)
{
    m_parentWidget = parent;

    m_hBoxLayout = new QHBoxLayout(this);
    m_windowMask = new QWidget(this);
    m_windowMask->setObjectName("windowMask");

    m_widget = new QFrame(this);
    m_widget->setObjectName("centerWidget");
    m_widget->setFixedSize(318, 218);
    m_hBoxLayout->addWidget(m_widget, 1, Qt::AlignCenter);

    m_vWidgetLayout = new QVBoxLayout;
    m_vWidgetLayout->setAlignment(Qt::AlignTop);
    m_widget->setLayout(m_vWidgetLayout);

    m_contentWidget = new QWidget;

    m_vContentWidgetLayout = new QVBoxLayout;
    m_vContentWidgetLayout->setSpacing(0);
    m_vContentWidgetLayout->setContentsMargins(24, 35, 24, 0);
    m_contentWidget->setLayout(m_vContentWidgetLayout);

    m_titleLabel = new QLabel;
    m_infoLabel = new QLabel;

    m_okBtn = new FluStyleButton;
    m_cancelBtn = new FluPushButton;

    m_okBtn->setText(tr("OK"));
    m_cancelBtn->setText(tr("Cancel"));

    m_titleLabel->setText(title);
    m_infoLabel->setText(info);

    m_titleLabel->setWordWrap(true);
    m_infoLabel->setWordWrap(true);

    m_okBtn->setFixedWidth(130);
    m_cancelBtn->setFixedWidth(130);

    m_titleLabel->setObjectName("titleLabel");
    m_infoLabel->setObjectName("infoLabel");

    // m_titleLabel->setText("This is a Title");
    // m_infoLabel->setText("This is a Content.");

    m_vWidgetLayout->setContentsMargins(0, 0, 0, 0);
    m_vWidgetLayout->setSpacing(0);
    // m_vWidgetLayout->addWidget(m_titleLabel);
    // m_vWidgetLayout->addWidget(m_infoLabel, 1);

    m_vWidgetLayout->addWidget(m_contentWidget);
    m_vContentWidgetLayout->addWidget(m_titleLabel);
    m_vContentWidgetLayout->addWidget(m_infoLabel, 1);

    // m_vWidgetLayout->addStretch();
    m_btnWidget = new QWidget;
    m_btnWidget->setObjectName("btnWidget");
    m_btnWidget->setFixedHeight(80);
    m_hBtnLayout = new QHBoxLayout;
    m_btnWidget->setLayout(m_hBtnLayout);

    // m_hBtnLayout->setSpacing(10);
    m_hBtnLayout->setSpacing(0);
    m_hBtnLayout->setContentsMargins(24, 0, 24, 0);
    m_hBtnLayout->addWidget(m_okBtn);
    m_hBtnLayout->addSpacing(10);
    m_hBtnLayout->addWidget(m_cancelBtn);

    m_vWidgetLayout->addWidget(new FluVSplitLine);
    m_vWidgetLayout->addWidget(m_btnWidget);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    LOG_DEBUG << m_parentWidget->size();
    setGeometry(0, 0, m_parentWidget->width(), m_parentWidget->height());
    m_windowMask->resize(m_parentWidget->size());

    connect(m_okBtn, &FluStyleButton::clicked, [=]() { accept(); });

    connect(m_cancelBtn, &QPushButton::clicked, [=]() { reject(); });

    onThemeChanged();
    m_parentWidget->installEventFilter(this);
}

QString FluMessageBox::getTitle()
{
    return m_titleLabel->text();
}

void FluMessageBox::setTitle(QString title)
{
    m_titleLabel->setText(title);
}

QString FluMessageBox::getInfo()
{
    return m_infoLabel->text();
}

void FluMessageBox::setInfo(QString info)
{
    m_infoLabel->setText(info);
}

void FluMessageBox::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);
}

void FluMessageBox::closeEvent(QCloseEvent* event)
{
    QDialog::closeEvent(event);
}

void FluMessageBox::resizeEvent(QResizeEvent* event)
{
    QDialog::resizeEvent(event);
    m_windowMask->resize(m_parentWidget->size());
    resize(m_parentWidget->size());
}

bool FluMessageBox::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == m_parentWidget && event->type() == QEvent::Resize)
    {
        QResizeEvent* resizeEvent = (QResizeEvent*)event;
        m_windowMask->resize(m_parentWidget->size());
        resize(m_parentWidget->size());
        return true;
    }

    if (event->type() == QEvent::KeyPress)
    {
        QThread::msleep(0);
    }

    return QDialog::eventFilter(obj, event);
}

void FluMessageBox::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluMessageBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
