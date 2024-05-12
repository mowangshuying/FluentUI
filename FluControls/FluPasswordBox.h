#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

#include "../FluUtils/FluUtils.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

class FluPasswordBox : public FluWidget
{
    Q_OBJECT
  public:
    FluPasswordBox(QWidget* parent = nullptr) : FluWidget(parent)
    {
        m_hLayout = new QHBoxLayout(this);
        setLayout(m_hLayout);
        m_hLayout->setContentsMargins(1, 0, 1, 0);
        m_hLayout->setSpacing(0);
        m_hLayout->setAlignment(Qt::AlignHCenter);

        m_edit = new QLineEdit(this);
        m_btn = new QPushButton(this);
        m_btn->setFixedSize(30, 20);
        m_btn->setIconSize(QSize(18, 18));
        m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::RedEye));

        //  m_edit->setFixedWidth(120);
        m_edit->setFixedHeight(30);

        m_hLayout->addWidget(m_edit, 1);
        m_hLayout->addWidget(m_btn);
        m_hLayout->addSpacing(4);

        // setFixedWidth(155);
        setFixedHeight(32);

        m_edit->installEventFilter(this);
        m_edit->setFocusPolicy(Qt::ClickFocus);

        m_btn->installEventFilter(this);

        m_edit->setEchoMode(QLineEdit::Password);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPasswordBox.qss", this);
        // connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); }); { onThemeChanged(); });
    }

    void setMaskC(unsigned maskC)
    {
        m_edit->setProperty("maskC", maskC);
    }

    bool eventFilter(QObject* watched, QEvent* event)
    {
        if (watched == m_edit)
        {
            if (event->type() == QEvent::FocusIn)
            {
                setProperty("isFocused", true);
                style()->polish(this);
                // LOG_DEBUG << "focuse in";
            }
            else if (event->type() == QEvent::FocusOut)
            {
                setProperty("isFocused", false);
                style()->polish(this);
                // LOG_DEBUG << "focuse out";
            }
        }

        if (watched == m_btn)
        {
            if (event->type() == QEvent::MouseButtonPress)
            {
                // LOG_DEBUG << "EchoMode Normal.";
                m_edit->setEchoMode(QLineEdit::Normal);
            }
            else if (event->type() == QEvent::MouseButtonRelease)
            {
                // LOG_DEBUG << "EchoMode Password.";
                m_edit->setEchoMode(QLineEdit::Password);
            }
        }

        return QWidget::eventFilter(watched, event);
    }

    void resizeEvent(QResizeEvent* event)
    {
        // m_edit->resize(width() - m_btn->width() - m_hLayout->contentsMargins().left() - m_hLayout->contentsMargins().right() - 4, m_edit->height());
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::RedEye, FluTheme::Light));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPasswordBox.qss", this);
        }
        else
        {
            m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::RedEye, FluTheme::Dark));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluPasswordBox.qss", this);
        }
    }

  protected:
    QLineEdit* m_edit;
    QPushButton* m_btn;
    QHBoxLayout* m_hLayout;

    unsigned int m_maskC;
};
