#include "FluIntructionsDemo.h"

FluIntructionsDemo::FluIntructionsDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto instructions = new FluIntructions(this);
    instructions->setFixedWidth(400);
    instructions->move(200, 200);
    instructions->setTitleLabelText("Instructions on how to use Segoe Fluent Icons");
    instructions->addTitleContent("How to get the font", "On Windows 11: There's nothing you need to do, the font comes with Windows.\n On Windows 10: Segoe Fluent Icons is not included by default on Windows 10. You can download it here.");

    instructions->addVSplitLine();

    instructions->addTitleContent(
        "How to use the font",
        "If you don't specify a FontFamily, or you specify a FontFamily that is not available on the system at runtime, the FontIcon falls back to the default font family defined by the SymbolThemeFontFamily resource.\n"
        "An icon with a 16-epx font size is the equivalent of a 16x16-epx icon, to make sizing and positioning more predictable. For optimal appearance, use these specific sizes: 16, 20, 24, 32, 40, 48, and 64. Deviating from these font "
        "sizes could lead to less crisp or blurry outcomes.\n"
        "All glyphs in Segoe Fluent Icons have the same fixed width with a consistent height and left origin point, so layering and colorization effects can be achieved by drawing glyphs directly on top of each other.");
}
