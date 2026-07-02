#pragma once

#include <QMenu>
 
class FluPMenu : public QMenu
{
	Q_OBJECT
  public:
	  FluPMenu(QWidget* parent = nullptr)
	  {

	  }

	  FluPMenu(const QString &title, QWidget* parent = nullptr)
		  : QMenu(title, parent)
	  {

	  }
};
