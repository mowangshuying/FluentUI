#pragma once

#include "FluMessageBox.h"
#include <QKeyEvent>
#include <vector>
#include <QHBoxLayout>

class FluShortcutPickerDlg : public FluMessageBox
{
    Q_OBJECT
  public:
    FluShortcutPickerDlg(QWidget* parent = nullptr);

    std::vector<QString> getKeyTexts();

    void setKeyTexts(std::vector<QString> keyTexts);

    void updateKeys();

    void clearLabels();

    QString keyToString(int key, bool isShift = false);

    void keyPressEvent(QKeyEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    std::vector<QString> m_keyTexts;
    QHBoxLayout* m_keysLayout;
    QWidget* m_KeysWidget;
};
