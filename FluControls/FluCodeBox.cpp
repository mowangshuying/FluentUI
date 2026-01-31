#include "FluCodeBox.h"
#include <cmark.h>
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QTextDocumentFragment>
#include "FluCodeSyntaxHighlighter.h"

FluCodeBox::FluCodeBox(QWidget* parent /*= nullptr*/) : QTextEdit(parent), m_syntaxHighlighter(nullptr)
{
    setReadOnly(true);
    setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    setContextMenuPolicy(Qt::NoContextMenu);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluCodeBox::setCodeText(QString code)
{
    char* buf = cmark_markdown_to_html(code.toStdString().c_str(), code.toStdString().size(), CMARK_OPT_UNSAFE);
    QByteArray out(buf);
    free(buf);

    QString html = QString::fromUtf8(out);
    
    setHtml(html);
    
    if (!m_syntaxHighlighter) {
        m_syntaxHighlighter = new FluCodeSyntaxHighlighter(document());
    }
}

void FluCodeBox::resizeEvent(QResizeEvent*)
{
    document()->setTextWidth(viewport()->width());
    int newHeight = document()->size().height() + document()->documentMargin();
    setFixedHeight(newHeight);
}

// bool FluCodeBox::eventFilter(QObject* object, QEvent *event);
// {
//     if (event->type() == QEvent::Wheel)
//     {
//         return true;
//     }

//     return false;
// }

void FluCodeBox::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluCodeBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}