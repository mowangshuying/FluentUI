﻿#pragma once

#include <QPropertyAnimation>

class FluValueObject : public QObject
{
	Q_OBJECT
    Q_PROPERTY(float value READ getValue WRITE setValue)
  public:
	  FluValueObject(QObject* parent = nullptr) : QObject(parent)
	  {
              m_value = 0;
	  }

	  void setValue(float value)
	  {
              m_value = value;
	  }

	  float getValue()
	  {
              return m_value;
	  }

   protected:
      float m_value;
};
