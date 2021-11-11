#include "../../include/builtins.h"
void *ft_memcpy(void *dest, const void *src, size_t n)
{
    char *dtmp;
    const char *stmp;
    
    if (!dest && !src)
        return (0);
    dtmp = dest;
    stmp = src;
    while (n--)
    {
        *dtmp++ = *stmp++;
    }
    return (dest);
}
