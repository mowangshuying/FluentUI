#pragma once

#include <QWidget>
#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluPivot.h"

class FluPivotPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluPivotPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("Pivot");
        m_infoLabel->setText("A pivot allows you to show a collection of items from different sources in a tabbed view.");

        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("A basic pivot.");
        displayBox->getCodeExpander()->setCodeByPath("../code/PivotPageCode1.md");
        displayBox->setBodyWidgetFixedHeight(360);

        auto pivot = new FluPivot;
        // pivot->setFixedWidth(800);

        auto label1 = new QLabel;
        label1->setObjectName("label");
        label1->setText("This is a All Page");
        label1->setAlignment(Qt::AlignCenter);
        pivot->addPivotItem("All", label1);

        auto label2 = new QLabel;
        label2->setObjectName("label");
        label2->setText("This is a Unread Page");
        label2->setAlignment(Qt::AlignCenter);
        pivot->addPivotItem("Unread", label2);

        auto label3 = new QLabel;
        label3->setObjectName("label");
        label3->setText("This is Flagged Page");
        label3->setAlignment(Qt::AlignCenter);
        pivot->addPivotItem("Flagged", label3);

        auto label4 = new QLabel;
        label4->setObjectName("label");
        label4->setText("This is Urgent Page");
        label4->setAlignment(Qt::AlignCenter);
        pivot->addPivotItem("Urgent", label4);

        displayBox->getBodyLayout()->addWidget(pivot);

        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPivotPage.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPivotPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluPivotPage.qss", this);
        }
    }
};
