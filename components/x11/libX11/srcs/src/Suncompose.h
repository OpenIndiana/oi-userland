/*
 * Copyright (c) 1986, 2013, Oracle and/or its affiliates. All rights reserved.
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

#ifndef _SUNCOMPOSE_H
#define _SUNCOMPOSE_H

/*
 * Suncompose.h -- Compose Key Sequence Table
 * 
 * The idea here is to create a simple index into a table of
 * compose key sequences.  The purpose is to provide a fast
 * lookup mechanism using as little space as possible (while
 * still using a table of triplets).
 *
 * For reference, here is the set of all composable characters:
 * SP !\"\'*+,-./01234:<>?ACDEHILNOPRSTUXY\\^_`acdehilnoprstuxy|~
 *
 * if ascii_char[i] is not composable,
 *	compose_map[i] is -1
 * else
 * 	if ascii_char[i] appears as a first char in compose_table,
 *		compose_map[i] is the index of it's first appearance
 *	else
 *		compose_map[i] is 112	(end of table)
 */

#define ASCII_SET_SIZE	128

const char compose_map[ASCII_SET_SIZE] = {
	 -1,	/* 000 (^@) */
	 -1,	/* 001 (^A) */
	 -1,	/* 002 (^B) */
	 -1,	/* 003 (^C) */
	 -1,	/* 004 (^D) */
	 -1,	/* 005 (^E) */
	 -1,	/* 006 (^F) */
	 -1,	/* 007 (^G) */
	 -1,	/* 008 (^H) */
	 -1,	/* 009 (^I) */
	 -1,	/* 010 (^J) */
	 -1,	/* 011 (^K) */
	 -1,	/* 012 (^L) */
	 -1,	/* 013 (^M) */
	 -1,	/* 014 (^N) */
	 -1,	/* 015 (^O) */
	 -1,	/* 016 (^P) */
	 -1,	/* 017 (^Q) */
	 -1,	/* 018 (^R) */
	 -1,	/* 019 (^S) */
	 -1,	/* 020 (^T) */
	 -1,	/* 021 (^U) */
	 -1,	/* 022 (^V) */
	 -1,	/* 023 (^W) */
	 -1,	/* 024 (^X) */
	 -1,	/* 025 (^Y) */
	 -1,	/* 026 (^Z) */
	 -1,	/* 027 (^[) */
	 -1,	/* 028 (^\) */
	 -1,	/* 029 (^]) */
	 -1,	/* 030 (^^) */
	 -1,	/* 031 (^_) */
	  0,	/* 032 (SP) */
	  1,	/* 033 (!) */
	  4,	/* 034 (") */
	 -1,	/* 035 (#) */
	 -1,	/* 036 ($) */
	 -1,	/* 037 (%) */
	 -1,	/* 038 (&) */
	 16,	/* 039 (') */
	 -1,	/* 040 (() */
	 -1,	/* 041 ()) */
	 28,	/* 042 (*) */
	 31,	/* 043 (+) */
	 32,	/* 044 (,) */
	 36,	/* 045 (-) */
	 48,	/* 046 (.) */
	 49,	/* 047 (/) */
	 54,	/* 048 (0) */
	 57,	/* 049 (1) */
	 60,	/* 050 (2) */
	 61,	/* 051 (3) */
	112,	/* 052 (4) */
	 -1,	/* 053 (5) */
	 -1,	/* 054 (6) */
	 -1,	/* 055 (7) */
	 -1,	/* 056 (8) */
	 -1,	/* 057 (9) */
	112,	/* 058 (:) */
	 -1,	/* 059 (;) */
	 63,	/* 060 (<) */
	 -1,	/* 061 (=) */
	 64,	/* 062 (>) */
	 65,	/* 063 (?) */
	 -1,	/* 064 (@) */
	 66,	/* 065 (A) */
	 -1,	/* 066 (B) */
	 70,	/* 067 (C) */
	112,	/* 068 (D) */
	 71,	/* 069 (E) */
	 -1,	/* 070 (F) */
	 -1,	/* 071 (G) */
	 73,	/* 072 (H) */
	 74,	/* 073 (I) */
	 -1,	/* 074 (J) */
	 -1,	/* 075 (K) */
	112,	/* 076 (L) */
	 -1,	/* 077 (M) */
	 76,	/* 078 (N) */
	 77,	/* 079 (O) */
	 84,	/* 080 (P) */
	 -1,	/* 081 (Q) */
	112,	/* 082 (R) */
	112,	/* 083 (S) */
	112,	/* 084 (T) */
	 85,	/* 085 (U) */
	 -1,	/* 086 (V) */
	 -1,	/* 087 (W) */
	112,	/* 088 (X) */
	112,	/* 089 (Y) */
	 -1,	/* 090 (Z) */
	 -1,	/* 091 ([) */
	 87,	/* 092 (\) */
	 -1,	/* 093 (]) */
	 88,	/* 094 (^) */
	 93,	/* 095 (_) */
	 94,	/* 096 (`) */
	 99,	/* 097 (a) */
	 -1,	/* 098 (b) */
	101,	/* 099 (c) */
	112,	/* 100 (d) */
	112,	/* 101 (e) */
	 -1,	/* 102 (f) */
	 -1,	/* 103 (g) */
	102,	/* 104 (h) */
	112,	/* 105 (i) */
	 -1,	/* 106 (j) */
	 -1,	/* 107 (k) */
	112,	/* 108 (l) */
	 -1,	/* 109 (m) */
	103,	/* 110 (n) */
	104,	/* 111 (o) */
	108,	/* 112 (p) */
	 -1,	/* 113 (q) */
	112,	/* 114 (r) */
	109,	/* 115 (s) */
	112,	/* 116 (t) */
	112,	/* 117 (u) */
	 -1,	/* 118 (v) */
	 -1,	/* 119 (w) */
	110,	/* 120 (x) */
	112,	/* 121 (y) */
	 -1,	/* 122 (z) */
	 -1,	/* 123 ({) */
	111,	/* 124 (|) */
	 -1,	/* 125 (}) */
	112,	/* 126 (~) */
	 -1,	/* 127 (DEL) */
};

typedef struct _ComposeTableEntry {
	unsigned char	first;
	unsigned char	second;
	unsigned char	result;
} ComposeTableEntry;

/*
 * IMPORTANT NOTE:  This table MUST be kept in proper sorted order:
 * 	The first and second characters in each entry must be in ASCII
 *	    collating sequence (left to right).
 *	The table must be in ASCII collating sequence by first character
 *	    (top to bottom).
 */

/* COMPOSE + first character + second character => ISO character */

const ComposeTableEntry compose_table[] = {

	{' ', ' ', 0xA0},	/* 000 */	/* NBSP (non-breaking space) */
	{'!', '!', 0xA1},	/* 001 */	/* inverted ! */
	{'!', 'P', 0xB6},	/* 002 */	/* paragraph mark */
	{'!', 'p', 0xB6},	/* 003 */	/* paragraph mark */
	{'"', '"', 0xA8},	/* 004 */	/* diaresis */
	{'"', 'A', 0xC4},	/* 005 */	/* A with diaresis */
	{'"', 'E', 0xCB},	/* 006 */	/* E with diaresis */
	{'"', 'I', 0xCF},	/* 007 */	/* I with diaresis */
	{'"', 'O', 0xD6},	/* 008 */	/* O with diaresis */
	{'"', 'U', 0xDC},	/* 009 */	/* U with diaresis */
	{'"', 'a', 0xE4},	/* 010 */	/* a with diaresis */
	{'"', 'e', 0xEB},	/* 011 */	/* e with diaresis */
	{'"', 'i', 0xEF},	/* 012 */	/* i with diaresis */
	{'"', 'o', 0xF6},	/* 013 */	/* o with diaresis */
	{'"', 'u', 0xFC},	/* 014 */	/* u with diaresis */
	{'"', 'y', 0xFF},	/* 015 */	/* y with diaresis */
	{'\'','A', 0xC1},	/* 016 */	/* A with acute accent */
	{'\'','E', 0xC9},	/* 017 */	/* E with acute accent */
	{'\'','I', 0xCD},	/* 018 */	/* I with acute accent */
	{'\'','O', 0xD3},	/* 019 */	/* O with acute accent */
	{'\'','U', 0xDA},	/* 020 */	/* U with acute accent */
	{'\'','Y', 0xDD},	/* 021 */	/* Y with acute accent */
	{'\'','a', 0xE1},	/* 022 */	/* a with acute accent */
	{'\'','e', 0xE9},	/* 023 */	/* e with acute accent */
	{'\'','i', 0xED},	/* 024 */	/* i with acute accent */
	{'\'','o', 0xF3},	/* 025 */	/* o with acute accent */
	{'\'','u', 0xFA},	/* 026 */	/* u with acute accent */
	{'\'','y', 0xFD},	/* 027 */	/* y with acute accent */
	{'*', 'A', 0xC5},	/* 028 */	/* A with ring */
	{'*', '^', 0xB0},	/* 029 */	/* degree */
	{'*', 'a', 0xE5},	/* 030 */	/* a with ring */
	{'+', '-', 0xB1},	/* 031 */	/* plus/minus */
	{',', ',', 0xB8},	/* 032 */	/* cedilla */
	{',', '-', 0xAC},	/* 033 */	/* not sign */
	{',', 'C', 0xC7},	/* 034 */	/* C with cedilla */
	{',', 'c', 0xE7},	/* 035 */	/* c with cedilla */
	{'-', '-', 0xAD},	/* 036 */	/* soft hyphen */
	{'-', ':', 0xF7},	/* 037 */	/* division sign */
	{'-', 'A', 0xAA},	/* 038 */	/* feminine superior numeral */
	{'-', 'D', 0xD0},	/* 039 */	/* Upper-case eth */
	{'-', 'L', 0xA3},	/* 040 */	/* pounds sterling */
	{'-', 'Y', 0xA5},	/* 041 */	/* yen */
	{'-', '^', 0xAF},	/* 042 */	/* macron */
	{'-', 'a', 0xAA},	/* 043 */	/* feminine superior numeral */
	{'-', 'd', 0xF0},	/* 044 */	/* Lower-case eth */
	{'-', 'l', 0xA3},	/* 045 */	/* pounds sterling */
	{'-', 'y', 0xA5},	/* 046 */	/* yen */
	{'-', '|', 0xAC},	/* 047 */	/* not sign */
	{'.', '^', 0xB7},	/* 048 */	/* centered dot */
	{'/', 'C', 0xA2},	/* 049 */	/* cent sign */
	{'/', 'O', 0xD8},	/* 050 */	/* O with slash */
	{'/', 'c', 0xA2},	/* 051 */	/* cent sign */
	{'/', 'o', 0xF8},	/* 052 */	/* o with slash */
	{'/', 'u', 0xB5},	/* 053 */	/* mu */
	{'0', 'X', 0xA4},	/* 054 */	/* currency symbol */
	{'0', '^', 0xB0},	/* 055 */	/* degree */
	{'0', 'x', 0xA4},	/* 056 */	/* currency symbol */
	{'1', '2', 0xBD},	/* 057 */	/* 1/2 */
	{'1', '4', 0xBC},	/* 058 */	/* 1/4 */
	{'1', '^', 0xB9},	/* 059 */	/* superior '1' */
	{'2', '^', 0xB2},	/* 060 */	/* superior '2' */
	{'3', '4', 0xBE},	/* 061 */	/* 3/4 */
	{'3', '^', 0xB3},	/* 062 */	/* superior '3' */
	{'<', '<', 0xAB},	/* 063 */	/* left guillemot */
	{'>', '>', 0xBB},	/* 064 */	/* right guillemot */
	{'?', '?', 0xBF},	/* 065 */	/* inverted ? */
	{'A', 'E', 0xC6},	/* 066 */	/* AE dipthong */
	{'A', '^', 0xC2},	/* 067 */	/* A with circumflex accent */
	{'A', '`', 0xC0},	/* 068 */	/* A with grave accent */
	{'A', '~', 0xC3},	/* 069 */	/* A with tilde */
	{'C', 'O', 0xA9},	/* 060 */	/* copyright */
	{'E', '^', 0xCA},	/* 071 */	/* E with circumflex accent */
	{'E', '`', 0xC8},	/* 072 */	/* E with grave accent */
	{'H', 'T', 0xDE},	/* 073 */	/* Upper-case thorn */
	{'I', '^', 0xCE},	/* 074 */	/* I with circumflex accent */
	{'I', '`', 0xCC},	/* 075 */	/* I with grave accent */
	{'N', '~', 0xD1},	/* 076 */	/* N with tilde */
	{'O', 'R', 0xAE},	/* 077 */	/* registered */
	{'O', 'S', 0xA7},	/* 078 */	/* section mark */
	{'O', 'X', 0xA4},	/* 079 */	/* currency symbol */
	{'O', '^', 0xD4},	/* 080 */	/* O with circumflex accent */
	{'O', '_', 0xBA},	/* 081 */	/* masculine superior numeral */
	{'O', '`', 0xD2},	/* 082 */	/* O with grave accent */
	{'O', '~', 0xD5},	/* 083 */	/* O with tilde */
	{'P', '|', 0xDE},	/* 084 */	/* Upper-case thorn */
	{'U', '^', 0xDB},	/* 085 */	/* U with circumflex accent */
	{'U', '`', 0xD9},	/* 086 */	/* U with grave accent */
	{'\\','\\',0xB4},	/* 087 */	/* acute accent */
	{'^', 'a', 0xE2},	/* 088 */	/* a with circumflex accent */
	{'^', 'e', 0xEA},	/* 089 */	/* e with circumflex accent */
	{'^', 'i', 0xEE},	/* 090 */	/* i with circumflex accent */
	{'^', 'o', 0xF4},	/* 091 */	/* o with circumflex accent */
	{'^', 'u', 0xFB},	/* 092 */	/* u with circumflex accent */
	{'_', 'o', 0xBA},	/* 093 */	/* masculine superior numeral */
	{'`', 'a', 0xE0},	/* 094 */	/* a with grave accent */
	{'`', 'e', 0xE8},	/* 095 */	/* e with grave accent */
	{'`', 'i', 0xEC},	/* 096 */	/* i with grave accent */
	{'`', 'o', 0xF2},	/* 097 */	/* o with grave accent */
	{'`', 'u', 0xF9},	/* 098 */	/* u with grave accent */
	{'a', 'e', 0xE6},	/* 099 */	/* ae dipthong */
	{'a', '~', 0xE3},	/* 100 */	/* a with tilde */
	{'c', 'o', 0xA9},	/* 101 */	/* copyright */
	{'h', 't', 0xFE},	/* 102 */	/* Lower-case thorn */
	{'n', '~', 0xF1},	/* 103 */	/* n with tilde */
	{'o', 'r', 0xAE},	/* 104 */	/* registered */
	{'o', 's', 0xA7},	/* 105 */	/* section mark */
	{'o', 'x', 0xA4},	/* 106 */	/* currency symbol */
	{'o', '~', 0xF5},	/* 107 */	/* o with tilde */
	{'p', '|', 0xFE},	/* 108 */	/* Lower-case thorn */
	{'s', 's', 0xDF},	/* 109 */	/* German double-s */
	{'x', 'x', 0xD7},	/* 110 */	/* multiplication sign */
	{'|', '|', 0xA6},	/* 111 */	/* broken bar */

	{0, 0, 0},			/* end of table */
};

#endif /* _SUNCOMPOSE_H */
