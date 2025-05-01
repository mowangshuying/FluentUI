#include "FluShortcutPicker.h"
#include "FluShortcutPickerDlg.h"

FluShortcutPicker::FluShortcutPicker(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setSpacing(10);
    setLayout(m_hMainLayout);

    updateKeys();
    setFixedHeight(48);
    connect(this, &FluShortcutPicker::clicked, this, [=]() {
        FluShortcutPickerDlg dlg(window());
        dlg.setKeyTexts(m_keyTexts);
        dlg.updateKeys();
        if (dlg.exec() == QDialog::Accepted)
        {
            std::vector<QString> keyTexts = dlg.getKeyTexts();
            m_keyTexts.clear();
            m_keyTexts.insert(m_keyTexts.begin(), keyTexts.begin(), keyTexts.end());
            updateKeys();
        }
    });

    onThemeChanged();
}

void FluShortcutPicker::updateKeys()
{
    clearLabels();

    // adjust
    for (auto text : m_keyTexts)
    {
        QLabel* label = new QLabel;
        label->setFixedHeight(32);
        label->setMinimumWidth(40);
        label->setText(text);
        label->setObjectName("keyLabel");
        label->setAlignment(Qt::AlignCenter);
        m_hMainLayout->addWidget(label);
    }

    // set icon;
    auto label = new QLabel;
    label->setFixedSize(32, 32);
    label->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::PenWorkspace, FluThemeUtils::getUtils()->getTheme()));
    m_hMainLayout->addWidget(label);
}

void FluShortcutPicker::clearLabels()
{
    QLayoutItem* child;
    while ((child = m_hMainLayout->takeAt(0)) != nullptr)
    {
        if (child->widget())
        {
            child->widget()->setParent(nullptr);
            delete child->widget();
        }
        delete child;
    }
}

void FluShortcutPicker::mouseReleaseEvent(QMouseEvent* event)
{
    FluWidget::mouseReleaseEvent(event);
    emit clicked();
    // LOG_DEBUG << "clicked.";
}

void FluShortcutPicker::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluShortcutPicker::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluShortcutPicker.qss", this, FluThemeUtils::getUtils()->getTheme());
    updateKeys();
}
