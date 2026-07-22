#include "FluComboBoxDemo.h"
#include "../Controls/FluLabel.h"
#include "../Controls/FluPushButton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

FluComboBoxDemo::FluComboBoxDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto* centralWidget = new QWidget;
    auto* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(24, 16, 24, 16);
    mainLayout->setSpacing(12);

    auto* titleLabel = new FluLabel(FluLabelStyle::TitleLargeTextBlockStyle);
    titleLabel->setText("ComboBoxEx Demo");
    mainLayout->addWidget(titleLabel);

    // ── Grid: Basic / Placeholder / Icons / Enabled ──
    {
        auto* grid = new QGridLayout;
        grid->setHorizontalSpacing(16);
        grid->setVerticalSpacing(10);

        auto makeRow = [&](int row, const QString& labelText, FluComboBoxEx*& combo) {
            auto* lbl = new FluLabel(FluLabelStyle::BodyStrongTextBlockStyle);
            lbl->setText(labelText);
            lbl->setFixedWidth(100);
            grid->addWidget(lbl, row, 0);

            combo = new FluComboBoxEx;
            combo->setFixedWidth(180);
            grid->addWidget(combo, row, 1);
        };

        makeRow(0, "Basic:", m_basicCombo);
        m_basicCombo->addItem("Blue");
        m_basicCombo->addItem("Green");
        m_basicCombo->addItem("Red");
        m_basicCombo->addItem("Yellow");

        makeRow(1, "Placeholder:", m_placeholderCombo);
        m_placeholderCombo->setPlaceholderText("Select a fruit...");
        m_placeholderCombo->addItem("Apple");
        m_placeholderCombo->addItem("Banana");
        m_placeholderCombo->addItem("Cherry");
        m_placeholderCombo->addItem("Grape");

        makeRow(2, "With Icons:", m_iconCombo);
        m_iconCombo->addItem(FluAwesomeType::Settings, "Settings");
        m_iconCombo->addItem(FluAwesomeType::Delete, "Delete");
        m_iconCombo->addItem(FluAwesomeType::Share, "Share");
        m_iconCombo->addItem(FluAwesomeType::Copy, "Copy");

        makeRow(3, "Enabled:", m_enableCombo);
        m_enableCombo->addItem("Option A");
        m_enableCombo->addItem("Option B (disabled)");
        m_enableCombo->addItem("Option C");
        m_enableCombo->setItemEnabled(1, false);

        m_resultLabel = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
        m_resultLabel->setText("Selected: (none)");
        grid->addWidget(m_resultLabel, 0, 2);

        auto* btnDisable = new FluPushButton;
        btnDisable->setText("Toggle Enable");
        btnDisable->setFixedWidth(110);
        grid->addWidget(btnDisable, 3, 2);
        connect(btnDisable, &FluPushButton::clicked, [=]() {
            m_enableCombo->setEnabled(!m_enableCombo->isEnabled());
        });

        connect(m_basicCombo, &FluComboBoxEx::currentTextChanged, [=](const QString& text) {
            m_resultLabel->setText("Selected: " + text);
        });

        mainLayout->addLayout(grid);
    }

    // ── Group: Programmatic control ──
    {
        auto* group = new QGroupBox("Programmatic Control");
        auto* layout = new QVBoxLayout(group);
        layout->setSpacing(8);

        auto* comboRow = new QHBoxLayout;
        auto* lbl = new FluLabel(FluLabelStyle::BodyStrongTextBlockStyle);
        lbl->setText("Programmatic:");
        lbl->setFixedWidth(100);
        comboRow->addWidget(lbl);

        m_programCombo = new FluComboBoxEx;
        m_programCombo->setFixedWidth(180);
        m_programCombo->setPlaceholderText("Click a button...");
        m_programCombo->addItem("First");
        m_programCombo->addItem("Second");
        m_programCombo->addItem("Third");
        m_programCombo->addItem("Fourth");
        comboRow->addWidget(m_programCombo);
        comboRow->addStretch();
        layout->addLayout(comboRow);

        auto* btnGrid = new QGridLayout;
        btnGrid->setHorizontalSpacing(8);
        btnGrid->setVerticalSpacing(6);
        auto addBtn = [&](int row, int col, const QString& text, std::function<void()> fn) {
            auto* btn = new FluPushButton;
            btn->setText(text);
            btn->setFixedHeight(28);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            btnGrid->addWidget(btn, row, col);
            connect(btn, &FluPushButton::clicked, this, std::move(fn));
        };

        addBtn(0, 0, "Set Index=2", [this]() { m_programCombo->setCurrentIndex(2); });
        addBtn(0, 1, "Find 'Fourth'", [this]() {
            int idx = m_programCombo->findText("Fourth");
            if (idx >= 0) m_programCombo->setCurrentIndex(idx);
        });
        addBtn(1, 0, "Insert @1", [this]() { m_programCombo->insertItem(1, "INSERTED"); });
        addBtn(1, 1, "Remove Current", [this]() {
            int idx = m_programCombo->currentIndex();
            if (idx >= 0) m_programCombo->removeItem(idx);
        });
        addBtn(2, 0, "Clear All", [this]() { m_programCombo->clear(); });

        layout->addLayout(btnGrid);
        mainLayout->addWidget(group);
    }

    // ── Status bar ──
    {
        auto* layout = new QHBoxLayout;
        auto* infoLabel = new FluLabel(FluLabelStyle::CaptionTextBlockStyle);
        infoLabel->setText("Status: ");
        layout->addWidget(infoLabel);

        m_countLabel = new FluLabel(FluLabelStyle::CaptionTextBlockStyle);
        layout->addWidget(m_countLabel);
        layout->addStretch();
        mainLayout->addLayout(layout);

        auto updateStatus = [this]() {
            m_countLabel->setText(QString("Count=%1 | currentIndex=%2 | text='%3'")
                                      .arg(m_programCombo->count())
                                      .arg(m_programCombo->currentIndex())
                                      .arg(m_programCombo->currentText()));
        };
        connect(m_programCombo, &FluComboBoxEx::currentIndexChanged, this, [=](int) { updateStatus(); });
        connect(m_programCombo, &FluComboBoxEx::currentTextChanged, this, [=](const QString&) { updateStatus(); });
        updateStatus();
    }

    mainLayout->addStretch();

    m_contentLayout->addWidget(centralWidget);

    setMinimumSize(600, 600);
    resize(800, 800);
}
