#include<iostream>
#include<vector>
using namespace std;
void rec(int x,vector<int> &v)
{
    if(x==0) 
    return;
    else
    v.push_back(x);
    rec(x-1,v);

}
int main()
{
    int n;
    cin>>n;
    vector<int> v;
    rec(n,v);
    for(auto it:v)
    {
        cout<<it<<endl;
    }
}