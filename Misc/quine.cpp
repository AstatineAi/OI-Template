#include <iostream>
using namespace std;
int main()
{
   char ch = 34;
   string str[] = {
       "#include <iostream>",
       "using namespace std;",
       "int main()",
       "{",
       "   char ch = 34;",
       "   string str[] = {",
       "       ",
       "   };",
       "   for (int i = 0; i <= 5;i++) cout << str[i] << endl;",
       "   for (int i = 0; i <= 12; i++) cout << str[6] + ch + str[i] + ch + ',' << endl;",
       "   for (int i = 7; i <= 12; i++) cout << str[i] << endl;",
       "   return 0;",
       "}",
   };
   for (int i = 0; i <= 5;i++) cout << str[i] << endl;
   for (int i = 0; i <= 12; i++) cout << str[6] + ch + str[i] + ch + ',' << endl;
   for (int i = 7; i <= 12; i++) cout << str[i] << endl;
   return 0;
}
