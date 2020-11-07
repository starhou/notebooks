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
