#include "FluRatingControl.h"

FluRatingControl::FluRatingControl(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);

    addStar();
    setFixedSize(170, 45);
    onThemeChanged();
}

void FluRatingControl::addStar()
{
    for (int i = 0; i < 5; i++)
    {
        auto star = new FluStar(this);
        star->installEventFilter(this);
        m_stars.push_back(star);
        m_hMainLayout->addWidget(star);
    }
}

int FluRatingControl::getNum()
{
    return m_nNum;
}

bool FluRatingControl::eventFilter(QObject* watched, QEvent* event)
{
    for (int i = 0; i < 5; i++)
    {
        if (m_stars[i] == watched && event->type() == QEvent::HoverEnter)
        {
            // LOG_DEBUG << i << "," <<event;
            for (int j = 0; j < 5; j++)
            {
                if (j > i)
                {
                    m_stars[j]->setEmptyStar();
                    continue;
                }

                m_stars[j]->setSolidStar();
            }
            m_nNum = i;
            break;
        }
    }

    return QWidget::eventFilter(watched, event);
}

void FluRatingControl::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluRatingControl::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluRatingControl.qss", this, FluThemeUtils::getUtils()->getTheme());
}
