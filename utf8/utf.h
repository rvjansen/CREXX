// The latest version of this library is available on GitHub;
// https://github.com/sheredom/utf8.h

// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>

#ifndef SHEREDOM_UTF8_H_INCLUDED
#define SHEREDOM_UTF8_H_INCLUDED

#if defined(_MSC_VER)
#pragma warning(push)

/* disable warning: no function prototype given: converting '()' to '(void)' */
#pragma warning(disable : 4255)

/* disable warning: '__cplusplus' is not defined as a preprocessor macro,
 * replacing with '0' for '#if/#elif' */
#pragma warning(disable : 4668)

/* disable warning: bytes padding added after construct */
#pragma warning(disable : 4820)
#endif

#include <stddef.h>
#include <stdlib.h>

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1920)
typedef __int32 utf8_int32_t;
#else
#include <stdint.h>
typedef int32_t utf8_int32_t;
#endif

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wcast-qual"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
#define utf8_nonnull
#define utf8_pure
#define utf8_restrict __restrict
#define utf8_weak static __inline
#elif defined(__clang__) || defined(__GNUC__)
#define utf8_nonnull __attribute__((nonnull))
#define utf8_pure __attribute__((pure))
#define utf8_restrict __restrict__
//#define utf8_weak __attribute__((weak))
#define utf8_weak static inline __attribute__((always_inline))
#else
#error Non clang, non gcc, non MSVC compiler found!
#endif

#ifdef __cplusplus
#define utf8_null NULL
#else
#define utf8_null 0
#endif

// Return less than 0, 0, greater than 0 if src1 < src2, src1 == src2, src1 >
// src2 respectively, case insensitive.
utf8_nonnull utf8_pure utf8_weak int utf8casecmp(const void *src1,
                                                 const void *src2);

// Append the utf8 string src onto the utf8 string dst.
utf8_nonnull utf8_weak void *utf8cat(void *utf8_restrict dst,
                                     const void *utf8_restrict src);

// Find the first match of the utf8 codepoint chr in the utf8 string src.
utf8_nonnull utf8_pure utf8_weak void *utf8chr(const void *src,
                                               utf8_int32_t chr);

// Return less than 0, 0, greater than 0 if src1 < src2,
// src1 == src2, src1 > src2 respectively.
utf8_nonnull utf8_pure utf8_weak int utf8cmp(const void *src1,
                                             const void *src2);

// Copy the utf8 string src onto the memory allocated in dst.
utf8_nonnull utf8_weak void *utf8cpy(void *utf8_restrict dst,
                                     const void *utf8_restrict src);

// Number of utf8 codepoints in the utf8 string src that consists entirely
// of utf8 codepoints not from the utf8 string reject.
utf8_nonnull utf8_pure utf8_weak size_t utf8cspn(const void *src,
                                                 const void *reject);

// Duplicate the utf8 string src by getting its size, malloc'ing a new buffer
// copying over the data, and returning that. Or 0 if malloc failed.
utf8_weak void *utf8dup(const void *src);

// Number of utf8 codepoints in the utf8 string str,
// excluding the null terminating byte.
utf8_nonnull utf8_pure utf8_weak size_t utf8len(const void *str);

// Similar to utf8len, except that only at most n bytes of src are looked.
utf8_nonnull utf8_pure utf8_weak size_t utf8nlen(const void *str, size_t n);

// Return less than 0, 0, greater than 0 if src1 < src2, src1 == src2, src1 >
// src2 respectively, case insensitive. Checking at most n bytes of each utf8
// string.
utf8_nonnull utf8_pure utf8_weak int utf8ncasecmp(const void *src1,
                                                  const void *src2, size_t n);

// Append the utf8 string src onto the utf8 string dst,
// writing at most n+1 bytes. Can produce an invalid utf8
// string if n falls partway through a utf8 codepoint.
utf8_nonnull utf8_weak void *utf8ncat(void *utf8_restrict dst,
                                      const void *utf8_restrict src, size_t n);

// Return less than 0, 0, greater than 0 if src1 < src2,
// src1 == src2, src1 > src2 respectively. Checking at most n
// bytes of each utf8 string.
utf8_nonnull utf8_pure utf8_weak int utf8ncmp(const void *src1,
                                              const void *src2, size_t n);

// Copy the utf8 string src onto the memory allocated in dst.
// Copies at most n bytes. If n falls partway through a utf8
// codepoint, or if dst doesn't have enough room for a null
// terminator, the final string will be cut short to preserve
// utf8 validity.

utf8_nonnull utf8_weak void *utf8ncpy(void *utf8_restrict dst,
                                      const void *utf8_restrict src, size_t n);

// Similar to utf8dup, except that at most n bytes of src are copied. If src is
// longer than n, only n bytes are copied and a null byte is added.
//
// Returns a new string if successful, 0 otherwise
utf8_weak void *utf8ndup(const void *src, size_t n);

// Locates the first occurrence in the utf8 string str of any byte in the
// utf8 string accept, or 0 if no match was found.
utf8_nonnull utf8_pure utf8_weak void *utf8pbrk(const void *str,
                                                const void *accept);

// Find the last match of the utf8 codepoint chr in the utf8 string src.
utf8_nonnull utf8_pure utf8_weak void *utf8rchr(const void *src, int chr);

// Number of bytes in the utf8 string str,
// including the null terminating byte.
utf8_nonnull utf8_pure utf8_weak size_t utf8size(const void *str);

// Similar to utf8size, except that the null terminating byte is excluded.
utf8_nonnull utf8_pure utf8_weak size_t utf8size_lazy(const void *str);

// Similar to utf8size, except that only at most n bytes of src are looked and
// the null terminating byte is excluded.
utf8_nonnull utf8_pure utf8_weak size_t utf8nsize_lazy(const void *str, size_t n);

// Number of utf8 codepoints in the utf8 string src that consists entirely
// of utf8 codepoints from the utf8 string accept.
utf8_nonnull utf8_pure utf8_weak size_t utf8spn(const void *src,
                                                const void *accept);

// The position of the utf8 string needle in the utf8 string haystack.
utf8_nonnull utf8_pure utf8_weak void *utf8str(const void *haystack,
                                               const void *needle);

// The position of the utf8 string needle in the utf8 string haystack, case
// insensitive.
utf8_nonnull utf8_pure utf8_weak void *utf8casestr(const void *haystack,
                                                   const void *needle);

// Return 0 on success, or the position of the invalid
// utf8 codepoint on failure.
utf8_nonnull utf8_pure utf8_weak void *utf8valid(const void *str);

// Similar to utf8valid, except that only at most n bytes of src are looked.
utf8_nonnull utf8_pure utf8_weak void *utf8nvalid(const void *str, size_t n);

// Given a null-terminated string, makes the string valid by replacing invalid
// codepoints with a 1-byte replacement. Returns 0 on success.
utf8_nonnull utf8_weak int utf8makevalid(void *str,
                                         const utf8_int32_t replacement);

// Sets out_codepoint to the current utf8 codepoint in str, and returns the
// address of the next utf8 codepoint after the current one in str.
utf8_nonnull utf8_weak void *
utf8codepoint(const void *utf8_restrict str,
              utf8_int32_t *utf8_restrict out_codepoint);

// Calculates the size of the next utf8 codepoint in str.
utf8_nonnull utf8_weak size_t utf8codepointcalcsize(const void *str);

// Calculates the size of the prev utf8 codepoint in str.
utf8_nonnull utf8_weak size_t utf8rcodepointcalcsize(const void *str);

// Returns the size of the given codepoint in bytes.
utf8_weak size_t utf8codepointsize(utf8_int32_t chr);

// Write a codepoint to the given string, and return the address to the next
// place after the written codepoint. Pass how many bytes left in the buffer to
// n. If there is not enough space for the codepoint, this function returns
// null.
utf8_nonnull utf8_weak void *utf8catcodepoint(void *str, utf8_int32_t chr,
                                              size_t n);

// Returns 1 if the given character is lowercase, or 0 if it is not.
utf8_weak int utf8islower(utf8_int32_t chr);

// Returns 1 if the given character is uppercase, or 0 if it is not.
utf8_weak int utf8isupper(utf8_int32_t chr);

// Transform the given string into all lowercase codepoints.
utf8_nonnull utf8_weak void utf8lwr(void *utf8_restrict str);

// Transform the given string into all uppercase codepoints.
utf8_nonnull utf8_weak void utf8upr(void *utf8_restrict str);

// Make a codepoint lower case if possible.
utf8_weak utf8_int32_t utf8lwrcodepoint(utf8_int32_t cp);

// Make a codepoint upper case if possible.
utf8_weak utf8_int32_t utf8uprcodepoint(utf8_int32_t cp);

// Sets out_codepoint to the current utf8 codepoint in str, and returns the
// address of the previous utf8 codepoint before the current one in str.
utf8_nonnull utf8_weak void *
utf8rcodepoint(const void *utf8_restrict str,
               utf8_int32_t *utf8_restrict out_codepoint);

// Duplicate the utf8 string src by getting its size, calling alloc_func_ptr to
// copy over data to a new buffer, and returning that. Or 0 if alloc_func_ptr
// returned null.
utf8_weak void *utf8dup_ex(const void *src,
                           void *(*alloc_func_ptr)(void *, size_t),
                           void *user_data);

// Similar to utf8dup, except that at most n bytes of src are copied. If src is
// longer than n, only n bytes are copied and a null byte is added.
//
// Returns a new string if successful, 0 otherwise.
utf8_weak void *utf8ndup_ex(const void *src, size_t n,
                            void *(*alloc_func_ptr)(void *, size_t),
                            void *user_data);

#undef utf8_weak
#undef utf8_pure
#undef utf8_nonnull

int utf8casecmp(const void *src1, const void *src2) {
    utf8_int32_t src1_lwr_cp, src2_lwr_cp, src1_upr_cp, src2_upr_cp, src1_orig_cp,
            src2_orig_cp;

    for (;;) {
        src1 = utf8codepoint(src1, &src1_orig_cp);
        src2 = utf8codepoint(src2, &src2_orig_cp);

        // lower the srcs if required
        src1_lwr_cp = utf8lwrcodepoint(src1_orig_cp);
        src2_lwr_cp = utf8lwrcodepoint(src2_orig_cp);

        // lower the srcs if required
        src1_upr_cp = utf8uprcodepoint(src1_orig_cp);
        src2_upr_cp = utf8uprcodepoint(src2_orig_cp);

        // check if the lowered codepoints match
        if ((0 == src1_orig_cp) && (0 == src2_orig_cp)) {
            return 0;
        } else if ((src1_lwr_cp == src2_lwr_cp) || (src1_upr_cp == src2_upr_cp)) {
            continue;
        }

        // if they don't match, then we return the difference between the characters
        return src1_lwr_cp - src2_lwr_cp;
    }
}

void *utf8cat(void *utf8_restrict dst, const void *utf8_restrict src) {
    char *d = (char *)dst;
    const char *s = (const char *)src;

    // find the null terminating byte in dst
    while ('\0' != *d) {
        d++;
    }

    // overwriting the null terminating byte in dst, append src byte-by-byte
    while ('\0' != *s) {
        *d++ = *s++;
    }

    // write out a new null terminating byte into dst
    *d = '\0';

    return dst;
}

void *utf8chr(const void *src, utf8_int32_t chr) {
    char c[5] = {'\0', '\0', '\0', '\0', '\0'};

    if (0 == chr) {
        // being asked to return position of null terminating byte, so
        // just run s to the end, and return!
        const char *s = (const char *)src;
        while ('\0' != *s) {
            s++;
        }
        return (void *)s;
    } else if (0 == ((utf8_int32_t)0xffffff80 & chr)) {
        // 1-byte/7-bit ascii
        // (0b0xxxxxxx)
        c[0] = (char)chr;
    } else if (0 == ((utf8_int32_t)0xfffff800 & chr)) {
        // 2-byte/11-bit utf8 code point
        // (0b110xxxxx 0b10xxxxxx)
        c[0] = 0xc0 | (char)(chr >> 6);
        c[1] = 0x80 | (char)(chr & 0x3f);
    } else if (0 == ((utf8_int32_t)0xffff0000 & chr)) {
        // 3-byte/16-bit utf8 code point
        // (0b1110xxxx 0b10xxxxxx 0b10xxxxxx)
        c[0] = 0xe0 | (char)(chr >> 12);
        c[1] = 0x80 | (char)((chr >> 6) & 0x3f);
        c[2] = 0x80 | (char)(chr & 0x3f);
    } else { // if (0 == ((int)0xffe00000 & chr)) {
        // 4-byte/21-bit utf8 code point
        // (0b11110xxx 0b10xxxxxx 0b10xxxxxx 0b10xxxxxx)
        c[0] = 0xf0 | (char)(chr >> 18);
        c[1] = 0x80 | (char)((chr >> 12) & 0x3f);
        c[2] = 0x80 | (char)((chr >> 6) & 0x3f);
        c[3] = 0x80 | (char)(chr & 0x3f);
    }

    // we've made c into a 2 utf8 codepoint string, one for the chr we are
    // seeking, another for the null terminating byte. Now use utf8str to
    // search
    return utf8str(src, c);
}

int utf8cmp(const void *src1, const void *src2) {
    const unsigned char *s1 = (const unsigned char *)src1;
    const unsigned char *s2 = (const unsigned char *)src2;

    while (('\0' != *s1) || ('\0' != *s2)) {
        if (*s1 < *s2) {
            return -1;
        } else if (*s1 > *s2) {
            return 1;
        }

        s1++;
        s2++;
    }

    // both utf8 strings matched
    return 0;
}

int utf8coll(const void *src1, const void *src2);

void *utf8cpy(void *utf8_restrict dst, const void *utf8_restrict src) {
    char *d = (char *)dst;
    const char *s = (const char *)src;

    // overwriting anything previously in dst, write byte-by-byte
    // from src
    while ('\0' != *s) {
        *d++ = *s++;
    }

    // append null terminating byte
    *d = '\0';

    return dst;
}

size_t utf8cspn(const void *src, const void *reject) {
    const char *s = (const char *)src;
    size_t chars = 0;

    while ('\0' != *s) {
        const char *r = (const char *)reject;
        size_t offset = 0;

        while ('\0' != *r) {
            // checking that if *r is the start of a utf8 codepoint
            // (it is not 0b10xxxxxx) and we have successfully matched
            // a previous character (0 < offset) - we found a match
            if ((0x80 != (0xc0 & *r)) && (0 < offset)) {
                return chars;
            } else {
                if (*r == s[offset]) {
                    // part of a utf8 codepoint matched, so move our checking
                    // onwards to the next byte
                    offset++;
                    r++;
                } else {
                    // r could be in the middle of an unmatching utf8 code point,
                    // so we need to march it on to the next character beginning,

                    do {
                        r++;
                    } while (0x80 == (0xc0 & *r));

                    // reset offset too as we found a mismatch
                    offset = 0;
                }
            }
        }

        // found a match at the end of *r, so didn't get a chance to test it
        if (0 < offset) {
            return chars;
        }

        // the current utf8 codepoint in src did not match reject, but src
        // could have been partway through a utf8 codepoint, so we need to
        // march it onto the next utf8 codepoint starting byte
        do {
            s++;
        } while ((0x80 == (0xc0 & *s)));
        chars++;
    }

    return chars;
}

void *utf8dup(const void *src) { return utf8dup_ex(src, utf8_null, utf8_null); }

void *utf8dup_ex(const void *src, void *(*alloc_func_ptr)(void *, size_t),
                 void *user_data) {
    const char *s = (const char *)src;
    char *n = utf8_null;

    // figure out how many bytes (including the terminator) we need to copy first
    size_t bytes = utf8size(src);

    if (alloc_func_ptr) {
        n = (char *)alloc_func_ptr(user_data, bytes);
    } else {
        n = (char *)malloc(bytes);
    }

    if (utf8_null == n) {
        // out of memory so we bail
        return utf8_null;
    } else {
        bytes = 0;

        // copy src byte-by-byte into our new utf8 string
        while ('\0' != s[bytes]) {
            n[bytes] = s[bytes];
            bytes++;
        }

        // append null terminating byte
        n[bytes] = '\0';
        return n;
    }
}

void *utf8fry(const void *str);

size_t utf8len(const void *str) {
    return utf8nlen(str, SIZE_MAX);
}

size_t utf8nlen(const void *str, size_t n) {
    const unsigned char *s = (const unsigned char *)str;
    const unsigned char *t = s;
    size_t length = 0;

    while ((size_t) (s-t) < n && '\0' != *s) {
        if (0xf0 == (0xf8 & *s)) {
            // 4-byte utf8 code point (began with 0b11110xxx)
            s += 4;
        } else if (0xe0 == (0xf0 & *s)) {
            // 3-byte utf8 code point (began with 0b1110xxxx)
            s += 3;
        } else if (0xc0 == (0xe0 & *s)) {
            // 2-byte utf8 code point (began with 0b110xxxxx)
            s += 2;
        } else { // if (0x00 == (0x80 & *s)) {
            // 1-byte ascii (began with 0b0xxxxxxx)
            s += 1;
        }

        // no matter the bytes we marched s forward by, it was
        // only 1 utf8 codepoint
        length++;
    }

    if ((size_t) (s-t) > n) {
        length--;
    }
    return length;
}

int utf8ncasecmp(const void *src1, const void *src2, size_t n) {
    utf8_int32_t src1_lwr_cp, src2_lwr_cp, src1_upr_cp, src2_upr_cp, src1_orig_cp,
            src2_orig_cp;

    do {
        const unsigned char *const s1 = (const unsigned char *)src1;
        const unsigned char *const s2 = (const unsigned char *)src2;

        // first check that we have enough bytes left in n to contain an entire
        // codepoint
        if (0 == n) {
            return 0;
        }

        if ((1 == n) && ((0xc0 == (0xe0 & *s1)) || (0xc0 == (0xe0 & *s2)))) {
            const utf8_int32_t c1 = (0xe0 & *s1);
            const utf8_int32_t c2 = (0xe0 & *s2);

            if (c1 < c2) {
                return c1 - c2;
            } else {
                return 0;
            }
        }

        if ((2 >= n) && ((0xe0 == (0xf0 & *s1)) || (0xe0 == (0xf0 & *s2)))) {
            const utf8_int32_t c1 = (0xf0 & *s1);
            const utf8_int32_t c2 = (0xf0 & *s2);

            if (c1 < c2) {
                return c1 - c2;
            } else {
                return 0;
            }
        }

        if ((3 >= n) && ((0xf0 == (0xf8 & *s1)) || (0xf0 == (0xf8 & *s2)))) {
            const utf8_int32_t c1 = (0xf8 & *s1);
            const utf8_int32_t c2 = (0xf8 & *s2);

            if (c1 < c2) {
                return c1 - c2;
            } else {
                return 0;
            }
        }

        src1 = utf8codepoint(src1, &src1_orig_cp);
        src2 = utf8codepoint(src2, &src2_orig_cp);
        n -= utf8codepointsize(src1_orig_cp);

        src1_lwr_cp = utf8lwrcodepoint(src1_orig_cp);
        src2_lwr_cp = utf8lwrcodepoint(src2_orig_cp);

        src1_upr_cp = utf8uprcodepoint(src1_orig_cp);
        src2_upr_cp = utf8uprcodepoint(src2_orig_cp);

        // check if the lowered codepoints match
        if ((0 == src1_orig_cp) && (0 == src2_orig_cp)) {
            return 0;
        } else if ((src1_lwr_cp == src2_lwr_cp) || (src1_upr_cp == src2_upr_cp)) {
            continue;
        }

        // if they don't match, then we return the difference between the characters
        return src1_lwr_cp - src2_lwr_cp;
    } while (0 < n);

    // both utf8 strings matched
    return 0;
}

void *utf8ncat(void *utf8_restrict dst, const void *utf8_restrict src,
               size_t n) {
    char *d = (char *)dst;
    const char *s = (const char *)src;

    // find the null terminating byte in dst
    while ('\0' != *d) {
        d++;
    }

    // overwriting the null terminating byte in dst, append src byte-by-byte
    // stopping if we run out of space
    do {
        *d++ = *s++;
    } while (('\0' != *s) && (0 != --n));

    // write out a new null terminating byte into dst
    *d = '\0';

    return dst;
}

int utf8ncmp(const void *src1, const void *src2, size_t n) {
    const unsigned char *s1 = (const unsigned char *)src1;
    const unsigned char *s2 = (const unsigned char *)src2;

    while ((0 != n--) && (('\0' != *s1) || ('\0' != *s2))) {
        if (*s1 < *s2) {
            return -1;
        } else if (*s1 > *s2) {
            return 1;
        }

        s1++;
        s2++;
    }

    // both utf8 strings matched
    return 0;
}

void *utf8ncpy(void *utf8_restrict dst, const void *utf8_restrict src,
               size_t n) {
    char *d = (char *)dst;
    const char *s = (const char *)src;
    size_t index, check_index;

    // overwriting anything previously in dst, write byte-by-byte
    // from src
    for (index = 0; index < n; index++) {
        d[index] = s[index];
        if ('\0' == s[index]) {
            break;
        }
    }

    for ( check_index = index - 1; check_index > 0 && 0x80 == (0xc0 & d[check_index]); check_index--) {
        // just moving the index
    }

    if (check_index < index && (index - check_index) < utf8codepointsize(d[check_index])) {
        index = check_index;
    }

    // append null terminating byte
    for (; index < n; index++) {
        d[index] = 0;
    }

    return dst;
}

void *utf8ndup(const void *src, size_t n) {
    return utf8ndup_ex(src, n, utf8_null, utf8_null);
}

void *utf8ndup_ex(const void *src, size_t n,
                  void *(*alloc_func_ptr)(void *, size_t), void *user_data) {
    const char *s = (const char *)src;
    char *c = utf8_null;
    size_t bytes = 0;

    // Find the end of the string or stop when n is reached
    while ('\0' != s[bytes] && bytes < n) {
        bytes++;
    }

    // In case bytes is actually less than n, we need to set it
    // to be used later in the copy byte by byte.
    n = bytes;

    if (alloc_func_ptr) {
        c = (char *)alloc_func_ptr(user_data, bytes + 1);
    } else {
        c = (char *)malloc(bytes + 1);
    }

    if (utf8_null == c) {
        // out of memory so we bail
        return utf8_null;
    }

    bytes = 0;

    // copy src byte-by-byte into our new utf8 string
    while ('\0' != s[bytes] && bytes < n) {
        c[bytes] = s[bytes];
        bytes++;
    }

    // append null terminating byte
    c[bytes] = '\0';
    return c;
}

void *utf8rchr(const void *src, int chr) {
    const char *s = (const char *)src;
    const char *match = utf8_null;
    char c[5] = {'\0', '\0', '\0', '\0', '\0'};

    if (0 == chr) {
        // being asked to return position of null terminating byte, so
        // just run s to the end, and return!
        while ('\0' != *s) {
            s++;
        }
        return (void *)s;
    } else if (0 == ((int)0xffffff80 & chr)) {
        // 1-byte/7-bit ascii
        // (0b0xxxxxxx)
        c[0] = (char)chr;
    } else if (0 == ((int)0xfffff800 & chr)) {
        // 2-byte/11-bit utf8 code point
        // (0b110xxxxx 0b10xxxxxx)
        c[0] = 0xc0 | (char)(chr >> 6);
        c[1] = 0x80 | (char)(chr & 0x3f);
    } else if (0 == ((int)0xffff0000 & chr)) {
        // 3-byte/16-bit utf8 code point
        // (0b1110xxxx 0b10xxxxxx 0b10xxxxxx)
        c[0] = 0xe0 | (char)(chr >> 12);
        c[1] = 0x80 | (char)((chr >> 6) & 0x3f);
        c[2] = 0x80 | (char)(chr & 0x3f);
    } else { // if (0 == ((int)0xffe00000 & chr)) {
        // 4-byte/21-bit utf8 code point
        // (0b11110xxx 0b10xxxxxx 0b10xxxxxx 0b10xxxxxx)
        c[0] = 0xf0 | (char)(chr >> 18);
        c[1] = 0x80 | (char)((chr >> 12) & 0x3f);
        c[2] = 0x80 | (char)((chr >> 6) & 0x3f);
        c[3] = 0x80 | (char)(chr & 0x3f);
    }

    // we've created a 2 utf8 codepoint string in c that is
    // the utf8 character asked for by chr, and a null
    // terminating byte

    while ('\0' != *s) {
        size_t offset = 0;

        while (s[offset] == c[offset]) {
            offset++;
        }

        if ('\0' == c[offset]) {
            // we found a matching utf8 code point
            match = s;
            s += offset;
        } else {
            s += offset;

            // need to march s along to next utf8 codepoint start
            // (the next byte that doesn't match 0b10xxxxxx)
            if ('\0' != *s) {
                do {
                    s++;
                } while (0x80 == (0xc0 & *s));
            }
        }
    }

    // return the last match we found (or 0 if no match was found)
    return (void *)match;
}

void *utf8pbrk(const void *str, const void *accept) {
    const char *s = (const char *)str;

    while ('\0' != *s) {
        const char *a = (const char *)accept;
        size_t offset = 0;

        while ('\0' != *a) {
            // checking that if *a is the start of a utf8 codepoint
            // (it is not 0b10xxxxxx) and we have successfully matched
            // a previous character (0 < offset) - we found a match
            if ((0x80 != (0xc0 & *a)) && (0 < offset)) {
                return (void *)s;
            } else {
                if (*a == s[offset]) {
                    // part of a utf8 codepoint matched, so move our checking
                    // onwards to the next byte
                    offset++;
                    a++;
                } else {
                    // r could be in the middle of an unmatching utf8 code point,
                    // so we need to march it on to the next character beginning,

                    do {
                        a++;
                    } while (0x80 == (0xc0 & *a));

                    // reset offset too as we found a mismatch
                    offset = 0;
                }
            }
        }

        // we found a match on the last utf8 codepoint
        if (0 < offset) {
            return (void *)s;
        }

        // the current utf8 codepoint in src did not match accept, but src
        // could have been partway through a utf8 codepoint, so we need to
        // march it onto the next utf8 codepoint starting byte
        do {
            s++;
        } while ((0x80 == (0xc0 & *s)));
    }

    return utf8_null;
}

size_t utf8size(const void *str) {
    return utf8size_lazy(str) + 1;
}

size_t utf8size_lazy(const void *str) {
    return utf8nsize_lazy(str, SIZE_MAX);
}

size_t utf8nsize_lazy(const void *str, size_t n) {
    const char *s = (const char *)str;
    size_t size = 0;
    while (size < n && '\0' != s[size]) {
        size++;
    }
    return size;
}

size_t utf8spn(const void *src, const void *accept) {
    const char *s = (const char *)src;
    size_t chars = 0;

    while ('\0' != *s) {
        const char *a = (const char *)accept;
        size_t offset = 0;

        while ('\0' != *a) {
            // checking that if *r is the start of a utf8 codepoint
            // (it is not 0b10xxxxxx) and we have successfully matched
            // a previous character (0 < offset) - we found a match
            if ((0x80 != (0xc0 & *a)) && (0 < offset)) {
                // found a match, so increment the number of utf8 codepoints
                // that have matched and stop checking whether any other utf8
                // codepoints in a match
                chars++;
                s += offset;
                offset = 0;
                break;
            } else {
                if (*a == s[offset]) {
                    offset++;
                    a++;
                } else {
                    // a could be in the middle of an unmatching utf8 codepoint,
                    // so we need to march it on to the next character beginning,
                    do {
                        a++;
                    } while (0x80 == (0xc0 & *a));

                    // reset offset too as we found a mismatch
                    offset = 0;
                }
            }
        }

        // found a match at the end of *a, so didn't get a chance to test it
        if (0 < offset) {
            chars++;
            s += offset;
            continue;
        }

        // if a got to its terminating null byte, then we didn't find a match.
        // Return the current number of matched utf8 codepoints
        if ('\0' == *a) {
            return chars;
        }
    }

    return chars;
}

void *utf8str(const void *haystack, const void *needle) {
    const char *h = (const char *)haystack;
    utf8_int32_t throwaway_codepoint;

    // if needle has no utf8 codepoints before the null terminating
    // byte then return haystack
    if ('\0' == *((const char *)needle)) {
        return (void *)haystack;
    }

    while ('\0' != *h) {
        const char *maybeMatch = h;
        const char *n = (const char *)needle;

        while (*h == *n && (*h != '\0' && *n != '\0')) {
            n++;
            h++;
        }

        if ('\0' == *n) {
            // we found the whole utf8 string for needle in haystack at
            // maybeMatch, so return it
            return (void *)maybeMatch;
        } else {
            // h could be in the middle of an unmatching utf8 codepoint,
            // so we need to march it on to the next character beginning
            // starting from the current character
            h = (const char *)utf8codepoint(maybeMatch, &throwaway_codepoint);
        }
    }

    // no match
    return utf8_null;
}

void *utf8casestr(const void *haystack, const void *needle) {
    const void *h = haystack;

    // if needle has no utf8 codepoints before the null terminating
    // byte then return haystack
    if ('\0' == *((const char *)needle)) {
        return (void *)haystack;
    }

    for (;;) {
        const void *maybeMatch = h;
        const void *n = needle;
        utf8_int32_t h_cp, n_cp;

        // Get the next code point and track it
        const void *nextH = h = utf8codepoint(h, &h_cp);
        n = utf8codepoint(n, &n_cp);

        while ((0 != h_cp) && (0 != n_cp)) {
            h_cp = utf8lwrcodepoint(h_cp);
            n_cp = utf8lwrcodepoint(n_cp);

            // if we find a mismatch, bail out!
            if (h_cp != n_cp) {
                break;
            }

            h = utf8codepoint(h, &h_cp);
            n = utf8codepoint(n, &n_cp);
        }

        if (0 == n_cp) {
            // we found the whole utf8 string for needle in haystack at
            // maybeMatch, so return it
            return (void *)maybeMatch;
        }

        if (0 == h_cp) {
            // no match
            return utf8_null;
        }

        // Roll back to the next code point in the haystack to test
        h = nextH;
    }
}

void *utf8valid(const void *str) {
    return utf8nvalid(str, SIZE_MAX);
}

void *utf8nvalid(const void *str, size_t n) {
    const char *s = (const char *)str;
    const char *t = s;
    size_t consumed, remained;

    while ((void) (consumed = (size_t) (s-t)), consumed < n && '\0' != *s) {
        remained = n - consumed;

        if (0xf0 == (0xf8 & *s)) {
            // ensure that there's 4 bytes or more remained
            if (remained < 4) {
                return (void *)s;
            }

            // ensure each of the 3 following bytes in this 4-byte
            // utf8 codepoint began with 0b10xxxxxx
            if ((0x80 != (0xc0 & s[1])) || (0x80 != (0xc0 & s[2])) ||
                (0x80 != (0xc0 & s[3]))) {
                return (void *)s;
            }

            // ensure that our utf8 codepoint ended after 4 bytes
            if (0x80 == (0xc0 & s[4])) {
                return (void *)s;
            }

            // ensure that the top 5 bits of this 4-byte utf8
            // codepoint were not 0, as then we could have used
            // one of the smaller encodings
            if ((0 == (0x07 & s[0])) && (0 == (0x30 & s[1]))) {
                return (void *)s;
            }

            // 4-byte utf8 code point (began with 0b11110xxx)
            s += 4;
        } else if (0xe0 == (0xf0 & *s)) {
            // ensure that there's 3 bytes or more remained
            if (remained < 3) {
                return (void *)s;
            }

            // ensure each of the 2 following bytes in this 3-byte
            // utf8 codepoint began with 0b10xxxxxx
            if ((0x80 != (0xc0 & s[1])) || (0x80 != (0xc0 & s[2]))) {
                return (void *)s;
            }

            // ensure that our utf8 codepoint ended after 3 bytes
            if (0x80 == (0xc0 & s[3])) {
                return (void *)s;
            }

            // ensure that the top 5 bits of this 3-byte utf8
            // codepoint were not 0, as then we could have used
            // one of the smaller encodings
            if ((0 == (0x0f & s[0])) && (0 == (0x20 & s[1]))) {
                return (void *)s;
            }

            // 3-byte utf8 code point (began with 0b1110xxxx)
            s += 3;
        } else if (0xc0 == (0xe0 & *s)) {
            // ensure that there's 2 bytes or more remained
            if (remained < 2) {
                return (void *)s;
            }

            // ensure the 1 following byte in this 2-byte
            // utf8 codepoint began with 0b10xxxxxx
            if (0x80 != (0xc0 & s[1])) {
                return (void *)s;
            }

            // ensure that our utf8 codepoint ended after 2 bytes
            if (0x80 == (0xc0 & s[2])) {
                return (void *)s;
            }

            // ensure that the top 4 bits of this 2-byte utf8
            // codepoint were not 0, as then we could have used
            // one of the smaller encodings
            if (0 == (0x1e & s[0])) {
                return (void *)s;
            }

            // 2-byte utf8 code point (began with 0b110xxxxx)
            s += 2;
        } else if (0x00 == (0x80 & *s)) {
            // 1-byte ascii (began with 0b0xxxxxxx)
            s += 1;
        } else {
            // we have an invalid 0b1xxxxxxx utf8 code point entry
            return (void *)s;
        }
    }

    return utf8_null;
}

int utf8makevalid(void *str, const utf8_int32_t replacement) {
    char *read = (char *)str;
    char *write = read;
    const char r = (char)replacement;
    utf8_int32_t codepoint;

    if (replacement > 0x7f) {
        return -1;
    }

    while ('\0' != *read) {
        if (0xf0 == (0xf8 & *read)) {
            // ensure each of the 3 following bytes in this 4-byte
            // utf8 codepoint began with 0b10xxxxxx
            if ((0x80 != (0xc0 & read[1])) || (0x80 != (0xc0 & read[2])) ||
                (0x80 != (0xc0 & read[3]))) {
                *write++ = r;
                read++;
                continue;
            }

            // 4-byte utf8 code point (began with 0b11110xxx)
            read = (char *)utf8codepoint(read, &codepoint);
            write = (char *)utf8catcodepoint(write, codepoint, 4);
        } else if (0xe0 == (0xf0 & *read)) {
            // ensure each of the 2 following bytes in this 3-byte
            // utf8 codepoint began with 0b10xxxxxx
            if ((0x80 != (0xc0 & read[1])) || (0x80 != (0xc0 & read[2]))) {
                *write++ = r;
                read++;
                continue;
            }

            // 3-byte utf8 code point (began with 0b1110xxxx)
            read = (char *)utf8codepoint(read, &codepoint);
            write = (char *)utf8catcodepoint(write, codepoint, 3);
        } else if (0xc0 == (0xe0 & *read)) {
            // ensure the 1 following byte in this 2-byte
            // utf8 codepoint began with 0b10xxxxxx
            if (0x80 != (0xc0 & read[1])) {
                *write++ = r;
                read++;
                continue;
            }

            // 2-byte utf8 code point (began with 0b110xxxxx)
            read = (char *)utf8codepoint(read, &codepoint);
            write = (char *)utf8catcodepoint(write, codepoint, 2);
        } else if (0x00 == (0x80 & *read)) {
            // 1-byte ascii (began with 0b0xxxxxxx)
            read = (char *)utf8codepoint(read, &codepoint);
            write = (char *)utf8catcodepoint(write, codepoint, 1);
        } else {
            // if we got here then we've got a dangling continuation (0b10xxxxxx)
            *write++ = r;
            read++;
            continue;
        }
    }

    *write = '\0';

    return 0;
}

void *utf8codepoint(const void *utf8_restrict str,
                    utf8_int32_t *utf8_restrict out_codepoint) {
    const char *s = (const char *)str;

    if (0xf0 == (0xf8 & s[0])) {
        // 4 byte utf8 codepoint
        *out_codepoint = ((0x07 & s[0]) << 18) | ((0x3f & s[1]) << 12) |
                         ((0x3f & s[2]) << 6) | (0x3f & s[3]);
        s += 4;
    } else if (0xe0 == (0xf0 & s[0])) {
        // 3 byte utf8 codepoint
        *out_codepoint =
                ((0x0f & s[0]) << 12) | ((0x3f & s[1]) << 6) | (0x3f & s[2]);
        s += 3;
    } else if (0xc0 == (0xe0 & s[0])) {
        // 2 byte utf8 codepoint
        *out_codepoint = ((0x1f & s[0]) << 6) | (0x3f & s[1]);
        s += 2;
    } else {
        // 1 byte utf8 codepoint otherwise
        *out_codepoint = s[0];
        s += 1;
    }

    return (void *)s;
}

size_t utf8codepointcalcsize(const void *str) {
    const char *s = (const char *)str;

    if (0xf0 == (0xf8 & s[0])) {
        // 4 byte utf8 codepoint
        return 4;
    } else if (0xe0 == (0xf0 & s[0])) {
        // 3 byte utf8 codepoint
        return 3;
    } else if (0xc0 == (0xe0 & s[0])) {
        // 2 byte utf8 codepoint
        return 2;
    }

    // 1 byte utf8 codepoint otherwise
    return 1;
}

size_t utf8rcodepointcalcsize(const void *str) {
    const char *s = (const char *) str;

    do {
        s--;
    } while ((0 != (0x80 & s[0])) && (0x80 == (0xc0 & s[0])));

    return (const char*)str - s;
}

size_t utf8codepointsize(utf8_int32_t chr) {
    if (0 == ((utf8_int32_t)0xffffff80 & chr)) {
        return 1;
    } else if (0 == ((utf8_int32_t)0xfffff800 & chr)) {
        return 2;
    } else if (0 == ((utf8_int32_t)0xffff0000 & chr)) {
        return 3;
    } else { // if (0 == ((int)0xffe00000 & chr)) {
        return 4;
    }
}

void *utf8catcodepoint(void *str, utf8_int32_t chr, size_t n) {
    char *s = (char *)str;

    if (0 == ((utf8_int32_t)0xffffff80 & chr)) {
        // 1-byte/7-bit ascii
        // (0b0xxxxxxx)
        if (n < 1) {
            return utf8_null;
        }
        s[0] = (char)chr;
        s += 1;
    } else if (0 == ((utf8_int32_t)0xfffff800 & chr)) {
        // 2-byte/11-bit utf8 code point
        // (0b110xxxxx 0b10xxxxxx)
        if (n < 2) {
            return utf8_null;
        }
        s[0] = 0xc0 | (char)((chr >> 6) & 0x1f);
        s[1] = 0x80 | (char)(chr & 0x3f);
        s += 2;
    } else if (0 == ((utf8_int32_t)0xffff0000 & chr)) {
        // 3-byte/16-bit utf8 code point
        // (0b1110xxxx 0b10xxxxxx 0b10xxxxxx)
        if (n < 3) {
            return utf8_null;
        }
        s[0] = 0xe0 | (char)((chr >> 12) & 0x0f);
        s[1] = 0x80 | (char)((chr >> 6) & 0x3f);
        s[2] = 0x80 | (char)(chr & 0x3f);
        s += 3;
    } else { // if (0 == ((int)0xffe00000 & chr)) {
        // 4-byte/21-bit utf8 code point
        // (0b11110xxx 0b10xxxxxx 0b10xxxxxx 0b10xxxxxx)
        if (n < 4) {
            return utf8_null;
        }
        s[0] = 0xf0 | (char)((chr >> 18) & 0x07);
        s[1] = 0x80 | (char)((chr >> 12) & 0x3f);
        s[2] = 0x80 | (char)((chr >> 6) & 0x3f);
        s[3] = 0x80 | (char)(chr & 0x3f);
        s += 4;
    }

    return s;
}

int utf8islower(utf8_int32_t chr) { return chr != utf8uprcodepoint(chr); }

int utf8isupper(utf8_int32_t chr) { return chr != utf8lwrcodepoint(chr); }

void utf8lwr(void *utf8_restrict str) {
    void *p, *pn;
    utf8_int32_t cp;

    p = (char *)str;
    pn = utf8codepoint(p, &cp);

    while (cp != 0) {
        const utf8_int32_t lwr_cp = utf8lwrcodepoint(cp);
        const size_t size = utf8codepointsize(lwr_cp);

        if (lwr_cp != cp) {
            utf8catcodepoint(p, lwr_cp, size);
        }

        p = pn;
        pn = utf8codepoint(p, &cp);
    }
}

void utf8upr(void *utf8_restrict str) {
    void *p, *pn;
    utf8_int32_t cp;

    p = (char *)str;
    pn = utf8codepoint(p, &cp);

    while (cp != 0) {
        const utf8_int32_t lwr_cp = utf8uprcodepoint(cp);
        const size_t size = utf8codepointsize(lwr_cp);

        if (lwr_cp != cp) {
            utf8catcodepoint(p, lwr_cp, size);
        }

        p = pn;
        pn = utf8codepoint(p, &cp);
    }
}

utf8_int32_t utf8lwrcodepoint(utf8_int32_t cp) {
    if (((0x0041 <= cp) && (0x005a >= cp)) ||
        ((0x00c0 <= cp) && (0x00d6 >= cp)) ||
        ((0x00d8 <= cp) && (0x00de >= cp)) ||
        ((0x0391 <= cp) && (0x03a1 >= cp)) ||
        ((0x03a3 <= cp) && (0x03ab >= cp)) ||
        ((0x0410 <= cp) && (0x042f >= cp))) {
        cp += 32;
    } else if ((0x0400 <= cp) && (0x040f >= cp)) {
        cp += 80;
    } else if (((0x0100 <= cp) && (0x012f >= cp)) ||
               ((0x0132 <= cp) && (0x0137 >= cp)) ||
               ((0x014a <= cp) && (0x0177 >= cp)) ||
               ((0x0182 <= cp) && (0x0185 >= cp)) ||
               ((0x01a0 <= cp) && (0x01a5 >= cp)) ||
               ((0x01de <= cp) && (0x01ef >= cp)) ||
               ((0x01f8 <= cp) && (0x021f >= cp)) ||
               ((0x0222 <= cp) && (0x0233 >= cp)) ||
               ((0x0246 <= cp) && (0x024f >= cp)) ||
               ((0x03d8 <= cp) && (0x03ef >= cp)) ||
               ((0x0460 <= cp) && (0x0481 >= cp)) ||
               ((0x048a <= cp) && (0x04ff >= cp))) {
        cp |= 0x1;
    } else if (((0x0139 <= cp) && (0x0148 >= cp)) ||
               ((0x0179 <= cp) && (0x017e >= cp)) ||
               ((0x01af <= cp) && (0x01b0 >= cp)) ||
               ((0x01b3 <= cp) && (0x01b6 >= cp)) ||
               ((0x01cd <= cp) && (0x01dc >= cp))) {
        cp += 1;
        cp &= ~0x1;
    } else {
        switch (cp) {
            default:
                break;
            case 0x0178:
                cp = 0x00ff;
                break;
            case 0x0243:
                cp = 0x0180;
                break;
            case 0x018e:
                cp = 0x01dd;
                break;
            case 0x023d:
                cp = 0x019a;
                break;
            case 0x0220:
                cp = 0x019e;
                break;
            case 0x01b7:
                cp = 0x0292;
                break;
            case 0x01c4:
                cp = 0x01c6;
                break;
            case 0x01c7:
                cp = 0x01c9;
                break;
            case 0x01ca:
                cp = 0x01cc;
                break;
            case 0x01f1:
                cp = 0x01f3;
                break;
            case 0x01f7:
                cp = 0x01bf;
                break;
            case 0x0187:
                cp = 0x0188;
                break;
            case 0x018b:
                cp = 0x018c;
                break;
            case 0x0191:
                cp = 0x0192;
                break;
            case 0x0198:
                cp = 0x0199;
                break;
            case 0x01a7:
                cp = 0x01a8;
                break;
            case 0x01ac:
                cp = 0x01ad;
                break;
            case 0x01af:
                cp = 0x01b0;
                break;
            case 0x01b8:
                cp = 0x01b9;
                break;
            case 0x01bc:
                cp = 0x01bd;
                break;
            case 0x01f4:
                cp = 0x01f5;
                break;
            case 0x023b:
                cp = 0x023c;
                break;
            case 0x0241:
                cp = 0x0242;
                break;
            case 0x03fd:
                cp = 0x037b;
                break;
            case 0x03fe:
                cp = 0x037c;
                break;
            case 0x03ff:
                cp = 0x037d;
                break;
            case 0x037f:
                cp = 0x03f3;
                break;
            case 0x0386:
                cp = 0x03ac;
                break;
            case 0x0388:
                cp = 0x03ad;
                break;
            case 0x0389:
                cp = 0x03ae;
                break;
            case 0x038a:
                cp = 0x03af;
                break;
            case 0x038c:
                cp = 0x03cc;
                break;
            case 0x038e:
                cp = 0x03cd;
                break;
            case 0x038f:
                cp = 0x03ce;
                break;
            case 0x0370:
                cp = 0x0371;
                break;
            case 0x0372:
                cp = 0x0373;
                break;
            case 0x0376:
                cp = 0x0377;
                break;
            case 0x03f4:
                cp = 0x03b8;
                break;
            case 0x03cf:
                cp = 0x03d7;
                break;
            case 0x03f9:
                cp = 0x03f2;
                break;
            case 0x03f7:
                cp = 0x03f8;
                break;
            case 0x03fa:
                cp = 0x03fb;
                break;
        }
    }

    return cp;
}

utf8_int32_t utf8uprcodepoint(utf8_int32_t cp) {
    if (((0x0061 <= cp) && (0x007a >= cp)) ||
        ((0x00e0 <= cp) && (0x00f6 >= cp)) ||
        ((0x00f8 <= cp) && (0x00fe >= cp)) ||
        ((0x03b1 <= cp) && (0x03c1 >= cp)) ||
        ((0x03c3 <= cp) && (0x03cb >= cp)) ||
        ((0x0430 <= cp) && (0x044f >= cp))) {
        cp -= 32;
    } else if ((0x0450 <= cp) && (0x045f >= cp)) {
        cp -= 80;
    } else if (((0x0100 <= cp) && (0x012f >= cp)) ||
               ((0x0132 <= cp) && (0x0137 >= cp)) ||
               ((0x014a <= cp) && (0x0177 >= cp)) ||
               ((0x0182 <= cp) && (0x0185 >= cp)) ||
               ((0x01a0 <= cp) && (0x01a5 >= cp)) ||
               ((0x01de <= cp) && (0x01ef >= cp)) ||
               ((0x01f8 <= cp) && (0x021f >= cp)) ||
               ((0x0222 <= cp) && (0x0233 >= cp)) ||
               ((0x0246 <= cp) && (0x024f >= cp)) ||
               ((0x03d8 <= cp) && (0x03ef >= cp)) ||
               ((0x0460 <= cp) && (0x0481 >= cp)) ||
               ((0x048a <= cp) && (0x04ff >= cp))) {
        cp &= ~0x1;
    } else if (((0x0139 <= cp) && (0x0148 >= cp)) ||
               ((0x0179 <= cp) && (0x017e >= cp)) ||
               ((0x01af <= cp) && (0x01b0 >= cp)) ||
               ((0x01b3 <= cp) && (0x01b6 >= cp)) ||
               ((0x01cd <= cp) && (0x01dc >= cp))) {
        cp -= 1;
        cp |= 0x1;
    } else {
        switch (cp) {
            default:
                break;
            case 0x00ff:
                cp = 0x0178;
                break;
            case 0x0180:
                cp = 0x0243;
                break;
            case 0x01dd:
                cp = 0x018e;
                break;
            case 0x019a:
                cp = 0x023d;
                break;
            case 0x019e:
                cp = 0x0220;
                break;
            case 0x0292:
                cp = 0x01b7;
                break;
            case 0x01c6:
                cp = 0x01c4;
                break;
            case 0x01c9:
                cp = 0x01c7;
                break;
            case 0x01cc:
                cp = 0x01ca;
                break;
            case 0x01f3:
                cp = 0x01f1;
                break;
            case 0x01bf:
                cp = 0x01f7;
                break;
            case 0x0188:
                cp = 0x0187;
                break;
            case 0x018c:
                cp = 0x018b;
                break;
            case 0x0192:
                cp = 0x0191;
                break;
            case 0x0199:
                cp = 0x0198;
                break;
            case 0x01a8:
                cp = 0x01a7;
                break;
            case 0x01ad:
                cp = 0x01ac;
                break;
            case 0x01b0:
                cp = 0x01af;
                break;
            case 0x01b9:
                cp = 0x01b8;
                break;
            case 0x01bd:
                cp = 0x01bc;
                break;
            case 0x01f5:
                cp = 0x01f4;
                break;
            case 0x023c:
                cp = 0x023b;
                break;
            case 0x0242:
                cp = 0x0241;
                break;
            case 0x037b:
                cp = 0x03fd;
                break;
            case 0x037c:
                cp = 0x03fe;
                break;
            case 0x037d:
                cp = 0x03ff;
                break;
            case 0x03f3:
                cp = 0x037f;
                break;
            case 0x03ac:
                cp = 0x0386;
                break;
            case 0x03ad:
                cp = 0x0388;
                break;
            case 0x03ae:
                cp = 0x0389;
                break;
            case 0x03af:
                cp = 0x038a;
                break;
            case 0x03cc:
                cp = 0x038c;
                break;
            case 0x03cd:
                cp = 0x038e;
                break;
            case 0x03ce:
                cp = 0x038f;
                break;
            case 0x0371:
                cp = 0x0370;
                break;
            case 0x0373:
                cp = 0x0372;
                break;
            case 0x0377:
                cp = 0x0376;
                break;
            case 0x03d1:
                cp = 0x0398;
                break;
            case 0x03d7:
                cp = 0x03cf;
                break;
            case 0x03f2:
                cp = 0x03f9;
                break;
            case 0x03f8:
                cp = 0x03f7;
                break;
            case 0x03fb:
                cp = 0x03fa;
                break;
        }
    }

    return cp;
}

void *utf8rcodepoint(const void *utf8_restrict str,
                     utf8_int32_t *utf8_restrict out_codepoint) {
    const char *s = (const char *)str;

    if (0xf0 == (0xf8 & s[0])) {
        // 4 byte utf8 codepoint
        *out_codepoint = ((0x07 & s[0]) << 18) | ((0x3f & s[1]) << 12) |
                         ((0x3f & s[2]) << 6) | (0x3f & s[3]);
    } else if (0xe0 == (0xf0 & s[0])) {
        // 3 byte utf8 codepoint
        *out_codepoint =
                ((0x0f & s[0]) << 12) | ((0x3f & s[1]) << 6) | (0x3f & s[2]);
    } else if (0xc0 == (0xe0 & s[0])) {
        // 2 byte utf8 codepoint
        *out_codepoint = ((0x1f & s[0]) << 6) | (0x3f & s[1]);
    } else {
        // 1 byte utf8 codepoint otherwise
        *out_codepoint = s[0];
    }

    do {
        s--;
    } while ((0 != (0x80 & s[0])) && (0x80 == (0xc0 & s[0])));

    return (void *)s;
}

#undef utf8_restrict
#undef utf8_null

#ifdef __cplusplus
} // extern "C"
#endif

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // SHEREDOM_UTF8_H_INCLUDED
