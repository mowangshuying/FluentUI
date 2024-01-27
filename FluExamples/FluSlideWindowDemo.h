#pragma once

#include <QWidget>
#include <QStackedLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QHBoxLayout>

class FluSlideWindowDemo : public QWidget
{
    Q_OBJECT
  public:
    FluSlideWindowDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        //m_sLayout = new QStackedLayout;
        setFixedSize(600, 400);
        m_hLayout = new QHBoxLayout;
        setLayout(m_hLayout);

        m_page1 = new QWidget(this);
        m_page1->setFixedSize(600, 400);
        m_page1->setStyleSheet("background-color:red;");
        auto label1 = new QLabel;
        label1->setText("label1");
        auto layout1 = new QVBoxLayout;
        m_page1->setLayout(layout1);
        layout1->addWidget(label1);

        m_page2 = new QWidget(this);
        m_page2->setFixedSize(600, 400);
        m_page2->move(0, 600);

        m_page2->setStyleSheet("background-color:green;");
        auto label2 = new QLabel;
        label2->setText("label2");
        auto layout2 = new QVBoxLayout;
        m_page2->setLayout(layout2);
        layout2->addWidget(label2);


        m_page3 = new QWidget(this);
        m_page3->move(0, 2 * 600);
        m_page3->setFixedSize(600, 400);
        m_page3->setStyleSheet("background-color:blue;");
        auto label3 = new QLabel;
        label3->setText("label3");
        auto layout3 = new QVBoxLayout;
        m_page3->setLayout(layout3);
        layout3->addWidget(label3);

       // m_hLayout->addWidget(m_page1);
       // m_hLayout->addWidget(m_page2);
       // m_hLayout->addWidget(m_page3);
    }

    void slideIt()
    {
        // cur widget
        QPropertyAnimation* curAnimation = new QPropertyAnimation(m_page1, "pos");
        curAnimation->setDuration(500);
        curAnimation->setStartValue(QPoint(0, 0));
        curAnimation->setEndValue(QPoint(-width(), 0));
        curAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        //m_hLayout->setCurrentWidget(nextWidget);
        
        // next widget
        QPropertyAnimation* nextAnimation = new QPropertyAnimation(m_page2, "pos");
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
    //QStackedLayout* m_sLayout;
    QHBoxLayout* m_hLayout;
};
