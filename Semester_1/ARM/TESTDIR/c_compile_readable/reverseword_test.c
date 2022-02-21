
int reverse()
{
   char s[] = "Hello World!", r[13];
   int begin, end, count = 0;

   while (s[count] != '\0')
      count++;

   end = count - 1;

   for (begin = 0; begin < count; begin++) {
      r[begin] = s[end];
      end--;
   }

   r[begin] = '\0';

   printf("%s\n", r);
}