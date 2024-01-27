#pragma once

#include <QWidget>
#include <QStackedLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPropertyAnimation>

class FluSlideWindowDemo : public QWidget
{
    Q_OBJECT
  public:
    FluSlideWindowDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        m_sLayout = new QStackedLayout;
        setLayout(m_sLayout);

        m_page1 = new QWidget;
        m_page1->setStyleSheet("background-color:red;");
        auto label1 = new QLabel;
        label1->setText("label1");
        auto layout1 = new QVBoxLayout;
        m_page1->setLayout(layout1);
        layout1->addWidget(label1);

        m_page2 = new QWidget;
        m_page2->setStyleSheet("background-color:green;");
        auto label2 = new QLabel;
        label2->setText("label2");
        auto layout2 = new QVBoxLayout;
        m_page2->setLayout(layout2);
        layout2->addWidget(label2);


        m_page3 = new QWidget;
        m_page3->setStyleSheet("background-color:blue;");
        auto label3 = new QLabel;
        label3->setText("label3");
        auto layout3 = new QVBoxLayout;
        m_page3->setLayout(layout3);
        layout3->addWidget(label3);

        m_sLayout->addWidget(m_page1);
        m_sLayout->addWidget(m_page2);
        m_sLayout->addWidget(m_page3);
    }

    void slideIt()
    {
       // int curIndex = m_sLayout->currentIndex();
        auto curWidget = m_sLayout->currentWidget();
        auto nextWidget = m_sLayout->widget(m_sLayout->currentIndex() + 1);
        if (curWidget == nullptr || nextWidget == nullptr)
            return;

        // cur widget
        QPropertyAnimation* curAnimation = new QPropertyAnimation(curWidget, "pos");
        curAnimation->setDuration(500);
        curAnimation->setStartValue(QPoint(0, 0));
        curAnimation->setEndValue(QPoint(-width(), 0));
        curAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        m_sLayout->setCurrentWidget(nextWidget);


        // next widget
        QPropertyAnimation* nextAnimation = new QPropertyAnimation(nextWidget, "pos");
        nextAnimation->setDuration(500);
        nextAnimation->setStartValue(QPoint(width(), 0));
        nextAnimation->setEndValue(QPoint(0, 0));
        nextAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        //m_sLayout->setCurrentWidget(nextWidget);
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
        QWidget::mouseReleaseEvent(event);
       // emit clicked();
        slideIt();
    }

//signals:
//    void clicked();
  protected:
    QWidget* m_page1;
    QWidget* m_page2;
    QWidget* m_page3;
    QStackedLayout* m_sLayout;
};
