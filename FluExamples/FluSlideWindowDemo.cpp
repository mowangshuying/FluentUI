#include "FluSlideWindowDemo.h"

FluSlideWindowDemo::FluSlideWindowDemo(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    // m_sLayout = new QStackedLayout;
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
