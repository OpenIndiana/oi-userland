/*
 * Copyright © 1996, 2008, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include "Xlibint.h"
#include "XlcGeneric.h"

/* 
 * codesets will derived from XLC_XLOCALE and codesets[0] is 
 * gb18030.2000-1 in XLC_XLOCALE 
 */
#define CS0		codesets[2]	/* Codeset 0 - 7-bit ASCII	*/
#define CS1		codesets[0]	/* Codeset 1 - gb18030.2000-0  	*/
#define CS2		codesets[1]	/* Codeset 2 - gb18030.2000-1  	*/

#define ascii		(codeset->cs_num == 0)
#define gb18030		(codeset->cs_num == 2)

#define	ASCII_CODESET	0
#define GBK2K_CODESET1	1
#define GBK2K_CODESET2	2
#define MAX_CODESETS	3

#define ISASCII(ch)	((unsigned char)(ch) <= 0x7F)

#define GR		0x80	/* Begins right-side (non-ascii) region. */
#define GL		0x7f    /* Ends left-side (ascii) region.        */

#define isleftside(c)	(((c) & GR) ? 0 : 1)
#define isrightside(c)	(! isleftside(c))

typedef unsigned char   Uchar;
typedef unsigned long	Ulong;
typedef unsigned int	Uint;

#define BIT8OFF(c)	((c) & GL)
#define BIT8ON(c)	((c) | GR)

#define ESC    		0x1b

typedef struct _CT_DATA
{
    char *charset;
    char *encode_string;
} CT_DATA;

static CT_DATA default_ct_data[] =
{
    {"ASCII",  "\033(B" },
    {"GB2312",  "\033$(A" },
    {"GB18030-0",  "\033%/2??SUN-GB18030-0" },
    {"GB18030-1",  "\033%/2??SUN-GB18030-1" }
};

static int num_ct_data = sizeof(default_ct_data)/sizeof(CT_DATA);

static char *
get_CT_encode_string(const char *charset)
{
    if (charset) {
	int  i;
	
	for (i=0; i < num_ct_data; ++i)
	    if (strncmp(charset,
			default_ct_data[i].charset,
			strlen(charset)) == 0)
		return default_ct_data[i].encode_string;
    }
  
   return NULL;
}

typedef enum {t_ASCII, t_GB2312, t_GB18030_0, t_GB18030_1, t_NONE} CharSet_Type;

static  CharSet_Type
get_charset_with_encode_string(const char *s)
{
    if (s) {
	int i;

	for (i=0; i < num_ct_data; ++i)
	    if (strncmp(s, default_ct_data[i].encode_string,
			strlen(default_ct_data[i].encode_string)) == 0)
	        return i;
     }

    return t_NONE;
}

static void
twobyte_to_fourbyte(unsigned char *in_buf, unsigned char *out_buf)
{
    int tmp;
   
    tmp=(in_buf[0] << 8) + in_buf[1];
   
    out_buf[3] = 0x30 + tmp%10; tmp/=10;
    out_buf[2] = 0x81 + tmp%126; tmp/=126;
    out_buf[1] = 0x30 + tmp%10; tmp/=10;
    out_buf[0] = 0x81 + tmp;
}

static void
fourbyte_to_twobyte(unsigned char *in_buf, unsigned char *out_buf)
{ 
    int tmp;

    tmp = 12600 * (in_buf[0] - 0x81) + 1260 * (in_buf[1] - 0x30) +
	10 * (in_buf[2] - 0x81) + (in_buf[3] - 0x30);
    out_buf[0] = (tmp & 0xff00) >> 8;
    out_buf[1] = tmp & 0xff;
}

/*
 * In GB2312 range or not
 */
static int
isgb(unsigned char *s)
{
    /* consider the first byte */
    if (s[0] >= 0xA1 && s[0] <= 0xFE && s[1] >= 0xA1 &&
	    s[1] <= 0xFE) {
	return True;
    }else{
	return False;
    }
}

/*
 * In GB18030 2 bytes range or not
 */
static int
isgb18030_2(unsigned char *s)
{
    /* consider the first byte */
    if (s[0] >= 0x81 && s[0] <= 0xfe &&
	    ((s[1] >= 0x40 && s[1] <= 0x7e) ||
	     (s[1] >= 0x80 && s[1] <= 0xfe)))
	return True;
    else
	return False;
}

/*
 * In GB18030 4 bytes range or not
 */
static int isgb18030_4(unsigned char *s)
{
    /* consider the first byte */
    if (s[0] >= 0x81 && s[0] <= 0xfe && s[1] >= 0x30 && s[1] <= 0x39 &&
	    s[2] >= 0x81 && s[2] <= 0xfe && s[3] >= 0x30 && s[3] <= 0x39)
        return True;
    else
	return False;
}

/*
 * multibyte -> charset: codesets[0], codesets[1], codeset[2]
 */
static int
gb18030_mbtocs(
    XlcConv conv,
    XPointer *from,
    int *from_left,
    XPointer *to,
    int *to_left,
    XPointer *args,
    int num_args)
{
    unsigned char *src = (unsigned char *)*from;
    unsigned char *dst = (unsigned char *)*to;
    int		unconv_num = 0;
    int		char_size = 0;
    XLCd	lcd = (XLCd)conv->state;
    CodeSet	*codesets = XLC_GENERIC(lcd, codeset_list);
    int		codeset_num = XLC_GENERIC(lcd, codeset_num);
    XlcCharSet	charset = NULL;

    if (isgb18030_2(src)) {
	if (GBK2K_CODESET1 >= codeset_num)
	    return -1;
	charset = *CS1->charset_list;
	char_size = charset->char_size;

	if (*from_left >= 2 && *to_left >= char_size) {
            *dst++ = *src++;
	    *dst++ = *src++;
	} else {
	    return -1;
	}

    	*from_left -= char_size;
    	*to_left -= char_size;
    } else if (isgb18030_4(src)) {
	unsigned char iconv_buf[6];

	if (GBK2K_CODESET2 >= codeset_num)
	    return -1;

	charset = *CS2->charset_list;
	char_size = charset->char_size;
        fourbyte_to_twobyte(src, iconv_buf);
	if (*from_left >= 4 && *to_left >= char_size) {
            *dst++ = iconv_buf[0];
	    *dst++ = iconv_buf[1];
	    src += 4;
	} else {
	    return -1;
	}

    	*from_left -= 4;
    	*to_left -= char_size;
    } else if (ISASCII(*src)) {
	if (ASCII_CODESET >= codeset_num)
	    return -1;
	charset = *CS0->charset_list;
	char_size = charset->char_size;

	if (*from_left >= char_size && *to_left >= char_size)
	    *dst++ = *src++;
	else
	    return -1;

    	*from_left -= char_size;
    	*to_left -= char_size;
    } else {		/* unknown */
	unconv_num++;
	src++;
        *from_left -= 1;
    }

    *to = (XPointer)dst;
    *from = (XPointer)src;

    if (num_args > 0)
	*((XlcCharSet *) args[0]) = charset;
   
    return unconv_num;
}

static int
gb18030_mbstocs(
    XlcConv conv,
    XPointer *from,
    int *from_left,
    XPointer *to,
    int *to_left,
    XPointer *args,
    int num_args)
{
    unsigned char *src = (unsigned char *)*from;
    unsigned char *dst = (unsigned char *)*to;
    int		char_size = 0;
    int		unconv_num = 0;
    int		flag = 0;
    XLCd	lcd = (XLCd)conv->state;
    CodeSet	*codesets = XLC_GENERIC(lcd, codeset_list);
    int		codeset_num = XLC_GENERIC(lcd, codeset_num);
    XlcCharSet	charset = NULL;

    for (;;) {
	if (isgb18030_2(src)) {
	    if (flag == 0)
		flag = 1;
	    if (flag == 3 || flag == 2 )
		break;
	    if (GBK2K_CODESET1 >= codeset_num)
		return -1;

	    charset = *CS1->charset_list;
	    char_size = charset->char_size;

	    if (*from_left >= char_size && *to_left >= char_size) {
		*dst++ = *src++;
		*dst++ = *src++;
		*to_left -= char_size;
		*from_left -= char_size;
	    }else {
		return -1;
	    }
	} else if (isgb18030_4(src)) {
	    unsigned char iconv_buf[6];

	    if (flag == 0)
		flag = 2;
	    if (flag == 3 || flag == 1)
		break;
	    if (GBK2K_CODESET2 >= codeset_num)
		return -1;

	    charset = *CS2->charset_list;
	    char_size = charset->char_size;
	    fourbyte_to_twobyte(src, iconv_buf);

	    if (*from_left >= 4 && *to_left >= char_size) {
		*dst++ = iconv_buf[0];
		*dst++ = iconv_buf[1];
		src += 4;
		*to_left -= char_size;
		*from_left -= 4;
	    } else {
		return -1;
	    }
	} else if (ISASCII(*src)) {
	    if 	(flag == 0)
		flag = 3;
	    if (flag == 1 || flag ==2 )
		break;
	    if (ASCII_CODESET >= codeset_num)
		return -1;

	    charset = *CS0->charset_list;
	    char_size = charset->char_size;
	    if (*from_left >= char_size && *to_left >= char_size) {
		*dst++ = *src++;
		*to_left -= char_size;
		*from_left -= char_size;
	    } else {
		break;
	    }
	} else{ 		/* unknown */
	    unconv_num++;
	    src++;
	    *from_left -= 1;
	}
	
	if (*from_left <= 0)
	    break;
    }

    *from = (XPointer)src;
    *to = (XPointer)dst;

    if (num_args > 0)
	*((XlcCharSet *) args[0]) = charset;

    return unconv_num;
}

static int
gb18030_wcstocs(
    XlcConv conv,
    XPointer *from,
    int *from_left,
    XPointer *to,
    int *to_left,
    XPointer *args,
    int num_args)
{
    unsigned char *dst = (unsigned char *)*to;
    wchar_t	*src = (wchar_t *)*from;
    int		char_size = 0;
    int		unconv_num = 0;
    int		flag = 0;
    XLCd	lcd = (XLCd)conv->state;
    XlcCharSet	charset = NULL;
    CodeSet	*codesets = XLC_GENERIC(lcd, codeset_list);
    int		codeset_num = XLC_GENERIC(lcd, codeset_num);

    charset = (XlcCharSet)args[0];

    for (;;) {
	wchar_t wch = *src;
	char tmp[32];
	
	wctomb(tmp, wch);
	
	if (isgb18030_2((unsigned char*)tmp)) {
	    if (flag == 0)
		flag = 1;
	    if (flag == 2 || flag == 3)
		break;
	    if (GBK2K_CODESET1 >= codeset_num)
		return -1;
	    
	    charset = *CS1->charset_list;
	    char_size = charset->char_size;
	   
	    if (*from_left > 0 && *to_left >= char_size) {
		*dst++ = tmp[0];
		*dst++ = tmp[1];
		*to_left -= char_size;
	    } else {
		return -1;
	    }
	} else if (isgb18030_4((unsigned char*)tmp)) {
	    unsigned char iconv_buf[6];

	    if (flag == 0)
		flag = 2;
	    if (flag == 1 || flag == 3)
		break;
	    if (GBK2K_CODESET2 >= codeset_num)
		return -1;

	    charset = *CS2->charset_list;
	    char_size = charset->char_size;
	    fourbyte_to_twobyte((unsigned char*)tmp, iconv_buf);

	    if (*from_left > 0 && *to_left >= char_size) {
		*dst++ = iconv_buf[0];
		*dst++ = iconv_buf[1];
		*to_left -= char_size;
	    } else {
		return -1;
	    }
	} else if (ISASCII(tmp[0])) {
	    if (flag == 0)
		flag = 3;
	    if (flag == 1 || flag == 2)
		break;
	    if (ASCII_CODESET >= codeset_num)
		return -1;

	    charset = *CS0->charset_list;
	    char_size = charset->char_size;
	    if (*from_left > 0 && *to_left >= char_size) {
		*dst++ = tmp[0];
		*to_left -= char_size;
	    } else {
		return -1;
	    }
	} else { 	/* unknown */
	    unconv_num++;
	}

	src++;		/* advance one wchar_t */
	(*from_left)--;
	if (*from_left <= 0)
	    break;
    }

    *from = (XPointer)src;
    *to = (XPointer)dst;

    if (num_args > 0)
	*((XlcCharSet *)args[0]) = charset;
   
    return unconv_num;
}

static CodeSet
get_code_set_from_charset(
    XLCd lcd,
    XlcCharSet charset)
{
    CodeSet	*codeset = XLC_GENERIC(lcd, codeset_list);
    XlcCharSet	*charset_list;
    int		codeset_num, num_charsets;

    codeset_num = XLC_GENERIC(lcd, codeset_num);

    for (; codeset_num-- > 0; codeset++) {
	num_charsets = (*codeset)->num_charsets;
	charset_list = (*codeset)->charset_list;

	for (; num_charsets-- > 0; charset_list++)
	    if (*charset_list == charset)
		return *codeset;
    }

    return (CodeSet)NULL;
}

static int
gb18030_cstombs(
    XlcConv conv,
    XPointer *from,
    int *from_left,
    XPointer *to,
    int *to_left,
    XPointer *args,
    int num_args)
{
    unsigned char *src = (unsigned char *)*from;
    unsigned char *dst = (unsigned char *)*to;
    int		char_size = 0;
    int		unconv_num = 0;
    XLCd	lcd = (XLCd)conv->state;
    XlcCharSet	charset = (XlcCharSet) args[0];
    CodeSet	codeset;

    codeset = get_code_set_from_charset(lcd, charset);
    if (codeset == NULL)
	return -1;

    for (;;) {
	if (codeset->wc_encoding==0x5e84) {		/* GB18030-1 */
	    char_size = 2;
	   
	    if (*from_left >= 2 && *to_left >= 4) {
		unsigned char iconv_buf[6];
	
		twobyte_to_fourbyte(src, iconv_buf);
		*dst++ = iconv_buf[0];
		*dst++ = iconv_buf[1];
		*dst++ = iconv_buf[2];
		*dst++ = iconv_buf[3];
		*to_left -= 4;
	    } else {
		return -1;
	    }
	} else if (isgb18030_2((unsigned char*)src)) { 	/*2 bytes character*/
	    char_size = 2;

	    if (*from_left >= 2 && *to_left >= 2) {
		*dst++ = *src++;
		*dst++ = *src++;
		*to_left -= 2;
	    } else {
		return -1;
	    }
	} else if (ISASCII(*src)) { 	/*ASCII character*/
	    char_size = 1;

	    if (*from_left >= 1 && *to_left >= 1) {
		*dst++ = *src++;
		*to_left -= 1;
	    } else {
		return -1;
	    }
	} else { 			/* unknown */
	    unconv_num++;
	    src++;
	    char_size = 1;
	}

	*from_left -= char_size;;
	if (*from_left <= 0)
	    break;
    }

    *from = (XPointer)src;
    *to = (XPointer )dst;

    if (num_args > 0)
	*((XlcCharSet *) args[0]) = charset;
   
    return unconv_num;
}

static int
gb18030_cstowcs(
    XlcConv conv,
    XPointer *from,
    int *from_left,
    XPointer *to,
    int *to_left,
    XPointer *args,
    int num_args)
{
    XPointer	outbufptr, outbufptr_save;
    int		to_left_save = *to_left;
    wchar_t	*pwc = (wchar_t *) *to;
    int		rtn, rtn_1;

    outbufptr = (XPointer) Xmalloc(*to_left * 4);
    outbufptr_save = outbufptr;

    rtn = gb18030_cstombs(conv, from, from_left,
	    &outbufptr, to_left,
	    args, num_args);
    *outbufptr='\0';

    rtn_1 = mbstowcs(pwc, outbufptr_save, (to_left_save - *to_left));
    
    Xfree(outbufptr_save);

    *to_left = to_left_save - rtn_1;
    *to = *to+ rtn_1 * sizeof(wchar_t);

    return rtn;
}


/*
 * In gb18030 locale, we only consider the following possibilities
 * all other ct formats are ignored, keep looping until end of buffer
 * 	ASCII
 * 	GB2312
 * 	GB18030-0
 * 	GB18030-1
 */
static int
gb18030_ctstombs(
    XlcConv conv,
    XPointer *from,
    int *from_left,
    XPointer *to,
    int *to_left,
    XPointer *args,
    int num_args)
{
    unsigned char *inbufptr = (unsigned char *)*from;
    unsigned char *outbufptr = (unsigned char *)*to;
    int unconv_num = 0;
    int i, j;
    int save_outbuf = True;
    CharSet_Type charset_type;
	 
    /*
     * If outbufptr is NULL, doen't save output, but just counts
     * a length to hold the output.
     */
    if (outbufptr == NULL)
	save_outbuf = False;
    
    i = 0;
    j = 0;

    while (i < *from_left) {
	if (inbufptr[i] == ESC) { 	/* got an escape */
	    charset_type = get_charset_with_encode_string(
		    (const char *)inbufptr + i);

	    switch (charset_type) {
	    case t_ASCII:
		i += strlen(default_ct_data[charset_type].encode_string);

		for (;;) {
		    if (i >= *from_left) {	/* end of from buffer */
			goto FINISHED;
		    }
		   
		    if ((inbufptr[i] == 0x0a || inbufptr[i] == 0x09 ||
			 inbufptr[i] >= 0x20) && ISASCII(inbufptr[i])) {
			if (*to_left < 1) {  	/* end of to buffer */
			    goto FINISHED;	
			}
			
			if (save_outbuf == True)
			    outbufptr[j++] = inbufptr[i];

			(*to_left)--;
			++i;
		    } else {
			break;
		    }
		}
		break;
	   
	    case t_GB2312:
		i += strlen(default_ct_data[charset_type].encode_string);

		for (;;) {
		    unsigned char iconv_buf[3];

		    if (i >= *from_left) {  /* end of from buffer */
			goto FINISHED;
		    }
		   
		    iconv_buf[0] = (inbufptr[i] & 0x7f) | 0x80;
		    iconv_buf[1] = (inbufptr[i + 1] & 0x7f) | 0x80;
		   
		    if (isgb(iconv_buf)) {
			if (*to_left < 2 || *from_left < 2) {
			    goto FINISHED;
			}
			
			if (save_outbuf == True) {
			    outbufptr[j++] = iconv_buf[0];
			    outbufptr[j++] = iconv_buf[1];
			}
			
			*to_left -= 2;
			i = i + 2;
		    } else {
			break;
		    }
		}
		break;
	   
	    case t_GB18030_0:
		i += strlen(default_ct_data[charset_type].encode_string);
		
		for (;;) {
		    if (i >= *from_left) {  	/* end of from buffer */
			goto FINISHED;	
		    }
		   
		    if (isgb18030_2(inbufptr + i)) {
			if (*to_left < 2 || *from_left < 2) {
			    goto FINISHED;
			}
			
			if (save_outbuf == True) {
			    outbufptr[j++] = inbufptr[i];
			    outbufptr[j++] = inbufptr[i + 1];
			}
			
			*to_left -= 2;
			i = i + 2;
		    } else {
			break;
		    }
		}
		break;
	   
	    case t_GB18030_1: 			/* gb18030.2000-1 character */
		i += strlen(default_ct_data[charset_type].encode_string);
		
		for (;;) {
		    if (i >= *from_left) {  	/* end of from buffer */
			goto FINISHED;
		    }

		    if (isgb18030_4(inbufptr + i)) {
			if (*to_left < 4 || *from_left < 4) {
			    goto FINISHED;
			}
			
			if (save_outbuf == True) {
			    outbufptr[j++] = inbufptr[i] & 0xff;
			    outbufptr[j++] = inbufptr[i+1] & 0xff;
			    outbufptr[j++] = inbufptr[i+2] & 0xff;
			    outbufptr[j++] = inbufptr[i+3] & 0xff;
			}
			
			*to_left -= 4;
			i = i + 4;
		    } else {
			break;
		    }
		}
		break;
	   
	    case t_NONE:
		i++; 		/* encounter unknown escape sequence */
		unconv_num++;
		break;
	    }
	} else if ((inbufptr[i] == 0x0a || inbufptr[i] == 0x09 ||
		    inbufptr[i] >= 0x20) && ISASCII(inbufptr[i])) {
	    /* Process default CT G0 ascii character */
	    if (*to_left < 1) {
		goto FINISHED;
	    }
	   
	    if (save_outbuf == True)
		outbufptr[j++] = inbufptr[i];
	   
	    i++;
	    *to_left -= 1;
	} else { 		/* unknown character */
	    i++;
	    unconv_num++;
	}
    }

FINISHED:
    *from = (XPointer)(inbufptr + i);
    *to = (XPointer)(outbufptr + j);
    if (i >= *from_left)
	*from_left = 0;
    else
	*from_left -= i;

    return (unconv_num);
}

static int
gb18030_ctstowcs(
    XlcConv conv,
    XPointer *from,
    int *from_left,
    XPointer *to,
    int *to_left,
    XPointer *args,
    int num_args)
{
    XPointer	outbufptr, outbufptr_save;
    int		to_left_save = *to_left;
    wchar_t 	*pwc = (wchar_t *) *to;
    int		rtn, rtn_1;


    outbufptr = (XPointer) Xmalloc(*to_left * 4); /* 100 safty tolerence */
    outbufptr_save = outbufptr;

    rtn = gb18030_ctstombs(conv,
	    from,
	    from_left,
	    &outbufptr,
	    to_left,
	    args,
	    num_args);

    *outbufptr='\0';

    rtn_1 = mbstowcs(pwc, outbufptr_save, (to_left_save - *to_left));

    Xfree(outbufptr_save);

    *to_left = to_left_save - rtn_1;
    *to = *to + rtn_1 * sizeof(wchar_t);

    return rtn;
}

/*
 * The mbs is GB18030 code, must be converted to euc code,
 * then pack to ct format.
 */
static int
gb18030_mbstocts(
    XlcConv conv,
    XPointer *from,
    int *from_left,
    XPointer *to,
    int *to_left,
    XPointer *args,
    int num_args)
{
    unsigned char *inbufptr = (unsigned char *)*from;
    unsigned char *outbufptr = (unsigned char *)*to;
    int 	unconv_num = 0;
    int 	flag = 0, j = 0, i = 0;
    int  	encode_string_len;
    char 	*encode_string;

    while (i < *from_left && j < *to_left)  {
	if (isgb(&inbufptr[i])) {	/* GB2312 character */
	    if (flag == 0 || flag != 2) {
		encode_string = get_CT_encode_string("GB2312");
		if (! encode_string )
		    return -1;

		encode_string_len = strlen(encode_string);
		if (j + encode_string_len + 2 >= *to_left)
		    break;
		
		strncpy((char *)outbufptr+j, encode_string, encode_string_len);
		j += encode_string_len;
		flag = 2;
	    }
       
	    if (j + 2 >= *to_left)
		break;

	    outbufptr[j++] = inbufptr[i++] & 0x7f;
	    outbufptr[j++] = inbufptr[i++] & 0x7f;
	} else if (isgb18030_2(&inbufptr[i])) {		/* 2 bytes GB 18030 */
	    if (flag == 0 || flag != 4) {
		encode_string = get_CT_encode_string("GB18030-0");
		if (! encode_string )
		    return -1;
		
		encode_string_len = strlen(encode_string);
		if (j + encode_string_len + 2 >= *to_left)
		    break;
	
		strncpy((char *)outbufptr+j, encode_string, encode_string_len);
		j += encode_string_len;
		flag = 4;
	    }

	    if (j + 2 >= *to_left)
		break;

	    outbufptr[j++] = inbufptr[i++] & 0xff;
	    outbufptr[j++] = inbufptr[i++] & 0xff;
	} else if (isgb18030_4(&inbufptr[i])) {		/* 4 bytes GB18030 */
	    if (flag == 0 || flag != 5) {
		encode_string = get_CT_encode_string("GB18030-1");
		if (!encode_string)
		    return -1;
		encode_string_len = strlen(encode_string);
		
		if (j + encode_string_len + 4 >= *to_left)
		    break;

		strncpy((char *)outbufptr+j, encode_string, encode_string_len);
		j += encode_string_len;
		flag = 5;
	    }

	    if (j + 4 >= *to_left)
		break;

	    outbufptr[j++] = inbufptr[i++];
	    outbufptr[j++] = inbufptr[i++];
	    outbufptr[j++] = inbufptr[i++];
	    outbufptr[j++] = inbufptr[i++];
	} else if (ISASCII(inbufptr[i])) {	/* ASCII */
	    if (flag == 0 || flag != 3) {
		encode_string = get_CT_encode_string("ASCII");
		if (!encode_string )
		    return -1;
		
		encode_string_len = strlen(encode_string);
		if (j + encode_string_len + 1 >= *to_left)
		    break;
	
		strncpy((char *)outbufptr+j, encode_string, encode_string_len);
		j += encode_string_len;
		flag = 3;
	    }
	   
	    if (j + 1 >= *to_left)
		break;

	    outbufptr[j++] = inbufptr[i++];
	} else{
	    i++; 		/* Skip this byte */
	    unconv_num++; 	/* Count this as an unconverted byte */
	}
    }

    *from = (XPointer)&inbufptr[i];
    *to = (XPointer)&outbufptr[j];
    *from_left = *from_left - i;
    *to_left = *to_left - j;
   
    return unconv_num;
}

static int
gb18030_wcstocts(
    XlcConv conv,
    XPointer *from,
    int *from_left,
    XPointer *to,
    int *to_left,
    XPointer *args,
    int num_args)
{

    unsigned char inbufptr[10];
    unsigned char *outbufptr = (unsigned char *)*to;
    wchar_t	*pwc = (wchar_t *)*from;
    int		unconv_num = 0;
    int		flag,j,i,k;
    char	*encode_string;
    int		encode_string_len;	    
  
    i = k = j = 0;
    flag = 0;

    while (k < *from_left) {
	if (wctomb((char *)inbufptr, pwc[k++]) == -1)
	    return (-1);

	i=0;
	
	if (isgb(&inbufptr[i])) {		/* GB2312 */
	    if (flag == 0 || flag != 1) {
		encode_string = get_CT_encode_string("GB2312");
		if (! encode_string)
		    return (-1);

		encode_string_len = strlen(encode_string);
		if (j + encode_string_len + 2 >= *to_left)
		    break;
		
		strncpy((char *)outbufptr+j, encode_string, encode_string_len);
		j += encode_string_len;
		flag = 1;
	    }

	    if (j + 2 >= *to_left)
		break;

	    outbufptr[j++] = inbufptr[i++];
	    outbufptr[j++] = inbufptr[i++];
	} else if (isgb18030_2(&inbufptr[i])) {
	    if (flag == 0 || flag != 2) {
		encode_string = get_CT_encode_string("GB18030-0");
		if (! encode_string)
		    return -1;
		
		encode_string_len = strlen(encode_string);
		if (j + encode_string_len + 2 >= *to_left)
		    break;
		
		strncpy((char *)outbufptr+j, encode_string, encode_string_len);
		j += encode_string_len;
		flag = 2;
	    }

	    if (j + 2 >= *to_left)
		break;

	    outbufptr[j++] = inbufptr[i++];
	    outbufptr[j++] = inbufptr[i++];
	} else if (isgb18030_4(&inbufptr[i])) {
	    if (flag == 0 || flag != 6) {
		encode_string = get_CT_encode_string("GB18030-1");
		if (! encode_string)
		    return -1;
		
		encode_string_len = strlen(encode_string);
		if (j + encode_string_len + 4 >= *to_left)
		    break;
	   
		strncpy((char *)outbufptr+j, encode_string, encode_string_len);
		j += encode_string_len;
		flag = 6;
	    }

	    if (j + 4 >= *to_left)
		break;

	    outbufptr[j++] = inbufptr[i++];
	    outbufptr[j++] = inbufptr[i++];
	    outbufptr[j++] = inbufptr[i++];
	    outbufptr[j++] = inbufptr[i++];
	} else if (ISASCII(inbufptr[i])) {
	    if (flag == 0 || flag != 3) {
		encode_string = get_CT_encode_string("ASCII");
		if (! encode_string)
		    return -1;
		
		encode_string_len = strlen(encode_string);
		if (j + encode_string_len + 1 >= *to_left)
		    break;
		
		strncpy((char *)outbufptr+j, encode_string, encode_string_len);
		j += encode_string_len;
		
		flag = 3;
	    }
	   
	    outbufptr[j++] = inbufptr[i++];
	} else {
	    unconv_num++;
	}
    }
   
    *from = (XPointer)&pwc[k];
    *to = (XPointer)&outbufptr[j];
    *from_left = *from_left - k;
    *to_left = *to_left - j;

    return unconv_num;
}

static int
gb18030_mbstowcs(
    XlcConv conv,
    XPointer *from,
    int *from_left,
    XPointer *to,
    int *to_left,
    XPointer *args,
    int num_args)
{
    char *src = *((char **) from);
    wchar_t *dst = *((wchar_t **) to);
    int src_left = *from_left;
    int dst_left = *to_left;
    int mblen, unconv_num = 0;

    while (src_left > 0 && dst_left > 0) {
        mblen = mbtowc(dst, src, src_left);

        if (mblen > 0) {
            src += mblen;
            src_left -= mblen;
            dst++;
            dst_left--;
        } else {
            src++;
            src_left--;
	    if (mblen < 0) {
		unconv_num++;
	    } else {
		*dst++ = L'\0';
            	dst_left--;
	    }
        }
    }

    *from = (XPointer) src;
    *to = (XPointer) dst;
    *from_left = src_left;
    *to_left = dst_left;
    return unconv_num;
}

static int
gb18030_wcstombs(
    XlcConv conv,
    XPointer *from,
    int *from_left,
    XPointer *to,
    int *to_left,
    XPointer *args,
    int num_args)
{
    wchar_t *src = *((wchar_t **)from);
    char *dst = *((char **) to);
    char buf[MB_CUR_MAX];
    int src_left = *from_left;
    int dst_left = *to_left;
    int mblen, unconv_num = 0;

    while (src_left > 0) {
        mblen = wctomb(buf, *src);

	if (dst_left < mblen) {
	    break;
	}

        src++;
        src_left--;

	if (mblen < 0) {
	    unconv_num++;
	    continue;
	}

        dst_left -= mblen;
	for (int i = 0; i < mblen; i++) {
	    *dst++ = buf[i];
	}
    }

    *from = (XPointer) src;
    *to = (XPointer) dst;
    *from_left = src_left;
    *to_left = dst_left;
    return unconv_num;
}


static void
close_converter(XlcConv conv)
{
    Xfree((char *) conv);
}

static XlcConv
create_conv(
    XLCd lcd,
    XlcConvMethods methods)
{
    XlcConv conv;

    conv = (XlcConv) Xmalloc(sizeof(XlcConvRec));
    if (conv == NULL)
	return (XlcConv) NULL;
   
    conv->methods = methods;
    conv->state = (XPointer) lcd;
    return conv;
}


enum { MBSTOCS, WCSTOCS, MBTOCS, CSTOMBS, CSTOWCS, MBSTOCTS, CTSTOMBS,
       CTSTOWCS, WCSTOCTS, MBSTOWCS, WCSTOMBS, STRTOMBS };

static XlcConvMethodsRec conv_methods[] = {
    {close_converter, gb18030_mbstocs,  NULL },
    {close_converter, gb18030_wcstocs,  NULL },
    {close_converter, gb18030_mbtocs,   NULL },
    {close_converter, gb18030_cstombs,  NULL },
    {close_converter, gb18030_cstowcs,  NULL },
    {close_converter, gb18030_mbstocts, NULL },
    {close_converter, gb18030_ctstombs, NULL },
    {close_converter, gb18030_ctstowcs, NULL },
    {close_converter, gb18030_wcstocts, NULL },
    {close_converter, gb18030_mbstowcs, NULL },
    {close_converter, gb18030_wcstombs, NULL },

};


static XlcConv
open_mbstocs(
    XLCd from_lcd,
    const char *from_type,
    XLCd to_lcd,
    const char *to_type)
{
    return create_conv(from_lcd, &conv_methods[MBSTOCS]);
}

static XlcConv
open_wcstocs(
    XLCd from_lcd,
    const char *from_type,
    XLCd to_lcd,
    const char *to_type)
{
    return create_conv(from_lcd, &conv_methods[WCSTOCS]);
}

static XlcConv
open_mbtocs(
    XLCd from_lcd,
    const char *from_type,
    XLCd to_lcd,
    const char *to_type)
{
    return create_conv(from_lcd, &conv_methods[MBTOCS]);
}

static XlcConv
open_cstombs(
    XLCd from_lcd,
    const char *from_type,
    XLCd to_lcd,
    const char *to_type)
{
    return create_conv(from_lcd, &conv_methods[CSTOMBS]);
}

static XlcConv
open_cstowcs(
    XLCd from_lcd,
    const char *from_type,
    XLCd to_lcd,
    const char *to_type)
{
    return create_conv(from_lcd, &conv_methods[CSTOWCS]);
}

static XlcConv
open_wcstocts(
    XLCd from_lcd,
    const char *from_type,
    XLCd to_lcd,
    const char *to_type)
{
    return create_conv(from_lcd, &conv_methods[WCSTOCTS]);
}

static XlcConv
open_mbstocts(
    XLCd from_lcd,
    const char *from_type,
    XLCd to_lcd,
    const char *to_type)
{
    return create_conv(from_lcd, &conv_methods[MBSTOCTS]);
}

static XlcConv
open_ctstombs(
    XLCd from_lcd,
    const char *from_type,
    XLCd to_lcd,
    const char *to_type)
{
    return create_conv(from_lcd, &conv_methods[CTSTOMBS]);
}

static XlcConv
open_ctstowcs(
    XLCd from_lcd,
    const char *from_type,
    XLCd to_lcd,
    const char *to_type)
{
    return create_conv(from_lcd, &conv_methods[CTSTOWCS]);
}

static XlcConv
open_mbstowcs(
    XLCd from_lcd,
    const char *from_type,
    XLCd to_lcd,
    const char *to_type)
{
    return create_conv(from_lcd, &conv_methods[MBSTOWCS]);
}

static XlcConv
open_wcstombs(
    XLCd from_lcd,
    const char *from_type,
    XLCd to_lcd,
    const char *to_type)
{
    return create_conv(from_lcd, &conv_methods[WCSTOMBS]);
}

XLCd
_XlcGb18030Loader(const char *name)
{
    XLCd lcd;

    lcd = _XlcCreateLC(name, _XlcGenericMethods);
    if (lcd == NULL)
	return lcd;

    if ((_XlcNCompareISOLatin1(XLC_PUBLIC_PART(lcd)->codeset, "gb18030", 7))) {
	_XlcDestroyLC(lcd);
	return (XLCd) NULL;
    }

    /* MB/WC  <->  CS */
    _XlcSetConverter(lcd, XlcNMultiByte,  lcd, XlcNCharSet,   open_mbstocs);
    _XlcSetConverter(lcd, XlcNWideChar,   lcd, XlcNCharSet,   open_wcstocs);
    _XlcSetConverter(lcd, XlcNCharSet,    lcd, XlcNMultiByte, open_cstombs);
    _XlcSetConverter(lcd, XlcNCharSet,    lcd, XlcNWideChar,  open_cstowcs);

    _XlcSetConverter(lcd, XlcNMultiByte,  lcd, XlcNChar,      open_mbtocs);

    /* MB/WC  <->  CT */
    _XlcSetConverter(lcd, XlcNMultiByte, lcd, XlcNCompoundText, open_mbstocts);
    _XlcSetConverter(lcd, XlcNCompoundText, lcd, XlcNMultiByte, open_ctstombs);
    _XlcSetConverter(lcd, XlcNCompoundText, lcd, XlcNWideChar, open_ctstowcs);
    _XlcSetConverter(lcd, XlcNWideChar, lcd, XlcNCompoundText, open_wcstocts);

    /* MB <-> WC */
    _XlcSetConverter(lcd, XlcNMultiByte, lcd, XlcNWideChar,     open_mbstowcs);
    _XlcSetConverter(lcd, XlcNWideChar,  lcd, XlcNMultiByte,    open_wcstombs);


    _XlcAddUtf8Converters(lcd);

    return lcd;
}

