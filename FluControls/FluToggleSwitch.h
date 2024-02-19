#pragma once

#include <QWidget>
#include <QCheckBox>
#include "../FluUtils/FluUtils.h"

class FluToggleSwitch : public QCheckBox
{
	Q_OBJECT
  public:
	  FluToggleSwitch(QWidget* parent = nullptr) : QCheckBox(parent)
      {
          m_onText = "On";
          m_offText = "Off";

		  FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleSwitch.qss", this);
          connect(this, &FluToggleSwitch::clicked, [=](bool bChecked) { 
			  if (bChecked)
                 setText(m_onText);
              else
                 setText(m_offText);
          });
	  }

	  FluToggleSwitch(QString text, QWidget* parent = nullptr)
		  : QCheckBox(text, parent)
	  {
          m_onText = "On";
          m_offText = "Off";

		  FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluToggleSwitch.qss", this);
          connect(this, &FluToggleSwitch::clicked, [=](bool bChecked) {
              if (bChecked)
                  setText(m_onText);
              else
                  setText(m_offText);
          });
	  }


	  void setOnOffText(QString onText, QString offText)
	  {
          m_onText = onText;
          m_offText = offText;
	  }

  protected:
	  QString m_onText;
	  QString m_offText;
};
