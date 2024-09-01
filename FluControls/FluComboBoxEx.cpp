#include "FluComboBoxEx.h"

FluComboBoxEx::FluComboBoxEx(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    // m_nMaxTextLen = 0;
    m_textAwesomeType = FluAwesomeType::None;
    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(3, 3, 3, 3);
    m_hMainLayout->setSpacing(0);

    setLayout(m_hMainLayout);

    // add text and icon
    m_textBtn = new QPushButton;
    m_iconBtn = new QPushButton;

    m_textBtn->setObjectName("textBtn");
    m_iconBtn->setObjectName("iconBtn");

    m_iconBtn->setFixedSize(24, 24);
    m_textBtn->setFixedHeight(24);

    // m_textBtn->setAlignment(Qt::AlignLeft);

    m_iconBtn->setFixedSize(24, 24);
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));

    m_hMainLayout->addWidget(m_textBtn, 1);
    m_hMainLayout->addSpacing(3);
    m_hMainLayout->addWidget(m_iconBtn);
    setFixedHeight(30);

    m_menu = new FluMenu;

    connect(m_textBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });
    connect(m_iconBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });
    connect(this, &FluComboBoxEx::clicked, [=]() {
        QPoint leftBottomPos = rect().bottomLeft();
        leftBottomPos = mapToGlobal(leftBottomPos);
        leftBottomPos.setY(leftBottomPos.y() + 3);
        m_menu->setMinimumWidth(width());
        m_menu->exec(leftBottomPos);
    });

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluComboBoxEx.qss", this);

    connect(m_menu, &FluMenu::triggered, [=](QAction* action) {
        m_textBtn->setText(action->text());
        emit currentTextChanged(action->text());
        int nIndex = 0;
        for (auto tmpAct : m_menu->actions())
        {
            if (tmpAct == action)
            {
                break;
            }

            nIndex++;
        }
        emit currentIndexChanged(nIndex);
    });
}

QPushButton* FluComboBoxEx::getTextBtn()
{
    return m_textBtn;
}
