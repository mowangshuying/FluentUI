#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "../FluUtils/FluUtils.h"
#include <QListWidget>
#include <QListWidgetItem>

 class FluComboBoxTextItem : public QWidget
{
    Q_OBJECT
   public:
        FluComboBoxTextItem(QWidget* parent = nullptr) : QWidget(parent)
       {
           m_hBoxLayout = new QHBoxLayout;
           m_indicatorLabel = new QLabel;
           m_textLabel = new QLabel;

         //  m_indicatorLabel->setFixedSize(4,20);
           setFixedHeight(30);

           m_indicatorLabel->setObjectName("indicatorLabel");
           m_textLabel->setText("textLabel");

           m_hBoxLayout->setContentsMargins(0, 0, 0, 0);
           m_hBoxLayout->setSpacing(0);

           m_hBoxLayout->addWidget(m_indicatorLabel);
           m_hBoxLayout->addWidget(m_textLabel);

           setLayout(m_hBoxLayout);

#ifdef _DEBUG
           m_indicatorLabel->setText("0000");
#endif
           FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluComboBoxTextItem.qss", this);
       }


        QString  getItemText()
        {
           LOG_DEBUG << m_textLabel->text();
           return m_textLabel->text();
        }

        void setItemText(QString text)
        {
           m_textLabel->setText(text);
        }

        void setListItem(QListWidgetItem* listItem)
        {
           m_listItem = listItem;
        }


        void mouseReleaseEvent(QMouseEvent* event)
        {
           emit itemCliceked();
        } 
signals:
    void itemCliceked();
   protected:
     QListWidgetItem* m_listItem;
     QLabel* m_indicatorLabel;
     QLabel* m_textLabel;
     QHBoxLayout* m_hBoxLayout;
 };