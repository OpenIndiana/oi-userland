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

package com.oracle.solaris.vp.panels.coreadm.client.swing.path;

import javax.swing.text.*;

@SuppressWarnings({"serial"})
public class PathDocument extends DefaultStyledDocument {
    //
    // Inner classes
    //

    protected static class TokenSearchResult {
	// The found token, or null if not found
	public String token;

	// The index of the found token, or -1 if not found
	public int index = -1;
    }

    //
    // Static data
    //

    public static final String[] TOKENS = {
	"%d", "%f", "%g", "%m", "%n", "%p", "%t", "%u", "%z", "%%",
    };

    private static int MAX_TOKEN_LENGTH;
    static {
	for (String token : TOKENS) {
	    if (token.length() > MAX_TOKEN_LENGTH) {
		MAX_TOKEN_LENGTH = token.length();
	    }
	}
    }

    //
    // Instance data
    //

    private TokenAttributeSetFactory factory;

    //
    // Constructors
    //

    public PathDocument(TokenAttributeSetFactory factory) {
	this.factory = factory;
    }

    //
    // StyledDocument methods
    //

    @Override
    public void insertString(int offset, String str, AttributeSet a)
	throws BadLocationException {

	// Remove newlines
	if (str != null) {
	    str = str.replace('\n', ' ');
	}

	// If offset is in the middle of a token element, move it to the end
	Element element = getCharacterElement(offset);
	if (isToken(element)) {
	    offset = element.getStartOffset();
	}

	super.insertString(offset, str, a);

	// Define the range to search for tokens

	int start = offset;
	for (int i = 0; i < MAX_TOKEN_LENGTH - 1; i++) {
	    if (start - 1 < 0 || isPartOfToken(start - 1)) {
		break;
	    }
	    start--;
	}

	int docLength = getLength();
	int insLength = str.length();
	int end = offset + insLength;
	for (int i = 0; i < MAX_TOKEN_LENGTH - 1; i++) {
	    if (end >= docLength || isPartOfToken(end)) {
		break;
	    }
	    end++;
	}

	try {
	    String search = getText(start, end - start);
//	    System.out.printf("doc: \"%s\", search: \"%s\" (%d - %d)\n",
//		getText(0, docLength), search, start, end);
	    int sOffset = 0;
	    while (true) {
		TokenSearchResult result = findToken(search, sOffset);
		if (result.token == null) {
		    break;
		}

//		System.out.printf("Found \"%s\" within \"%s\" at point %d\n",
//		    result.token, search, result.index);

		AttributeSet style = factory.getAttributeSet(result.token);

		int cStart = start + result.index;
		int cLength = result.token.length();
		setCharacterAttributes(cStart, cLength, style, true);

		// Hack -- JTextPane doesn't always display updated styles,
		// so force an insert/remove
		int cEnd = cStart + cLength;
		super.insertString(cEnd, " ", SimpleAttributeSet.EMPTY);
		super.remove(cEnd, 1);

		sOffset = start + result.index + result.token.length();
	    }
	} catch (BadLocationException e) {
	    // XXX
	    e.printStackTrace();
	}
    }

    @Override
    public void remove(int offset, int length) throws BadLocationException {
	// If the beginning or end of the deleted segment overlaps a token
	// element, remove the entire element

	Element element = getCharacterElement(offset);
	if (isToken(element)) {
	    int sOffset = element.getStartOffset();
	    if (sOffset != offset) {
		length += offset - sOffset;
		offset = sOffset;
	    }
	}

	element = getCharacterElement(offset + length - 1);
	if (isToken(element)) {
	    length = element.getEndOffset() - offset;
	}

	super.remove(offset, length);
    }

    //
    // PathDocument methods
    //

    public String getText() {
	int start = -1;
	int offset = 0;
	StringBuilder buffer = new StringBuilder();

	try {
	    for (int n = getLength(); offset < n; offset++) {
		Element element = getCharacterElement(offset);

		if (isToken(element)) {
		    if (start != -1) {
			String token =
			    getText(start, offset - start).replace("%", "%%");
			buffer.append(token);
			start = -1;
		    }

		    int end = element.getEndOffset();
		    int length = end - offset;
		    buffer.append(getText(offset, length));
		    offset = end - 1;
		} else if (start == -1) {
		    start = offset;
		}
	    }

	    if (start != -1) {
		String token =
		    getText(start, offset - start).replace("%", "%%");
		buffer.append(token);
	    }
	} catch (BadLocationException ignore) {
	    ignore.printStackTrace();
	}

	return buffer.toString();
    }

    //
    // Private methods
    //

    private TokenSearchResult findToken(String text, int offset) {
	TokenSearchResult result = new TokenSearchResult();

	for (String token : TOKENS) {
	    int i = text.indexOf(token, offset);
	    if (i != -1 && (result.index == -1 || i < result.index)) {
		result.index = i;
		result.token = token;
	    }
	}

	return result;
    }

    private boolean isPartOfToken(int offset) {
	Element element = getCharacterElement(offset);
	return isToken(element);
    }

    //
    // Static data
    //

    protected static boolean isToken(Element element) {
	return element.getName().equals(
	    StyleConstants.ComponentElementName);
    }
}
