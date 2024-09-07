#include "FluTabWidget.h"

FluTabWidget::FluTabWidget(QWidget *parent /*= nullptr*/) : QTabWidget(parent)
{
    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluTabWidget.qss");
    setStyleSheet(qss);
}
