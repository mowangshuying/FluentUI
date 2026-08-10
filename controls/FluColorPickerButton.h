#pragma once

#include <QPushButton>
#include <QColorDialog>
#include "../utils/FluUtils.h"
#include "FluColorFlyout.h"
#include "FluColorButton.h"
#include "FluPushButton.h"

class FluColorPickerButton : public QPushButton
{
    Q_OBJECT
  public:
    FluColorPickerButton(QWidget* parent = nullptr) : QPushButton(parent)
    {
        setFixedSize(30, 30);
        m_flyout = nullptr;
        onThemeChanged();

        connect(this, &QPushButton::clicked, this, [=]() { showColorFlyout(); });
    }

    void setColor(QColor color)
    {
        std::map<QString, QString> kvmap;
        m_color = color;
        kvmap["color"] = QString::asprintf("rgb(%d,%d,%d)", color.red(), color.green(), color.blue());
        FluStyleSheetUtils::setQssByFileName(kvmap, "FluColorPickerButton.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

    QColor getColor()
    {
        return m_color;
    }

  signals:
    // Emitted after the user picks a color (from a preset or the free picker).
    void colorChanged(QColor color);

  public slots:
    void onThemeChanged()
    {
        setColor(m_color);
    }

  protected:
    void showColorFlyout()
    {
        if (m_flyout == nullptr)
        {
            m_flyout = new FluColorFlyout(this);

            // preset colors;
            const QColor presets[] = {
                QColor(255, 0, 0),   QColor(255, 165, 0), QColor(255, 255, 0),
                QColor(0, 128, 0),   QColor(75, 0, 130),  QColor(238, 130, 238),
                QColor(128, 128, 128), QColor(255, 255, 255), QColor(0, 0, 0),
            };
            for (auto& color : presets)
            {
                m_flyout->addColorButton(new FluColorButton(color, m_flyout));
            }

            // free color entry;
            auto customBtn = new FluPushButton(m_flyout);
            customBtn->setText(tr("Custom..."));
            customBtn->setFixedSize(88, 30);
            m_flyout->addCustomButton(customBtn);

            connect(m_flyout, &FluColorFlyout::colorChanged, this, [=](QColor color) {
                setColor(color);
                emit colorChanged(color);
            });

            connect(customBtn, &FluPushButton::clicked, this, [=]() {
                m_flyout->close();
                QColor color = QColorDialog::getColor(m_color, this, tr("Select Color"));
                if (color.isValid())
                {
                    setColor(color);
                    emit colorChanged(color);
                }
            });
        }

        m_flyout->show();
    }

    QColor m_color;
    FluColorFlyout* m_flyout;
};