#pragma once

#include <QPushButton>
#include "FluWidget.h"
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "FluMenu.h"
#include <QIcon>

class FluDropDownButton : public FluWidget
{
    Q_OBJECT
  public:
    FluDropDownButton(QWidget* parent = nullptr);

    QPushButton* getTextBtn();

    QPushButton* getIconBtn();

    void setIcon(FluAwesomeType type);

    void setIcon(QIcon icon);

    void setSvgPath(QString svgLightPath, QString svgDarkPath);

    void setText(QString text);

    void addTextItem(QString text);

    void addIconTextItem(FluAwesomeType type, QString text);

    //  void mousePressedEvent(QMouseEvent* event)
    //  {

    //  }

    void mouseReleaseEvent(QMouseEvent* e);

    void paintEvent(QPaintEvent* event);
  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    QPushButton* m_textBtn;
    QPushButton* m_iconBtn;  // dropdown button;

    FluAwesomeType m_textAwesomeType;
    //  FluAwesomeType* m_iconAwesomeType;

    QString m_svgLightPath;
    QString m_svgDarkPath;

    QHBoxLayout* m_hMainLayout;
    FluMenu* m_menu;
};
