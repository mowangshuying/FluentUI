#pragma once

#include "FluWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "../utils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include <QPropertyAnimation>
#include <QEasingCurve>

enum class FluShortInfoBarType
{
    Info,
    Suc,
    Warn,
    Error,
};

class FluShortInfoBar : public FluWidget
{
    Q_OBJECT
    Q_PROPERTY(double opacity READ getOpacity WRITE setOpacity)
  public:
    FluShortInfoBar(FluShortInfoBarType infobarType, QWidget* parent = nullptr);

    ~FluShortInfoBar();

    void setInfoBarTypeProperty(QString infoBarType);

    void setInfoBarType(FluShortInfoBarType type);

    void setInfoBarText(QString infoBarText);

    void updateInfoBarTypeProperty(FluShortInfoBarType infoBarType);

    void disappear();

    void setDisappearDuration(int disappearDuration);

    QPushButton* getCloseButton();

    double getOpacity() const;
    void setOpacity(double opacity);

    void paintEvent(QPaintEvent* event) override;

  public slots:
    void onThemeChanged();

  protected:
    void showEvent(QShowEvent* event) override;

    void showFadeIn();

    QHBoxLayout* m_mainLayout;
    QLabel* m_iconLabel;
    QLabel* m_infoLabel;
    QPushButton* m_closeButton;

    QPropertyAnimation* m_opacityAni;
    double m_opacity;

    int m_disappearDuration;
    bool m_isDisappearing;
#ifdef _DEBUG
    static int m_count;
#endif
};