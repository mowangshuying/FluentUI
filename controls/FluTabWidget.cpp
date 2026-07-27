#include "FluTabWidget.h"

FluTabWidget::FluTabWidget(QWidget *parent /*= nullptr*/) : QTabWidget(parent)
{
    QString qss = FluStyleSheetUtils::getQssByFileName("../stylesheet/light/FluTabWidget.qss");
    setStyleSheet(qss);
}
