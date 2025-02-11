## 论文
In *.tex
```
\documentclass[a4paper,11pt,UTF8]{article}
\usepackage{CTEX} #中文
\usepackage{amsfonts}
\usepackage{amssymb}
\usepackage{mathrsfs}
\usepackage[arrow,matrix]{xy}
\usepackage{amsmath,amssymb,amscd,bm,bbm,amsthm,mathrsfs}
\usepackage{amsmath,amscd}
\usepackage{amsfonts,amssymb}
\usepackage{xypic}
\usepackage{indentfirst}
\usepackage{diagbox} #表格
\usepackage{graphicx} #图片

\def\d{\textup{d}} #\d表示d的正体，用于输入微分符号

\theoremstyle{plain}
\newtheorem{thm}{定理}[section]
\newtheorem{lem}{引理}[section]
\newtheorem{prop}{命题}[section]
\newtheorem{cor}{推论}[section]

\theoremstyle{definition}
\newtheorem{defn}{定义}[section]
\newtheorem{exmp}{例子}[section]
\newtheorem*{ack}

\theoremstyle{Remark}
\newtheorem{rem}{注释}[section]

\renewcommand{\qedsymbol}{$\square$}
\renewcommand\baselinestretch{1.25}
```
```
\begin{document}
\title{论文标题}
\author{作者}
// \date{\today}
\maketitle

\begin{abstract}
...
\end{abstract}

\setcounter{section}{-1} #引言从0开始编号

\section{引言}
...
\section{正文}
...

\end{document}
```
## PPT
```
\documentclass[fontset = none]{beamer}
\usetheme{Madrid}
\useoutertheme{smoothbars}
\def\mathfamilydefault{\rmdefault}
\usepackage{fontspec}
\setmainfont{Times New Roman}

\usepackage{CTEX} 
\usepackage{amsfonts}
\usepackage{amssymb}
\usepackage{mathrsfs}
\usepackage[arrow,matrix]{xy}
\usepackage{amsmath,amssymb,amscd,bm,bbm,amsthm,mathrsfs}
\usepackage{amsmath,amscd}
\usepackage{amsfonts,amssymb}
\usepackage{xypic}
\usepackage{indentfirst}
\usepackage{diagbox} 
\usepackage{graphicx} 

\def\d{\textup{d}} #\d表示d的正体，用于输入微分符号

\theoremstyle{plain}
\newtheorem{thm}{定理}[section]
\newtheorem{lem}{引理}[section]
\newtheorem{prop}{命题}[section]
\newtheorem{cor}{推论}[section]

\theoremstyle{definition}
\newtheorem{defn}{定义}[section]
\newtheorem{exmp}{例子}[section]
\newtheorem*{ack}

\theoremstyle{Remark}
\newtheorem{rem}{注释}[section]

\renewcommand{\qedsymbol}{$\square$}
\renewcommand\baselinestretch{1.5}

\definecolor{uibblue}{HTML}{262686}
\defindcolor{uibgreen}{HTML}{006000}
```
```
\begin{document}
\begin{frame}
\title{标题}
\author{作者}
\institute{学院}
\date{\today}
\titlepage
\end{frame}

\section{第一章}
\begin{frame}{第一节}
\begin{thm}[名称]
\hspace{2em}定理.
\end{thm}
\pause
\setbeamercolor{block title}{fg = white,bg = uibgreen}
\begin{proof}
\hspace{2em}证明.
\end{proof}
\pause
\setbeamercolor{block title}{fg = white,bg = uibblue}
\begin{block}{自定义}
\hspace{2em}自定义内容.
\end{block}
\end{frame}
\end{document}
```
## 编译