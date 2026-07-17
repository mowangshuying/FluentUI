#include "FluTranslatorUtils.h"
#include <QTranslator>
void FluTranslatorUtils::installTranslator(QApplication* app, QString lang)
{
    QTranslator* translator = new QTranslator();
#ifndef USE_QRC
        bool bLoad = translator->load(QString(":/i18n/%1.qm").arg(lang));
#else
        bool bLoad = translator->load(QString(":/i18n/%1.qm").arg(lang));
#endif
    if (bLoad)
    {
        app->installTranslator(translator);
    }
}
