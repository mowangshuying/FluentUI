#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

#include "../FluUtils/FluUtils.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

class FluSearchLineEdit : public FluWidget
{
    Q_OBJECT
  public:
    FluSearchLineEdit(QWidget* parent = nullptr) : FluWidget(parent)
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
        m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search));

        //  m_edit->setFixedWidth(120);
        m_edit->setFixedHeight(30);

        m_hLayout->addWidget(m_edit, 1, Qt::AlignLeft);
        m_hLayout->addWidget(m_btn, 0, Qt::AlignRight);
        m_hLayout->addSpacing(4);

        // setFixedWidth(155);
        setFixedHeight(32);

        m_edit->installEventFilter(this);
        m_edit->setFocusPolicy(Qt::ClickFocus);

        connect(m_btn, &QPushButton::clicked, [=]() { emit onSearchBtnClicked(); });

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSearchLineEdit.qss", this);
        // connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); }); { onThemeChanged(); });
    }

    QString getText()
    {
        return m_edit->text();
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
            else if (event->type() == QEvent::KeyRelease)
            {
                QKeyEvent* keyEvent = (QKeyEvent*)event;
                if (keyEvent->key() == Qt::Key_Return)
                {
                    emit onSearchBtnClicked();
                }
            }
        }

        return QWidget::eventFilter(watched, event);
    }

    void resizeEvent(QResizeEvent* event)
    {
        m_edit->resize(width() - m_btn->width() - m_hLayout->contentsMargins().left() - m_hLayout->contentsMargins().right() - 4, m_edit->height());
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
  signals:
    void onSearchBtnClicked();
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, FluTheme::Light));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSearchLineEdit.qss", this);
        }
        else
        {
            m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, FluTheme::Dark));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSearchLineEdit.qss", this);
        }
    }

  protected:
    QLineEdit* m_edit;
    QPushButton* m_btn;
    QHBoxLayout* m_hLayout;
};
