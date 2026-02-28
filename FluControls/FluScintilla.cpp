#include "FluScintilla.h"

FluScintilla::FluScintilla(QWidget* parent) : QsciScintilla(parent)
{
    // m_edit = new QsciScintilla;
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // m_contentLayout->addWidget(m_edit);

    // show line number;
    setMarginType(0, QsciScintilla::NumberMargin);
    setMarginLineNumbers(0, true);
    setMarginWidth(0, 30);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setScrollWidth(5);
    setScrollWidthTracking(true);

    // no border;
    setFrameStyle(QFrame::NoFrame);
     //setStyleSheet("QsciScintilla { border: none; padding: 0px; margin: 0px; color: black; }");
    m_delegate = new FluScrollDelegate(this);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, &FluScintilla::onThemeChanged);
}

// public slots:
void FluScintilla::onThemeChanged()
{
    if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
    {
        setPaper(QColor(232, 232, 232));

        // set line number background color;
        setMarginsBackgroundColor(QColor(232, 232, 232));
        // set line number text color;
        setMarginsForegroundColor(Qt::black);

        // set text color;
        setColor(Qt::black);

        // set caret color;
        setCaretForegroundColor(Qt::black);
    }
    else if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Dark)
    {
        setPaper(QColor(39, 39, 39));

        // set line number background color;
        setMarginsBackgroundColor(QColor(39, 39, 39));
        // set line number text color;
        setMarginsForegroundColor(Qt::white);

        // set text color;
        setColor(Qt::white);

        //  set caret color;
        setCaretForegroundColor(Qt::white);
    }
    else if (FluThemeUtils::getUtils()->getTheme() == FluTheme::AtomOneDark)
    {
        setPaper(QColor(40, 44, 52));
        // set line number background color;
        setMarginsBackgroundColor(QColor(40, 44, 52));
        // set line number text color;
        setMarginsForegroundColor(Qt::white);

        // set text color;
        setColor(Qt::white);

        //  set caret color;
        setCaretForegroundColor(Qt::white);
    }
}
