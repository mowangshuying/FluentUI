#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include "../Utils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "FluIndicatorRoundMenu.h"
#include <QIcon>
#include <QPropertyAnimation>

class FluComboBoxEx : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QString currentText READ currentText NOTIFY currentTextChanged)
    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText)
    Q_PROPERTY(bool editable READ isEditable WRITE setEditable)
    Q_PROPERTY(qreal chevronRotation READ chevronRotation WRITE setChevronRotation)
  public:
    FluComboBoxEx(QWidget* parent = nullptr);

    QPushButton* getTextBtn();
    QPushButton* getIconBtn();

    int count() const;
    int currentIndex() const;
    QString currentText() const;
    QString itemText(int index) const;
    QIcon itemIcon(int index) const;
    bool isItemEnabled(int index) const;
    QString itemToolTip(int index) const;

    bool isEditable() const;
    bool isEnabled() const;
    QString placeholderText() const;
    qreal chevronRotation() const;

    void setIcon(FluAwesomeType type);
    void setText(QString text);

    void addItem(QString text);
    void addItem(FluAwesomeType type, QString text);
    void addItem(QIcon icon, QString text);
    void addTextItem(QString text);
    void addIconTextItem(FluAwesomeType type, QString text);
    void insertItem(int index, QString text);
    void insertItem(int index, FluAwesomeType type, QString text);
    void removeItem(int index);
    void clear();

    void setCurrentIndex(int index);
    int findText(const QString& text) const;

    void setMaxVisibleItems(int num);
    void setPlaceholderText(const QString& text);
    void setEditable(bool editable);
    void setEnabled(bool enabled);
    void setItemEnabled(int index, bool enabled);
    void setItemToolTip(int index, const QString& tooltip);
    void setChevronRotation(qreal rotation);

    void mouseReleaseEvent(QMouseEvent* e) override;
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* e) override;

  signals:
    void clicked();
    void currentIndexChanged(int index);
    void currentTextChanged(const QString& text);
    void activated(int index);
    void highlighted(int index);
    void chevronRotationChanged(qreal rotation);

  public slots:
    void onThemeChanged();

  protected:
    void updateText();
    void startChevronAnimation(bool expand);

    QPushButton* m_textBtn;
    QPushButton* m_iconBtn;

    FluAwesomeType m_textAwesomeType;

    QHBoxLayout* m_hMainLayout;
    FluIndicatorRoundMenu* m_menu;

    int m_currentIndex;
    QString m_placeholderText;
    bool m_editable;
    QPropertyAnimation* m_chevronAni;
    qreal m_chevronRotation;
};
