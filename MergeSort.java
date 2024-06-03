public class MergeSort {
    static void mergeSort(int arr[],int left,int mid,int right)
    {
        int temp[] = new int[5];
        int center = mid+1;
        int t = 0;
        int start = left;
        while(start<=mid && center<=right)
        {
            
            if(arr[start] <= arr[center])
            {
             temp[t] = arr[start];  
            start++;
            t++;
            }
            else
            {
                temp[t] = arr[center];
                center++;
                t++;
            }
        } 
        while (start<=mid) {
            temp[t] = arr[start];
            start++;
            t++;
        }
        while(center<=right){
            temp[t] =arr[center];
            center++;
            t++;
        }
        for(int i=left;i<=right;i++)
        {
            arr[i] = temp[i-left];
        }
    }
    static void merge(int []arr,int low,int high)
    {
        if(low >= high)
        return;
        int mid=((low+high)/2);
        merge(arr, low, mid);
        merge(arr, mid+1, high);
        mergeSort(arr,low,mid,high);
    }
    
    public static void main(String[] args) {
        int arr[] = new int[]{5,4,3,2,11};
        merge(arr,0,4);
        for(int i=0;i<5;i++)
        {
            System.out.println(arr[i]);
        }
    }
}
