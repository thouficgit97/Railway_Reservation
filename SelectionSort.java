public class SelectionSort{
    void display(int []arr)
    {
        for(int i=0;i<5;i++)
        {
            System.out.println(arr[i]);
        }
    }
    public static void main(String args[]) {
       int [] arr = new int[]{1,3,2,5,4};
       for(int i=0;i<5;i++)
       {
        int minPos = i;
        for(int j=i+1;j<5;j++)
        {
            if(arr[minPos] < arr[j])
            {
                minPos = j;
            }
        }
        int temp = arr[minPos];
        arr[minPos] = arr[i];
        arr[i] = temp;
       }
       SelectionSort sl = new SelectionSort();
    sl.display(arr);
    }
    
}