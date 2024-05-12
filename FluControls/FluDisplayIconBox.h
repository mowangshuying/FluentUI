#pragma once

#include "FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>

#include "../FluUtils/FluUtils.h"
#include "FluDef.h"
#include <QStyleOption>
#include <QPainter>

// box to display icon
class FluDisplayIconBox : public FluWidget
{
    Q_OBJECT
  public:
    FluDisplayIconBox(QWidget* parent = nullptr) : FluWidget(parent)
    {
        setFixedSize(48, 48);
        m_vMainLayout = new QVBoxLayout;
        m_vMainLayout->setSpacing(0);
        m_vMainLayout->setContentsMargins(5, 5, 5, 5);
        setLayout(m_vMainLayout);

        m_iconLabel = new QLabel(this);
        m_iconLabel->setFixedSize(30, 30);
        m_vMainLayout->addWidget(m_iconLabel, 0, Qt::AlignHCenter);

        m_textLable = new QLabel(this);
        m_vMainLayout->addWidget(m_textLable, 0, Qt::AlignHCenter);

        m_iconLabel->setObjectName("iconLabel");
        m_textLable->setObjectName("textLabel");
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayIconBox.qss", this);
        // connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); }); { onThemeChanged(); });
    }

    FluDisplayIconBox(FluAwesomeType type, QWidget* parent = nullptr) : FluDisplayIconBox(parent)
    {
        m_type = type;
        QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_type, QColor(8, 8, 8), 30, 30);
        m_iconLabel->setPixmap(pixmap);
        m_textLable->setText(EnumTypeToQString(type));
    }

    void setSelected(bool bSelected)
    {
        setProperty("selected", bSelected);
        update();
    }

    FluAwesomeType getAwesomeType()
    {
        return m_type;
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
            m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(m_type, QColor(8, 8, 8)));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayIconBox.qss", this);
        }
        else
        {
            m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(m_type, QColor(239, 239, 239)));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDisplayIconBox.qss", this);
        }
    }

  protected:
    FluAwesomeType m_type;
    QLabel* m_iconLabel;
    QLabel* m_textLable;
    QVBoxLayout* m_vMainLayout;
};
