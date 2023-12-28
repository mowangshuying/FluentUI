#include <QApplication>
#include <QWidget>

#include "FluGalleryWindow.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  FluGalleryWindow w;
  w.show();

  return app.exec();
}
