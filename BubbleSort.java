public class BubbleSort {
    BubbleSort(int[] arr)
    {
        for(int i=0;i<5;i++)
        {
            System.out.println(arr[i]);
        }
    }
    public static void main(String[] args) {
        int arr[] = new int[] {2,3,4,5,6};
        boolean swapped ;
        for(int i=0;i<5;i++)
        {
            swapped = false;
            for(int j=0;j<5-i-1;j++)
            {
                if(arr[j] > arr[j+1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                    swapped = true;
                }
            }
            if(!swapped)
            break;
        }
        BubbleSort bs = new BubbleSort(arr);

    }
}
