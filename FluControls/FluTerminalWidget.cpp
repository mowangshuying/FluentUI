#include "FluTerminalWidget.h"
#include "../FluUtils/FluStyleSheetUitls.h"
#include <QDebug>

FluTerminalWidget::FluTerminalWidget()
{
    // setStyleSheet("background-color:rgb(0,0,0); color:rgb(255,255,255); border:0px;");
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    resize(1000, 700);
    setWindowTitle("Terminal");
    // m_font.setFamily("Times New Roman");
    // m_font.setPixelSize(14);
    setFont(m_font);

    m_process = new QProcess();
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadyReadStandardOutput()));
    connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(onReadyReadStandardError()));

#ifdef Q_OS_WIN
    m_process->start("cmd");
#elif defined(Q_OS_LINUX)
    m_process->start("bash");
#elif defined(Q_OS_MACOS)
    m_process->start("bash");
#endif

    QTextCursor editCursor = textCursor();
    QTextBlockFormat textBlockFormat;
    textBlockFormat.setLineHeight(20, QTextBlockFormat::FixedHeight);
    editCursor.setBlockFormat(textBlockFormat);
    setTextCursor(editCursor);

    FluStyleSheetUitls::setQssByFileName("FluTerminalWidget.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluTerminalWidget::keyPressEvent(QKeyEvent* e)
{
    QTextCursor editCursor = textCursor();
    if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
    {
        e->ignore();
        editCursor.setPosition(m_lastPosition, QTextCursor::MoveAnchor);
        editCursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
        QString string = editCursor.selectedText();
        editCursor.clearSelection();
#ifdef Q_OS_WIN
        m_lastInput = string.toLocal8Bit() + '\r' + '\n';
#elif defined(Q_OS_LINUX)
        m_lastInput = string.toLocal8Bit() + '\n';
#elif defined(Q_OS_MACOS)
        m_lastInput = string.toLocal8Bit() + '\n';
#endif
        m_process->write(m_lastInput);
        return;
    }
    else if (e->key() == Qt::Key_Backspace && editCursor.position() <= m_lastPosition)
        return;
    else if (e->key() == Qt::Key_Delete && editCursor.position() <= m_lastPosition)
        return;
    else
        return QTextEdit::keyPressEvent(e);
}

void FluTerminalWidget::onReadyReadStandardOutput()
{
    QByteArray ba = m_process->readAllStandardOutput();
    QTextCodec* textCodec = QTextCodec::codecForName("System");
    assert(textCodec != nullptr);
    QString output = textCodec->toUnicode(ba);

    if (output.length() > 0 && output != QString::fromLocal8Bit(m_lastInput))
    {
        if (FluThemeUtils::isDarkTheme())
            setTextColor(Qt::white);

        if (FluThemeUtils::isLightTheme())
            setTextColor(Qt::black);

        append(output.trimmed());
        moveCursor(QTextCursor::End);
        m_lastPosition = textCursor().position();
    }
}

void FluTerminalWidget::onReadyReadStandardError()
{
    QByteArray ba = m_process->readAllStandardError();
    QTextCodec* textCodec = QTextCodec::codecForName("System");
    assert(textCodec != nullptr);
    QString output = textCodec->toUnicode(ba);

    if (output.length() > 0 && output != QString::fromLocal8Bit(m_lastInput))
    {
        setTextColor(Qt::red);
        append(output.trimmed());
        moveCursor(QTextCursor::End);
        m_lastPosition = textCursor().position();
    }
}