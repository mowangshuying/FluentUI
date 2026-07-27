#include "FluObjectPtrUtils.h"

FluObjectPtrUtils::FluObjectPtrUtils()
{
}

FluObjectPtrUtils* FluObjectPtrUtils::getUtils()
{
    static FluObjectPtrUtils utils;
    return (FluObjectPtrUtils*)(&utils);
}

void FluObjectPtrUtils::add(int64_t key, QString value)
{
    m_ptr2strMap[key] = value;
}

void FluObjectPtrUtils::remove(int64_t key)
{
    m_ptr2strMap.erase(key);
}
