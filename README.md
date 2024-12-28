# Markdown2HTML

USTC CS Experiment: Markdown to HTML(USTCCSExp_Md2HTML)

---

## 实验简介

本项目是作者的 USTC 计算机程序设计 A 大作业，Markdown 转 HTML 的工具。

### 背景

静态网页使用 HTML 语言，但是 HTML 语言繁琐，不易书写。Markdown 语言是一种轻量级标记语言，易于书写，但是不适合直接用于网页展示。

因此，需要将 Markdown 转换为有效的 HTML 文档。

### 目标

写一个程序实现 Markdown 转 HTML 的功能，至少实现[GFM规范](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)中常用的 Text，Heading，List，Images，Links 这五项内容的转换，其他内容可自行选择实现。

### 使用

#### Windows 环境

将 Markdown 文件（支持多个）拖入可执行文件 `Markdown2HTML.exe`，在与 Markdown 源文件的目录下生成对应的 HTML 文件。

---

### 更新日志

#### beta v1.0

- 完成基本功能
  - Text，Heading，List，Images，Links，Code Block，Block Quote，Horizontal Rule

#### alpha v0.5.0

- 加入基本 Quote 和 List 语法支持
  - 部分支持嵌套使用，不支持形如`- - -`，`1. 2. 3.`的嵌套
- 加入简单的分割线

#### alpha v0.4.1

- 加入 Markdown 图片、链接的支持
  - 目前支持 http(s) 链接
- 加入单行 HTML 注释的支持

- 修复
    - para中不匹配的多个`_`会被替换成`<i>``<\i>`，或者说，code中的`_`会被替换成`<i>``<\i>`

#### alpha v0.4.0

- 加入基本代码块支持（未实现高亮）
- （调试）现在不会对单行`\n`进行处理
- 在cmd中显示进度，按行显示

- 功能：a0.3 + Code Block
- 修复：Text 中单个`_`被替换成`<i>`的 bug，其余同理
  - 例如，para 中，一行单个的 no_content 的`_`被替换成`<i>`

- 已知 bug: para 中不匹配的多个`_`会被替换成`<i>``<\i>`

#### alpha v0.3

- 完成基本的 Markdown 转 HTML 功能
- 功能：Heading，List，Text(bold, italic, strike, bold italic, code)

- 已知bug: 尚未正确处理 Markdown 段落，导致HTML空段落过多
  - 从某个版本开始，Markdown 空段落被直接忽略
