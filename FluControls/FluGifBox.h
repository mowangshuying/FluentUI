#pragma once

#include <QLabel>
#include "../FluUtils/FluThemeUtils.h"
#include "../FluUtils/FluStyleSheetUitls.h"
#include <QMovie>

class FluGifBox : public QLabel
{
    Q_OBJECT
  public:
    FluGifBox(QString lightGifPath, QString darkGifPath, QWidget* parent = nullptr);

    void setFixedSize(int nH, int nW)
    {
        QLabel::setFixedSize(nH, nW);
        m_lightMovie->setScaledSize(QSize(nH, nW));
        m_darkMovie->setScaledSize(QSize(nH, nW));
    }
  public slots:
    void onThemeChanged();

  protected:
    QMovie* m_lightMovie;
    QMovie* m_darkMovie;
};
