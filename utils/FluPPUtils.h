#pragma once

#include <QObject>
#include "../Controls/FluDef.h"

namespace FluPPUtils
{

// PPMouseState
Q_NAMESPACE
enum class PPMouseState
{
    Normal,
    Hover,
    Pressed,
    Disabled,
};
Q_ENUM_NS(PPMouseState)

static void setPPMouseState(QObject* obj, PPMouseState state)
{
    setEnumProperty(obj, "ppMouseState", state);
}

static PPMouseState getPPMouseState(QObject* obj)
{
    return getEnumProperty<PPMouseState>(obj, "ppMouseState");
}

static void setPPMouseState(QObject* obj, QString ext, PPMouseState state)
{
    setEnumProperty(obj, ext + "_ppMouseState", state);
}

static PPMouseState getPPMouseState(QObject* obj, QString ext)
{
    return getEnumProperty<PPMouseState>(obj, ext + "_ppMouseState");
}

/// others;
static void setProperty(QObject* obj, QString name, QVariant value)
{
    obj->setProperty(name.toStdString().c_str(), value);
}
}  // namespace FluPPUtils
