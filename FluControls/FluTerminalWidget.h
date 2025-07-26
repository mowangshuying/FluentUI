#pragma once

#include <QTextEdit>
#include <QKeyEvent>
#include <QFont>
#include <QProcess>
#include <QByteArray>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextLayout>
#include <QTextCursor>
#include <QTextBlock>
#include <QTextCodec>
#include <assert.h>

class FluTerminalWidget : public QTextEdit
{
    Q_OBJECT
  public:
    FluTerminalWidget();

    void keyPressEvent(QKeyEvent *e);

  protected:
    QFont m_font;
    QProcess *m_process;
    long long m_lastPosition = 0;
    QByteArray m_lastInput;

  public slots:
    void onReadyReadStandardOutput();
    void onReadyReadStandardError();
};
