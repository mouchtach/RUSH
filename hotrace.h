#ifndef HOTRACE_H
# define HOTRACE_H

# include <unistd.h>
# include <stdlib.h>


# define TABLE_SIZE 10007

typedef struct s_entry {
	char			*word;
	char			*value;
	struct s_entry	*next;
}	t_entry;

char			*get_next_line(int fd);



#endif