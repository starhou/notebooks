# 随机森林

&ensp;&ensp;&ensp;Bagging或者说BootStrap是一种减小模型方差的方法。Bagging方法用在高方差低偏差的模型上效果最好，例如树模型。其思想是训练多个模型，最后的结果投票产生，有并行的思想在其中。

necessarily 
&ensp;&ensp;&ensp;对B个i.i.d(identically distributed,independent)的变量, 如果每个变量的方差是$\sigma^{2}$，则Bagging后的方差为$\frac{1}{B} \sigma^{2}$。如果是i.d (identically distributed, but not necessarily independent), 相关系数是\rho，怎方差是
$$
\rho \sigma^{2}+\frac{1-\rho}{B} \sigma^{2}
$$

&ensp;&ensp;&ensp;随机森林的算法过程可以表述如下
Algorithm
 Random Forest for Regression or Classification.
1. For $b=1$ to $B$ :
(a) Draw a bootstrap sample $\mathrm{Z}^{*}$ of size $N$ from the training data.
(b) Grow a random-forest tree $T_{b}$ to the bootstrapped data, by recursively repeating the following steps for each terminal node of the tree, until the minimum node size $n_{\min }$ is reached.
i. Select $m$ variables at random from the $p$ variables.
ii. Pick the best variable/split-point among the $m$.
iii. Split the node into two daughter nodes.
2. Output the ensemble of trees $\left\{T_{b}\right\}_{1}^{B}$.
To make a prediction at a new point $x$ :
Regression: $\hat{f}_{\mathrm{rf}}^{B}(x)=\frac{1}{B} \sum_{b=1}^{B} T_{b}(x)$
Classification: Let $\hat{C}_{b}(x)$ be the class prediction of the $b$ th random-forest tree. Then $\hat{C}_{\mathrm{rf}}^{B}(x)=$ majority vote $\left\{\hat{C}_{b}(x)\right\}_{1}^{B}$

当随机





