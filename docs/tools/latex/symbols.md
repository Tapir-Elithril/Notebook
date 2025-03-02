## 常用符号
```
$a+b=c$ //行内公式
$$a+b=c$$ //行间公式
```
### 数学符号
#### 四则运算
```
+,-,\times,\div,\cdot,\pm,\mp,=,\approx //加减乘除、点乘、加减、减加、等于、约等于
```
#### 大小比较
```
\le,\ge,\ll,\gg,\ne,\equiv //小于等于、大于等于、远小于、远大于、不等于、恒等于
```
#### 上下标
```
x_2,x^2,C_n^m,a_{ij},f^{(n)} //下标与上标
```
#### 分数
```
\frac{分子}{分母}
\displaystyle\frac{}{} //行内公式手动放大
\frac{c}{displaystyle\frac{a}{b}} //行间子分数手动放大
```
#### 极限 级数
```
\sqrt{a},\sqrt{n}{a}
\lim\limits_{x \rightarrow 0}x //极限
\sum\limits_{i=1}^na_i //求和
\prod\limits_{i=1}^nb_i //连乘
\bigoplus\limits_{i=1}^nV_i //直和
\bigotimes\limits_{i=1}^nW_i //张量积
\lim\limits_{\substack{x \rightarrow 0 \\ y \rightarrow 0}}xy //多重下标
```
#### 集合
```
\in,\subset,\subseteq,\supset,\supseteq,\cap,\cup,\emptyset,\varnothing
//属于，包含于，真包含于，包含，真包含，交，并，空集，空集(格式不同)
\not\in,\not\subset //不属于，不包含于
```
#### 整除
```
\mid,\not\mid,\nmid //整除，不整除，不整除(格式不同)
```
#### 字母符号
```
\mathbb{R} //空心符号

\mathcal{A},\mathscr{I},\mathfrak{g} //花写符号
```
#### 离散数学
```
\forall,\exists //任意，存在

\wedge,\vee //逻辑与，逻辑或
```
#### 希腊字母
```
\alpha,\beta,\gamma,\delta,\epsilon,\varepsilon(格式不同),\eta,\theta,\lambda,
\mu,\pi,\rho,\sigma,\tau,\phi,\varphi,\psi,\omega,\xi,\zeta
\Gamma,\Delta,\Pi,\Sigma,\Phi,\Psi,\Omega
```
#### 无穷
```
\infty,\aleph //无穷大，阿列夫
```
#### 初等函数
```
\sin,\cos,\tan,\cot,\log,\lg,\ln
```
#### 微积分
```
\d x //微分
\int_a^bf(x)\d x //积分
\frac{\partial y}{partial x} //偏微分
\iint_D f(x,y) \d x \d y //二重积分
\oint_DP\d x + Q\d y //曲线积分
\nabla //梯度
```
#### 上划线
```
\overline{AB},\widetilde{AB},\widehat{AB},\overrightarrow{AB}
//上划线，上波浪线，上尖号，矢量
```
#### 特殊符号
```
\backslash,\left\{a\right\} //反斜杠，大括号
```
#### 括号
```
(a),[a],\left(\frac{1}{2},1\right),\left(\frac{1}{2},1\right] //区间与单侧括号
```
#### 方程组
```
{l}:左对齐一列

\left\{\begin{array}}{l}
x+y=1,\\
x-y=1.\\
\end{array}\right.
```
#### 矩阵
```
*{n}{X}:重复X格式n次，c:centre居中对齐

A=\left( {\begin{array}{*{20}{c}}
{a_{11}} & {a_{12}} & {\cdots} & {a_{1n}} \\
{a_{21}} & {a_{22}} & {\cdots} & {a_{2n}} \\
{\vdots} & {\vdots} & {} & {\vdots} \\
{a_{n1}} & {a_{n2}} & {\cdots} & {a_{nn}} \\
\end{array}}    
    \right)
```
#### 相似全等
```
\sim,\cong //相似，全等
```
#### 箭头与关系
```
\rightarrow,\Rightarrow,\rightrightarrows,\Leftrightarrow,\iff,\mapsto
//右箭头，推出，双右箭头，等价，等价(不同格式)，映射箭头
```
#### 几何
```
\circ,\triangle,\odot,\bot,\parallel //度，三角，圆，垂直，平行
```
## 排版符号
```
//利用数组实现对齐
\begin{array}{*{20}{c}}
{f:} & {A \rightarrow B} \\
{} & {a \mapsto f(a)} \\
\end{array}

//换行公式对齐
{lll}:三列分别左对齐

\begin{displaymath}
    \begin{array}{lll}
&&a+a+a+a+a+a+a+a\\
&=&a+a+a+a+a+a+a+a.
    \end{array}
\end{displaymath}

//(第一列)&(第二列)&(第三列)：表示第一行的前两列为空，第三列才开始填充内容
//&=：表示 = 处于第二列，右侧的表达式在第三列

//行间距
\renewcommand*{\arraystretch}{1.5} //1.5倍行距
\begin{displaymath}
    \begin{array}{lll}
...
    \end{array}
\end{displaymath}
\renewcommand*{\arraystretch}{1} //调整回默认行距

//文字
\text{定理：}公式

//项目编号
自动标号1.2.3.
\begin{enumerate}
 \item 一;
 \item 二;
 \item 三.
\end{enumerate}
小括号标号(1)(2)(3)
\begin{enumerate}
 \item[(1)] 首先;
 \item[(2)] 其次;
 \item[(3)] 最后.
\end{enumerate}

//表格
\begin{center} //居中
\begin{tabular}{|m{3cm}<{\centering}|m{3cm}<{\centering}|m{3cm}<{\centering}|} //3cm:列宽
\hline //换行
\textbf{第一列}&\textbf{第二列}&\textbf{第三列}\\ //加粗
\hline
& & \\
\hline
\end{tabular}
\end{center}

//插图
\begin{center}
\includegraphics[scale=0.1]{./1.png} //缩放比率
\end{center}
```
## 定理环境
```
\begin{lem}
引理.
\end{lem}

\begin{thm}[名称]
带有名字的定理.
\end{thm}
prop,cor,defn,exmp,ack同理

\begin{defn}\label{D3.2}
带有标签的定义.
\end{defn}

\begin{defn}
定义\ref{D3.2}中我们提到
\end{defn}
```
## 参考文献
```
\bibliographystyle{elsarticle-num-names}

\begin{thebibliography}{60}
  \bibitem{1}作者，\emph{题目}，期刊，\textbf{卷号}(年份)，页码.
\end{thebibliography}
//bibitem:标识符(使用cite可以引用，方法同label) emph:斜体 textbf:加粗
```