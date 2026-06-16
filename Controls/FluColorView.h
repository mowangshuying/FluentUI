#pragma once

#include "FluColorViewGradient.h"
#include "FluColorViewHHandle.h"
#include "FluColorViewVHandle.h"
#include "FluIntValidator.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include "FluLabel.h"
#include "FluLineEdit.h"
#include "FluPushButton.h"
#include "FluStyleButton.h"
#include <QStyleOption>
#include <QPainter>
#include <QDialog>
#include <QEvent>
#include <QResizeEvent>
#include <QMutex>
#include <QApplication>

class FluColorView : public QDialog
{
    Q_OBJECT
  public:
    FluColorView(QWidget* parent = nullptr) : QDialog(parent)
    {
        m_parentWidget = parent;
        setMouseTracking(true);
        m_hMainLayout = new QHBoxLayout(this);

        if (m_parentWidget != nullptr)
        {
            m_windowMask = new QWidget(this);
            m_windowMask->setObjectName("windowMask");
        }

        initContentWidget();

        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);

        if (m_parentWidget != nullptr)
        {
            setGeometry(0, 0, m_parentWidget->width(), m_parentWidget->height());
            m_windowMask->resize(m_parentWidget->size());
            m_parentWidget->installEventFilter(this);
        }

        onThemeChanged();
    }

    void initContentWidget()
    {
        m_widget = new QFrame(this);
        m_widget->setObjectName("centerWidget");
        m_widget->setFixedSize(320, 460);
        m_hMainLayout->addWidget(m_widget, 1, Qt::AlignCenter);

        m_vContentWidgetLayout = new QVBoxLayout;
        m_vContentWidgetLayout->setContentsMargins(5, 5, 5, 5);

        m_widget->setLayout(m_vContentWidgetLayout);

        auto hLayout = new QHBoxLayout;
        colorViewGradient = new FluColorViewGradient;
        colorViewGradient->setFixedSize(256, 256);

        auto colorViewVHandle = new FluColorViewVHandle;
        colorViewVHandle->setFixedSize(45, 256);

        hLayout->addWidget(colorViewGradient);
        hLayout->addWidget(colorViewVHandle);

        m_vContentWidgetLayout->addLayout(hLayout);

        colorViewHHandle = new FluColorViewHHandle;
        colorViewHHandle->setFixedHeight(17);
        m_vContentWidgetLayout->addWidget(colorViewHHandle);

        hLayout = new QHBoxLayout;
        auto rLabel = new FluLabel;
        rLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
        rLabel->setFixedWidth(50);
        rLabel->setText(tr("Red:"));

        rEdit = new FluLineEdit;
        rEdit->setText("0");
        rEdit->setValidator(new FluIntValidator(0, 255, rEdit));
        rEdit->setFixedSize(120, 35);

        hLayout->addWidget(rLabel);
        hLayout->addWidget(rEdit);
        hLayout->addStretch();

        m_vContentWidgetLayout->addLayout(hLayout);

        hLayout = new QHBoxLayout;
        auto gLabel = new FluLabel;
        gLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
        gLabel->setText(tr("Green:"));
        gLabel->setFixedWidth(50);

        gEdit = new FluLineEdit;
        gEdit->setText("0");
        gEdit->setValidator(new FluIntValidator(0, 255, gEdit));
        gEdit->setFixedSize(120, 35);

        hLayout->addWidget(gLabel);
        hLayout->addWidget(gEdit);
        hLayout->addStretch();

        m_vContentWidgetLayout->addLayout(hLayout);

        hLayout = new QHBoxLayout;
        auto bLabel = new FluLabel;
        bLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
        bLabel->setText(tr("Blue:"));
        bLabel->setFixedWidth(50);

        bEdit = new FluLineEdit;
        bEdit->setText("0");
        bEdit->setValidator(new FluIntValidator(0, 255, bEdit));
        bEdit->setFixedSize(120, 35);

        hLayout->addWidget(bLabel);
        hLayout->addWidget(bEdit);
        hLayout->addStretch();

        m_vContentWidgetLayout->addLayout(hLayout);

        hLayout = new QHBoxLayout;
        auto okBtn = new FluStyleButton;
        okBtn->setText(tr("Ok"));
        okBtn->setFixedWidth(150);

        auto cancelBtn = new FluPushButton;
        cancelBtn->setText(tr("cancel"));
        cancelBtn->setFixedWidth(150);

        hLayout->addWidget(okBtn);
        // hLayout->addSpacing(15);
        hLayout->addWidget(cancelBtn);

        m_vContentWidgetLayout->addLayout(hLayout);

        // limit edit value;

        connect(okBtn, &FluStyleButton::clicked, this, [=]() {
            if (m_parentWidget == nullptr)
                return;
            accept();
        });

        connect(cancelBtn, &FluPushButton::clicked, this, [=]() {
            if (m_parentWidget == nullptr)
                return;
            reject();
        });

        connect(colorViewGradient, &FluColorViewGradient::colorChanged, [=](QColor color) { colorViewHHandle->setColor(color); });

        connect(colorViewHHandle, &FluColorViewHHandle::valueChanged, [=](float percentage) {
            int r = colorViewHHandle->getColor().red() * percentage;
            int g = colorViewHHandle->getColor().green() * percentage;
            int b = colorViewHHandle->getColor().blue() * percentage;

            // m_bRgbChanging = true;

            // m_mutex.lock();
            rEdit->setText(QString::asprintf("%d", r));
            gEdit->setText(QString::asprintf("%d", g));
            bEdit->setText(QString::asprintf("%d", b));
            colorViewVHandle->setColor(QColor(r, g, b));
            // m_mutex.unlock();
            // m_bRgbChanging = false;
        });

        connect(rEdit, &FluLineEdit::textChanged, this, [=](const QString& rValue) { onRgbValueChanged(); });

        connect(gEdit, &FluLineEdit::textChanged, this, [=](const QString& gValue) { onRgbValueChanged(); });

        connect(bEdit, &FluLineEdit::textChanged, this, [=](const QString& bValue) { onRgbValueChanged(); });

        connect(colorViewHHandle, &FluColorViewHHandle::pressed, this, [=]() {
            rEdit->clearFocus();
            gEdit->clearFocus();
            bEdit->clearFocus();
        });
    }

    QColor getColor()
    {
        return colorViewHHandle->getColor();
    }

    void mousePressEvent(QMouseEvent* event)
    {
        auto child = static_cast<QWidget*>(childAt(event->pos()));
        if (child == nullptr)
            return;

        if (child != rEdit && child != gEdit && child != bEdit)
        {
            rEdit->clearFocus();
            gEdit->clearFocus();
            bEdit->clearFocus();
        }
    }

    void resizeEvent(QResizeEvent* event)
    {
        QDialog::resizeEvent(event);
        if (m_parentWidget != nullptr)
        {
            m_windowMask->resize(m_parentWidget->size());
            resize(m_parentWidget->size());
        }
    }

    bool eventFilter(QObject* watched, QEvent* event)
    {
        if (m_parentWidget != nullptr && watched == m_parentWidget && event->type() == QEvent::Resize)
        {
            QResizeEvent* resizeEvent = (QResizeEvent*)event;
            m_windowMask->resize(m_parentWidget->size());
            resize(m_parentWidget->size());
            return true;
        }

        return QDialog::eventFilter(watched, event);
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  public slots:

    void onRgbValueChanged()
    {
        bool bHasFocus = rEdit->hasFocus() || bEdit->hasFocus() || gEdit->hasFocus();
        if (!bHasFocus)
            return;

        // get r value;
        // get g value;
        // get b value;
        int r = rEdit->text().toInt();
        int g = gEdit->text().toInt();
        int b = bEdit->text().toInt();

        // if (m_bRgbChanging)
        //{
        //     LOG_DEBUG << "called";
        //     return;
        // }

        float fv = 0;
        if (r >= g && r >= b)
        {
            fv = r * 1.0 / 255;
            // return;
        }

        if (g >= r && g >= b)
        {
            fv = g * 1.0 / 255;
        }

        if (b >= r && b >= g)
        {
            fv = b * 1.0 / 255;
        }

        r = r / fv;
        g = g / fv;
        b = b / fv;

        // m_mutex.lock();
        colorViewHHandle->setV(fv);
        colorViewHHandle->setColor(QColor(r, g, b), false);

        // m_mutex.unlock();
        colorViewGradient->circleMoveToPoint(QColor(r, g, b));
    }

    void onThemeChanged()
    {
        FluStyleSheetUitls::setQssByFileName("FluColorView.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

  protected:
    bool m_bRgbChanging;
    QWidget* m_parentWidget;
    QWidget* m_windowMask;

    QHBoxLayout* m_hMainLayout;

    // content widget;
    QFrame* m_widget;
    QVBoxLayout* m_vContentWidgetLayout;

    FluColorViewGradient* colorViewGradient;
    // colorViewHHandle;
    FluColorViewHHandle* colorViewHHandle;
    // r/g/b edit;
    FluLineEdit* rEdit;
    FluLineEdit* gEdit;
    FluLineEdit* bEdit;

    // mutex;
    QMutex m_mutex;
};
