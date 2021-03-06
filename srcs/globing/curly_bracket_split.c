#include "glob.h"
#include "list.h"
#include "libft.h"

static unsigned int	ft_count_words(char *s, char c)
{
	unsigned int	i;
	unsigned int	nb_words;
	int				depth;

	depth = 0;
	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c && depth == 0)
			nb_words++;
		while (s[i] && (!(s[i] == c && depth == 0)))
		{
			if (s[i] == '{' && !ft_is_backslash(s, i))
				depth++;
			if (s[i] == '}' && !ft_is_backslash(s, i))
				depth--;
			i++;
		}
	}
	return (nb_words);
}

static void			ft_malloc_t(char *s, char **t, char c)
{
	unsigned int	i;
	unsigned int	no_words;
	unsigned int	nb_letters;
	int				depth;

	depth = 0;
	i = 0;
	no_words = -1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c && depth == 0)
			no_words++;
		nb_letters = 0;
		while (s[i] && (!(s[i] == c && depth == 0)))
		{
			if ((s[i] == '{' || s[i] == '}') && !ft_is_backslash(s, i))
				(s[i] == '{') ? depth++ : depth--;
			i++;
			nb_letters++;
		}
		if (nb_letters != 0 && depth == 0)
			t[no_words] = ft_strnew(nb_letters);
	}
}

static void			ft_fill_t(char *s, char **t, char c)
{
	unsigned int	i;
	unsigned int	no_words;
	unsigned int	no_letters;
	int				depth;

	depth = 0;
	i = 0;
	no_words = -1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c && depth == 0)
			no_words++;
		no_letters = 0;
		while (s[i] && (!(s[i] == c && depth == 0)))
		{
			if ((s[i] == '{' || s[i] == '}') && !ft_is_backslash(s, i))
				(s[i] == '{') ? depth++ : depth--;
			t[no_words][no_letters] = s[i];
			i++;
			no_letters++;
		}
	}
}

char				**ft_strsplit_coma_bracket(char *s)
{
	unsigned int	nb_words;
	unsigned int	i;
	char			**t;
	char			c;

	c = ',';
	if (!s)
		return (NULL);
	i = 0;
	nb_words = ft_count_words(s, c);
	t = NULL;
	if (!(t = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	t[nb_words] = NULL;
	ft_malloc_t(s, t, c);
	ft_fill_t(s, t, c);
	return (t);
}
