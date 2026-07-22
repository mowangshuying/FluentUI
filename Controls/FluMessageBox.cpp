#include "FluMessageBox.h"
#include <QThread>

FluMessageBox::FluMessageBox(QString title, QString info, QWidget* parent) : QDialog(parent)
{
    m_parentWidget = parent;

    m_boxLayout = new QHBoxLayout(this);
    m_windowMask = new QWidget(this);
    m_windowMask->setObjectName("windowMask");

    m_widget = new QFrame(this);
    m_widget->setObjectName("centerWidget");
    m_widget->setFixedSize(318, 218);
    m_boxLayout->addWidget(m_widget, 1, Qt::AlignCenter);

    m_widgetLayout = new QVBoxLayout;
    m_widgetLayout->setAlignment(Qt::AlignTop);
    m_widget->setLayout(m_widgetLayout);

    m_contentWidget = new QWidget;

    m_contentWidgetLayout = new QVBoxLayout;
    m_contentWidgetLayout->setSpacing(0);
    m_contentWidgetLayout->setContentsMargins(24, 35, 24, 0);
    m_contentWidget->setLayout(m_contentWidgetLayout);

    m_titleLabel = new QLabel;
    m_infoLabel = new QLabel;

    m_okButton = new FluStyleButton;
    m_cancelButton = new FluPushButton;

    m_okButton->setText(tr("OK"));
    m_cancelButton->setText(tr("Cancel"));

    m_titleLabel->setText(title);
    m_infoLabel->setText(info);

    m_titleLabel->setWordWrap(true);
    m_infoLabel->setWordWrap(true);

    m_okButton->setFixedWidth(130);
    m_cancelButton->setFixedWidth(130);

    m_titleLabel->setObjectName("titleLabel");
    m_infoLabel->setObjectName("infoLabel");

    // m_titleLabel->setText("This is a Title");
    // m_infoLabel->setText("This is a Content.");

    m_widgetLayout->setContentsMargins(0, 0, 0, 0);
    m_widgetLayout->setSpacing(0);
    // m_widgetLayout->addWidget(m_titleLabel);
    // m_widgetLayout->addWidget(m_infoLabel, 1);

    m_widgetLayout->addWidget(m_contentWidget);
    m_contentWidgetLayout->addWidget(m_titleLabel);
    m_contentWidgetLayout->addWidget(m_infoLabel, 1);

    // m_widgetLayout->addStretch();
    m_buttonWidget = new QWidget;
    m_buttonWidget->setObjectName("btnWidget");
    m_buttonWidget->setFixedHeight(80);
    m_buttonLayout = new QHBoxLayout;
    m_buttonWidget->setLayout(m_buttonLayout);

    // m_buttonLayout->setSpacing(10);
    m_buttonLayout->setSpacing(0);
    m_buttonLayout->setContentsMargins(24, 0, 24, 0);
    m_buttonLayout->addWidget(m_okButton);
    m_buttonLayout->addSpacing(10);
    m_buttonLayout->addWidget(m_cancelButton);

    m_widgetLayout->addWidget(new FluVSplitLine);
    m_widgetLayout->addWidget(m_buttonWidget);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    LOG_DEBUG << m_parentWidget->size();
    setGeometry(0, 0, m_parentWidget->width(), m_parentWidget->height());
    m_windowMask->resize(m_parentWidget->size());

    connect(m_okButton, &FluStyleButton::clicked, [=]() { accept(); });

    connect(m_cancelButton, &QPushButton::clicked, [=]() { reject(); });

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

void FluMessageBox::onTitleChanged(QString title)
{
    setTitle(title);
}

void FluMessageBox::onInfoChanged(QString info)
{
    setInfo(info);
}

void FluMessageBox::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluMessageBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
