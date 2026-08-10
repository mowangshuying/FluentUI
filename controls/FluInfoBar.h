#pragma once

#include "FluWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPainterPath>
#include "../utils/FluUtils.h"

enum class FluInfoBarSeverity
{
    Informational,
    Success,
    Warning,
    Error,
};

class FluInfoBar : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(double opacity READ getOpacity WRITE setOpacity)
  public:
    explicit FluInfoBar(FluInfoBarSeverity severity = FluInfoBarSeverity::Informational, QWidget* parent = nullptr);

    FluInfoBarSeverity severity() const;
    void setSeverity(FluInfoBarSeverity severity);

    QString title() const;
    void setTitle(const QString& title);

    QString message() const;
    void setMessage(const QString& message);

    bool isOpen() const;
    void setIsOpen(bool isOpen);

    bool isClosable() const;
    void setIsClosable(bool isClosable);

    double getOpacity() const;
    void setOpacity(double opacity);

  signals:
    void isOpenChanged(bool isOpen);
    void closeRequested();

  public slots:
    void onThemeChanged();

  protected:
    void paintEvent(QPaintEvent* event) override;

  private:
    void updateSeverityVisuals();
    QColor severityColor() const;
    QColor severityIconColor() const;
    QString severityString() const;

  private:
    FluInfoBarSeverity m_severity;
    QString m_title;
    QString m_message;
    bool m_isOpen;
    bool m_isClosable;

    QHBoxLayout* m_mainLayout;
    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QLabel* m_messageLabel;
    QPushButton* m_closeBtn;

    QPropertyAnimation* m_fadeAnim;
    double m_opacity;
};