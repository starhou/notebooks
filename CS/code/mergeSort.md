# 归并排序的多种解法

归并排序

平均时间复杂度 O(NlogN)
最坏时间复杂度 O(NlogN)
额外空间复杂度 O(N)

## merge三部曲

归并排序中最核心的操作是合并两个有序数组。

1. 保存区间个数
2. 择优分配
3. 个数递减拷回来

## 递归实现
```C++
void merge(vector<int>& pre, vector<int>& tmp, int l, int mid, int re)
{
     int le = mid, r = mid;
     int k = l; 
     /*1. 保存区间个数*/
     int num = re-l;
     
     /*2. （3 while法） 择优分配*/
     while(l<le && r<re)
     {
         if(pre[l]<pre[r])
             tmp[k++] = pre[l++];
         else
             tmp[k++] = pre[r++];
     }
     while(l<le) tmp[k++] = pre[l++];
     while(r<re) tmp[k++] = pre[r++];
    
    /*3. 个数递减拷回来*/
    --re;
    for(int i = 0; i<num; ++i,--re)
        pre[re] = tmp[re];

}
void mergeSort(vector<int>& pre, vector<int>& tmp, int l, int r)
{
    if(r-l<=1) return;
    int mid = l + (r-l)/2;
    
    mergeSort(pre, tmp, l, mid);
    mergeSort(pre, tmp, mid, r);
    merge(pre, tmp, l, mid, r);  
}
```
## 迭代实现

迭代三部曲
1. 归并结果左右来回倒 
2. 长度每次加倍
3. merge尾巴要特判

```C++
void merge(vector<int>& pre, vector<int>& tmp, int l, int mid, int re)
{
     int le = mid, r = mid;
     int num = re-l;
     int k = l; 

     while(l<le && r<re)
     {
         if(pre[l]<pre[r])
             tmp[k++] = pre[l++];
         else
             tmp[k++] = pre[r++];
     }

     while(l<le) tmp[k++] = pre[l++];
     while(r<re) tmp[k++] = pre[r++];
}

void mergePass(vector<int>& nums, vector<int>& tmp, int n, int len)
{
    int i, j;
    
    for(i = 0; i<=n-2*len; i += 2*len)
        merge(nums, tmp, i, i+len, i+2*len);

    /*3. merge尾巴要特判*/
    if(i+len<n)
        merge(nums, tmp, i, i+len, n);
    else
        for(j=i; j<n; ++j)
            tmp[j] = nums[j];
}
void mergeSort(vector<int>& nums, vector<int>& tmp)
{
    int n = nums.size();
    int len = 1;
    while(len<n)
    {
        /*1. 归并结果左右来回倒 */
        mergePass(nums, tmp, n, len);
        /*2 长度每次加倍*/
        len *= 2;
        mergePass(tmp, nums, n, len);
        len *= 2;
    }  
}
```
## 链表的归并排序 (非递归版本)

链表具有顺序访问的特点，所以比较特殊。

时间复杂度O(nlog(n)), 空间复杂度O(1)

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
typedef ListNode* nodePtr;
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        nodePtr dummy = new ListNode();
        dummy->next = head;
        int n = 0;

        /*1. 统计长度*/
        nodePtr pre = dummy;
        while(pre)
        {
            ++n;
            pre = pre->next;
        }

        /*2. 择优分配*/
        nodePtr now, left, right;
        for(int size = 1; size<n; size *= 2)
        {
            now = dummy->next;
            pre = dummy;

            while(now)
            {
                left = now;
                right = cut(left, size);
                now = cut(right, size);

                pre->next = merge(left, right);
                while(pre->next)
                {
                    pre = pre->next;
                }
            }
        }
        return dummy->next;
    }

    /*3. 断链并返回下一段的头*/
    nodePtr cut(nodePtr head, int n)
    {
        nodePtr p = head;
        while(--n && p)
        {
            p = p->next;
        }

        if(p == nullptr) return nullptr;

        auto next = p->next;
        p->next = nullptr;
        return next;
    }
    /*3. 合并两个有序链表*/
    nodePtr merge(nodePtr lhs, nodePtr rhs)
    {
        nodePtr dummy = new ListNode();
        nodePtr p = dummy;
        while(lhs && rhs)
        {
            if(lhs->val < rhs->val)
            {
                p->next = lhs;
                lhs = lhs->next;
            }else
            {
                p->next = rhs;
                rhs = rhs->next;
            }
            p = p->next;
        }
        p->next = lhs? lhs:rhs;
        return dummy->next;
    }
};
```