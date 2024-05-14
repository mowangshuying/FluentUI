#pragma once

#include <map>
#include <QString>

class FluObjectPtrUtils
{
  public:
    FluObjectPtrUtils();
    static FluObjectPtrUtils* getUtils();

    void add(int64_t key, QString value);

    void remove(int64_t key);
  protected:
    std::map<int64_t, QString> m_ptr2strMap;
};
