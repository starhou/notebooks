#  决策树
![图1](../decision_Tree.png)

## 思想
&ensp;&ensp;&ensp;如上图所示，决策树每次选取单个输入（特征），将整个数据集划分成两个子集，生成一个二叉树。然后递归地对两个子集进行划分，直到达到停止条件。

&ensp;&ensp;&ensp;停止条件选择比较多，一般是在模型的复杂度（叶子结点）和整体损失取折中的方案。

## 4个问题
1.  每个结点选哪个特征？
2.  分隔阈值的选择？
3.  分隔终止条件？
4.  每个区域的预测值（回归问题）？

## 回归树

&ensp;&ensp;&ensp;**问题**：对于N个输入样本$\{x_i,y_i\}, i = 1,2...N$，每个$x_i$包含$K$个特征，最后N个样本划分成M个子集sub，每个子集预测值为$p_m,m=1,2...M$。不妨取损失函数为均方误差，则有 **（问题 4.）**
$$
p_m = avg(y_i), \ \ y_i\epsilon sub_m 
$$
&ensp;&ensp;&ensp;取均值时，均方误差最小。目标是确定m个结点所用特征k及其阈值$thr_m$，直接根据均方误差最小化来优化，复杂度太高，无法实现。采用贪心算法，一个一个确定，每个都取最优。每一步的优化可以用下面的公式来表示，**（问题 1.，2.）**
$$cost_m = \min _{k,thr}\left[\min _{p_1} \sum_{}\left(y_{i}-p_{1}\right)^{2}+\min_{p_2}\sum_{}\left(y_{i}-p_{2}\right)^{2}\right]$$
&ensp;&ensp;&ensp;具体来说就是枚举，比如说，每个特征$k$都对当前数据集确定最优的$thr$，再取其中最大的$k$。（不太聪明的方法~）


&ensp;&ensp;&ensp;最直接的终止条件就是二叉树的叶子结点，也就是深度，本问题就是M的个数。

$$\min_{\alpha,M}C=\sum_{m}^{M}cost_m+\alpha|M|$$

&ensp;&ensp;&ensp;上式极为整体损失，其中$\alpha$为超参数，平衡模型的复杂度（叶子结点）和整体损失。**（问题 4.）**


## 分类树

&ensp;&ensp;&ensp;分类树只需更换损失函数
$$
\begin{aligned}
&\text { Misclassification error: } \quad \frac{1}{N_{m}} \sum_{i \in R_{m}} I\left(y_{i} \neq k(m)\right)=1-\hat{p}_{m k(m)}\\
&\text { Gini index: } \quad \sum_{k \neq k^{\prime}} \hat{p}_{m k} \hat{p}_{m k^{\prime}}=\sum_{k=1}^{K} \hat{p}_{m k}\left(1-\hat{p}_{m k}\right)\\
&\text { Cross-entropy or deviance: }-\sum_{k=1}^{K} \hat{p}_{m k} \log \hat{p}_{m k}
\end{aligned}
$$

&ensp;&ensp;&ensp;一般地，Gini指数和交叉熵对分类更敏感，用于cost,在剪枝时候，一般用分类误差。
