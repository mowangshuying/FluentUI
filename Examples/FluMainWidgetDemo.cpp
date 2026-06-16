#include "FluMainWidgetDemo.h"

FluMainWidgetDemo::FluMainWidgetDemo(QWidget* parent) : FluFrameLessWidget(parent)
{
    setWindowTitle("CppQt FluentUI MainWidget Demo.");
    setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));
#ifdef USE_QRC
    setWindowIcon(QIcon(":/res/Tiles/GalleryIcon.ico"));
#endif
    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
    m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
    m_titleBar->setFixedHeight(30);
    m_titleBar->setObjectName("titleBar");

    m_menuBar = new FluMenuBar();
    m_vMainLayout->insertWidget(1, m_menuBar);

    __initMenuBar();

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluMainWidgetDemo::__initMenuBar()
{
    auto newFileAction = new FluAction("new");
    auto openFileAction = new FluAction("Open");
    auto saveFileAction = new FluAction("Save");
    auto exitFileAction = new FluAction("Exit");

    auto fileMenu = new FluMenu(m_menuBar);
    fileMenu->setTitle("File");
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(exitFileAction);

    m_menuBar->addAction(fileMenu->menuAction());

    // undo cut copy paste
    auto undoEditAction = new FluAction("Undo");
    auto cutEditAction = new FluAction("Cut");
    auto copyEditAction = new FluAction("Copy");
    auto pasteEditAction = new FluAction("Paste");

    auto editMenu = new FluMenu(m_menuBar);
    editMenu->setTitle("Edit");
    editMenu->addAction(undoEditAction);
    editMenu->addAction(cutEditAction);
    editMenu->addAction(copyEditAction);
    editMenu->addAction(pasteEditAction);
    // menuBar->addMenu(editMenu);
    m_menuBar->addAction(editMenu->menuAction());

    //
    auto changeThemeMenu = new FluMenu(m_menuBar);
    changeThemeMenu->setTitle("ChangeTheme");

    auto lightAction = new FluAction("Light");
    auto darkAction = new FluAction("Dark");

    changeThemeMenu->addAction(lightAction);
    changeThemeMenu->addAction(darkAction);

    connect(lightAction, &FluAction::triggered, this, [=]() { FluThemeUtils::getUtils()->setTheme(FluTheme::Light); });

    connect(darkAction, &FluAction::triggered, this, [=]() { FluThemeUtils::getUtils()->setTheme(FluTheme::Dark); });

    m_menuBar->addAction(changeThemeMenu->menuAction());

    // Help
    auto aboutAction = new FluAction("About");
    auto helpMenu = new FluMenu(m_menuBar);
    helpMenu->setTitle("Help");
    helpMenu->addAction(aboutAction);
    // menuBar->addMenu(helpMenu);
    m_menuBar->addAction(helpMenu->menuAction());
}
