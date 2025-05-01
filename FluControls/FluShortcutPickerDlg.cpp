#include "FluShortcutPickerDlg.h"

FluShortcutPickerDlg::FluShortcutPickerDlg(QWidget* parent /*= nullptr*/) : FluMessageBox("", "", parent)
{
    setTitle(tr("Active the Shortcut"));
    setInfo(tr("Press the key combination to change the shortcut."));
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    m_KeysWidget = new QWidget;
    m_KeysWidget->setFixedHeight(50);
    m_hKeysLayout = new QHBoxLayout;
    m_KeysWidget->setLayout(m_hKeysLayout);
    m_hKeysLayout->setAlignment(Qt::AlignCenter);
    m_hKeysLayout->setSpacing(10);
    m_vContentWidgetLayout->addWidget(m_KeysWidget);

    m_btnWidget->setFixedHeight(60);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

std::vector<QString> FluShortcutPickerDlg::getKeyTexts()
{
    return m_keyTexts;
}

void FluShortcutPickerDlg::setKeyTexts(std::vector<QString> keyTexts)
{
    m_keyTexts.clear();
    m_keyTexts.insert(m_keyTexts.begin(), keyTexts.begin(), keyTexts.end());
}

void FluShortcutPickerDlg::updateKeys()
{
    clearLabels();

    // adjust
    for (auto text : m_keyTexts)
    {
        QLabel* label = new QLabel;
        label->setFixedHeight(32);
        label->setMinimumWidth(45);
        label->setText(text);
        label->setObjectName("keyLabel");
        label->setAlignment(Qt::AlignCenter);
        m_hKeysLayout->addWidget(label);
    }

    // set icon;
    // auto label = new QLabel;
    // label->setFixedSize(32, 32);
    // label->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::PenWorkspace));
    // m_hKeysLayout->addWidget(label);
}

void FluShortcutPickerDlg::clearLabels()
{
    QLayoutItem* child;
    while ((child = m_hKeysLayout->takeAt(0)) != nullptr)
    {
        if (child->widget())
        {
            child->widget()->setParent(nullptr);
            delete child->widget();
        }
        delete child;
    }
}

QString FluShortcutPickerDlg::keyToString(int nKey, bool bShift /*= false*/)
{
    switch (nKey)
    {
        case Qt::Key_Period:
            return ".";
        case Qt::Key_Greater:
            return bShift ? ">" : ".";
        case Qt::Key_Comma:
            return ",";
        case Qt::Key_Less:
            return bShift ? "<" : ",";
        case Qt::Key_Slash:
            return "/";
        case Qt::Key_Question:
            return bShift ? "?" : "/";
        case Qt::Key_Semicolon:
            return ";";
        case Qt::Key_Colon:
            return bShift ? ":" : ";";
        case Qt::Key_Apostrophe:
            return "'";
        case Qt::Key_QuoteDbl:
            return bShift ? "'" : "\"";
        case Qt::Key_QuoteLeft:
            return "`";
        case Qt::Key_AsciiTilde:
            return bShift ? "~" : "`";
        case Qt::Key_Minus:
            return "-";
        case Qt::Key_Underscore:
            return bShift ? "_" : "-";
        case Qt::Key_Equal:
            return "=";
        case Qt::Key_Plus:
            return bShift ? "+" : "=";
        case Qt::Key_BracketLeft:
            return "[";
        case Qt::Key_BraceLeft:
            return bShift ? "{" : "[";
        case Qt::Key_BracketRight:
            return "]";
        case Qt::Key_BraceRight:
            return bShift ? "}" : "]";
        case Qt::Key_Backslash:
            return "\\";
        case Qt::Key_Bar:
            return bShift ? "|" : "\\";
        case Qt::Key_Up:
            return "Up";
        case Qt::Key_Down:
            return "Down";
        case Qt::Key_Right:
            return "Right";
        case Qt::Key_Left:
            return "Left";
        case Qt::Key_Space:
            return "Space";
        case Qt::Key_PageDown:
            return "PgDown";
        case Qt::Key_PageUp:
            return "PgUp";
        case Qt::Key_0:
            return "0";
        case Qt::Key_1:
            return "1";
        case Qt::Key_2:
            return "2";
        case Qt::Key_3:
            return "3";
        case Qt::Key_4:
            return "4";
        case Qt::Key_5:
            return "5";
        case Qt::Key_6:
            return "6";
        case Qt::Key_7:
            return "7";
        case Qt::Key_8:
            return "8";
        case Qt::Key_9:
            return "9";
        case Qt::Key_Exclam:
            return bShift ? "!" : "1";
        case Qt::Key_At:
            return bShift ? "@" : "2";
        case Qt::Key_NumberSign:
            return bShift ? "#" : "3";
        case Qt::Key_Dollar:
            return bShift ? "$" : "4";
        case Qt::Key_Percent:
            return bShift ? "%" : "5";
        case Qt::Key_AsciiCircum:
            return bShift ? "^" : "6";
        case Qt::Key_Ampersand:
            return bShift ? "&" : "7";
        case Qt::Key_Asterisk:
            return bShift ? "*" : "8";
        case Qt::Key_ParenLeft:
            return bShift ? "(" : "9";
        case Qt::Key_ParenRight:
            return bShift ? ")" : "0";
        case Qt::Key_A:
            return "A";
        case Qt::Key_B:
            return "B";
        case Qt::Key_C:
            return "C";
        case Qt::Key_D:
            return "D";
        case Qt::Key_E:
            return "E";
        case Qt::Key_F:
            return "F";
        case Qt::Key_G:
            return "G";
        case Qt::Key_H:
            return "H";
        case Qt::Key_I:
            return "I";
        case Qt::Key_J:
            return "J";
        case Qt::Key_K:
            return "K";
        case Qt::Key_L:
            return "L";
        case Qt::Key_M:
            return "M";
        case Qt::Key_N:
            return "N";
        case Qt::Key_O:
            return "O";
        case Qt::Key_P:
            return "P";
        case Qt::Key_Q:
            return "Q";
        case Qt::Key_R:
            return "R";
        case Qt::Key_S:
            return "S";
        case Qt::Key_T:
            return "T";
        case Qt::Key_U:
            return "U";
        case Qt::Key_V:
            return "V";
        case Qt::Key_W:
            return "W";
        case Qt::Key_X:
            return "X";
        case Qt::Key_Y:
            return "Y";
        case Qt::Key_Z:
            return "Z";
        case Qt::Key_F1:
            return "F1";
        case Qt::Key_F2:
            return "F2";
        case Qt::Key_F3:
            return "F3";
        case Qt::Key_F4:
            return "F4";
        case Qt::Key_F5:
            return "F5";
        case Qt::Key_F6:
            return "F6";
        case Qt::Key_F7:
            return "F7";
        case Qt::Key_F8:
            return "F8";
        case Qt::Key_F9:
            return "F9";
        case Qt::Key_F10:
            return "F10";
        case Qt::Key_F11:
            return "F11";
        case Qt::Key_F12:
            return "F12";
        case Qt::Key_Home:
            return "Home";
        case Qt::Key_End:
            return "End";
        case Qt::Key_Insert:
            return "Insert";
        case Qt::Key_Delete:
            return "Delete";
    }
    return "";
}

void FluShortcutPickerDlg::keyPressEvent(QKeyEvent* event)
{
    m_keyTexts.clear();
    if (event->modifiers() & Qt::AltModifier)
    {
        m_keyTexts.push_back("Alt");
    }

    if (event->modifiers() & Qt::ControlModifier)
    {
        m_keyTexts.push_back("Ctrl");
    }

    if (event->modifiers() & Qt::ShiftModifier)
    {
        m_keyTexts.push_back("Shift");
    }

    QString key = keyToString(event->key());
    if (!key.isEmpty())
        m_keyTexts.push_back(key);

    // event->setAccepted(true);

    // LOG_DEBUG << m_keyTexts;
    updateKeys();
}

void FluShortcutPickerDlg::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluShortcutPickerDlg.qss", this, FluThemeUtils::getUtils()->getTheme());
}
