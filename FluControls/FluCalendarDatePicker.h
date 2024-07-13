#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QStyleOption>

#include "../FluUtils/FluUtils.h"
#include "FluCalendarDatePicker.h"
#include "FluCalendarView.h"

class FluCalendarDatePicker : public QPushButton
{
    Q_OBJECT
  public:
    FluCalendarDatePicker(QWidget* parent = nullptr) : QPushButton(parent)
    {
        m_hMainLayout = new QHBoxLayout;
        m_textButton = new QPushButton;
        m_iconButton = new QPushButton;

        m_textButton->setObjectName("textButton");
        m_iconButton->setObjectName("iconButton");

        setLayout(m_hMainLayout);

        setFixedSize(120, 30);
        m_textButton->setText("Pick a date");

        m_iconButton->setIconSize(QSize(20, 20));
        m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Calendar));
        m_iconButton->setFixedWidth(30);

        m_hMainLayout->setContentsMargins(0, 0, 0, 0);
        m_hMainLayout->addWidget(m_textButton);
        m_hMainLayout->addWidget(m_iconButton);

        m_calendarView = new FluCalendarView(window());
        m_calendarView->setWindowFlag(Qt::Popup);

        connect(m_calendarView, &FluCalendarView::selectedDate, [=](QDate date) {
            QString dateText = QString::asprintf("%d/%d/%d", date.month(), date.day(), date.year());
            m_textButton->setText(dateText);
            LOG_DEBUG << date;
            m_calendarView->hide();
        });

        connect(this, &FluCalendarDatePicker::clicked, [=]() { onClicked(); });
        connect(m_textButton, &QPushButton::clicked, [=]() { onClicked(); });
        connect(m_iconButton, &QPushButton::clicked, [=]() { onClicked(); });

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarDatePicker.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
        //  {
        //     onThemeChanged();
        // });
    }

    QDate getCurDate()
    {
        return m_calendarView->getCurDate();
    }

    void setCurDate(QDate date)
    {
        m_calendarView->setCurDate(date);
    }

  public slots:
    void onClicked()
    {
        LOG_DEBUG << "clicked!";
        // if (!m_calendarView->isHidden())
        // {
        //     m_calendarView->hide();
        //      return;
        //  }

        // the pos
        int nX = width() / 2;
        int nY = height() + 5;

        LOG_DEBUG << "nX:" << nX << ",nY:" << nY;
        LOG_DEBUG << m_calendarView->width();
        QPoint gPoint = mapToGlobal(QPoint(nX, nY));
        LOG_DEBUG << gPoint;
        m_calendarView->move(gPoint.x() - m_calendarView->width() / 2, gPoint.y());
        m_calendarView->show();
    }

    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Calendar));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCalendarDatePicker.qss", this);
        }
        else
        {
            m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Calendar, FluTheme::Dark));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCalendarDatePicker.qss", this);
        }
    }

  protected:
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_textButton;
    QPushButton* m_iconButton;

    FluCalendarView* m_calendarView;
};
