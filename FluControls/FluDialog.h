#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QEvent>
#include <QResizeEvent>
#include <QLabel>

#include "../FluUtils/FluUtils.h"
#include "FluPushButton.h"
#include "FluStyleButton.h"
#include "FluVSplitLine.h"

// note: parent can't be null.
// can use window()
class FluDialog : public QDialog
{
    Q_OBJECT
  public:
    FluDialog(QWidget* parent = nullptr);

    //QString getTitle();

    //void setTitle(QString title);

    //QString getInfo();

    //void setInfo(QString info);

    QWidget* getWidget()
    {
        return m_widget;
    }

    QVBoxLayout* getContentWidgetLayout()
    {
        return m_vContentWidgetLayout;
    }

    void showEvent(QShowEvent* event);

    void closeEvent(QCloseEvent* event);

    void resizeEvent(QResizeEvent* event);

    bool eventFilter(QObject* obj, QEvent* event);



  public slots:
    void onThemeChanged();

    //void onTitleChanged(QString title);
    //void onInfoChanged(QString info);

  protected:
    QWidget* m_parentWidget;

    QHBoxLayout* m_hBoxLayout;
    QWidget* m_windowMask;

    QFrame* m_widget;
    QVBoxLayout* m_vWidgetLayout;

    QWidget* m_contentWidget;
    QVBoxLayout* m_vContentWidgetLayout;
    //QLabel* m_titleLabel;
    //QLabel* m_infoLabel;

    QWidget* m_btnWidget;
    QHBoxLayout* m_hBtnLayout;
    FluPushButton* m_cancelBtn;
    FluStyleButton* m_okBtn;
};
