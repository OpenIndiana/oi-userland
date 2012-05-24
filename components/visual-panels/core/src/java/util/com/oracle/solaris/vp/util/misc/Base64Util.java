/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.util.misc;

import java.io.*;

public class Base64Util {
    //
    // Inner classes
    //

    @SuppressWarnings({"serial"})
    public static class Base64Exception extends IOException {
	public Base64Exception(String message) {
	    super(message);
	}
    }

    /**
     * Utility class provided for callers who wish to enforce a maximum
     * line length for their Base64-encoded output.
     */
    public static class WrappingWriter extends FilterWriter {
	private static final String NEWLINE =
	    System.getProperty("line.separator");

	private int column_ = 0;
	private int max_ = 76;

	/**
	 * Creates a new WrappingWriter which writes line-wrapped
	 * output to {@code out} using the default width (76
	 * characters).
	 *
	 * @param out the {@code Writer} to which output should be sent
	 */
    	public WrappingWriter(Writer out)
	{
	    super(out);
	}

	/**
	 * Creates a new WrappingWriter which writes line-wrapped
	 * output to {@code out} using the specified width.
	 *
	 * @param out the {@code Writer} to which output should be sent
	 * @param max the maximum number of characters per line
	 */
    	public WrappingWriter(Writer out, int max)
	{
	    super(out);
	    max_ = max;
	}

	@Override
	public void write(int c) throws IOException
	{
	    if (++column_ > max_) {
		column_ = 1;
		out.write(NEWLINE);
	    }

	    out.write(c);
	}

	@Override
	public void flush() throws IOException
	{
	    if (column_ != 0)
		out.write(NEWLINE);
	    column_ = 0;

	    out.flush();
	}

	/*
	 * We currently only use write(int), so we don't need to
	 * redefine any other methods.
	 */
    }

    //
    // Static data
    //

    private static final char ENCODE[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
    };

    private static final byte DECODE[] = new byte[256];

    static {
	for (int i = 0; i < DECODE.length; i++) {
	    DECODE[i] = (byte)-1;
	}
	for (int i = 0; i < ENCODE.length; i++) {
	    DECODE[ENCODE[i]] = (byte)i;
	}
    }

    private static final char CHAR_PAD = '=';

    //
    // Static methods
    //

    /**
     * Decodes the base64-encoded data on the given {@code InputStream} to the
     * given {@code OutputStream}.
     *
     * @exception   Base64Exception
     *		    if the given {@code InputStream} has invalid or insufficient
     *		    data
     *
     * @exception   IOException
     *		    if an I/O error ocurrs
     */
    public static void decode(InputStream in, OutputStream out)
	throws IOException {

	// Total number of bytes read
	int count = 0;

	OUTER: while (true) {
	    int pad = 0;
	    int atom = 0;

	    // Read in 4 characters (6 significant bits each)
	    for (int i = 0; i < 4; i++) {
		int b = in.read();

		if (b == -1) {
		    if (i == 0) {
			break OUTER;
		    }

		    if (pad != 0) {
			throw new Base64Exception(String.format(
			    "expected '%c' at position %d, found EOS", CHAR_PAD,
			    count));
		    } else {
			throw new Base64Exception(String.format(
			    "unexpected EOS at position %d", count));
		    }

		// Ignore whitespace
		} else if (Character.isWhitespace((char)b)) {
		    i--;
		    continue;
		}

		atom <<= 6;

		if (b == CHAR_PAD) {
		    // Pad chars can only be the 3rd or 4th char in the set
		    if (i < 2) {
			throw new Base64Exception(String.format(
			    "invalid char at position %d: %s", count,
			    getCharDescription((char)b)));
		    }
		    pad++;

		} else if (pad != 0) {
		    throw new Base64Exception(String.format(
			"invalid char at position %d: %s (expected %s)", count,
			getCharDescription((char)b),
			getCharDescription(CHAR_PAD)));

		} else {
		    // InputStream.read guarantees -1 <= b <= 255
		    int index = DECODE[b];

		    if (index < 0 || index > 63) {
			throw new Base64Exception(String.format(
			    "invalid char at position %d: %s", count,
			    getCharDescription((char)b)));
		    }

		    atom |= index;
		}

		count++;
	    }

	    // Output 3 8-bit bytes
	    for (int i = 0; i < 3 - pad; i++) {
		out.write((byte)((atom & 0x00FF0000) >>> 16));
		atom <<= 8;
	    }
	}

	out.flush();
    }

    public static byte[] decode(InputStream in)
	throws IOException {

	ByteArrayOutputStream out = new ByteArrayOutputStream();
	decode(in, out);

	return out.toByteArray();
    }

    public static void decode(String in, OutputStream out)
	throws IOException {

	ByteArrayInputStream bin =
	    new ByteArrayInputStream(in.getBytes());

	decode(bin, out);
    }

    public static byte[] decode(String in)
	throws IOException {

	ByteArrayOutputStream out = new ByteArrayOutputStream();
	decode(in, out);

	return out.toByteArray();
    }

    /**
     * Encodes the data on the given {@code InputStream} as base64 and writes it
     * to the given {@code Writer}.
     *
     * @exception   IOException
     *		    if an I/O error ocurrs
     */
    public static void encode(InputStream in, Writer out)
	throws IOException {

	OUTER: while (true) {
	    int pad = 0;
	    int atom = 0;

	    // Read in 3 8-bit bytes
	    for (int i = 0; i < 3; i++) {
		int b = in.read();

		if (b == -1) {
		    if (i == 0) {
			break OUTER;
		    }
		    pad++;
		} else {
		    atom |= b;
		}
		atom <<= 8;
	    }

	    // Output 4 6-bit characters...
	    for (int i = 0; i < 4 - pad; i++) {
		int index = (atom & 0xFC000000) >>> 26;
		out.write(ENCODE[index]);
		atom <<= 6;
	    }

	    // ...plus any padding if 3 bytes couldn't be read
	    for (int i = 0; i < pad; i++) {
		out.write(CHAR_PAD);
	    }
	}

	out.flush();
    }

    public static void encode(byte[] buffer, int offset, int len,
	Writer out) throws IOException {

	ByteArrayInputStream in =
	    new ByteArrayInputStream(buffer, offset, len);
	encode(in, out);
    }

    public static void encode(byte[] buffer, Writer out)
	throws IOException {
	encode(buffer, 0, buffer.length, out);
    }

    public static void encode(String s, Writer out)
	throws IOException {
	encode(s.getBytes(), out);
    }

    public static String encode(byte[] buffer, int offset, int len) {
	StringWriter out = new StringWriter();
	try {
	    encode(buffer, offset, len, out);
	    return out.toString();
	} catch (IOException e) {
	    // Not likely -- output is from a byte array to a String
	}

	return null;
    }

    public static String encode(byte[] buffer) {
	return encode(buffer, 0, buffer.length);
    }

    public static String encode(String s) {
	return encode(s.getBytes());
    }

    //
    // Private static methods
    //

    private static String getCharDescription(char c) {
	String desc = "";

	if (TextUtil.isPrintable(c)) {
	    desc = String.format("'%c',", c);
	}

	desc += String.format("%d,0x%02x", (int)c, (int)c);

	return desc;
    }
}
