clang-format --version
find FluControls FluExamples FluIconTool FluUtils FluWinGallery -name *.h -o -name *.cpp -exec unix2dos {} \;
find FluControls FluExamples FluIconTool FluUtils FluWinGallery -name *.h -o -name *.cpp|xargs clang-format -i -style=file