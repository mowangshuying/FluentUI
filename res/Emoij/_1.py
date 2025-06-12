# 打印当前目录下所有文件名不要后缀名， 按文件名排序生序
import os

for file in sorted(os.listdir('.'),  reverse=False):
    if os.path.isfile(file):
        # print(os.path.splitext(file)[0])
        # 输出到文件中 utf-8

        with open('./out/file.txt', 'a', encoding='utf-8') as f:
            f.write(os.path.splitext(file)[0] + ',\n')