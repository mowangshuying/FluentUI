#pragma once

#include <QPushButton>
#include <QIcon>

class FluWindowkitButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(QIcon iconNormal READ iconNormal WRITE setIconNormal FINAL)
    Q_PROPERTY(QIcon iconChecked READ iconChecked WRITE setIconChecked FINAL)
    Q_PROPERTY(QIcon iconDisabled READ iconDisabled WRITE setIconDisabled FINAL)

  public:
    FluWindowkitButton(QWidget *parent = nullptr);

    void init();

    QIcon iconNormal() const;
    void setIconNormal(const QIcon &icon);

    QIcon iconChecked() const;
    void setIconChecked(const QIcon &icon);

    QIcon iconDisabled() const;
    void setIconDisabled(const QIcon &icon);

    void reloadIcon();

    void checkStateSet() override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;
  signals:
    void doubleClicked();

  protected:
    QIcon m_iconNormal;
    QIcon m_iconChecked;
    QIcon m_iconDisabled;
};
