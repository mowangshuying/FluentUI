#pragma once

#include <QLabel>
#include <map>
#include "../FluUtils/FluUtils.h"
#include <QStyle>

class FluBorder : public QLabel
{
    Q_OBJECT
  public:
    FluBorder(QWidget* parent = nullptr);

    void updateProperty(QString textColor, QString bgColor, QString borderWidth, QString borderColor);

    void setBackGroundColor(QColor bgColor);

    void setBorderWidth(int width);

    void setBorderColor(QColor borderColor);

    void setTExtColor(QColor textColor);

    bool isTransparentBackground();

  protected:
    std::map<QString, QString> m_map;
};
