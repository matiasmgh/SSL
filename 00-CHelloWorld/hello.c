#include <stdio.h>

int main(void) {
   FILE *f = freopen("output.txt", "w", stdout);
   printf("Hello, World!");
   fclose(f);
}