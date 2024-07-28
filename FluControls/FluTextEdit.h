#pragma once

#include <QTextEdit>
#include "../FluUtils/FluUtils.h"
#include <QTextDocument>
#include <QWidget>

class FluTextEditWrap;
class FluTextEdit : public QTextEdit
{
    Q_OBJECT
  public:
    FluTextEdit(QWidget* parent = nullptr);

    bool getAutoAdjustSize()
    {
        return m_bAutoAdjustSize;
    }

    void setAutoAdjustSize(bool bAdjustSize)
    {
        m_bAutoAdjustSize = bAdjustSize;
        document()->contentsChanged();
    }

    void paintEvent(QPaintEvent* event)
    {
        QTextEdit::paintEvent(event);
        if (!hasFocus())
            return;

        QPainter painter(viewport());
        FluStyleSheetUitls::drawBottomLineIndicator(this, &painter);
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTextEdit.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTextEdit.qss", this);
        }
    }

  protected:
    FluTextEditWrap* m_wrap;
    bool m_bAutoAdjustSize;
};
