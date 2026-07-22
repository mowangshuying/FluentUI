#include "FluComboBoxEx.h"
#include <QKeyEvent>
#include <QApplication>

FluComboBoxEx::FluComboBoxEx(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_textAwesomeType = FluAwesomeType::None;
    m_currentIndex = -1;
    m_editable = false;
    m_chevronRotation = 0;

    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(3, 3, 3, 3);
    m_hMainLayout->setSpacing(0);

    setLayout(m_hMainLayout);

    m_textBtn = new QPushButton;
    m_iconBtn = new QPushButton;

    m_textBtn->setObjectName("textBtn");
    m_iconBtn->setObjectName("iconBtn");

    m_iconBtn->setFixedSize(24, 24);
    m_textBtn->setFixedHeight(24);

    m_iconBtn->setFixedSize(24, 24);
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown));

    m_hMainLayout->addWidget(m_textBtn, 1);
    m_hMainLayout->addSpacing(3);
    m_hMainLayout->addWidget(m_iconBtn);
    setFixedHeight(30);

    setFocusPolicy(Qt::StrongFocus);

    m_menu = new FluIndicatorRoundMenu("", FluAwesomeType::None, this);
    m_menu->getView()->setBTSpacing(true);

    m_chevronAni = new QPropertyAnimation(this, "chevronRotation", this);
    m_chevronAni->setDuration(200);
    m_chevronAni->setEasingCurve(QEasingCurve::OutQuad);

    connect(m_textBtn, &QPushButton::clicked, [=](bool) { emit clicked(); });
    connect(m_iconBtn, &QPushButton::clicked, [=](bool) { emit clicked(); });
    connect(this, &FluComboBoxEx::clicked, [=]() {
        if (m_menu->actions().isEmpty())
            return;

        QPoint leftBottomPos = rect().bottomLeft();
        leftBottomPos = mapToGlobal(leftBottomPos);
        leftBottomPos.setY(leftBottomPos.y() + 1);

        if (m_currentIndex >= 0 && m_currentIndex < m_menu->actions().size())
        {
            m_menu->setDefaultAction(m_currentIndex);
        }

        startChevronAnimation(true);
        m_menu->popup(leftBottomPos);
    });

    connect(m_menu, &FluRoundMenu::triggered, [=](QAction* action) {
        int nIndex = m_menu->actions().indexOf(action);
        if (nIndex < 0)
            return;

        setCurrentIndex(nIndex);
        startChevronAnimation(false);
    });

    connect(m_menu, &FluRoundMenu::closed, [=]() {
        startChevronAnimation(false);
    });

    onThemeChanged();
}

QPushButton* FluComboBoxEx::getTextBtn()
{
    return m_textBtn;
}

QPushButton* FluComboBoxEx::getIconBtn()
{
    return m_iconBtn;
}

int FluComboBoxEx::count() const
{
    return m_menu->actions().size();
}

int FluComboBoxEx::currentIndex() const
{
    return m_currentIndex;
}

void FluComboBoxEx::setCurrentIndex(int index)
{
    if (index < -1 || index >= m_menu->actions().size())
        return;
    if (m_currentIndex == index)
        return;
    m_currentIndex = index;
    updateText();
    emit currentIndexChanged(m_currentIndex);
    emit currentTextChanged(currentText());
}

QString FluComboBoxEx::currentText() const
{
    if (m_currentIndex >= 0 && m_currentIndex < m_menu->actions().size())
    {
        return m_menu->actions()[m_currentIndex]->text();
    }
    return QString();
}

QString FluComboBoxEx::itemText(int index) const
{
    if (index < 0 || index >= m_menu->actions().size())
        return QString();
    return m_menu->actions()[index]->text();
}

QIcon FluComboBoxEx::itemIcon(int index) const
{
    if (index < 0 || index >= m_menu->actions().size())
        return QIcon();
    return m_menu->actions()[index]->icon();
}

bool FluComboBoxEx::isItemEnabled(int index) const
{
    if (index < 0 || index >= m_menu->actions().size())
        return false;
    return m_menu->actions()[index]->isEnabled();
}

QString FluComboBoxEx::itemToolTip(int index) const
{
    if (index < 0 || index >= m_menu->actions().size())
        return QString();
    return m_menu->actions()[index]->toolTip();
}

bool FluComboBoxEx::isEditable() const
{
    return m_editable;
}

bool FluComboBoxEx::isEnabled() const
{
    return QWidget::isEnabled();
}

QString FluComboBoxEx::placeholderText() const
{
    return m_placeholderText;
}

void FluComboBoxEx::setIcon(FluAwesomeType type)
{
    m_textAwesomeType = type;
    m_textBtn->setIconSize(QSize(18, 18));
    m_textBtn->setIcon(FluIconUtils::getFluentIconPixmap(type, FluThemeUtils::getUtils()->getTheme()));
}

void FluComboBoxEx::setText(QString text)
{
    m_textBtn->setText(text);
}

void FluComboBoxEx::addItem(QString text)
{
    addTextItem(text);
}

void FluComboBoxEx::addItem(FluAwesomeType type, QString text)
{
    addIconTextItem(type, text);
}

void FluComboBoxEx::addItem(QIcon icon, QString text)
{
    auto action = new FluAction(text);
    action->setIcon(icon);
    m_menu->addAction(action);
    if (m_menu->actions().size() == 1)
    {
        m_currentIndex = 0;
        updateText();
    }
}

void FluComboBoxEx::addTextItem(QString text)
{
    m_menu->addAction(new FluAction(text));
    if (m_menu->actions().size() == 1)
    {
        m_currentIndex = 0;
        updateText();
    }
}

void FluComboBoxEx::addIconTextItem(FluAwesomeType type, QString text)
{
    m_menu->addAction(new FluAction(type, text));
    if (m_menu->actions().size() == 1)
    {
        m_currentIndex = 0;
        updateText();
    }
}

void FluComboBoxEx::insertItem(int index, QString text)
{
    if (index < 0 || index > m_menu->actions().size())
        return;

    if (index == m_menu->actions().size())
    {
        addTextItem(text);
        return;
    }

    auto before = m_menu->actions()[index];
    auto action = new FluAction(text);
    m_menu->insertAction(before, action);

    if (m_currentIndex >= index)
        m_currentIndex++;

    updateText();
}

void FluComboBoxEx::insertItem(int index, FluAwesomeType type, QString text)
{
    if (index < 0 || index > m_menu->actions().size())
        return;

    if (index == m_menu->actions().size())
    {
        addIconTextItem(type, text);
        return;
    }

    auto before = m_menu->actions()[index];
    auto action = new FluAction(type, text);
    m_menu->insertAction(before, action);

    if (m_currentIndex >= index)
        m_currentIndex++;

    updateText();
}

void FluComboBoxEx::removeItem(int index)
{
    if (index < 0 || index >= m_menu->actions().size())
        return;

    auto action = m_menu->actions()[index];
    m_menu->removeAction(action);

    if (m_menu->actions().isEmpty())
    {
        m_currentIndex = -1;
    }
    else if (m_currentIndex == index)
    {
        m_currentIndex = qMin(index, m_menu->actions().size() - 1);
    }
    else if (m_currentIndex > index)
    {
        m_currentIndex--;
    }

    updateText();
}

void FluComboBoxEx::clear()
{
    m_menu->clear();
    m_currentIndex = -1;
    updateText();
}

int FluComboBoxEx::findText(const QString& text) const
{
    for (int i = 0; i < m_menu->actions().size(); i++)
    {
        if (m_menu->actions()[i]->text() == text)
            return i;
    }
    return -1;
}

void FluComboBoxEx::setMaxVisibleItems(int num)
{
    m_menu->setMaxVisibleItems(num);
}

void FluComboBoxEx::setPlaceholderText(const QString& text)
{
    if (m_placeholderText == text)
        return;

    m_placeholderText = text;
    updateText();
}

void FluComboBoxEx::setEditable(bool editable)
{
    m_editable = editable;
}

void FluComboBoxEx::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    m_textBtn->setEnabled(enabled);
    m_iconBtn->setEnabled(enabled);
}

void FluComboBoxEx::setItemEnabled(int index, bool enabled)
{
    if (index < 0 || index >= m_menu->actions().size())
        return;
    m_menu->actions()[index]->setEnabled(enabled);
}

void FluComboBoxEx::setItemToolTip(int index, const QString& tooltip)
{
    if (index < 0 || index >= m_menu->actions().size())
        return;
    m_menu->actions()[index]->setToolTip(tooltip);
}

void FluComboBoxEx::updateText()
{
    if (m_currentIndex >= 0 && m_currentIndex < m_menu->actions().size())
    {
        m_textBtn->setText(m_menu->actions()[m_currentIndex]->text());
    }
    else if (!m_placeholderText.isEmpty())
    {
        m_textBtn->setText(m_placeholderText);
        m_textBtn->setProperty("isPlaceholder", true);
        m_textBtn->style()->polish(m_textBtn);
    }
    else
    {
        m_textBtn->setText(QString());
        m_textBtn->setProperty("isPlaceholder", false);
        m_textBtn->style()->polish(m_textBtn);
    }
}

void FluComboBoxEx::startChevronAnimation(bool expand)
{
    m_chevronAni->stop();
    m_chevronAni->setStartValue(m_chevronRotation);
    m_chevronAni->setEndValue(expand ? 180.0 : 0.0);
    m_chevronAni->start();
}

void FluComboBoxEx::mouseReleaseEvent(QMouseEvent* e)
{
    emit clicked();
}

void FluComboBoxEx::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluComboBoxEx::keyPressEvent(QKeyEvent* e)
{
    switch (e->key())
    {
        case Qt::Key_Up:
        {
            int newIndex = m_currentIndex - 1;
            if (newIndex < 0)
                newIndex = m_menu->actions().size() - 1;
            if (newIndex >= 0)
                setCurrentIndex(newIndex);
            e->accept();
            break;
        }
        case Qt::Key_Down:
        {
            int newIndex = m_currentIndex + 1;
            if (newIndex >= m_menu->actions().size())
                newIndex = 0;
            if (m_menu->actions().size() > 0)
                setCurrentIndex(newIndex);
            e->accept();
            break;
        }
        case Qt::Key_Return:
        case Qt::Key_Enter:
        {
            if (!m_menu->actions().isEmpty())
            {
                QPoint leftBottomPos = rect().bottomLeft();
                leftBottomPos = mapToGlobal(leftBottomPos);
                leftBottomPos.setY(leftBottomPos.y() + 1);
                startChevronAnimation(true);
                m_menu->popup(leftBottomPos);
            }
            e->accept();
            break;
        }
        case Qt::Key_Escape:
        {
            m_menu->close();
            startChevronAnimation(false);
            e->accept();
            break;
        }
        default:
            QWidget::keyPressEvent(e);
    }
}

qreal FluComboBoxEx::chevronRotation() const
{
    return m_chevronRotation;
}

void FluComboBoxEx::setChevronRotation(qreal rotation)
{
    if (qFuzzyCompare(m_chevronRotation, rotation))
        return;

    m_chevronRotation = rotation;

    QPixmap originalPixmap = FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme());
    QTransform transform;
    transform.rotate(rotation);
    QPixmap rotatedPixmap = originalPixmap.transformed(transform, Qt::SmoothTransformation);

    m_iconBtn->setIcon(rotatedPixmap);
    emit chevronRotationChanged(rotation);
}

void FluComboBoxEx::onThemeChanged()
{
    m_iconBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme()));
    if (m_textAwesomeType != FluAwesomeType::None)
        m_textBtn->setIcon(FluIconUtils::getFluentIcon(m_textAwesomeType, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUtils::setQssByFileName("FluComboBoxEx.qss", this, FluThemeUtils::getUtils()->getTheme());
}
