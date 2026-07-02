#pragma once

#include <QObject>
#include "FluPMenu.h"

class FluPMenuPrivate : public QObject
{
	Q_OBJECT
	Q_DECLARE_PUBLIC(FluPMenu)
  public:
	  FluPMenuPrivate(QObject* parent = nullptr) : QObject(parent)
	  {

	  }

	  ~FluPMenuPrivate()
	  {

	  }
  protected:
    FluPMenu* q_ptr;
};
