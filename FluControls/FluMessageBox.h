#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QEvent>
#include <QResizeEvent>
#include <QLabel>

#include "../FluUtils/FluUtils.h"
#include "FluPushButton.h"
#include "FluStyleButton.h"
#include "FluVSplitLine.h"

// note: parent can't be null.
// can use window()
class FluMessageBox : public QDialog
{
    Q_OBJECT
  public:
    FluMessageBox(QString title, QString info, QWidget* parent) : QDialog(parent)
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

        m_okBtn->setText("OK");
        m_cancelBtn->setText("Cancel");

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

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMessageBox.qss", this);
        if (FluThemeUtils::isDarkTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluMessageBox.qss", this);
        }

        m_parentWidget->installEventFilter(this);
    }

    void showEvent(QShowEvent* event)
    {
        QDialog::showEvent(event);
    }

    void closeEvent(QCloseEvent* event)
    {
        QDialog::closeEvent(event);
    }

    void resizeEvent(QResizeEvent* event)
    {
        QDialog::resizeEvent(event);
        m_windowMask->resize(m_parentWidget->size());
        resize(m_parentWidget->size());
    }

    bool eventFilter(QObject* obj, QEvent* event)
    {
        if (obj == m_parentWidget && event->type() == QEvent::Resize)
        {
            QResizeEvent* resizeEvent = (QResizeEvent*)event;
            m_windowMask->resize(m_parentWidget->size());
            resize(m_parentWidget->size());
            return true;
        }

        return QDialog::eventFilter(obj, event);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMessageBox.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluMessageBox.qss", this);
        }
    }

  protected:
    QWidget* m_parentWidget;

    QHBoxLayout* m_hBoxLayout;
    QWidget* m_windowMask;

    QFrame* m_widget;
    QVBoxLayout* m_vWidgetLayout;

    QWidget* m_contentWidget;
    QVBoxLayout* m_vContentWidgetLayout;
    QLabel* m_titleLabel;
    QLabel* m_infoLabel;

    QWidget* m_btnWidget;
    QHBoxLayout* m_hBtnLayout;
    FluPushButton* m_cancelBtn;
    FluStyleButton* m_okBtn;
};
