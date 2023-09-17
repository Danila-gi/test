#include <stdio.h>  // Для printf
#include <string.h> // Для strtok
int main (void)
{    
   char str [24]="test1/test2/test3/test4";
   // Набор символов, которые должны входить в искомый сегмент
   char sep [10]="/";
   // Переменная, в которую будут заноситься начальные адреса частей
   // строки str
   printf("%s\n", str);
   char *istr = strtok (str,sep);

   // Выделение последующих частей
   while (istr != NULL)
   {
      printf ("%s     %s\n", istr, str);
      istr = strtok(NULL, sep);
   }

   return 0;
}