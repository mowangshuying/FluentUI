clang-format --version
find Controls Examples IconTool Utils Gallery -name *.h -o -name *.cpp -exec unix2dos {} \;
find Controls Examples IconTool Utils Gallery -name *.h -o -name *.cpp|xargs clang-format -i -style=file