/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:49:44 by tguillem          #+#    #+#             */
/*   Updated: 2016/04/14 09:11:28 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define MIN -2147483648
# define MAX 2147483647
# define ABS(x) ((x) < 0 ? (-(x)) : (x))
# define BASE_16 "0123456789ABCDEF"
# include <wchar.h>
# include <string.h>
# include <inttypes.h>
# include "ft_time.h"
# include "ft_printf/ft_printf.h"

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_strdup(const char *s1);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
void				ft_bzero(void *s, size_t n);
char				*ft_memnew(size_t size);
void				*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *s1, const void *s2, size_t n);
void				*ft_memcpy_bwd(void *s1, const void *s2, size_t n);
void				*ft_memmove(void *s1, const void *s2, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isstralnum(char *str);

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *));

size_t				ft_lstsize(t_list *lst);
int					ft_iswhitespace(int c);
int					ft_isblank(int c);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isxdigit(int c);
int					ft_iscntrl(int c);
char				*ft_strtrimch(const char *s, char c);
char				*ft_strtrimcmp(const char *s, int (*f)(int c));

int					ft_max(int x, int y);
int					ft_min(int x, int y);
void				ft_putnbrbase(uintmax_t nbr, char *base);
void				ft_putnbrbase_fd(uintmax_t nbr, char *base, int fd);
size_t				ft_wstrlen(wchar_t *str);
void				ft_putwchar(wchar_t chr);
void				ft_putwchar_fd(wchar_t chr, int fd);
void				ft_putwstr(wchar_t *strr);
void				ft_putwstr_fd(wchar_t *strr, int fd);
int					ft_count_digit(int value, int base);
char				*ft_itoa_base(int value, int base);

typedef struct		s_buff
{
	int				fd;
	char			*buff;
	struct s_buff	*next;
}					t_buff;

int					get_next_line(int const fd, char **line);
int					ft_parse_args(int ac, char **av, void *data,
						int (*compute_options)(void*, char*));
int					ft_usage(char *prg_name, char *usage, char illegal_char);
char				*ft_error_return(char *str, char *code);
char				*ft_get_filename(char *path);
char				**ft_strsplitcmp(char const *s, int (*f)(int c));
int					ft_error_retint(char *str, int code);

typedef struct		s_array
{
	char			*data;
	struct s_array	*next;
}					t_array;

t_array				*array_init(t_array *root, char *str);
t_array				*array_dup(t_array *src);
t_array				*to_array(char **src);
char				**to_char_array(t_array *src);
void				destroy_array(t_array *array);

#endif
