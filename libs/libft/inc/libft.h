/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:38:10 by hazunic           #+#    #+#             */
/*   Updated: 2026/03/10 16:45:55 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file	libft.h
 * @brief	Prototypes for the Libft project functions.
 *
 */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stddef.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

/// 
/// @brief Singly linked list node used by Libft.
/// Generic node that stores arbitrary data and a pointer to the
/// next node in the list. The list terminates when `next` is NULL.
struct s_list
{
	/** Pointer to the data stored in the node.
	 *
	 * May point to any type of dynamically or statically allocated object.
	 * Libft list functions never interpret the pointed-to memory.
	 */
	void			*content;
	/** Pointer to the next node in the list, or NULL if this is the last. */
	struct s_list	*next;
};
typedef struct s_list	t_list;

/**
 * @brief	Checks if a character is a decimal digit (0–9) or
 * 			an alphabetic character (A–Z, a–z).
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is alphanumeric,
 * 			0 otherwise.
 * @see ft_isalpha()
 * @see ft_isdigit()
 */
int		ft_isalnum(int c);

/**
 * @brief	Checks if a character is alphabetic (A–Z or a–z).
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is alphabetic,
 * 			0 otherwise.
 */
int		ft_isalpha(int c);

/**
 * @brief 	Checks if a character is a 7-bit ASCII value (0–127).
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is in the ASCII range,
 * 			0 otherwise.
 */
int		ft_isascii(int c);

/**
 * @brief	Checks if a character is a decimal digit (0–9).
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is a digit,
 * 			0 otherwise.
 */
int		ft_isdigit(int c);

/**
 * @brief	Checks if a character is printable (includes space).
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is printable,
 * 			0 otherwise.
 */
int		ft_isprint(int c);

/**
 * @brief	Checks for white-space characters (space or a tab).
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is a space or a tab,
 * 			0 otherwise.
 */
int		ft_isblank(int c);

/**
 * @brief	Checks for control characters
 * 			(ASCII 0x00–0x1F or 0x7F).
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is a control character,
 * 			0 otherwise.
 */
int		ft_iscntrl(int c);

/**
 * @brief	Checks for any visible character except space 
 * 			(i.e., printable & not ' ').
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is a graphical character,
 * 			0 otherwise.
 */
int		ft_isgraph(int c);

/**
 * @brief	Checks for uppercase letters (A–Z).
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is uppercase,
 * 			0 otherwise.
 */
int		ft_isupper(int c);

/**
 * @brief	Checks for lowercase letters (a–z).
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is lowercase,
 * 			0 otherwise.
 */
int		ft_islower(int c);

/**
 * @brief	Checks for punctuation characters
 * 			(any printable char, except space or alnum).
 * 			!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is punctuation,
 * 			0 otherwise.
 */
int		ft_ispunct(int c);

/**
 * @brief	Checks for standard whitespace
 * 
 * @par
 *  - space				— (' ')
 *  - form-feed			— (\\f)
 *  - new_line			— (\\n)
 *	- carriage-return	— (\\r)
 *	- horizontal tab	— (\\t)
 *	- vertical tab		— (\\v)
 *
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is whitespace
 * 			0 otherwise.
 */
int		ft_isspace(int c);

/**
 * @brief	Checks for hexadecimal digits (0–9, a–f, A–F).
 * @param c	The character to test, passed as an int. The value
 *			is either EOF or representable as an unsigned char.
 * @return	1 if @p c is a hex digit
 * 			0 otherwise.
 */
int		ft_isxdigit(int c);

/**
 * @brief	Converts an uppercase letter to lowercase.
 * @note	MACRO defined: ASCII_CASE_DIFF 32
 * 			('A' = 65, 'a' = 97 → difference = 32)
 * @param c	The character to convert.
 * @return	The lowercase equivalent if @p c is uppercase,
 * 			otherwise @p c unchanged.
 */
int		ft_tolower(int c);

/**
 * @brief	Converts a lowercase letter to uppercase.
 * @note	MACRO defined: ASCII_CASE_DIFF 32
 * 			('a' = 97, 'A' = 65 → difference = 32)
 * @param c	The character to convert.
 * @return	The uppercase equivalent
 * 			if @p c is lowercase, otherwise @p c unchanged.
 */
int		ft_toupper(int c);

/**
 * @brief	Sets a block of memory to zero.
 * 
 * Writes @p n zero bytes to the memory area starting at @p s.
 * 
 * @param s	Pointer to the memory area to zero.
 * @param n	Number of bytes to write as zero.
 * @note	Behavior is undefined if @p s is NULL and @p n > 0.
 */
void	ft_bzero(void *s, size_t n);

/**
 * @brief	Scans memory for a byte value.
 *
 * Searches the first @p n bytes of @p s for the first occurrence of the byte
 * value (unsigned char) @p c.
 *
 * @param s	Pointer to the memory area to scan.
 * @param c	Byte value to look for (interpreted as unsigned char).
 * @param n	Number of bytes to examine (not elements).
 * 			For arrays, sizeof arr; for slices, use the actual length.
 * 			For strings: strlen(s) (or strlen(s) + 1 ) -> '\0'
 * @return	A pointer to the matching byte within @p s
 * 			(A pointer to the first occurrence of @p c in @p s )
 * 			or NULL if not found.
 * @note	Behavior is undefined if @p s is NULL and @p n > 0.
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief	Compares two memory blocks byte by byte.
 *
 * Compares the first @p n bytes of @p s1 and @p s2, treating bytes as
 * unsigned char values.
 *
 * @param s1 First memory block.
 * @param s2 Second memory block.
 * @param n  Number of bytes to compare.
 * @return	<0, 0, or >0 if @p s1 is found to be less than, equal to, or greater
 *			than @p s2 in the first differing byte.
 * @note	Behavior is undefined
 * 			if either pointer is NULL and @p n > 0.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Copies a block of memory (no-overlap variant).
 *
 * Copies @p n bytes from @p src to @p dest. The memory areas must not overlap.
 *
 * @param dest Destination buffer.
 * @param src  Source buffer.
 * @param n    Number of bytes to copy.
 *
 * @return A pointer to @p dest.
 * @warning	Overlapping regions yield undefined behavior.
 * 			Use ft_memmove() for overlapping copies.
 * @note	Behavior is undefined if @p dest or @p src is NULL and @p n > 0.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);// \/

/**
 * @brief Copies a block of memory, allowing overlap (overlap-safe).
 *
 * Copies @p n bytes from the memory area @p src to the memory area @p dst.
 * The copy is performed as if the bytes are first copied into a temporary
 * buffer, so overlapping regions are handled correctly.
 *
 * @param dest Destination buffer.
 * @param src  Source buffer.
 * @param n    Number of bytes to copy.
 *
 * @return The pointer to @p dest.
 * @note Behavior is undefined if @p dest or @p src is NULL and @p n > 0.
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Fills a block of memory with a byte value.
 *
 * Sets the first @p n bytes of the memory area pointed to by @p s
 * to (unsigned char) @p c.
 *
 * @param s Pointer to the memory area to fill.
 * @param c The byte value to write (interpreted as unsigned char).
 * @param n Number of bytes to write.
 * @return A pointer to @p s.
 *
 * @note Behavior is undefined if @p s is NULL and @p n > 0.
 */
void	*ft_memset(void *s, int c, size_t n);

/**
 * @brief Finds the first occurrence of a character in a string.
 * @param s The string to search.
 * @param c The character to find (as unsigned char).
 * @return Pointer to first occurrence, or NULL if not found.
 * @note The terminating null byte is considered part of the string,
 *       so that if c is specified as '\0',
 *       the function returns a pointer to the terminator.
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief Concatenates two strings with size limit.
 * @param dst  Destination buffer (must be null-terminated).
 * @param src  Source string.
 * @param size Total size of destination buffer.
 * @return The sum of the initial lengths of @p dst and @p src.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief Copies a string with size limit.
 * @param dst Destination buffer.
 * @param src Source string.
 * @param size Size of destination buffer.
 * @return The total length of @p src.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief Computes the length of a string (excluding the null byte).
 * @param s The string to measure.
 * @return The number of characters in @p s.
 * @note Behavior in libc is undefined if @p s is NULL or not null-terminated.
 * 		 This version returns 0 if @p s == NULL
 */
size_t	ft_strlen(const char *s);

/**
 * @brief Compares two strings up to a maximum length.
 * @param s1 First string.
 * @param s2 Second string.
 * @param n  Maximum number of characters to compare.
 * @return <0, 0, or >0 if @p s1 is less, equal, or greater than @p s2.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Locates a substring in a string, up to @p len chars.
 * @param haystack The string to search.
 * @param needle   The substring to find.
 * @param len      Maximum number of characters to search.
 * @return Pointer to start of located substring, or NULL if not found.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/**
 * @brief Finds the last occurrence of a character in a string.
 * @param s The string to search.
 * @param c The character to find (as unsigned char).
 * @return Pointer to last occurrence, or NULL if not found.
 */
char	*ft_strrchr(const char *s, int c);

/**
 * @brief Applies a function to each character of a string in place.
 * @param s The string to modify (must be mutable).
 * @param f Function applied to each character: f(index, &char).
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief Concatenates two strings into a new string.
 * @param s1 Prefix string.
 * @param s2 Suffix string.
 * @return Newly allocated concatenation, or NULL on failure.
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Maps a function to each character of a string (returns a new string).
 * @param s The input string.
 * @param f Function: f(index, char) -> char.
 * @return Newly allocated mapped string, or NULL on failure.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Splits a string by a delimiter into a NULL-terminated array of strings.
 * @param s The string to split.
 * @param c The delimiter character.
 * @return NULL-terminated array of tokens, or NULL on allocation failure.
 */
char	**ft_split(char const *s, char c);
char	**ft_split_ws(const char *s);

/**
 * @brief Trims characters from both ends of a string.
 * @param s1  The string to be trimmed.
 * @param set The set of characters to remove.
 * @return Newly allocated trimmed string, or NULL on failure.
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Creates a substring from a given string.
 * @param s     Source string (null-terminated).
 * @param start Starting index within @p s.
 * @param len   Maximum number of characters to copy.
 * @return Newly allocated substring, or NULL on failure.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Duplicates a string (mallocs and copies).
 * @param s The string to duplicate.
 * @return Newly allocated copy, or NULL on failure.
 */
char	*ft_strdup(const char *s);

/**
 * @brief Duplicates a string up to length n (mallocs and copies).
 * @param src The string to duplicate.
 * @param n the length to copy
 * @return Newly allocated copy, or NULL on failure.
 */
char	*ft_strndup(const char *src, size_t n);

/**
 * @brief Converts a string to an integer (base 10).
 * @param nptr The string to convert.
 * @return The converted integer value.
 */
int		ft_atoi(const char *nptr);

/**
 * @brief Converts an integer to a newly allocated string (base 10).
 * @param n Integer to convert.
 * @return Newly allocated string representation, or NULL on failure.
 */
char	*ft_itoa(int n);

/**
 * @brief Allocates zero-initialized memory for an array.
 * @param nmemb Number of elements.
 * @param size  Size of each element.
 * @return Pointer to allocated memory, or NULL on failure.
 * @note If nmemb or size is 0, returns a unique pointer valid for free().
 */
void	*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief Writes a single character to a file descriptor.
 * @param c  The character to write.
 * @param fd The file descriptor (e.g., 1 for stdout, 2 for stderr).
 */
void	ft_putchar_fd(char c, int fd);

/**
 * @brief Writes a string followed by a newline to a file descriptor.
 * @param s  The string to write.
 * @param fd The file descriptor.
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @brief Writes an integer (base 10) to a file descriptor.
 * @param n  The integer to write.
 * @param fd The file descriptor.
 */
void	ft_putnbr_fd(int n, int fd);

/**
 * @brief Writes a null-terminated string to a file descriptor.
 * @param s  The string to write.
 * @param fd The file descriptor.
 *
 * @par Example
 * @code
 * ft_putstr_fd("error\n", 2); // write to stderr
 * @endcode
 */
void	ft_putstr_fd(char *s, int fd);

/**
 * @brief 
 * 
 * @param lst 
 * @return t_list* 
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief 
 * 
 * @param lst 
 * @param f 
 * @param del 
 * @return t_list* 
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**
 * @brief 
 * 
 * @param content 
 * @return t_list* 
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief 
 * 
 * @param lst 
 * @param new 
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief 
 * 
 * @param lst 
 * @param new 
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief 
 * 
 * @param lst 
 * @param f 
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief 
 * 
 * @param lst 
 * @return int 
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief 
 * 
 * @param lst 
 * @param del 
 */
void	ft_lstclear(t_list **lst, void (*del)(void*));

/**
 * @brief 
 * 
 * @param lst 
 * @param del 
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*));
/** @} */

/**
 * @brief Frees a buffer and sets the pointer to NULL.
 */
void	*free_and_null(char **ptr_to_free);

/// @brief 
/// @param ptr 
/// @param old_size 
/// @param new_size 
/// @return 
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/**
 * @brief 
 * 
 * @param arr 
 */
void	free_array(char **arr);

/**
 * @brief Read the next line from a file descriptor.
 * @ingroup getline
 */
char	*get_next_line(int fd);

int		ft_stris_ws(const char *s);
int		ft_strtoi(const char *s, int *out);
int		ft_strtod(const char *s, double *out);

#endif /* LIBFT_H */
