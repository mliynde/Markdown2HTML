# USTCCSExp_Md2HTML

USTC CS Experiment: Markdown to HTML

## 实验简介

本项目是作者的USTC程设A大作业，计划实现Markdown转HTML的工具。

### 背景

静态网页使用HTML语言，但是HTML语言繁琐，不易书写。Markdown语言是一种轻量级标记语言，易于书写，但是不适合直接用于网页展示。

因此，需要将Markdown转换为有效的HTML文档。

### 目标

写一个程序实现Markdown转HTML的功能，至少实现[GFM规范](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)中常用的 Text，Heading，List，Images，Links 这五项内容的转换，其他内容可自行选择实现。

### 更新日志

#### alpha v0.4.1

- 加入markdown图片、链接的支持
- 加入单行html注释的支持

- 修复
  - para中不匹配的多个`_`会被替换成`<i>``<\i>`，或者说，code中的`_`会被替换成`<i>``<\i>`

#### alpha v0.4.0

- 加入基本代码块支持（未实现高亮）
- （调试）现在不会对单行`\n`进行处理
- 在cmd中显示进度，按行显示

- 功能：a0.3 + Code Block
- 修复：Text中单个`_`被替换成`<i>`的bug，其余同理
  - 例如，para中，一行单个的no_content的`_`被替换成`<i>`

- 已知bug: para中不匹配的多个`_`会被替换成`<i>``<\i>`（见input.md中的line 33）

#### alpha v0.3

- 完成基本的 Markdown 转 HTML 功能
- 功能：Heading，List，Text(bold, italic, strike, bold italic, code)

- 已知bug: 尚未正确处理markdown段落，导致html空段落过多
