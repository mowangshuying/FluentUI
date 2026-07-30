#include "FluMediaPage.h"

FluMediaPage::FluMediaPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Media"));

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/AnimatedVisualPlayer.png")), tr("AnimatedVisualPlayer"), tr("An element to render and control playback of motion graphics."), "AnimatedVisualPlayerPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/CaptureElement.png")), tr("Capture Element / Camera Perview"), tr("A sample for doing a camera preview."), "CaptureElementAndCameraPerviewPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Image.png")), tr("Image"), tr("A control to display image content."), "ImagePage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/MapControl.png")), tr("MapControl"), tr("Display a symbolic map of the Earth."), "MapControlPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/MediaPlayerElement.png")), tr("MediaPlayerElement"), tr("A control to display video and image content."), "MediaPlayerElementPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/PersonPicture.png")), tr("PersonPicture"), tr("Displays the picture of a person/contact."), "PersonPicturePage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Sound.png")), tr("Sound"), tr("A code-behind only API that enables 2D and 3D UI sounds on all XAML controls."), "SoundPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/WebView.png")), tr("WebView2"), tr("A Microsoft Edge(Chrominum) based control that hosts HTML content in an app."), "WebView2Page");

    onThemeChanged();
}

void FluMediaPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluMediaPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
