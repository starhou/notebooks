# 记录一下lambda特殊用法
用到该用法的力扣题目，[字母异位词分组](https://leetcode-cn.com/problems/group-anagrams/solution/zi-mu-yi-wei-ci-fen-zu-by-leetcode-solut-gyoc/)



[参考地址](https://zh.cppreference.com/w/cpp/language/lambda)


带有初始化器的捕获符，其行为如同它声明并显示捕获一个以类型 auto 声明的变量，该变量的声明区是 lambda 表达式体（即它不在其初始化器的作用域中），但：

若以复制捕获，则闭包对象的非静态数据成员是指代这个 auto 变量的另一种方式。
若以引用捕获，则引用变量的生存期在闭包对象的生存期结束时结束。
这可用于以如 x = std::move(x) 这样的捕获符捕获仅可移动的类型。

这亦使得以 const 引用进行捕获称为可能，比如以 &cr = std::as_const(x) 或类似的方式。

```C++
#include<stdio.h>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
	/* code */
	int  x = 4;
	auto y = [x = x + 6, &r = x, a = x -10]()->int
	    {
	    	printf("r=%d,x=%d,a=%d\n", r, x, a);
	        r += 5;
	        printf("r=%d,x=%d,a=%d\n", r, x, a);
	        return x * x;
	    }();

	printf("x=%d\n", x);
	printf("y=%d\n", y);

	return 0;
}

/*结果
r=4,x=10,a=-6
r=9,x=10,a=-6
x=9    注意到x的值发生了改变，说明在lambda中，r即为x,x即为r
y=100
*/
```

* 捕获列表中语句可以认为同时执行
* 捕获列表中变量&形式可修改，值的形式为const,不可修改