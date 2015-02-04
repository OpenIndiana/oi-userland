/*
 * Copyright  The Open Group
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that the
 * above copyright notice appear in all copies and that both that copyright notice
 * and this permission notice appear in supporting documentation.

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE OPEN GROUP
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 * Except as contained in this notice, the name of The Open Group shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in this
 * Software without prior written authorization from The Open Group.

 * Portions also covered by other licenses as noted in the above URL.
 */

/*
 * GB18030
 */

/*
 * GB18030, as implemented in glibc-2.2, is an extension of GBK (= CP936).
 * It adds the following ranges:
 * 1. Two-byte range
 *    0xA2E3, 0xA8BF, 0xA98A..0xA995, 0xFE50..0xFE9F
 * 2. Four-byte range
 *    0x{81..84}{30..39}{81..FE}{30..39}
 *    Most of Unicode plane 1 in Unicode order.
 *    Start: 0x81308130 = 0x0080
 *    End:   0x8431A439 = 0xFFFF
 * 3. Four-byte range
 *    0x{90..E3}{30..39}{81..FE}{30..39}
 *    Unicode plane 2..16 in Unicode order.
 *    Start: 0x90308130 = 0x010000
 *    End:   0xE3329A35 = 0x10FFFF
 */

#include "gb18030ext.h"
#include "gb18030uni.h"

#define sun

static int
gb18030_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  int ret;

#ifdef sun
  int v = (s[0] << 8 | s[1]);
  unsigned char buf[4];

  buf[3] = 0x30 + v%10; v/=10;
  buf[2] = 0x81 + v%126; v/=126;
  buf[1] = 0x30 + v%10; v/=10;
  buf[0] = 0x81 + v;

  /* Code set 2 (remainder of Unicode U+0000..U+FFFF) */
  ret = gb18030uni_mbtowc(conv,pwc,buf,4);
  if (ret != RET_ILSEQ)
    ret = 2;

  return ret;
#else
  /* Code set 0 (ASCII) */
  if (*s < 0x80)
    return ascii_mbtowc(conv,pwc,s,n);

  /* Code set 1 (GBK extended) */
  ret = gbk_mbtowc(conv,pwc,s,n);
  if (ret != RET_ILSEQ)
    return ret;

  ret = gb18030ext_mbtowc(conv,pwc,s,n);
  if (ret != RET_ILSEQ)
    return ret;

  /* Code set 2 (remainder of Unicode U+0000..U+FFFF) */
  ret = gb18030uni_mbtowc(conv,pwc,s,n);
  if (ret != RET_ILSEQ)
    return ret;

  /* Code set 3 (Unicode U+10000..U+10FFFF) */
  {
    unsigned char c1 = s[0];
    if (c1 >= 0x90 && c1 <= 0xe3) {
      if (n >= 2) {
        unsigned char c2 = s[1];
        if (c2 >= 0x30 && c2 <= 0x39) {
          if (n >= 3) {
            unsigned char c3 = s[2];
            if (c3 >= 0x81 && c3 <= 0xfe) {
              if (n >= 4) {
                unsigned char c4 = s[3];
                if (c4 >= 0x30 && c4 <= 0x39) {
                  unsigned int i = (((c1 - 0x90) * 10 + (c2 - 0x30)) * 126 + (c3 - 0x81)) * 10 + (c4 - 0x30);
                  if (i >= 0 && i < 0x100000) {
                    *pwc = (ucs4_t) (0x10000 + i);
                    return 4;
                  }
                }
                return RET_ILSEQ;
              }
              return RET_TOOFEW(0);
            }
            return RET_ILSEQ;
          }
          return RET_TOOFEW(0);
        }
        return RET_ILSEQ;
      }
      return RET_TOOFEW(0);
    }
    return RET_ILSEQ;
  }
#endif
}

static int
gb18030_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  int ret;

#ifndef sun
  /* Code set 0 (ASCII) */
  ret = ascii_wctomb(conv,r,wc,n);
  if (ret != RET_ILUNI)
    return ret;

  /* Code set 1 (GBK extended) */
  ret = gbk_wctomb(conv,r,wc,n);
  if (ret != RET_ILUNI)
    return ret;

  ret = gb18030ext_wctomb(conv,r,wc,n);
  if (ret != RET_ILUNI)
    return ret;
#endif

  /* Code set 2 (remainder of Unicode U+0000..U+FFFF) */
  ret = gb18030uni_wctomb(conv,r,wc,n);
  if (ret != RET_ILSEQ)
#ifdef sun
    {
	int v = 12600 * (r[0] - 0x81) + 1260 * (r[1] - 0x30) + 10 * (r[2] - 0x81) + (r[3] - 0x30);

	r[0] = (v & 0xff00) >> 8;
	r[1] = v & 0xff;
	ret = 2;
    }
#endif
    return ret;

#ifndef sun
  /* Code set 3 (Unicode U+10000..U+10FFFF) */
  if (n >= 4) {
    if (wc >= 0x10000 && wc < 0x110000) {
      unsigned int i = wc - 0x10000;
      r[3] = (i % 10) + 0x30; i = i / 10;
      r[2] = (i % 126) + 0x81; i = i / 126;
      r[1] = (i % 10) + 0x30; i = i / 10;
      r[0] = i + 0x90;
      return 4;
    }
    return RET_ILUNI;
  }
  return RET_TOOSMALL;
#endif
}
