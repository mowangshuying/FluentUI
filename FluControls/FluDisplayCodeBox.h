#pragma once

#include <QPlainTextEdit>
#include "../FluUtils/FluUtils.h"
#include <QSyntaxHighlighter>
#include <QFile>
#include <QSettings>
#include "FluCppSHLRule.h"
#include "FluCppSyntaxHightLighter.h"

class FluDisplayCodeBox : public QTextEdit
{
    Q_OBJECT
  public:
    FluDisplayCodeBox(QWidget* parent = nullptr) : QTextEdit(parent)
    {
        auto hightLigher = new FluCppSyntaxHightLighter(document());
        setReadOnly(true);
        setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
        setContextMenuPolicy(Qt::NoContextMenu);
        setFocusPolicy(Qt::FocusPolicy::NoFocus);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayCodeBox.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    void setCode(QString code)
    {
        setPlainText(code);
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
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayCodeBox.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluDisplayCodeBox.qss", this);
        }
    }
};
