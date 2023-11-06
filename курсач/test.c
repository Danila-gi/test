#include <stdio.h> 
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
int main ()
{
   setlocale(LC_CTYPE, "");
   wchar_t str[200];
   wchar_t sep[4] = L" -,";
   fgetws(str, 200, stdin);
   wchar_t *istr;
   istr = wcstok(str, sep);

   while (istr != NULL)
   {
      wprintf(L"%s\n",istr);
      istr = wcstok(NULL, sep);
   }

   return 0;
}