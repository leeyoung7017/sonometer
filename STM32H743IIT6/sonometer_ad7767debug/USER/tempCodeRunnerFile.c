#include <stdio.h>

// f(int a)
// {
//     static c=0;
//     c=a+c++;
//     return(c);
// }
// char b[]="ABCD";

int main()
{
    unsigned a=0112,x;
    x=a>>3;
    printf("x=%o",x);

    // int a=2,i,k;
    // for(i=0;i<2;i++)
    // {
    //     k=f(a++);
    // }
    // printf("%d\n",k);

    // int arr[10],i,k=0;
    // for(i=0;i<10;i++)
    // {
    //     arr[i]=i;
    // }
    // for(i=1;i<4;i++)
    // {
    //     k+=arr[i]+i;
    // }
    // printf("%d\n",k);

    // char str[]="Hello";
    // char *p = str;
    // int n=10;
    // printf("%d%d%d",sizeof(str),sizeof(p),sizeof(n));

//     char b[30];
//     strcpy(&b[0],"GH");
//     strcpy(&b[1],"GH");
//     strcpy(&b[2],"GH");
//     printf("%s\n",b);
}
