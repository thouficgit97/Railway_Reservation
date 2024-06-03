#include<iostream>
#include<cmath>
using namespace std;
long reverseBits(long n) {
    // Write your code here.
    long sum=0;
    int cnt=0;
    while(n>0)
    {
        if(n%2)
        {
            sum=sum+(pow(2,31-cnt));
        }
        n/=2;
        cnt++;
    }
    return sum;
}

int main()
{
    long n;
    cin>>n;
    cout<<reverseBits(n);
}