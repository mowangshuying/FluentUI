#pragma once

#include "FluTemplateDemo.h"
#include <QrCode.hpp>

class FluQrCodeDemo : public FluTemplateDemo
{
  public:
    FluQrCodeDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        auto qrCodeLabel = new QLabel(this);
        qrCodeLabel->setFixedSize(100, 100);
        qrCodeLabel->setPixmap(QPixmap::fromImage(getQrCode("Hello World", 100)));
        m_contentLayout->addWidget(qrCodeLabel, 0, Qt::AlignCenter);
    }

    QImage getQrCode(QString text, int size)
    {
        qrcodegen::QrCode qrcode = qrcodegen::QrCode::encodeText(text.toStdString().c_str(), qrcodegen::QrCode::Ecc::LOW);

        int qrSize = qrcode.getSize();
        QImage image(qrSize, qrSize, QImage::Format_ARGB32);
        image.fill(Qt::white);
        for (int y = 0; y < qrSize; y++)
        {
            for (int x = 0; x < qrSize; x++)
            {
                if (qrcode.getModule(x, y))
                {
                    image.setPixel(x, y, qRgb(0, 0, 0));
                }
            }
        }

        image = image.scaled(size, size);
        return image;
    }
};