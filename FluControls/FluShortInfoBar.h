#pragma

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

enum class FluShortInfoBarType
{
    Info,
    Suc,
    Warn,
    Error,
};

class FluShortInfoBar : public QWidget
{
    Q_OBJECT
  public:
    FluShortInfoBar(FluShortInfoBarType infobarType, QWidget* parent = nullptr);

    void setInfoBarTypeProperty(QString infoBarType);

    void updateInfoBarTypeProperty(FluShortInfoBarType infoBarType);

    void disappear();

    void setDisappearDurartion(int disappearDuration);

    void paintEvent(QPaintEvent* event);

    public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            m_closeBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChromeClose, FluTheme::Light));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluShortInfoBar.qss", this);
        }
        else
        {
            m_closeBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChromeClose, FluTheme::Dark));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluShortInfoBar.qss", this);
        }
    }
  protected:
    QHBoxLayout* m_hMainLayout;
    QLabel* m_iconLabel;
    QLabel* m_infoLabel;
    QPushButton* m_closeBtn;

    QGraphicsOpacityEffect* m_opacityEffect;
    QPropertyAnimation* m_opacityAni;

    int m_nDisappearDuration;
    bool m_bDisappearing;
};
