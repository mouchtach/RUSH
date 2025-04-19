/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:27:27 by ymouchta          #+#    #+#             */
/*   Updated: 2025/04/19 20:58:23 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
#  define TABLE_SIZE 10
# endif


typedef struct s_entry {
	char			*word;
	char			*value;
	struct s_entry	*next;
}	t_entry;



char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);

//add_back.c
t_entry	*ft_lstlast(t_entry *lst);
void	ft_lstadd_back(t_entry **lst, t_entry *new);

#endif