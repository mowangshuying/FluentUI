#pragma once

#include <QWidget>
#include "../Utils/FluStyleSheetUtils.h"
#include "../Utils/FluThemeUtils.h"

class FluWidget : public QWidget
{
    Q_OBJECT
  public:
    FluWidget(QWidget* parent = nullptr);

    virtual ~FluWidget()
    {
    }

    void paintEvent(QPaintEvent* event);
    void showEvent(QShowEvent* event);

    virtual QString qssFileName()
    {
        return QString();
    }

  public slots:
    virtual void onThemeChanged()
    {
        QString qss = qssFileName();
        if (!qss.isEmpty())
        {
            FluStyleSheetUtils::setQssByFileName(qss, this, m_theme);
        }
    }

  protected:
    FluTheme m_theme;
};
