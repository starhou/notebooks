# 随机森林

### 随机森林的思想
&ensp;&ensp;&ensp;Bagging或者说BootStrap是一种减小模型方差的方法。Bagging方法用在高方差低偏差的模型上效果最好，例如树模型。其思想是训练多个模型，最后的结果投票产生，有并行的思想在其中。

### Bagging和随机森林可以减少模型方差
&ensp;&ensp;&ensp;对B个i.i.d(identically distributed,independent)的变量, 如果每个变量的方差是$\sigma^{2}$，则Bagging后的方差为$\frac{1}{B} \sigma^{2}$。如果是i.d (identically distributed, but not necessarily independent), 相关系数是$\rho$，则方差是

$$
\rho \sigma^{2}+\frac{1-\rho}{B} \sigma^{2}
$$

随着B的增大，上式的第二项会消失，而第一项会保留，所以不同bagging trees的相关性$\rho$是这种通过平均来减小方差的方法有效性的边界。随机森林通过减小变量间相关性来改善其边界性能。具体来说，是通过随机选择变量来实现的。

### 随机森林的算法适用范围
&ensp;&ensp;&ensp;并不是所有的估计器都适用于随机森林这种缩减数据的方式。对决策树这种非线性估计器的收益最好。换句话说，bagging无法改善线性分类器的方差

### 随机森林的一些特点

* 特征重要性
随机森林和梯度提升树一样可以衡量特征重要性。
    1. 对于任意一个变量来说，其特征重要性可以通过其每次分裂时所选标准的改善程度来衡量。累加模型中所有分裂结点，可以得到最后的特征重要性。
    2. 还有一种衡量特征重要性的方式通过在out_of_bag samples上的准确率来实现。对每棵树，记录其在out_of_bag samples的判别准确率，然后对每个变量，随机打乱其值后再次再out_of_bag samples判别。记录两次准确率之差。对每棵树都如此，最后对每个变量求平均。

* 样本相似图
样本的相似度可以通过一个N*N的矩阵表示，具体表示位样本i和样本j的特征重要性。对每个树来说，任何一对观测值所在的terminate结点一样，则这两个之间的样本相似性加一。

* 不易过拟合 
当特征向量中有用的向量占比较少时，每次选很小的m的，随机森林的效果会很差。当有用的向量增加一点点的时候，随机森林可以添加大量的噪声变量。就是说，随机森林对大量的无用特征不敏感，依然可以表现良好。
一般地，如果估计器使用了过多的特征，很容易造成过拟合。但是对于随机森林来说，这个问题不明显。



### 随机森林的算法实现
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






