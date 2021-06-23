// Reliably Checked Strings
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "string_rcs.h"

extern inline void* memcpy_rcs(size_t n, char s1[restrict static n], const char s2[restrict static n]);
extern inline void *memccpy_rcs(size_t n, char s1[restrict static n], const char s2[restrict static n], int c);
extern inline char *strcpy_rcs(char s1[restrict static 1], const char s2[restrict static 1]);
extern inline char *strncpy_rcs(size_t n, char s1[restrict static n], const char s2[restrict static 1]);
extern inline char *strcat_rcs(char s1[restrict static 1], const char s2[restrict static 1]);
extern inline char *strncat_rcs(size_t n, char s1[restrict static n], const char s2[restrict static 1]);
extern inline size_t strxfrm_rcs(size_t n, char s1[restrict static n], const char s2[restrict static 1]);

char *char_array_copy(size_t n, const char *s1) {
  if (n == 0) return NULL;
  char *p = (char *)malloc(n);
  if (p == NULL) return NULL; 
  for (size_t i = 0; i < n; ++i) p[i] = *s1++;
  return p;
}

bool char_array_copy_test(void) {
  char arr[] = { '0', '1', '2', '3', '4' };  
  
  char *p = char_array_copy(sizeof(arr), arr);
  puts("\narr after char_array_copy");
  for (size_t i = 0; i < sizeof(arr); ++i) fputc(p[i], stdout);
  
  return true;
}

bool char_array_copy_test002(void) {
  char arr[] = { '0', '1', '2', '3', '4' };  
  
  char *p = char_array_copy(sizeof(arr)+4, arr);
  puts("\narr after char_array_copy");
  for (size_t i = 0; i < sizeof(arr); ++i) fputc(p[i], stdout);
  
  return true;
}

char *char_array_copy_rcs(size_t n, const char s1[static n]) {
  if (n == 0) return NULL;
  char *p = (char *)malloc(n);
  if (p == NULL) return NULL; 
  for (size_t i = 0; i < n; ++i) p[i] = *s1++;
  return p;
}

bool char_array_copy_rcs_test(void) {
  char arr[] = { '0', '1', '2', '3', '4' };  
  
  char *p = char_array_copy_rcs(sizeof(arr), arr);
  puts("\narr after char_array_copy");
  for (size_t i = 0; i < sizeof(arr); ++i) fputc(p[i], stdout);
  
  return true;
}

bool char_array_copy_rcs_test002(void) {
  char arr[] = { '0', '1', '2', '3', '4' };  
  
  char *p = char_array_copy_rcs(sizeof(arr)+4, arr);
  puts("\narr after char_array_copy");
  for (size_t i = 0; i < sizeof(arr); ++i) fputc(p[i], stdout);
  
  return true;
}

bool memcpy_test(void) {
  char str1[] = "01234";  
  char str2[] = "abcdefghij";  
  
  memcpy(str1, str2, sizeof(str2));
  puts("\nstr1 after memcpy ");
  puts(str1);
  
  return true;
}

bool memcpy_test002(void) {
  char str1[] = "01234";  
  char str2[] = "abcdefghij";  
  
  memcpy(str1, str2, sizeof(str2)+1); // warns -Warray-bounds
  puts("\nstr1 after memcpy 002");
  puts(str1);
  
  return true;
}

// null pointers
bool memcpy_test003(void) {
/*
  char str1[] = "hello";  
  char str2[] = "world"; 
  
  memcpy(NULL, NULL, sizeof(str2)); 
  puts("\nstr1 after memcpy 003");
  puts(str1);
    */
  return true;
}

// dynamic memory
bool memcpy_test004(void) {
  char *str1 = malloc(6);
  char str2[] = "world"; 
  
  memcpy(str1, str2, sizeof(str2)); 
  puts("\nstr1 after memcpy 004");
  puts(str1);
    
  return true;
}

// destination too small
bool memcpy_test005(void) {
  char str1[] = "hi"; 
  char str2[] = "world"; 
  
  memcpy(str1, str2, sizeof(str2));  // warns -Warray-bounds
  puts("\nstr1 after memcpy 005");
  puts(str1);
    
  return true;
}

bool memcpy_rcs_test(void) {
  char str1[] = "01234";  
  char str2[] = "abcdefghij";  
  
  memcpy_rcs(sizeof(str2), str1, str2); 
  puts("\nstr1 after memcpy_rcs");
  puts(str1);
    
  return true;
}

// destination size too large
bool memcpy_rcs_test002(void) {
  char str1[] = "01234";  
  char str2[] = "abcdefghij";  
  
  memcpy_rcs(sizeof(str2)+1, str1, str2); // warns -Warray-bounds
  puts("\nstr1 after memcpy_rcs");
  puts(str1);
    
  return true;
}

// null pointers

bool memcpy_rcs_test003(void) {
	/*
  char str1[] = "hello";  
  char str2[] = "world"; 
  
  memcpy_rcs(sizeof(str1), NULL, NULL); 
  puts("\nstr1 after memcpy_rcs");
  puts(str1);
 */   
  return true;
}


// dynamic memory
bool memcpy_rcs_test004(void) {
  char *str1 = malloc(6);
  char str2[] = "world"; 
  
  memcpy_rcs(sizeof(str2), str1, str2); 
  puts("\nstr1 after memcpy_rcs");
  puts(str1);
    
  return true;
}

// destination too small
bool memcpy_rcs_test005(void) {
  char str1[] = "hi"; 
  char str2[] = "world"; 
  
  memcpy_rcs(sizeof(str2), str1, str2);  // warns -Warray-bounds
  puts("\nstr1 after memcpy_rcs");
  puts(str1);
    
  return true;
}

bool memccpy_test(void) {
  char str1[] = "0123456789";  
  char str2[] = "abcdefghij"; 
  
  /* memcpy - Copies contents of str2 to str1 */
  memccpy(str1, str2, 'f', sizeof(str2));
  puts("\nstr1 after memccpy ");
  puts(str1);
    
  return true;
}

bool memccpy_rcs_test(void) {
  char str1[] = "0123456789";  
  char str2[] = "abcdefghij"; 
  
  memccpy_rcs(sizeof(str2), str1, str2, 'f');
  puts("\nstr1 after memccpy_rcs");
  puts(str1);
    
  return true;
}

bool strcpy_test(void) {
  char str1[] = "hello";  
  char str2[] = "world";  
  
  strcpy(str1, str2);
  puts("\nstr1 after strcpy");
  puts(str1);
  
  return true;
}

bool strcpy_rcs_test(void) {
  char str1[] = "hello";  
  char str2[] = "world";  
  
  strcpy_rcs(str1, str2);
  puts("\nstr1 after strcpy_rcs");
  puts(str1);
  
  return true;
}

bool strcpy_rcs_test002(void) {
  strcpy_rcs(NULL, NULL);
  puts("\nstr1 after strcpy_rcs 002");
  
  return true;
}

bool strncpy_test(void) {
  char str1[] = "hello";  
  char str2[] = "world";  
  
  strncpy(str1, str2, sizeof(str2)-1); // warns -Wstringop-truncation]
  puts("\nstr1 after strncpy");
  puts(str1);
  
  return true;
}

bool strncpy_rcs_test(void) {
  char str1[] = "hello";  
  char str2[] = "world";  
  
  strncpy_rcs(sizeof(str1)-1, str1, str2); // warns -Wstringop-truncation]
  puts("\nstr1 after strncpy_rcs");
  puts(str1);
  
  return true;
}

bool strncpy_rcs_test002(void) {
  char str1[] = "hello";  
  char str2[] = "world";  
  
  strncpy_rcs(sizeof(str1), str1, str2);
  puts("\nstr1 after strncpy_rcs 002");
  puts(str1);
  
  return true;
}

bool strxfrm_test(void) {
  char str1[] = "hello";  
  char str2[] = "world"; 
  
  size_t size = strxfrm(str1, str2, sizeof(str1));
  puts("\nstr1 after strxfrm_rcs");
  printf("size = %lu, str1 = %s.\n", size, str1);
    
  return true;
}

// destination size too large
bool strxfrm_test002(void) {
  char str1[] = "hello";  
  char str2[] = "world"; 
  
  size_t size = strxfrm(str1, str2, sizeof(str1)+1);
  puts("\nstr1 after strxfrm_rcs");
  printf("size = %lu, str1 = %s.\n", size, str1);
    
  return true;
}

bool strxfrm_rcs_test(void) {
  char str1[] = "hello";  
  const char str2[] = "world";  
  
  size_t size = strxfrm_rcs(sizeof(str1), str1, str2);
  puts("\nstr1 after strxfrm_rcs");
  printf("size = %lu, str1 = %s.\n", size, str1);
  
  return true;
}

// destination size too large
bool strxfrm_rcs_test002(void) {
  char str1[] = "hello";  
  char str2[] = "world"; 
  
  size_t size = strxfrm_rcs(sizeof(str1)+1, str1, str2);
  puts("\nstr1 after strxfrm_rcs");
  printf("size = %lu, str1 = %s.\n", size, str1);
    
  return true;
}

int main(void) {
  if (!char_array_copy_test()) puts("char_array_copy test failed");
  if (!char_array_copy_test002()) puts("char_array_copy test failed");
  if (!memcpy_test002()) puts("memcpy 002 failed");
  if (!memcpy_test()) puts("memcpy test failed");
  
  if (!strxfrm_test()) puts("strxfrm test failed");
  if (!strxfrm_test002()) puts("strxfrm test 002 failed");
  if (!strxfrm_rcs_test()) puts("strxfrm_rcs test failed");
  if (!strxfrm_rcs_test002()) puts("strxfrm_rcs test 002 failed");

  if (!memcpy_rcs_test()) puts("memcpy_rcs failed");
  if (!memcpy_rcs_test002()) puts("memcpy_rcs 002 failed");
  if (!memcpy_rcs_test003()) puts("memcpy_rcs 003 failed");
  if (!memcpy_rcs_test004()) puts("memcpy_rcs 004 failed");
  if (!memcpy_rcs_test005()) puts("memcpy_rcs 005 failed");
  
  if (!memccpy_test()) puts("memccpy failed");
  if (!memccpy_rcs_test()) puts("memccpy_rcs failed");
  
  if (!strcpy_test()) puts("strcpy test failed");
  if (!strcpy_rcs_test()) puts("strcpy_rcs failed");
  if (!strcpy_rcs_test002()) puts("strcpy_rcs002 failed");
  
  if (!strncpy_test()) puts("strncpy test failed");
  if (!strncpy_rcs_test()) puts("strncpy_rcs failed");
  if (!strncpy_rcs_test002()) puts("strncpy_rcs002 failed");
  
  return EXIT_SUCCESS;
}
