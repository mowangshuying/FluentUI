#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QEvent>
#include <QResizeEvent>
#include <QLabel>

#include "../Utils/FluUtils.h"
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

    void setWidgetFixedSize(int width, int height)
    {
        m_widget->setFixedSize(width, height);
    }

    QWidget* getWidget()
    {
        return m_widget;
    }

    QVBoxLayout* getContentWidgetLayout()
    {
        return m_contentWidgetLayout;
    }

    void showEvent(QShowEvent* event);

    void closeEvent(QCloseEvent* event);

    void resizeEvent(QResizeEvent* event);

    bool eventFilter(QObject* obj, QEvent* event);

  public slots:
    void onThemeChanged();

    // void onTitleChanged(QString title);
    // void onInfoChanged(QString info);

  protected:
    QWidget* m_parentWidget;

    QHBoxLayout* m_boxLayout;
    QWidget* m_windowMask;

    QFrame* m_widget;
    QVBoxLayout* m_widgetLayout;

    QWidget* m_contentWidget;
    QVBoxLayout* m_contentWidgetLayout;
    // QLabel* m_titleLabel;
    // QLabel* m_infoLabel;

    QWidget* m_buttonWidget;
    QHBoxLayout* m_buttonLayout;
    FluPushButton* m_cancelButton;
    FluStyleButton* m_okButton;
};
