# 快速排序的多种实现

快排 
平均时间复杂度 O(NlogN)
最坏时间复杂度 O(N2)
额外空间复杂度 O(logN)

## 基础递归实现
快排核心三步曲，
1. 藏主元  
藏左(l) [右(rr)寻] 
藏右(r) [左(ll)寻]
2. 交叉移位
3. 换回主元 
右(rr)寻 [藏左(l)]
左(ll)寻 [藏右(r)]

快排五部曲：
1. 找主元
2. 藏主元
3. 交叉移位
4. 换回主元
5. 主元id为分界的递归
   [l, 主元id-1]
   [主元id+1, r]
   
```C++
    void qSort(vector<int>& nums, int l, int r)
    {
        if(l >= r) return;

        int pivotID = l + rand() % (r - l + 1);
        int pivot = nums[pivotID];
        //1. 藏主元  藏左边，最后主元指针为右指针rr 藏右边，最后主元位置是左指针ll
        swap(nums[pivotID], nums[r]);
        int ll = l, rr = r-1;

        //2. 交叉移位
        while(1)
        {
            while(ll<=rr && nums[ll]<=pivot) ++ll;// 不等关系主元指针必须取等号
            while(ll<rr && nums[rr]>=pivot) --rr;
            if(ll<rr)
            {
                swap(nums[ll], nums[rr]);
            }
            else
            {
                break;
            } 
        }
        /*3. 换回主元*/
        swap(nums[r], nums[ll]);

        qSort(nums, l, ll-1);
        qSort(nums, ll+1, r);
    } 

    void quickSort(vector<int>& nums)
    {
        int n = nums.size();
        qSort(nums, 0, n-1);
    }
```

## 另一种递归实现

```C++
    void qSort(vector<int>& nums, int l, int r)
    {
        if(l>=r) return;
        /*1.找主元*/
        int pivotID = l + rand()%(r-l+1);
        int pivot = nums[pivotID];

        /*2.藏（右）主元*/
        swap(nums[r], nums[pivotID]);

        /*3. 交叉移位*/
        int ll = l, rr = l;
        for(; rr<=r-1; ++rr)
        {
            if(nums[rr]<=pivot)
            {
               
                swap(nums[ll], nums[rr]); 
                 ++ll;
            }
        }
        /*4. 主元归位 左寻*/
        swap(nums[ll], nums[r]);

        /*5. 递归*/
        qSort(nums, l, ll-1);
        qSort(nums, ll+1, r);
    }
    // void qSort(vector<int>& nums, int l, int r)
    // {
    //     if(l>=r) return;
    //     /*1.找主元*/
    //     int pivotID = l + rand()%(r-l+1);
    //     int pivot = nums[pivotID];

    //     /*2.藏（左）主元*/
    //     swap(nums[l], nums[pivotID]);

    //     /*3. 交叉移位*/
    //     int ll = r, rr = r+1;
    //     for(; ll>l; --ll)
    //     {
    //         if(nums[ll]>=pivot)
    //         {
    //             --rr;
    //             swap(nums[ll], nums[rr]); 
    //         }
    //     }
    //     /*4. 主元归位右寻*/
    //     swap(nums[--rr], nums[l]);

    //     /*5. 递归*/
    //     qSort(nums, l, rr-1);
    //     qSort(nums, rr+1, r);
    // }
    void quickSort(vector<int>& nums)
    {
        int n = nums.size();
        qSort(nums, 0, n-1);
    }

```


## 非递归实现 栈
```C++
    void qSort(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> stk = {{0, n-1}};

        int l, r, pivotID, pivot, ll, rr;
        while(!stk.empty())
        {
            tie(l, r) = stk.back(); stk.pop_back();

            /*1. 找主元*/
            pivotID = l + rand()%(r-l+1);
            pivot = nums[pivotID];

            /*2. 藏（右）主元*/
            swap(nums[r], nums[pivotID]);

            /*3. 交叉移位*/
            for(ll = l-1, rr = l; rr<r; ++rr)
            {
                if(nums[rr]<=pivot)
                {
                    ++ll;
                    swap(nums[ll], nums[rr]);
                }
            }

            /*4. 换回主元 左寻*/
            swap(nums[r], nums[++ll]);

            /*5. 主元id分割入栈*/
            if(ll+1<r)
            {
                stk.emplace_back(make_pair(ll+1, r));
            }
            if(l<ll-1)
            {
                stk.emplace_back(make_pair(l, ll-1));
            }
        }

        return nums;
        
    }
```