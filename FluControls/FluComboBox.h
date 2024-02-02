#pragma once

#include <QCombobox>
#include "../FluUtils/FluStyleSheetUitls.h"
#include <QAbstractItemView>
#include <QStyleOptionComplex>
#include <QProxyStyle>
#include <QPainter>
#include <QStyleOptionComboBox>
#include <QListWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "FluComboBoxTextItem.h"

class FluComboBox : public QComboBox
{
  public:
    FluComboBox(QWidget* parent = nullptr) : QComboBox(parent)
    {
        setFixedHeight(30);
        setEditable(false);
        view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
        view()->window()->setAttribute(Qt::WA_TranslucentBackground);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluComboBox.qss", this);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluComboBox.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluComboBox.qss", this);
        }
    }

  protected:
};
