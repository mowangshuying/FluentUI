clang-format --version
find Controls FluExamples FluIconTool Utils Gallery -name *.h -o -name *.cpp -exec unix2dos {} \;
find Controls FluExamples FluIconTool Utils Gallery -name *.h -o -name *.cpp|xargs clang-format -i -style=file