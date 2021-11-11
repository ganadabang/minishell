#include "../../include/builtins.h"
char *ft_strdup(const char *str)
{
    char *arr;
    
    if (!(arr = malloc(sizeof(char) * (ft_strlen(str) + 1))))
        return (0);
    ft_memcpy(arr, str, ft_strlen(str) + 1);
    return (arr);
}