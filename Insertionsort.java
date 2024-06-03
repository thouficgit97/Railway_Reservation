public class Insertionsort {
    public static void main(String[] args) {
        int arr[] = new int[]{4,5,1,3,4};
        int i=1,j;
        while(i<5)
        {
            j=i;
            while(j>0 && arr[j] > arr[j-1])
            {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
                j--;
            }
            i++;
        }
        display(arr);
    }
    static void display(int arr[])
    {
        for(int i=0;i<5;i++)
        {
            System.out.println(arr[i]);
        }
    }
}
