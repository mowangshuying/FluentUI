#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include "FluWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStyleOption>
#include <QPainter>

#include "FluDatePickerView.h"

class FluDatePicker : public FluWidget
{
    Q_OBJECT
  public:
    FluDatePicker(QWidget* parent = nullptr) : FluWidget(parent)
    {
        m_hMainLayout = new QHBoxLayout;
        m_hMainLayout->setContentsMargins(0, 0, 0, 0);
        m_hMainLayout->setSpacing(0);
        setLayout(m_hMainLayout);

        m_monthBtn = new QPushButton;
        m_monthBtn->setText("month");
        m_monthBtn->setObjectName("monthBtn");

        m_dayBtn = new QPushButton;
        m_dayBtn->setText("dayBtn");
        m_dayBtn->setObjectName("dayBtn");

        m_yearBtn = new QPushButton;
        m_yearBtn->setText("year");
        m_yearBtn->setObjectName("yearBtn");

        m_monthBtn->setFixedWidth(140);
        m_dayBtn->setFixedWidth(80);
        m_yearBtn->setFixedWidth(80);

        m_hMainLayout->addWidget(m_monthBtn);
        m_hMainLayout->addWidget(m_dayBtn);
        m_hMainLayout->addWidget(m_yearBtn);

        m_datePickerView = new FluDatePickerView;
        m_datePickerView->setFixedWidth(300);
        m_datePickerView->hide();

        setFixedSize(300, 30);
        connect(m_monthBtn, &QPushButton::clicked, [=]() { emit clicked(); });
        connect(m_dayBtn, &QPushButton::clicked, [=]() { emit clicked(); });
        connect(this, &FluDatePicker::clicked, [=]() {
            // get current time
            LOG_DEBUG << "Called";
            // show FluTimerPickerView

            int nX = 0;
            int nY = height() / 2 - 180;
            QPoint gPoint = mapToGlobal(QPoint(nX, nY));
            m_datePickerView->move(gPoint.x(), gPoint.y());
            m_datePickerView->show();
        });

        connect(m_datePickerView, &FluDatePickerView::clickedOk, [=]() {
            const std::vector<QString> sMonths{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

            m_monthBtn->setText(sMonths[m_datePickerView->getMonth()]);
            QString sDay = QString::asprintf("%02d", m_datePickerView->getDay() + 1);
            m_dayBtn->setText(sDay);

            QString sYear = QString::asprintf("%04d", m_datePickerView->getYear() + 1924);
            m_yearBtn->setText(sYear);
        });

        FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluDatePicker.qss", this);
        // connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged,  this, [=](FluTheme theme) { onThemeChanged(); });
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
        emit clicked();
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
  signals:
    void clicked();
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluDatePicker.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/dark/FluDatePicker.qss", this);
        }
    }

  protected:
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_monthBtn;
    QPushButton* m_dayBtn;
    QPushButton* m_yearBtn;

    FluDatePickerView* m_datePickerView;
};
