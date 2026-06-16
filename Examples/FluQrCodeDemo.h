#pragma once

#include "FluTemplateDemo.h"
#include <QrCode.hpp>

class FluQrCodeDemo : public FluTemplateDemo
{
  public:
    FluQrCodeDemo(QWidget* parent = nullptr);

    QImage getQrCode(QString text, int size);
};