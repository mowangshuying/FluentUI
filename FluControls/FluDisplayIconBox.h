#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "../FluUtils/FluUtils.h"
#include "FluDef.h"
#include <QStyleOption>
#include <QPainter>

// box to display icon
class FluDisplayIconBox : public QWidget
{
    Q_OBJECT
  public:
    FluDisplayIconBox(QWidget* parent = nullptr) : QWidget(parent)
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
  protected:
    FluAwesomeType m_type;
    QLabel* m_iconLabel;
    QLabel* m_textLable;
    QVBoxLayout* m_vMainLayout;
};
