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

class FluDisplayCodeBox : public QTextEdit
{
    Q_OBJECT
  public:
    FluDisplayCodeBox(QWidget* parent = nullptr) : QTextEdit(parent)
    {
        auto hightLigher = new FluCppSyntaxHightLighter(document());
        setReadOnly(true);

        loadStyle("../config/drakula.xml");
        hightLigher->setCppSyntaxStyle(m_styles[0].second);

        setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
        setContextMenuPolicy(Qt::NoContextMenu);
        setFocusPolicy(Qt::FocusPolicy::NoFocus);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayCodeBox.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    void loadStyle(QString path)
    {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly))
        {
            LOG_DEBUG << "open file failed! path:" << path;
            return;
        }

        auto style = new FluCppSyntaxStyle(this);
        if (!style->loadXml(file.readAll()))
        {
            delete style;
            return;
        }

        std::pair<QString, FluCppSyntaxStyle*> pair(style->getName(), style);
        m_styles.push_back(pair);
    }

    void setCodeText(QString code)
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

  protected:
    std::vector<std::pair<QString, FluCppSyntaxStyle*>> m_styles;
};
