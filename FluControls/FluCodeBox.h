#pragma once

#include <QPlainTextEdit>
#include "../FluUtils/FluUtils.h"
#include <QSyntaxHighlighter>
#include <QFile>
#include <QSettings>
#include "FluCppSHLRule.h"
#include "FluCppSyntaxHightLighter.h"
#include <vector>
#include "FluCppSyntaxStyle.h"
#include <utility>

class FluCodeBox : public QTextEdit
{
    Q_OBJECT
  public:
    FluCodeBox(QWidget* parent = nullptr) : QTextEdit(parent)
    {
        setReadOnly(true);
        setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
        setContextMenuPolicy(Qt::NoContextMenu);
        setFocusPolicy(Qt::FocusPolicy::NoFocus);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCodeBox.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    void setCodeText(QString code)
    {
        setMarkdown(code);
    }

    void resizeEvent(QResizeEvent*)
    {
        document()->setTextWidth(viewport()->width());
        int newHeight = document()->size().height() + document()->documentMargin();
        setFixedHeight(newHeight);
    }

  signals:
    void sizeChanged();

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCodeBox.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCodeBox.qss", this);
        }
    }

  protected:
};
