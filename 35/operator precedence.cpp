#include <stdio.h>
int main() {
   int a = 25;
   int b = 9;
   int c = 14;
   int d = 6;
   int e;
   e = (a + b) * c / d;      
   printf("Value of (a + b) * c / d is : %d\n",  e );
   e = ((a + b) * c) / d;    
   printf("Value of ((a + b) * c) / d is  : %d\n" ,  e );
   e = (a + b) * (c / d);   
   printf("Value of (a + b) * (c / d) is  : %d\n",  e );
   e = a + (b * c) / d;     
   printf("Value of a + (b * c) / d is  : %d\n" ,  e );
   return 0;
}
