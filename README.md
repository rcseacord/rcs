# Reliably-checked String Library #
Buffer overflows continue to be a well-known security problem even in 2021. The term “buffer overflow” generally refers to memory accesses (reads and writes) outside the bounds of an object (typically an array). Buffer overflows can be exploited to execute arbitrary code with the permissions of a vulnerable process [Seacord 2013]. The 2020 common weakness enumeration (CWE) has “Weaknesses Improper Restriction of Operations within the Bounds of a Memory Buffer” ranked fifth on its list of top 25 most dangerous software weaknesses.

Traditionally, the C Library has contained many functions that trust the programmer to provide
output character arrays big enough to hold the result being produced. Not only do these functions
not check that the arrays are big enough, they frequently lack the information needed to perform
such checks.
The `memcpy` function is a well-known and oft-used function that copies `n` characters from the object pointed to by `s2` (the source array) into the object pointed to by `s1` (the destination array).
The following is a simple test of `memcpy`. The source string `str2` has 11 bytes and destination array `str1` has 6 bytes, including the null termination characters:

```c
bool memcpy_test(void) {
  char str1[] = "01234";  
  char str2[] = "abcdefghij";  
  
  memcpy(str1, str2, sizeof(str2));
  puts("\nstr1 after memcpy ");
  puts(str1);
  
  return true;
}
```

The gcc compiler produces no diagnostics when compiled with `gcc -Wall -Wextra` although the actual call to `memcpy` results in an 5 byte buffer overflow.

## Static Array Extents ##
Static array extents were added in C99 [ISO/IEC 9899:1999]. They are supported by gcc and clang, but not by even the 2022 preview release of Microsoft Visual Studio (go here to upvote the feature request). Along with variably modified array types, static array extents provide a mechanism of specifying the minimize size of array arguments in a way that can be statically checked at compile time. C17 [ISO/IEC 9899:2018] Section 6.7.6.2, “Array declarators” states that:

> The optional type qualifiers and the keyword static shall appear only in a declaration of a function parameter with an array type, and then only in the outermost array type 
> derivation.

Section 6.7.6.3, “Function declarators”, paragraph 6 states:

> A declaration of a parameter as “array of type” shall be adjusted to “qualified pointer to type”, where
> the type qualifiers (if any) are those specified within the [ and ] of the array type derivation. If the
> keyword static also appears within the [ and ] of the array type derivation, then for each call to
> the function, the value of the corresponding actual argument shall provide access to the first element
> of an array with at least as many elements as specified by the size expression.

In WG14 N2660 Improved Bounds Checking for Array Types by Martin Uecker argues that amending standard library function so that pointer arguments are declared as arrays with static array extents can be used instead of pointers for safe programming because compilers can use length information encoded in the type to detect errors.

In line with the C23 charter [Keaton 2020], this would make the API self documenting and allow tools to diagnose bound violations at compile-time or at runtime.
We can produce a binding for the `memcpy` function called `memcpy_rcs` that alters the signature as follows:

```c
extern inline void* memcpy_rcs(size_t n, char s1[static n], const char s2[static n]) {
  return memcpy(s1, s2, n);
}
```

The `size_t` parameter becomes the first parameter so we can use this size as part of a variably modified type in the second and third parameters.
The second parameter is the destination array and is declared as `char s1[static n]`. The keyword static appears within the `[` and `]` of the array type derivation indicating that the corresponding actual argument `n` must provide access to the first element of an array with at least as `n` elements.
The third parameter is the source array and is declare as `const char s2[static n]` because it is read and not written. The size parameter `n` applies to both the source and destination arrays because the semantics of `memcpy` guarantees that ``n bytes will be both read and written. This requires both arrays to be at least of size `n`.
