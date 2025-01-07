#pragma once

#include "FluWidget.h"
#include <vector>
#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>
#include <QPainter>
#include <QStyleOption>
#include "../FluUtils/FluUtils.h"

class FluShortcutPicker : public FluWidget
{
    Q_OBJECT
  public:
    FluShortcutPicker(QWidget* parent = nullptr);

    void updateKeys();

    void clearLabels();

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    std::vector<QString> m_keyTexts;
    QHBoxLayout* m_hMainLayout;
};
