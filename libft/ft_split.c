/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:31:33 by sniemela          #+#    #+#             */
/*   Updated: 2024/10/29 14:40:27 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**freesubs(char **array, int i)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
	return (0);
}

static size_t	count_subs(char const *s, char c)
{
	size_t	sub_count;
	size_t	inside_substring;

	sub_count = 0;
	inside_substring = 1;
	while (*s)
	{
		if (*s != c && inside_substring == 1)
		{
			sub_count++;
			inside_substring = 0;
		}
		if (*s == c && inside_substring == 0)
			inside_substring = 1;
		s++;
	}
	return (sub_count);
}

static char	*substringfactory(const char *s, char *split, size_t i, size_t len)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		split[j] = s[i - len];
		j++;
		i++;
	}
	split[j] = '\0';
	return (split);
}

static char	**splitthestrings(char const *s, char **split, char c, size_t subs)
{
	size_t	i;
	size_t	string;
	size_t	stringlen;

	i = 0;
	string = 0;
	while (*s != '\0' && string < subs)
	{
		stringlen = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			stringlen++;
			i++;
		}
		split[string] = (char *)malloc(sizeof(char) * (stringlen + 1));
		if (!split[string])
			return (freesubs(split, string));
		split[string] = substringfactory(s, split[string], i, stringlen);
		string++;
	}
	split[string] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	subcount;

	subcount = count_subs(s, c);
	split = (char **)malloc(sizeof(char *) * (subcount + 1));
	if (!split)
		return (NULL);
	split = splitthestrings(s, split, c, subcount);
	return (split);
}
