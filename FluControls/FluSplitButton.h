#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>

class FluSplitButton : public QWidget
{
    Q_OBJECT
  public:
    FluSplitButton(QWidget* parent = nullptr) : QWidget(parent)
    {
        m_hMainLayout = new QHBoxLayout;
        setLayout(m_hMainLayout);
        m_hMainLayout->setSpacing(0);

        m_dropDownBtn = new QPushButton;
        m_textBtn = new QPushButton;

        m_dropDownBtn->setObjectName("dropDownBtn");
        m_dropDownBtn->setIconSize(QSize(20, 20));
        m_textBtn->setObjectName("textBtn");

        m_hMainLayout->setContentsMargins(0, 0, 0, 0);

        m_hMainLayout->addWidget(m_textBtn);
        m_hMainLayout->addWidget(m_dropDownBtn);

        setFixedHeight(30);

        connect(m_textBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });
        connect(m_dropDownBtn, &QPushButton::clicked, [=](bool b) { emit clicked(); });

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSplitButton.qss", this);
        m_dropDownBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluThemeUtils::getUtils()->getTheme()));
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Dark)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSplitButton.qss", this);
        }

        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    void setText(QString text)
    {
        m_textBtn->setText(text);
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
        QWidget::mouseReleaseEvent(event);
        emit clicked();
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  signals:
    void clicked();
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            m_dropDownBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluTheme::Light));

            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSplitButton.qss", this);
        }
        else
        {
            m_dropDownBtn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChevronDown, FluTheme::Dark));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSplitButton.qss", this);
        }
    }

  protected:
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_dropDownBtn;
    QPushButton* m_textBtn;
};
