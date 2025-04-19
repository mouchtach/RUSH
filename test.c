#include <stdio.h>
#include "get_next_line.h"


int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
int newline(char *str)
{
    int i = 0;
    while (str[i++] == '\n');
    if (str[i] == '\0')
    {
        return (1);
    }
    else
        return (0);
}

int hash_function(char *word)
{
    unsigned long hash;
    int i = 0;

    hash = 5381;
    while (word[i])
    {
        hash = ((hash << 5) + hash) + word[i];
        i++;
    }
    return (hash % TABLE_SIZE);
}
void searching(t_entry **hash_table)
{
    char *word;
    int index;

    while (1)
    {
        word = get_next_line(0);
        if (word == NULL || (newline(word)))
            break;
        index = hash_function(word);
        t_entry *current = hash_table[index];
        while (current)
        {
            if (ft_strcmp(current->word, word) == 0)
            {
                printf("%s\n", current->value);
                break;
            }
            current = current->next;
        }
        if (!current)
            printf("%s: Not found.\n", word);
    }
}

void    store_data(char *word, char *value, t_entry **hash_table)
{
    t_entry *new_entry;
    int index;

    new_entry = malloc(sizeof(t_entry));
    if (!new_entry)
        return;
    new_entry->word = ft_strdup(word);
    new_entry->value = ft_strdup(value);
    new_entry->next = NULL;

    index = hash_function(word);
    if (hash_table[index] == NULL)
        hash_table[index] = new_entry;
    else
        ft_lstadd_back(&new_entry, hash_table[index]);
}

void creat_hash_table(t_entry **hash_table)
{
    int i = 0;
    while (i < TABLE_SIZE)
    {
        hash_table[i] = NULL;
        i++;
    }
}
int main()
{
    t_entry *hash_table[TABLE_SIZE];
    char *word;
    char *value;
    int i = 0;

    creat_hash_table(hash_table);
    while(1)
    {
        word = get_next_line(0);
        if (word == NULL || (newline(word) && i == 1))
            break;
        value = get_next_line(0);
        if (value == NULL)
            break;
        store_data(word, value, hash_table);
        printf("data stored\n");
        i = 1;
    }
    searching(hash_table);
}