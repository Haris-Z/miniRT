/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_memq.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:53:23 by hazunic           #+#    #+#             */
/*   Updated: 2025/10/04 15:22:58 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#define __GNUC__ 1
#define _FORTIFY_SOURCE 2

#include "../../include/libft.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>

//cc -g3 -Wall -Wextra -Werror -fsanitize=address,undefined t_memq.c ../../libft.a -o t_mem && ./t_mem
//  cc -g3 -fsanitize=address ,undefined t_memq.c ../../libft.a -o t_mem && ./t_mem
// using teh attributes - gives better messages with fsanititze and warns
// when running without cc -Wall -Wextra -Werror

int t_ftcpy(void);
int t_cpy(void);
int test_memcpy(void);
int test_ft_memcpy(void);
int test_memset(void);
int test_ft_memset(void);
int	test_ft_memmove(void);
int	test_memmove(void);
void *ft_memmove_bug(void *dest, const void *src, size_t n);
void *ft_memmove_fixed(void *dst, const void *src, size_t n);
static void show(const char *title, const char *buf);
int test_memmove_bugs(void);

int	ft_memcmp_old(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	while (n > 0)
	{
		if (*s1_ptr != *s2_ptr)
			return (*s1_ptr - *s2_ptr);
		s1_ptr++;
		s2_ptr++;
		n--;
	}
	return (0);
}

int test_memcmp(const void *s1, const void *s2, size_t n)
{
	int ret = 0;
	ret = memcmp(s1, s2, n);
	printf("\nmemcmp: %d\n", ret);
	return (ret);
}

int test_memcmp_old(const void *s1, const void *s2, size_t n)
{
	int ret = 0;
	ret = ft_memcmp_old(s1, s2, n);
	printf("\nold: %d\n", ret);
	return (ret);
}

int test_memcmp_new(const void *s1, const void *s2, size_t n)
{
	int ret = 0;
	ret = ft_memcmp(s1, s2, n);
	printf("\nnew: %d\n", ret);
	return (ret);
}

int main(void)
{
	//char s1[] = "hello";
	// For C strings you often use strlen(s) or strlen(s)+1 (to include the \0).
	//sizeof s only works when s is an array in the same scope (not a pointer).
	char s1[] = "hezzo";
	char s2[] = "hello";
	size_t n =  3;//sizeof(s1);//strlen(s1) + 1;//sizeof(s2);
	
	(void)test_memcmp(s1, s2, n);
	(void)test_memcmp_new(s1, s2, n);
	(void)test_memcmp_old(s1, s2, n);
	return (0);
}

/* --- your current "buggy" memmove (calls memcpy when dest < src) buggy with memcpy not with ft_memcpy
 cc -O3 -g3 -Wall -Wextra -Werror
 -Waddress t_memq.c ../../libft.a -o t_mem && ./t_mem | cat -e

cc -O0 -g3 -Wall -Wextra -Werror
 -Waddress -fsanitize=address,undefined t_memq.c ../../libft.a -o t_mem && ./t_mem | cat -e
--- */
void *ft_memmove_bug(void *dest, const void *src, size_t n)
{
    // unsigned char *d = (unsigned char *)dest;
    // const unsigned char *s = (const unsigned char *)src;

    // if (d == s || n == 0) return dest;
    // if (d > s) {
    //     /* copy backwards */
    //     d += n; s += n;
    //     while (n--) *--d = *--s;
    //     return dest;
    // }
    // /* risky: may be overlapping, but calls memcpy (UB by spec) */
    // return ft_memcpy(dest, src, n);
	return (ft_memmove(dest, src, n));
}

/* --- a safe memmove (never calls memcpy unless proven non-overlap) --- */
void *ft_memmove_fixed(void *dst, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;

    if (d == s || n == 0) return dst;

    /* if no overlap, we can delegate */
    if (d + n <= s || s + n <= d)
        return memcpy(dst, src, n);

    if (d > s) {             /* overlap, dest after src -> copy backwards */
        while (n--) d[n] = s[n];
    } else {                 /* overlap, dest before src -> copy forwards */
        for (size_t i = 0; i < n; ++i) d[i] = s[i];
    }
    return dst;
}

static void show(const char *title, const char *buf)
{
    printf("%-24s \"%s\"\n", title, buf);
}

int test_memmove_bugs(void)
{
    /* CASE A: overlap with dest < src  (dst = buf, src = buf+1)
       UB for memcpy, but often "seems" to work under -O0;
       under -O3 the optimizer may bite. */
    {
        char a1[32] = "ABCDEFGH";
        size_t n = strlen(a1 + 1) + 1; /* include '\0' */
        char a2[32]; strcpy(a2, "ABCDEFGH");
        char a3[32]; strcpy(a3, "ABCDEFGH");

        memmove(a1, a1 + 1, n);               /* reference */
        ft_memmove_bug(a2, a2 + 1, n);        /* your buggy branch calls memcpy */
        ft_memmove_fixed(a3, a3 + 1, n);      /* safe forward copy */

        puts("CASE A: overlap (dest < src), dst=buf, src=buf+1, n=strlen(src)+1");
        show("libc memmove ->", a1);          /* expected: "BCDEFGH" */
        show("ft_memmove_bug ->", a2);        /* UB: may match or differ */
        show("ft_memmove_fixed ->", a3);      /* "BCDEFGH" */
        puts("");
    }

    /* CASE B: overlap with dest > src  (dst = buf+1, src = buf)
       Forward memcpy is obviously wrong here; memmove must copy backwards. */
    {
        char b1[32] = "ABCDEFGH";
        size_t n = strlen(b1) + 1; /* include '\0' */
        char b2[32]; strcpy(b2, "ABCDEFGH");
        char b3[32]; strcpy(b3, "ABCDEFGH");

        memmove(b1 + 1, b1, n);               /* reference */
        ft_memmove_bug(b2 + 1, b2, n);        /* your code copies backwards here (ok) */
        ft_memmove_fixed(b3 + 1, b3, n);      /* also ok */

        puts("CASE B: overlap (dest > src), dst=buf+1, src=buf, n=strlen(src)+1");
        show("libc memmove ->", b1);          /* expected: "AABCDEFGH" */
        show("ft_memmove_bug ->", b2);        /* should match */
        show("ft_memmove_fixed ->", b3);      /* should match */
        puts("");
    }

    /* CASE C: no overlap (dest < src far enough apart)
       memcpy is fine; both implementations should match. */
    {
        char c1[32] = "ABCDEFGHIJ";
        char c2[32]; strcpy(c2, "ABCDEFGHIJ");
        char c3[32]; strcpy(c3, "ABCDEFGHIJ");
        size_t n = 4;

        memmove(c1, c1 + 6, n);               /* copy "GHIJ"[0..3] -> front */
        ft_memmove_bug(c2, c2 + 6, n);
        ft_memmove_fixed(c3, c3 + 6, n);

        puts("CASE C: no overlap, dst=buf, src=buf+6, n=4");
        show("libc memmove ->", c1);          /* "GHIJEFGHIJ" (front 4 bytes become GHIJ) */
        show("ft_memmove_bug ->", c2);        /* should match */
        show("ft_memmove_fixed ->", c3);      /* should match */
        puts("");
    }

    return 0;
}

// int	main(void)
// {
// 	test_ft_memmove();
// 	test_memmove();
// 	return (0);
// }
int	test_ft_memmove(void)
{
	char buf[100] = "Geeksfor";
	printf("\n\nft_memmove:\n");
	char *d = ft_memmove(buf + 5, buf, strlen(buf) + 1);
	printf("buf: %s\n", buf);   // "GeeksGeeksfor"
	printf("d:   %s\n", d);     // "Geeksfor"
	return (0);
}

int	test_memmove(void)
{
	char buf[100] = "Geeksfor";
	printf("\n\nmemmove:\n");
	char *d = memmove(buf + 5, buf, strlen(buf) + 1);
	printf("buf: %s\n", buf);   // "GeeksGeeksfor"
	printf("d:   %s\n", d);     // "Geeksfor"
	return (0);
}

int test_ft_memcpy(void)
{
	char	src[100] = "Geeksfor";
	char	*d;
	d = ft_memcpy(src + 5, src, strlen(src) + 1);
	printf("\n\nft_memcpy:\n");
	printf("ft_src:\t\t%s\n", src);
	printf("d:\t\t%s\n", d);
	return (0);
}

int test_memcpy(void)
{
	char	src[100] = "Geeksfor";
	char    dest[100];
	memcpy(dest, src, strlen(src) + 1);
	printf("\n\nmemcpy:\n");
	printf("src:\t\t%s\n", src);
	printf("d:\t\t%s\n", dest);
	return (0);
}

int test_ft_memset(void)
{
	//int a[5] = {1, 2, 3, 4, 5};
	char a[13] = " 1 2 3 4 5 6";

	
	printf("\n\nft_memset\n");
	printf("%zu: %zu: %s\n", strlen(a), sizeof(a), a);
	ft_memset(a, -1, sizeof(a));
	//size_t size = sizeof(a) / sizeof(int);
	//printf("size: %zu\n", size);
	// size_t i = 0;
	// while (i < size)
	// {
	// 	printf("%d, ", a[i]);
	// 	i++;
	// }
	//printf("%zu: %zu: %s\n", strlen(a), sizeof(a), a);
	printf("\n");
	return (0);
}

int test_memset(void)
{
	//int a[5] = {1, 2, 3, 4, 5};
	char a[13] = " 1 2 3 4 5 6";
	
	printf("\n\nmemset\n");
	printf("%zu: %zu: %s\n", strlen(a), sizeof(a), a);
	//memset(a, 12, sizeof(a));
	memset(a, -1, sizeof(a));
	// size_t size = sizeof(a) / sizeof(int);
	size_t size = sizeof(a);
	// printf("size: %zu\n", size);
	size_t i = 0;
	while (i < size)
	{
		printf("%d, ", a[i]);
		i++;
	}
	//printf("%zu: %zu: %s\n", strlen(a), sizeof(a), a);
	printf("%zu:\n", sizeof(a));
	printf("\n");
	return (0);
}
int t_cpy(void)
{
	char	s[3];
	char	*ss;
	char	sp[3];
	
	s[0] = 'a';
	s[1] = 'b';
	s[2] = 'c';
	printf("Before memcpy:\n");
	printf("s[0]: %c (%u) (%x)\n", s[0], (unsigned char )s[0], (unsigned char )s[0]);
	printf("s[1]: %c (%u) (%x)\n", s[1], (unsigned char )s[1], (unsigned char )s[1]);
	printf("s[2]: %c (%u) (%x)\n", s[2], (unsigned char )s[2], (unsigned char )s[2]);
	printf("number of elements : %zu\n", (size_t )(sizeof s / sizeof *s));
	printf("size in bytes : %zu\n", sizeof s );
	printf("After  memcpy:\n");
	ss = memcpy(sp, s, sizeof s);
	printf("\nss[0]: %c (%u) (%x)\n", ss[0], (unsigned char )ss[0], (unsigned char )ss[0]);
	printf("ss[1]: %c (%u) (%x)\n", ss[1], (unsigned char )ss[1], (unsigned char )ss[1]);
	printf("ss[2]: %c (%u) (%x)\n", ss[2], (unsigned char )ss[2], (unsigned char )ss[2]);
	return (0);
}

int t_ftcpy(void)
{
	char	s[3];
	char	*ss;
	char	sp[3];
	
	s[0] = 'a';
	s[1] = 'b';
	s[2] = 'c';
	printf("Before ft_memcpy:\n");
	printf("s[0]: %c (%u) (%x)\n", s[0], (unsigned char )s[0], (unsigned char )s[0]);
	printf("s[1]: %c (%u) (%x)\n", s[1], (unsigned char )s[1], (unsigned char )s[1]);
	printf("s[2]: %c (%u) (%x)\n", s[2], (unsigned char )s[2], (unsigned char )s[2]);
	printf("number of elements : %zu\n", (size_t )(sizeof s / sizeof *s));
	printf("size in bytes : %zu\n", sizeof s );
	printf("After ft_memcpy:\n");
	ss = ft_memcpy(sp, s, sizeof s);
	printf("s[0]: %c (%u) (%x)\n", s[0], (unsigned char )s[0], (unsigned char )s[0]);
	printf("s[1]: %c (%u) (%x)\n", s[1], (unsigned char )s[1], (unsigned char )s[1]);
	printf("s[2]: %c (%u) (%x)\n", s[2], (unsigned char )s[2], (unsigned char )s[2]);
	
	printf("\nss[0]: %c (%u) (%x)\n", ss[0], (unsigned char )ss[0], (unsigned char )ss[0]);
	printf("ss[1]: %c (%u) (%x)\n", ss[1], (unsigned char )ss[1], (unsigned char )ss[1]);
	printf("ss[2]: %c (%u) (%x)\n", ss[2], (unsigned char )ss[2], (unsigned char )ss[2]);
	return (0);
}


// 	/*
// 	The sizeof rules to remember
// 	sizeof array → gives total number of bytes in the array (here sizeof str == 5).
// 	sizeof pointer → gives size of the pointer itself (usually 8 on 64-bit).
// 	sizeof *pointer → gives size of the pointee type (here char, always 1).
// 	*/
	
// 	char	str[5] = "hello";//{0};
// 	char	*s = str;
// 	printf("%s\nsizeof str: %zu\n", s, sizeof s);
// 	printf("%s\n", str);
// 	ft_bzero(s, 0);
// 	//ft_bzero(s, sizeof *s); segfaults
// 	//ft_bzero((void *)str, sizeof str);
// 	printf("%s\nsizeof str: %zu\n", s, sizeof s);
// 	//sizeof *s  == sizeof(char) == 1
// 	return (0);
// }


// #include <stdio.h>

// #include <string.h>
// int	main(void)//test_memset_chararray(void)
// {
// 	char	s[3];
// 	char	*sp = NULL;
	
// 	s[0] = 'a';
// 	s[1] = 'b';
// 	s[2] = 'c';
// 	printf("Before ft_memset:\n");
// 	printf("s[0]: %c (%u) (%x)\n", s[0], (unsigned char )s[0], (unsigned char )s[0]);
// 	printf("s[1]: %c (%u) (%x)\n", s[1], (unsigned char )s[1], (unsigned char )s[1]);
// 	printf("s[2]: %c (%u) (%x)\n", s[2], (unsigned char )s[2], (unsigned char )s[2]);
// 	printf("number of elements : %zu\n", (size_t )(sizeof s / sizeof *s));
// 	printf("size in bytes : %zu\n", sizeof s );

// 	printf("after ft_memset:\n");
// 	sp = ft_memset(s, 0xDEADBEEF, sizeof s);
// 	printf("After (as chars): %c %c %c\n", (unsigned char)s[0], (unsigned char)s[1], (unsigned char)s[2]);
// 	printf("After (as bytes): %u %u %u\n", (unsigned char)s[0], (unsigned char)s[1], (unsigned char)s[2]);
// 	printf("After (as hex): 0x%X 0x%X 0x%X\n", (unsigned char)s[0], (unsigned char)s[1], (unsigned char)s[2]);
// 	if ((unsigned char )s[0] == 239)
// 		printf("poisened (byte == 239)\n");
// 	if ((unsigned char)s[0] == (unsigned char)0xDEADBEEF)
// 		printf("poisoned\n");
// 	if ((unsigned char)s[0] == (0xDEADBEEF & 0xFF))
// 		printf("matched low byte 0x%02X\n", (0xDEADBEEF & 0xFF));
// 	if ((unsigned char)s[0] == (0xDEADBEEF & 0xFF))
// 		printf("poisoned\n");
// 	printf("sp bytes: %u %u %u\n",
// 		(unsigned char)sp[0], (unsigned char)sp[1], (unsigned char)sp[2]);
// 	return (0);
// }

// int	test_memset_intarray(void)
// {
// 	int	s[3];
// 	int	*sp = NULL;
//	That warning is legit: the left side can only ever be 0–255, while 0xDEADBEEF is 3735928559, so the comparison is provably false.
// 	s[0] = 0;
// 	s[1] = 1;
// 	s[2] = 2;
// 	printf("Before ft_memset:\n");
// 	printf("s[0]: %d\n", s[0]);
// 	printf("s[1]: %d\n", s[1]);
// 	printf("s[2]: %d\n", s[2]);
// 	printf("number of elements : %zu\n", (size_t )(sizeof s / sizeof *s));
// 	printf("size in bytes : %zu\n", sizeof s );

// 	printf("after ft_memset:\n");
// 	sp = ft_memset(s, 100, sizeof s);
// 	printf("ft: s: %d | sizeof s: %zu\n", s[0], sizeof s);
// 	printf("ft: s: %d | sizeof s: %zu\n", s[1], sizeof s);
// 	printf("ft: s: %d | sizeof s: %zu\n", s[2], sizeof s);

// 	printf("ft: s: %d  \n",sp[0]);
// 	printf("ft: s: %d  \n", sp[1]);
// 	printf("ft: s: %d  \n", sp[2]);
// 	return (0);
// }

//		printf("ft: s: %s | p: &s %p | (void *)s %p |sizeof s: %zu\n", s, &s, (void *)s, sizeof s);

/*
memset(..., 0, ...) is safe for any object (integers, pointers, structs).
memset is defined in terms of bytes (unsigned char), not object types
int	s[3];
&s is of type int (*)[3]
works byte-wise, not element-wise.
Segfaults found // undefined behaviour
char str[5];
memset(str, 'Z', 30);  // poisoning an adress
char *str = NULL;
memset(str, 'Z', 10);

Undefined behaviour from memset(),
resulting from storage overflow,
will occur if len is greater than the the length of buffer dest.
The behaviour is also undefined if dest is an invalid pointer. 

sources found:
https://nxmnpg.lemoda.net/3/memset#google_vignette
*/

/*
int	main(void)
{
	//int t = 0;
	int	s[3];
	int	*sp = NULL;
	
	s[0] = 0;
	s[1] = 1;
	s[2] = 2;
	printf("Before ft_memset:\n");
	printf("s[0]: %d\n", s[0]);
	printf("s[1]: %d\n", s[1]);
	printf("s[2]: %d\n", s[2]);
	printf("sizeof : %zu\n", (size_t )(sizeof s / sizeof *s));
	if (t == 0)
	{
		sp = ft_memset(&s, 0, (size_t )(sizeof s / sizeof *s));
		printf("ft: s: %d | sizeof s: %zu\n",s[0], sizeof s);
		printf("ft: s: %d | sizeof s: %zu\n", s[1], sizeof s);
		printf("ft: s: %d | sizeof s: %zu\n", s[2], sizeof s);
	}
	// else
	// {
	// 	// memset(s, 0, sizeof s);
	// 	// printf("libc: s: %s | p: %p\n", s, &s);
	// }
	return (0);
}
*/



/*
//test overlapping, check n = 0 with original

	//if (dest == src)
	//	return (dest);

#include <stdio.h>
#include <string.h>
// void	test_ft_memcpy(void)
// {
// 	char dest[50];
// 	//char *src = "hello";
// 	char *src = dest;

// 	ft_memcpy(dest, src, 1);
// 	printf("dest after ft_memcpy: %s\n", dest);
// }
void	test_memcpy(void)
{
	char dest2[50] = "hello";
	char *src2 = dest2;

	memcpy(dest2, src2, 5);
	printf("dest after memcpy: %s\n", dest2);
}

int main(void)
{
	//test_ft_memcpy();
	test_memcpy();
	return (0);
}
*/


/*###########################*/
/* memmove */


// #include <stdio.h>
// #include <string.h>
// #include <stddef.h>

// void	test_memmove(void)
// {
// 	//void *memmove(void *dest, const void *src, size_t n);
// 	/* NOTES
// 	// n and len of dest being the same len prints garbage values. after 
// 	/ the initial string
// 	*/
// 	// char	dest[13]; -if NULL then segf
// 	// char	*src = "hello world!"; if NULL segfault
// 	//size_t	n = 0; if 0 nothing returned? or empty string dest
// 	// char	dest[13];
// 	// char	src[] = "hello";
// 	// size_t	n = 6;
// 	//char	dest[] = "world";
// 	char	src[] = "hello";
// 	//size_t	n = 6;

// 	//memmove(dest, src, n);
// 	memmove(src + 1, src, 4);//overlap
// 	printf("memmove: %s\n", src);

// }

// void	test_ft_memmove(void)
// {
// 	char	src[] = "hello";
// 	//char	dest[] = "world";
// 	//ft_memmove(dest, src, 6);
// 	ft_memmove(src + 1, src, 4);//overlap
// 	printf("ft_memmove: %s\n", src);
// }

// int	main(void)
// {
// 	test_memmove();
// 	test_ft_memmove();	
// 	return (0);
// }

// //reference https://cplusplus.com/reference/cstring/memmove/#google_vignette



// old memmove

/*
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr = (const unsigned char *)src;
	size_t				i;

	dest_ptr = (unsigned char *)dest;
	i = 0;
	if (src_ptr == dest_ptr || n == 0)
		return (dest);
	if (dest_ptr + n <= src_ptr || src_ptr + n <= dest_ptr) // overlap: dst starts inside src check that there is no overlap for sure
		return (ft_memcpy(dest, src, n));
	if (dest_ptr > src_ptr)
	{
		while (n--) // copy backwards
			dest_ptr[n] = src_ptr[n];
	}
	else
	{
		while (i < n)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dest);
}

*/

// MEMCMP
/*
#include <stdio.h>
#include <string.h>
void	test_ft_memcmp(void)
{
	char *s1 = "hellx";
	//char *src = "hello";
	char *s2 = "hello";

	if ((ft_memcmp(s1, s2, 5) > 0) || (ft_memcmp(s1, s2, 5) < 0))
	{
		printf("ft_memcmp: match/mismatch at position %ld\n", (s2 - s1) - 1);
		printf("s1: %s\ns2: %s\n", s1, s2);
	}
	else
		printf("ft_memcmp: data is match\n");
}
void	test_memcmp(void)
{
	char *s1 = "hellx";
	//char *src = "hello";
	char *s2 = "hello";

	//memcmp(s1, s2, 5);
	if ((memcmp(s1, s2, 5) > 0) || (memcmp(s1, s2, 5) < 0))
	{
		printf("memcmp: match/mismatch at position %ld\n", (s2 - s1) - 1);
		printf("s1: %s\ns2: %s\n", s1, s2);
	}
	else
		printf("memcmp: data is match\n");
}

int main(void)
{
	test_memcmp();
	test_ft_memcmp();
	return (0);
}
*/



/*
#include <stdio.h>
#include <string.h>
int	test_ft_memchr_int(void)
{
	int		array[] = {1, 2, 3};
	size_t	array_size = sizeof(array);
	int		*result = ft_memchr(array, 3, array_size);
	
	if (result == NULL)
	{
		printf("NULL: no match found\n");
	}
	else
	{
		ptrdiff_t	index;
		index = result - array;
		printf("first match at index %td\n", index);
		printf("string = %d\n", *result);
	}
	
	return (0);
}
int	test_memchr_int(void)
{
	int		array[] = {1, 2, 3};
	size_t	array_size = sizeof(array);
	
	int		*result = memchr(array, 3, array_size);
	
	if (result == NULL)
	{
		printf("NULL: no match found\n");
	}
	else
	{
		ptrdiff_t	index;
		index = result - array;
		printf("first match at index %td\n", index);
		printf("string = %d\n", *result);
	}
	
	return (0);
}

int	test_ft_memchr(void)
{
	char *s = "Hello";
	char *result;

	result = ft_memchr(s, 'e', 2);
	if (result == NULL)
	{
		printf("NULL: no match found\n");
	}
	else
	{
		printf("first match at index %ld\n", result - s);
		printf("string = %s\n", result);
	}
	
	return (0);
}
int	test_memchr(void)
{
	char *s = "Hello";
	char *result;

	result = memchr(s, 'e', 2);
	if (result == NULL)
		printf("NULL: no match found\n");
	else
	{
		printf("first match at index %ld\n", result - s);
		printf("string = %s\n", result);
	}
	return (0);
}
int main(void)
{
	printf("test ft_memchr:\n");
	test_ft_memchr();
	test_ft_memchr_int();
	printf("\ntest memchr:\n");
	test_memchr();
	test_memchr_int();
}
*/