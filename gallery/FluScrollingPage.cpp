#include "FluScrollingPage.h"

FluScrollingPage::FluScrollingPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Scrolling"));

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/AnnotatedScrollBar.png")), tr("AnnotatedScrollBar"), tr("A control that extends a regular vertical scrollbar's functionality for an easy navigation through large collections."), "AnnotatedScrollBarPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/PipsPager.png")), tr("PipsPager"), tr("A control to let the user navigate through a paginated collection when the page numbers do not need to be visually known."), "PipsPagerPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ScrollView.png")), tr("ScrollView"), tr("A container control that lets the user pan and zoom its content."), "ScrollViewPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ScrollViewer.png")), tr("ScrollViewer"), tr("A container control that lets the user pan and zoom its content."), "ScrollViewerPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/SemanticZoom.png")), tr("SemanticZoom"), tr("Lets the user zoom between two different views of a collection, making it easier to navigate through large collections of items.."), "SemanticZoomPage");
    onThemeChanged();
}
