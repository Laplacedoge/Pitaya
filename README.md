# Pitaya :yum:
A matrix operations lib for embedded platform in C.

## Features :rocket:
- Basic matrix operations
  - 2D matrix addition, subtraction, multiplication and hadamard product.
  - 2D matrix transpose.
- Common activation functions.
  - ReLU, Leaky ReLU.

## About git​ :eyes:
- git init current dir: `git init`

- git add: `git add .`

- git commit: `git commit -m "Added some basic operations"`

- git pull: `git pull origin master`

- git push: `git push -u origin master`

## 如何完成每次的提交 :speech_balloon:

  1. 在本地修改好代码，比如我这次新增了`ReLU`函数，文件在`matrix.c`和`matrix.h`中。
  2. 接下来使用命令`git add matrix.c matrix.h`来告诉git我们修改了什么文件。
  3. 然后使用命令`git commit -m "Add new function ReLU."`来为此次修改撰写说明。
  4. 最后使用命令`git push -u origin master`将代码上传至github。
