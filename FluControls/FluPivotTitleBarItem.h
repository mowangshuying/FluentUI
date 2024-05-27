#pragma once

#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include <QStyle>
#include <QVBoxLayout>

class FluPivotTitleBarItem : public QPushButton
{
    Q_OBJECT
  public:
    FluPivotTitleBarItem(QWidget* parent = nullptr) : QPushButton(parent)
    {
        m_vMainLayout = new QVBoxLayout;
        setLayout(m_vMainLayout);
        m_vMainLayout->setContentsMargins(5, 5, 5, 5);

        m_textLabel = new QLabel;
        m_textLabel->setWordWrap(true);
        m_textLabel->setObjectName("textLabel");
        m_vMainLayout->addWidget(m_textLabel);
        m_vMainLayout->addWidget(m_textLabel, 1);

        m_indicatorLabel = new QLabel;
        m_indicatorLabel->setObjectName("indicatorLabel");
        m_vMainLayout->addWidget(m_indicatorLabel);

        m_indicatorLabel->setFixedHeight(5);

        setSelected(false);
        setFixedHeight(45);

        FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluPivotTitleBarItem.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=]() { onThemeChanged();});
        adjustItemSize();
    }

    void setSelected(bool bSelected)
    {
        setProperty("selected", bSelected);
        m_textLabel->setProperty("selected", bSelected);
        m_indicatorLabel->setProperty("selected", bSelected);

        m_textLabel->style()->polish(m_textLabel);
        m_indicatorLabel->style()->polish(m_indicatorLabel);
        style()->polish(this);

        // adjustItemSize();
    }

    void setKey(QString key)
    {
        m_key = key;
        m_textLabel->setText(key);
        adjustItemSize();
    }

    QString getKey()
    {
        return m_key;
    }

    void adjustItemSize()
    {
        m_textLabel->show();
        int nLabelWidth = m_textLabel->sizeHint().width();
        m_textLabel->setFixedWidth(nLabelWidth);
        setFixedWidth(nLabelWidth + 10);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluPivotTitleBarItem.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/dark/FluPivotTitleBarItem.qss", this);
        }
    }

  protected:
    QString m_key;
    QLabel* m_textLabel;
    QLabel* m_indicatorLabel;
    QVBoxLayout* m_vMainLayout;
};
