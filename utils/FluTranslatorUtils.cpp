#include "FluTranslatorUtils.h"
#include <QTranslator>
void FluTranslatorUtils::installTranslator(QApplication* app, QString lang)
{
    QTranslator* translator = new QTranslator();
#ifndef USE_QRC
    bool isLoaded = translator->load(QString(":/i18n/%1.qm").arg(lang));
#else
    bool isLoaded = translator->load(QString(":/i18n/%1.qm").arg(lang));
#endif
    if (isLoaded)
    {
        app->installTranslator(translator);
    }
}
