#include "../../include/builtins.h"
char *ft_strjoin(char const *s1, char const *s2)
{
    int ls1;
    int ls2;
    char *arr;

    ls1 = ft_strlen(s1);
    ls2 = ft_strlen(s2);
    if (!(arr = (char *)malloc(sizeof(char) * (ls1 + ls2))))
        return (0);
    ft_memcpy(arr, s1, ls1);
    ft_memcpy(arr + ls1, s2, ls2);
    arr[ls1 + ls2] = '\0';
    return (arr);
}