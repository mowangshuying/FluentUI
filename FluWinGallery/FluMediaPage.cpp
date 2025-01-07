#include "FluMediaPage.h"

FluMediaPage::FluMediaPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Media"));

    auto animatedVisualPlayerCard = new FluHCard(QPixmap("../res/ControlImages/AnimatedVisualPlayer.png"), 
        tr("AnimatedVisualPlayer"), 
        tr("An element to render and control playback of motion graphics."));
    animatedVisualPlayerCard->setKey("AnimatedVisualPlayerPage");
    getFWScrollView()->getMainLayout()->addWidget(animatedVisualPlayerCard);
    connect(animatedVisualPlayerCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto captureElementAndCameraPreviewCard = new FluHCard(QPixmap("../res/ControlImages/CaptureElement.png"), 
        tr("Capture Element / Camera Perview"), tr("A sample for doing a camera preview."));
    captureElementAndCameraPreviewCard->setKey("CaptureElementAndCameraPerviewPage");
    getFWScrollView()->getMainLayout()->addWidget(captureElementAndCameraPreviewCard);
    connect(captureElementAndCameraPreviewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto imageCard = new FluHCard(QPixmap("../res/ControlImages/Image.png"), tr("Image"), tr("A control to display image content."));
    imageCard->setKey("ImagePage");
    getFWScrollView()->getMainLayout()->addWidget(imageCard);
    connect(imageCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto mapControlCard = new FluHCard(QPixmap("../res/ControlImages/MapControl.png"), tr("MapControl"), tr("Display a symbolic map of the Earth."));
    mapControlCard->setKey("MapControlPage");
    getFWScrollView()->getMainLayout()->addWidget(mapControlCard);
    connect(mapControlCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto mediaPlayerElementCard = new FluHCard(QPixmap("../res/ControlImages/MediaPlayerElement.png"), tr("MediaPlayerElement"), tr("A control to display video and image content."));
    mediaPlayerElementCard->setKey("MediaPlayerElementPage");
    getFWScrollView()->getMainLayout()->addWidget(mediaPlayerElementCard);
    connect(mediaPlayerElementCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto personPictureCard = new FluHCard(QPixmap("../res/ControlImages/PersonPicture.png"), tr("PersonPicture"), tr("Displays the picture of a person/contact."));
    personPictureCard->setKey("PersonPicturePage");
    getFWScrollView()->getMainLayout()->addWidget(personPictureCard);
    connect(personPictureCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto soundCard = new FluHCard(QPixmap("../res/ControlImages/Sound.png"), tr("Sound"), tr("A code-behind only API that enables 2D and 3D UI sounds on all XAML controls."));
    soundCard->setKey("SoundPage");
    getFWScrollView()->getMainLayout()->addWidget(soundCard);
    connect(soundCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto webView2Card = new FluHCard(QPixmap("../res/ControlImages/WebView.png"), tr("WebView2"), tr("A Microsoft Edge(Chrominum) based control that hosts HTML content in an app."));
    webView2Card->setKey("WebView2Page");
    getFWScrollView()->getMainLayout()->addWidget(webView2Card);
    connect(webView2Card, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    onThemeChanged();
}

void FluMediaPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluMediaPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluMediaPage.qss", this);
    }
}
