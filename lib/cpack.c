/*
 * Copyright (c) 2012, Victor Goya <phorque@libflm.me>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "cpack.h"

#include <stdlib.h>

char *
vpack (const char *     format,
       va_list          ap)
{
    char *      pack_str;
    char *      pack_str_base;

    size_t      pack_size;

    char        type;
    size_t      format_i;

    pack_size = 0;
    for (format_i = 0; (type = format[format_i]); format_i++) {
        switch (type) {
        case 'd':
            pack_size += sizeof (int);
            break ;
        case 'p':
            pack_size += sizeof (char *);
            break ;
        default:
            goto error;
        }
    }

    pack_str_base = malloc (pack_size * sizeof (*pack_str_base));
    if (pack_str_base == NULL) {
        goto error;
    }

    pack_str = pack_str_base;
    for (format_i = 0; (type = format[format_i]); format_i++) {
        switch (type) {
        case 'd':
            *((int *)pack_str) = va_arg (ap, int);
            pack_str += sizeof (int);
            break ;
        case 'p':
            *((char **)pack_str) = va_arg (ap, char *);
            pack_str += sizeof (char *);
            break ;
        default:
            goto error;
        }
    }

    return (pack_str_base);

  free_pack_str_base:
    free (pack_str_base);
  error:
    return (NULL);
}

char *
pack (const char *      format,
      ...)
{
    char *      pack_str;
    va_list     ap;

    va_start (ap, format);
    pack_str = vpack (format, ap);
    va_end (ap);

    return (pack_str);
}

void
vunpack (char *         pack_str,
         const char *   format,
         va_list        ap)
{
    char *      pack_str_base;

    char        type;
    size_t      format_i;

    pack_str_base = pack_str;
    for (format_i = 0; (type = format[format_i]); format++) {
        switch (type) {
        case 'd':
            *va_arg (ap, int *) = *((int *)pack_str);
            pack_str += sizeof (int);
            break ;
        case 'p':
            *va_arg (ap, char **) = *((char **)pack_str);
            pack_str += sizeof (char *);
            break ;
        }
    }

    free (pack_str_base);
    return ;
}

void
unpack (char *          pack_str,
        const char *    format,
        ...)
{
    va_list     ap;

    va_start (ap, format);
    vunpack (pack_str, format, ap);
    va_end (ap);

    return ;
}
