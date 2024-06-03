#include<stdio.h>
// using namespace std;
int i = 10;
void f(void)
{
    int i = 5;
    i = 7;
}
void g()
{
    i = 9;
}
int main()
{
    i = 1;
    g();
    f();
    printf("%d",i);
    return 0;
   
} 
