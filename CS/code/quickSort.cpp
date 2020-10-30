    void qSort(vector<int>& nums, int l, int r)
    {
        if(l >= r) return;

        int pivotID = l + (r-l)/2;
        int pivot = nums[pivotID];
        
        swap(nums[pivotID], nums[r]);
        int ll = l, rr = r-1;
        while(1)
        {
            while(ll<=rr && nums[ll]<=pivot) ++ll;
            while(ll<=rr && nums[rr]>=pivot) --rr;
            if(ll<rr)
            {
                swap(nums[ll], nums[rr]);
            }
            else
            {
                break;
            } 
        }
        swap(nums[r], nums[ll]);

        qSort(nums, l, ll-1);
        qSort(nums, ll+1, r);
    } 