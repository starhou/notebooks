## 二分查找实现细节汇总——starhou



> 本文目的：参考多篇文章，在此汇总，希望将各个流派说透，并且总结出规律，深入理解二分，而不仅仅是背模板，记套路。

### 参考各位大佬的文章，如下

[我作了首诗，保你闭着眼睛也能写对二分查找](https://mp.weixin.qq.com/s?__biz=MzAxODQxMDM0Mw==&mid=2247485044&idx=1&sn=e6b95782141c17abe206bfe2323a4226&scene=21)

[图解二分 | 最清晰易懂的讲解 | 一次性帮你解决二分边界问题【c++/java版本】 - 在排序数组中查找元素的第一个和最后一个位置 - 力扣（LeetCode](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/solution/tu-jie-er-fen-zui-qing-xi-yi-dong-de-jia-ddvc/)

## 正文

二分查找思路简单，实现是魔鬼。其实细细总结一下，也不全是魔鬼。作为最常用的算法之一，原理大家都懂，就是有策略的排查。其思想是，无效值远远多于目标值时，如何快速有效地找出我们的目标。我们的策略是，在数组有序的时候，每次扔掉一半的无效值。



## 二分查找的关键点

```c++
    int 二分查找(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0, r = ; 				     // 1. [l, r), [l, r]
        while () {				   		    // 2. 结束是 l > r 或者 l == r
            int mid = ;						// 3. 中间值是向上取整还是向下取整
            if (nums[mid] < target) {
                l = mid + 1;				// 4. 更新策略 是取mid + 1 还是 mid
            } else {
                r = mid;
            }
        }
        if (nums[r] == target) {
            ans[0] = r;
        } else {
            ans[0] = -1;
        }
        return ans;
```

## 基本二分查找

```c++
```

## 求左边界

[278. 第一个错误的版本 - 力扣（LeetCode） (leetcode-cn.com)](https://leetcode-cn.com/problems/first-bad-version/)

版本一

```c++
class Solution {
public:
    int firstBadVersion(int n) {
        int l = 1;
        int r = n;    	// 闭区间 [l, r]
        while(l < r){   // 结束是 l == r
            int mid = l + (r - l)/2;  // 中间值是向下取整
            if(isBadVersion(mid)){
                r = mid;			//  更新策略 左边或等于 取mid
            }else{
                l = mid + 1;
            }
        }
        if (nums[r] == target) {
            return -1;
        }
        return l;
    }
};
```

版本二

```c++
class Solution {
public:
    int firstBadVersion(int n) {
        int l = 1;
        int r = n + 1;    	// 开区间 [l, r]
        while(l < r){   // 结束是 l == r
            int mid = l + (r - l)/2;  // 中间值是向下取整
            if(isBadVersion(mid)){
                r = mid;			//  更新策略 左边或等于 取mid
            }else{
                l = mid + 1;
            }
        }
        if (l >= nums.length || nums[left] != target)
            return -1
        return r;
    }
};
```

