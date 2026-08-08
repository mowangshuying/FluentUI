#include "FluTabViewDemo.h"
#include <QLabel>
#include <QVBoxLayout>

FluTabViewDemo::FluTabViewDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto tabView = new FluTabView;

    // --- 3 initial pages so the junction is visible on launch ----
    auto makePage = [](const QString& title) {
        auto page = new QWidget;
        auto layout = new QVBoxLayout(page);
        auto label = new QLabel(title);
        label->setAlignment(Qt::AlignCenter);
        QFont f = label->font();
        f.setPointSize(14);
        label->setFont(f);
        layout->addWidget(label);
        return page;
    };

    tabView->addTab("Home", makePage("Welcome to the Home page"));
    tabView->addTab("Documents", makePage("Your documents are listed here"));
    tabView->addTab("Settings", makePage("Application settings"));

    connect(tabView, &FluTabView::addTabButtonClicked, this, [tabView]() {
        static int PAGENUM = 4;
        QString key  = QString::asprintf("Page%d", PAGENUM);
        QString text = QString::asprintf("Page%d: This is page%d", PAGENUM, PAGENUM);
        auto page = new QLabel;
        page->setText(text);
        page->setAlignment(Qt::AlignCenter);
        tabView->addTab(key, page);
        PAGENUM++;
    });

    m_contentLayout->addWidget(tabView);

    resize(600, 400);
}
