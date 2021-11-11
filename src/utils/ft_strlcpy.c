#include "../../include/builtins.h"
size_t ft_strlcpy(char *dest, const char *src, size_t size)
{
    size_t cnt;
    size_t i;

    cnt = ft_strlen(src);
    i = 0;
    if (size != 0)
    {
        while (src[i] != '\0' && i < (size - 1))
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
    return (cnt);
}