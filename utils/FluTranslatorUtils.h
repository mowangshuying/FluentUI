#pragma once

#include <QApplication>

class FluTranslatorUtils
{
  public:
    static void installTranslator(QApplication *app, QString lang);
};