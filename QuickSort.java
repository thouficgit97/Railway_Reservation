public class QuickSort {
    static int func(int arr[],int low,int high)
    {
        int pivot = arr[low];
        int i = low,j = high;
        while(i < j)
        {
            while(pivot>=arr[i] && i<=high )
            {
                i++;
            }
            while(pivot<arr[j] && j>=low)
            {
                j--;
            }
            if(i<j)
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[low];
        arr[low] = arr[j];
        arr[j] = temp;
        return j;

    }
    static void quicksort (int arr[],int low,int high)
    {
        if(low < high)
        { 
        int pIndex = func(arr,low,high);
        quicksort(arr,low,pIndex-1);
        quicksort(arr,pIndex+1,high);
        }
    }
    public static void main(String[] args) {
        int arr[] = new int[]{2,3,1,4,5};

        quicksort(arr,0,4);
        for(int i=0;i<5;i++) {
            System.out.println(arr[i]);
        }
        
    }
    
}
