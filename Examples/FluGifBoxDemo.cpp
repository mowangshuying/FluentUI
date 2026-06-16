#include "FluGifBoxDemo.h"

FluGifBoxDemo::FluGifBoxDemo(QWidget* parent) : FluTemplateDemo(parent)
{
    setWindowTitle("CppQt WinUI3 Gif Demo");
    auto gifBox = new FluGifBox("../res/mona-loading-dark.gif", "../res/mona-loading-dark.gif");
    gifBox->setFixedSize(40, 40);

    m_contentLayout->setAlignment(Qt::AlignCenter);
    m_contentLayout->addWidget(gifBox, 0, Qt::AlignCenter);
}
