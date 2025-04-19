#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define HASH_SIZE 65536
#define BUFFER_SIZE 1024

struct entry {
    char *word;
    char *value;
    struct entry *next;
};

struct entry *hash_table[HASH_SIZE] = { NULL };

size_t ft_strlen(const char *s) {
    size_t len = 0;
    while (s[len]) len++;
    return len;
}

char *ft_strchr(const char *s, int c) {
    while (*s) {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    return (c == '\0') ? (char *)s : NULL;
}

char *ft_strdup(const char *s) {
    size_t len = ft_strlen(s);
    char *new = malloc(len + 1);
    if (!new) return NULL;
    for (size_t i = 0; i <= len; i++)
        new[i] = s[i];
    return new;
}

char *ft_strjoin(char const *s1, char const *s2) {
    if (!s1 || !s2) return NULL;
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *new = malloc(len1 + len2 + 1);
    if (!new) return NULL;
    for (size_t i = 0; i < len1; i++)
        new[i] = s1[i];
    for (size_t i = 0; i <= len2; i++)
        new[len1 + i] = s2[i];
    return new;
}

unsigned long hash_func(const char *str) 
{
    unsigned long hash;
    int i = 0 ;

    
    hash = 5381;
    while (str[i])
    {
        hash = ((hash << 5) + hash) + str[i];
        i++;
    }
    return hash;
}

void insert_entry(char *word, char *value) 
{
    unsigned long index;
    
    index = hash_func(word) % HASH_SIZE;
    struct entry *e = malloc(sizeof(struct entry));
    if (!e) 
        return;
    e->word = word;
    e->value = value;
    e->next = hash_table[index];
    hash_table[index] = e;
}

char *lookup_entry(const char *word) {
    unsigned long index = hash_func(word) % HASH_SIZE;
    struct entry *current = hash_table[index];
    while (current) {
        const char *a = current->word, *b = word;
        while (*a || *b) {
            if (*a != *b) break;
            a++; b++;
        }
        if (*a == *b) return current->value;
        current = current->next;
    }
    return NULL;
}

char *read_line(int fd) {
    static char *leftover = NULL;
    char *line = NULL;
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;

    if (leftover) {
        char *newline = ft_strchr(leftover, '\n');
        if (newline) {
            *newline = '\0';
            line = ft_strdup(leftover);
            char *remaining = ft_strdup(newline + 1);
            free(leftover);
            leftover = remaining;
            return line;
        } else {
            line = leftover;
            leftover = NULL;
        }
    }

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE))) {
        if (bytes_read < 0) {
            free(line);
            return NULL;
        }
        buffer[bytes_read] = '\0';
        char *newline = ft_strchr(buffer, '\n');
        if (newline) {
            *newline = '\0';
            char *temp = line ? ft_strjoin(line, buffer) : ft_strdup(buffer);
            free(line);
            line = temp;
            leftover = ft_strdup(newline + 1);
            break;
        } else {
            char *temp = line ? ft_strjoin(line, buffer) : ft_strdup(buffer);
            free(line);
            line = temp;
        }
    }

    return line;
}

int main(void) 
{
    while (1) 
    {
        char *word = read_line(0);
        if (!word) break;
        if (ft_strlen(word) == 0) {
            free(word);
            break;
        }
        char *value = read_line(0);
        if (!value) {
            free(word);
            break;
        }
        insert_entry(word, value);
    }
    char *query;
    while ((query = read_line(0))) {
        char *result = lookup_entry(query);
        if (result) {
            write(1, result, ft_strlen(result));
            write(1, "\n", 1);
        } else {
            write(1, query, ft_strlen(query));
            write(1, ": Not found.\n", 13);
        }
        free(query);
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        struct entry *current = hash_table[i];
        while (current) {
            struct entry *next = current->next;
            free(current->word);
            free(current->value);
            free(current);
            current = next;
        }
    }

    return 0;
}