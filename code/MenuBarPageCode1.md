```cpp
auto menuBar = new FluMenuBar;
// menuBar->move(50, 50);

auto newFileAction = new FluAction("new");
auto openFileAction = new FluAction("Open");
auto saveFileAction = new FluAction("Save");
auto exitFileAction = new FluAction("Exit");

auto fileMenu = new FluMenu(menuBar);
fileMenu->setTitle("File");
fileMenu->addAction(newFileAction);
fileMenu->addAction(openFileAction);
fileMenu->addAction(saveFileAction);
fileMenu->addAction(exitFileAction);
menuBar->addMenu(fileMenu);

// undo cut copy paste
auto undoEditAction = new FluAction("Undo");
auto cutEditAction = new FluAction("Cut");
auto copyEditAction = new FluAction("Copy");
auto pasteEditAction = new FluAction("Paste");

auto editMenu = new FluMenu(menuBar);
editMenu->setTitle("Edit");
editMenu->addAction(undoEditAction);
editMenu->addAction(cutEditAction);
editMenu->addAction(copyEditAction);
editMenu->addAction(pasteEditAction);
menuBar->addMenu(editMenu);

// Help
auto aboutAction = new FluAction("About");
auto helpMenu = new FluMenu(menuBar);
helpMenu->setTitle("Help");
helpMenu->addAction(aboutAction);
menuBar->addMenu(helpMenu);
```

