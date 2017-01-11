/**
 * \file base64.h
 *
 * Base64 encoding/decoding, header.
 */

/*
 * Copyright (c) 2000 Virtual Unlimited B.V.
 *
 * Author: Bob Deblier <bob@virtualunlimited.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef _BASE64_H
#define _BASE64_H

#include "beecrypt.h"

/**
 * Decode white space character set (default).
 */
/*@-exportlocal@*/
/*@unchecked@*/ /*@observer@*/ /*@null@*/
extern const char * b64decode_whitespace;
/*@=exportlocal@*/
#define B64DECODE_WHITESPACE	" \f\n\r\t\v"

/**
 * Encode 72 characters per line (default).
 */
/*@-exportlocal@*/
/*@unchecked@*/
extern int b64encode_chars_per_line;
/*@=exportlocal@*/
#define B64ENCODE_CHARS_PER_LINE	72

/**
 * Encode end-of-line string (default).
 */
/*@-exportlocal@*/
/*@unchecked@*/ /*@observer@*/ /*@null@*/
extern const char * b64encode_eolstr;
/*@=exportlocal@*/
#define B64ENCODE_EOLSTR	"\n"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Encode chunks of 3 bytes of binary input into 4 bytes of base64 output.
 * @param data		binary data
 * @param ns		no. bytes of data (0 uses strlen(data))
 * @return		(malloc'd) base64 string
 */
BEECRYPTAPI /*@only@*/ /*@null@*/ /*@unused@*/
char * b64encode (const void * data, int ns)
	/*@*/;

/**
 * Encode crc of binary input data into 5 bytes of base64 output.
 * @param data		binary data
 * @param ns		crc of data
 * @return		(malloc'd) base64 string
 */
BEECRYPTAPI /*@only@*/ /*@null@*/ /*@unused@*/
char * b64crc (const void * data, int ns)
	/*@*/;

/**
 * Decode chunks of 4 bytes of base64 input into 3 bytes of binary output.
 * @param s		base64 string
 * @retval datap	address of (malloc'd) binary data
 * @retval lenp		address of no. bytes of binary data
 * @return		0 on success, 1: s == NULL, 2: bad length, 3: bad char
 */
BEECRYPTAPI /*@unused@*/
int b64decode (const char * s, /*@out@*/ void ** datap, /*@out@*/ int *lenp)
	/*@modifies *datap, *lenp @*/;

/**
 */
BEECRYPTAPI /*@only@*/ /*@null@*/ /*@unused@*/
char*		b64enc(const memchunk*);

/**
 */
BEECRYPTAPI /*@only@*/ /*@null@*/ /*@unused@*/
memchunk*	b64dec(const char*);

#ifdef __cplusplus
}
#endif

#endif
