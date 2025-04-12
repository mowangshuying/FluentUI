#include "FluScrollingPage.h"

FluScrollingPage::FluScrollingPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("Scrolling");

    auto annotatedScrollBarCard =
        new FluHCard(QPixmap(FLURC("res/ControlImages/AnnotatedScrollBar.png")), tr("AnnotatedScrollBar"), tr("A control that extends a regular vertical scrollbar's functionality for an easy navigation through large collections."));
    annotatedScrollBarCard->setKey("AnnotatedScrollBarPage");
    getFWScrollView()->getMainLayout()->addWidget(annotatedScrollBarCard);
    connect(annotatedScrollBarCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto pipsPagerCard = new FluHCard(QPixmap(FLURC("res/ControlImages/PipsPager.png")), tr("PipsPager"), tr("A control to let the user navigate through a paginated collection when the page numbers do not need to be visually known."));
    pipsPagerCard->setKey("PipsPagerPage");
    getFWScrollView()->getMainLayout()->addWidget(pipsPagerCard);
    connect(pipsPagerCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto scrollViewCard = new FluHCard(QPixmap(FLURC("res/ControlImages/ScrollView.png")), tr("ScrollView"), tr("A container control that lets the user pan and zoom its content."));
    scrollViewCard->setKey("ScrollViewPage");
    getFWScrollView()->getMainLayout()->addWidget(scrollViewCard);
    connect(scrollViewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto scrollViewerCard = new FluHCard(QPixmap(FLURC("res/ControlImages/ScrollViewer.png")), tr("ScrollViewer"), tr("A container control that lets the user pan and zoom its content."));
    scrollViewerCard->setKey("ScrollViewerPage");
    getFWScrollView()->getMainLayout()->addWidget(scrollViewerCard);
    connect(scrollViewerCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto semanticZoomCard = new FluHCard(QPixmap(FLURC("res/ControlImages/SemanticZoom.png")), tr("SemanticZoom"), tr("Lets the user zoom between two different views of a collection, making it easier to navigate through large collections of items.."));
    semanticZoomCard->setKey("SemanticZoomPage");
    getFWScrollView()->getMainLayout()->addWidget(semanticZoomCard);
    connect(semanticZoomCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });
}
