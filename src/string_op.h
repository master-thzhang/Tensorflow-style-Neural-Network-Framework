
#ifndef FORWARD_STRING_OP_H
#define FORWARD_STRING_OP_H

#include <cstring>

void strrpl(char *in, char *out, int outlen, const char *src, const char *dst)
{
    char *p = in;
    unsigned int  len = outlen - 1;
    if((NULL == src) || (NULL == dst) || (NULL == in) || (NULL == out))
    {
        return;
    }
    if((strncmp(in, "", 255) == 0) || (strncmp(src, "", 255) == 0))
    {
        return;
    }
    if(outlen <= 0)
    {
        return;
    }
    while((*p != '\0') && (len > 0))
    {
        if(strncmp(p, src, strlen(src)) != 0)
        {
            int n = strlen(out);

            out[n] = *p;
            out[n + 1] = '\0';

            p++;
            len--;
        }
        else
        {
            strncat(out, dst, outlen);
            p += strlen(src);
            len -= strlen(dst);
        }
    }
    return;
}

#endif
