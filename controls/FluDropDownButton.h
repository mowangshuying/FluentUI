#pragma once

#include <QPushButton>
#include "FluWidget.h"
#include <QHBoxLayout>
#include "../Utils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "FluMenu.h"
#include <QIcon>

class FluDropDownButton : public FluWidget
{
    Q_OBJECT
  public:
    FluDropDownButton(QWidget* parent = nullptr);

    QPushButton* getTextButton();

    QPushButton* getIconButton();

    void setIcon(FluAwesomeType type);

    void setIcon(QIcon icon);

    void setSvgPath(QString svgLightPath, QString svgDarkPath);

    void setText(QString text);

    void addTextItem(QString text);

    void addIconTextItem(FluAwesomeType type, QString text);

    void addIconTextItem(QIcon type, QString text);

    //  void mousePressedEvent(QMouseEvent* event)
    //  {

    //  }

    void mouseReleaseEvent(QMouseEvent* e);

    void paintEvent(QPaintEvent* event);

    void setEnabled(bool enabled);
  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    QPushButton* m_textButton;
    QPushButton* m_iconButton;  // dropdown button;

    FluAwesomeType m_textAwesomeType;
    //  FluAwesomeType* m_iconAwesomeType;

    QString m_svgLightPath;
    QString m_svgDarkPath;

    QHBoxLayout* m_mainLayout;
    FluMenu* m_menu;
};
