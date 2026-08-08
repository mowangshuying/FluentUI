clang-format --version
find ../controls ../examples  ../utils ../gallery -name *.h -o -name *.cpp -exec unix2dos {} \;
find ../controls ../examples  ../utils ../gallery -name *.h -o -name *.cpp|xargs clang-format -i -style=file