#include "FluScintillaDemo.h"

FluScintillaDemo::FluScintillaDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    FluThemeUtils::getUtils()->setTheme(FluTheme::Light);

    setWindowTitle("CppQt WinUI3 Scintiila Demo Dev");
#ifndef _DEBUG
    setWindowTitle("CppQt WinUI3 Scintiila Demo");
#endif

    m_contentLayout->setContentsMargins(0, 0, 0, 0);
    m_edit = new QsciScintilla;
    m_edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_contentLayout->addWidget(m_edit);

    // show line number;
    m_edit->setMarginType(0, QsciScintilla::NumberMargin);
    m_edit->setMarginLineNumbers(0, true);
    m_edit->setMarginWidth(0, 30);

    //// set background color;
    //m_edit->setStyleSheet("border:1px solid rgb(232, 232, 232);");

    //// set line number background color;
    //m_edit->setMarginsBackgroundColor(QColor(255, 255, 255));
    //// set line number text color;
    //m_edit->setMarginsForegroundColor(Qt::red);

    m_edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_edit->setScrollWidth(5);
    m_edit->setScrollWidthTracking(true);

    // no border;
    m_edit->setFrameStyle(QFrame::NoFrame);
    m_edit->setStyleSheet("QsciScintilla { border: none; padding: 0px; margin: 0px; color: black; }");

    // // set cpp lexer
    // edit->setLexer(new QsciLexerCPP(edit));
    // edit->setFolding(QsciScintilla::BoxedTreeFoldStyle);
    // edit->setFoldMarginColors(QColor(255, 255, 255), QColor(255, 255, 255));

    auto delegate = new FluScrollDelegate(m_edit);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, &FluScintillaDemo::onThemeChanged);
}

void FluScintillaDemo::onThemeChanged()
{
    FluTemplateDemo::onThemeChanged();
    if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
    {
        //m_edit->setStyleSheet("background-color:1px solid rgb(232, 232, 232);");
        m_edit->setPaper(QColor(232, 232, 232)); 
        
        // set line number background color;
        m_edit->setMarginsBackgroundColor(QColor(232, 232, 232));
        // set line number text color;
        m_edit->setMarginsForegroundColor(Qt::black);
        //m_edit->setBackgroundColor(QColor(255, 255, 255));
        // set text color;
        //m_edit->SendScintilla(QsciScintillaBase::SCI_STYLESETFORE, 0, Qt::black);
        m_edit->setColor(Qt::black);
        //m_edit->setIndicatorForegroundColor(Qt::black);

        // set caret color;
        m_edit->setCaretForegroundColor(Qt::black);
    }
    else if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Dark)
    {
        //m_edit->setStyleSheet("background-color:1px solid rgb(39, 39, 39);");
        m_edit->setPaper(QColor(39, 39, 39));

        // set line number background color;
        m_edit->setMarginsBackgroundColor(QColor(39, 39, 39));
        // set line number text color;
        m_edit->setMarginsForegroundColor(Qt::white);

        // set text color;
        //m_edit->SendScintilla(QsciScintillaBase::SCI_STYLESETFORE, 0, Qt::white);

        //m_edit->setFrameStyle(QFrame::NoFrame);
        //m_edit->setStyleSheet("QsciScintilla { border: none; padding: 0px; margin: 0px; color: rgb(255, 255, 255); }");
        m_edit->setColor(Qt::white);
        //m_edit->setIndicatorForegroundColor(Qt::white);
        //  set caret color;
        m_edit->setCaretForegroundColor(Qt::white);
    }
    else if (FluThemeUtils::getUtils()->getTheme() == FluTheme::AtomOneDark)
    {
        //m_edit->setStyleSheet("background-color:1px solid rgb(40, 44, 52);");
        m_edit->setPaper(QColor(40, 44, 52));
        // set line number background color;
        m_edit->setMarginsBackgroundColor(QColor(40, 44, 52));
        // set line number text color;
        m_edit->setMarginsForegroundColor(Qt::white);

        // set text color;
        //m_edit->SendScintilla(QsciScintillaBase::SCI_STYLESETFORE, 0, Qt::white);
        m_edit->setColor(Qt::white);
        //m_edit->setIndicatorForegroundColor(Qt::white);
        //  set caret color;
        m_edit->setCaretForegroundColor(Qt::white);
    }

}
