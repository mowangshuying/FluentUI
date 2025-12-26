#include "FluMVDemo.h"
#include "../FluControls/FluPushButton.h"

FluMVDemo::FluMVDemo(QWidget* parent)
{
    setWindowTitle("Model View Demo");
    resize(800, 600);

    // m_listView = new QListView(this);
    m_model = new QStringListModel(this);
    QStringList strList;
    for (int i = 0; i < 100; i++)
    {
        strList << QString("Item %1").arg(i + 1);
    }
    m_model->setStringList(strList);
    // m_listView->setModel(m_model);
    // m_listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    // QVBoxLayout* mainLayout = new QVBoxLayout(this);
    // mainLayout->addWidget(m_listView);
    // setLayout(mainLayout);

    m_listView = new QListView;

    m_listView->setModel(m_model);

    m_toolWidget = new QWidget;
    m_toolWidget->setFixedWidth(250);

    auto vToolLayout = new QVBoxLayout;
    m_toolWidget->setLayout(vToolLayout);
    // vToolLayout->addWidget(m_toolWidget);

    auto addBtn = new FluPushButton;
    addBtn->setText("Add");

    auto delBtn = new FluPushButton;
    delBtn->setText("del");

    auto insertBtn = new FluPushButton;
    insertBtn->setText("insert");

    auto clearBtn = new FluPushButton;
    clearBtn->setText("clear");

    vToolLayout->addWidget(addBtn);
    vToolLayout->addWidget(delBtn);
    vToolLayout->addWidget(insertBtn);
    vToolLayout->addWidget(clearBtn);
    vToolLayout->addStretch();

    m_contentLayout->addWidget(m_listView);
    m_contentLayout->addWidget(m_toolWidget);

    // __connect;
    connect(addBtn, &QPushButton::clicked, this, [=]() {
        m_model->insertRow(m_model->rowCount());
        QModelIndex index = m_model->index(m_model->rowCount() - 1, 0);
        m_model->setData(index, "new item", Qt::DisplayRole);
        m_listView->setCurrentIndex(index);
    });

    connect(delBtn, &QPushButton::clicked, this, [=]() {
        QModelIndex index = m_listView->currentIndex();
        m_model->removeRow(index.row());
    });

    connect(insertBtn, &QPushButton::clicked, this, [=]() {
        QModelIndex index = m_listView->currentIndex();
        m_model->insertRow(index.row());

        m_model->setData(index, "insert item", Qt::DisplayRole);
        m_listView->setCurrentIndex(index);
    });

    connect(clearBtn, &QPushButton::clicked, this, [=]() { m_model->removeRows(0, m_model->rowCount()); });
}

FluMVDemo::~FluMVDemo()
{
}