#pragma once

#include <QLabel>
#include "../Utils/FluThemeUtils.h"
#include "../Utils/FluStyleSheetUtils.h"
#include <QMovie>

class FluGifBox : public QLabel
{
    Q_OBJECT
  public:
    FluGifBox(QString lightGifPath, QString darkGifPath, QWidget* parent = nullptr);

    void setFixedSize(int h, int w)
    {
        QLabel::setFixedSize(h, w);
        m_lightMovie->setScaledSize(QSize(h, w));
        m_darkMovie->setScaledSize(QSize(h, w));
    }
  public slots:
    void onThemeChanged();

  protected:
    QMovie* m_lightMovie;
    QMovie* m_darkMovie;
};
