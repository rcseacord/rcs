#ifndef	STRING_RCS_H
#define	STRING_RCS_H
#pragma once
#include <string.h>
#include <stdio.h>

// 7.24.2.1 The memcpy function
//inline void *memcpy_rcs(size_t n, char s1[static n], const char s2[static n]) __attribute__((nonnull));
inline void* memcpy_rcs(size_t n, char s1[restrict static n], const char s2[restrict static n]) {
	return memcpy(s1, s2, n);
}

// 7.24.2.2 The memccpy function

//inline void *memccpy_rcs(size_t n, char s1[static n], const char s2[static n], unsigned char c) __attribute__((nonnull(2, 3)));
inline void *memccpy_rcs(size_t n, char s1[restrict static n], const char s2[restrict static n], int c) {
   return memccpy(s1, s2, c, n);
}

// 7.24.2.3 The memmove function
inline void *memmove_rcs(size_t n, char s1[restrict static n], const char s2[restrict static n]) {
	return memmove(s1, s2, n);
}

// 7.24.2.4 The strcpy function
// ??? size_t n doing any good here?
inline char *strcpy_rcs(char s1[restrict static 1], const char s2[restrict static 1]) {
	return strcpy(s1, s2);
}

// 7.24.2.5 The strncpy function
inline char *strncpy_rcs(size_t n, char s1[restrict static n], const char s2[restrict static 1]) {
	return strncpy(s1, s2, n);
}

// 7.24.3.1 The strcat function
inline char *strcat_rcs(char s1[restrict static 1], const char s2[restrict static 1]) {
	return strcat(s1, s2);
}

// 7.24.3.2 The strncat function
inline char *strncat_rcs(size_t n, char s1[restrict static n], const char s2[restrict static 1]) {
	return strncat(s1, s2, n);
}

// 7.24.4.1 The memcmp function
inline int memcmp_rcs(size_t n, const char s1[static n], const char s2[static n]) {
	return memcmp(s1, s2, n);
}

// 7.24.4.2 The strcmp function
inline int strcmp_rcs(const char s1[static 1], const char s2[static 1]) {
	return strcmp(s1, s2);
}

// 7.24.4.3 The strcoll function
inline int strcoll_rcs(const char s1[static 1], const char s2[static 1]) {
	return strcoll(s1, s2);
}

// 7.24.4.4 The strncmp function
inline int strncmp_rcs(size_t n, const char s1[static n], const char s2[static n]) {
	return strncmp(s1, s2, n);
}

// 7.24.4.5 The strxfrm function
// inline size_t strxfrm_rcs(size_t n, char s1[static n], const char s2[static 1]) __attribute__((nonnull));
inline size_t strxfrm_rcs(size_t n, char s1[restrict static n], const char s2[restrict static 1]) {
	return strxfrm(s1, s2, n);
}

// 7.24.5.1 The memchr function
inline void *memchr_rcs(size_t n, char s[static n], int c) {
	return memchr(s, c, n);
}

// 7.24.5.2 The strchr function
inline char *strchr_rcs(const char s[static 1], int c) {
	return strchr(s, c);
}

// 7.24.5.3 The strcspn function
inline size_t strcspn_rcs(const char s1[static 1], const char s2[static 1]) {
	return strcspn(s1, s2);
}

// 7.24.5.4 The strpbrk function
inline char *strpbrk_rcs(const char s1[static 1], const char s2[static 1]) {
	return strpbrk(s1, s2);
}

// 7.24.5.5 The strrchr function
inline char *strrchr_rcs(const char s[static 1], int c) {
	return strrchr(s, c);
}

// 7.24.5.6 The strspn function
inline size_t strspn_rcs(const char s1[static 1], const char s2[static 1]){
	return strspn(s1, s2);
}

// 7.24.5.7 The strstr function
inline char *strstr_rcs(const char s1[static 1], const char s2[static 1]) {
	return strstr(s1, s2);
}

// 7.24.5.8 The strtok function
inline char *strtok_rcs(char s1[restrict static 1], const char s2[restrict static 1]) {
	return strtok(s1, s2);
}

// 7.24.6.1 The memset function
inline void *memset_rcs(size_t n, char s[static n], int c) {
	return memset(s, c, n);
}

// 7.24.6.2 The strerror function  (signature doesn't change at all)
inline char *strerror_rcs(int errnum) {
	return strerror(errnum);
}

// 7.24.6.3 The strlen function
inline size_t strlen_rcs(const char s[static 1]) {
	return strlen(s);
}

// 7.24.6.4 The strdup function
inline char *strdup_rcs(const char s[static 1]) {
	return strdup(s);
}

// 7.24.6.5 The strndup function
inline char *strndup_rcs(const char s[static 1], size_t size) {
	return strndup(s, size);
}
#endif /* string_rcs.h  */
