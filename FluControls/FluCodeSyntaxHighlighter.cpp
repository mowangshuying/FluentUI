#include "FluCodeSyntaxHighlighter.h"
#include <QDebug>

FluCodeSyntaxHighlighter::FluCodeSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{

    keywordFormat.setForeground(QColor(189, 120, 188));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b"
                    << "\\bQString\\b" << "\\bQVariant\\b" << "\\bQList\\b"
                    << "\\bQMap\\b" << "\\binclude\\b" << "\\bif\\b"
                    << "\\belse\\b" << "\\bfor\\b" << "\\bwhile\\b"
                    << "\\breturn\\b" << "\\bauto\\b" << "\\bconst\\b"
                    << "\\bconstexpr\\b" << "\\bdecltype\\b" << "\\bdecltype\\b"
                    << "\\bdelete\\b" << "\\bdo\\b" << "\\benum\\b"
                    << "\\bexplicit\\b" << "\\bextern\\b" << "\\bfinal\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bmutable\\b"
                    << "\\bnew\\b" << "\\bnoexcept\\b" << "\\boverride\\b"
                    << "\\bprotected\\b" << "\\bpublic\\b" << "\\bregister\\b"
                    << "\\breinterpret_cast\\b" << "\\bsizeof\\b" << "\\bstatic_assert\\b"
                    << "\\bstatic_cast\\b" << "\\bswitch\\b" << "\\btemplate\\b"
                    << "\\bthis\\b" << "\\bthread_local\\b" << "\\bthrow\\b"
                    << "\\btry\\b" << "\\btypeid\\b" << "\\btypename\\b"
                    << "\\busing\\b" << "\\bvirtual\\b" << "\\bvolatile\\b"
                    << "\\bwchar_t\\b";
    
    for (const QString &pattern : keywordPatterns) {
        HighlightingRule rule(QRegularExpression(pattern), keywordFormat);
        highlightingRules.append(rule);
    }

        // func name
    functionFormat.setForeground(QColor(97, 175, 239));
    HighlightingRule rule = HighlightingRule(QRegularExpression("\\b[A-Za-z0-9_]+(?=\\s*\\()"), functionFormat);
    highlightingRules.append(rule);

    classFormat.setForeground(QColor(229, 192, 123));
    classFormat.setFontWeight(QFont::Bold);
    // 
    rule = HighlightingRule(QRegularExpression("\\bQ[A-Za-z]+\\b"), classFormat);
    highlightingRules.append(rule);
    
    // 
    HighlightingRule fluRule(QRegularExpression("\\bFlu[A-Za-z]+\\b"), classFormat);
    highlightingRules.append(fluRule);

    singleLineCommentFormat.setForeground(QColor(92, 99, 112));  
    rule = HighlightingRule(QRegularExpression("//[^\n]*"), singleLineCommentFormat);
    highlightingRules.append(rule);

    // ""
    quotationFormat.setForeground(QColor(152,184,89));  
    rule = HighlightingRule(QRegularExpression("\".*\""), quotationFormat);
    highlightingRules.append(rule);
    
    rule = HighlightingRule(QRegularExpression("\'.\'"), quotationFormat);
    highlightingRules.append(rule);

    numberFormat.setForeground(QColor(199, 154, 96)); 
    rule = HighlightingRule(QRegularExpression("\\b[0-9]+\\b"), numberFormat);
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void FluCodeSyntaxHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1) {
        startIndex = text.indexOf(commentStartExpression);
    }

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}