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

import java.util.Collection;
import java.util.regex.*;

public class TextUtil {
    //
    // Static methods
    //

    /**
     * Returns the base portion of a fully-qualified class name.
     */
    public static String getClassBaseName(String className) {
	return className.replaceFirst(".*\\.", "");
    }

    /**
     * Returns the base portion of the name of the given class.  In
     * constrast with the simple name, which is empty for anonymous
     * classes and the Java identifier for local classes, this is the
     * last component of the specified class's binary name.
     */
    public static String getBaseName(Class clazz) {
	return getClassBaseName(clazz.getName());
    }

    /**
     * Returns the package portion of a fully-qualified class name.
     */
    public static String getPackageName(String name) {
	return name.replaceFirst("\\.?\\.*[^.]*$", "");
    }

    /**
     * Returns a random alpha {@code String} with length between {@code minLen}
     * and {@code maxLen}.
     */
    public static String getRandomAlphaString(int minLen, int maxLen) {
	StringBuilder buffer = new StringBuilder();
	int length = (int)(Math.random() * (maxLen - minLen + 1)) + minLen;
	for (int j = 0; j < length; j++) {
	    char c = (char)((Math.random() * 26) + 97);
	    buffer.append(c);
	}
	return buffer.toString();
    }

    /**
     * Replace characters with special meaning to HTML with their HTML entity
     * equivalents.
     */
    public static String escapeHTMLChars(String text) {
	StringBuilder buffer = new StringBuilder();

	for (char c : text.toCharArray()) {
	    switch (c) {
		case '<':
		    buffer.append("&lt;");
		    break;

		case '>':
		    buffer.append("&gt;");
		    break;

		case '\"':
		    buffer.append("&quot;");
		    break;

		case '\'':
		    buffer.append("&#039;");
		    break;

		case '\\':
		    buffer.append("&#092;");
		    break;

		case '&':
		    buffer.append("&amp;");
		    break;

		case '\n':
		    buffer.append("<br/>");
		    break;

		default:
		    buffer.append(c);
	    }
	}

	return buffer.toString();
    }

    /**
     * Splits the given string into lines.
     *
     * @param	    text
     *		    the text to format
     *
     * @param	    width
     *		    the maximum width of each line
     *
     * @param	    indent1
     *		    the indent to put on the first line
     *
     * @param	    indent2
     *		    the indent to put on the second and remaining lines
     *
     * @param	    forceBreak
     *		    whether to force a break in the middle of a word
     *		    if the length of the word is greater than
     *		    <code>width</code>
     *
     * @return	    a wrapped string separated by newlines
     */
    public static String format(String text, int width,
	String indent1, String indent2, boolean forceBreak) {

	if (text == null) {
	    return text;
	}

	// Replace newlines
	text = text.replaceAll("\\s*[\\r\\n]\\s*", " ");

	StringBuilder buffer = new StringBuilder();

	String indent = indent1;
	int w = width - indent.length();
	if (w < 1) {
	    w = 1;
	}

	for (int i = 0; text.length() > 0; i++) {
	    String regex = "^\\s*(.{1," + w + "})($|\\s+.*)";
	    String[] groups = match(text, regex);

	    if (groups == null) {
		// Can't break line on whitespace without exceeding width
		if (forceBreak) {
		    // Break line in middle of word
		    regex = "^\\s*(.{1," + w + "})(.*)";
		} else {
		    // Break line at next whitespace
		    regex = "^\\s*(.+?)($|\\s+.*)";
		}

		groups = match(text, regex);
	    }

	    if (i != 0) {
		buffer.append("\n");
	    }

	    buffer.append(indent).append(groups[1].trim());
	    text = groups[2];

	    if (i == 0) {
		indent = indent2;
		w = width - indent.length();
		if (w < 1) {
		    w = 1;
		}
	    }
	}

	return buffer.toString();
    }

    /**
     * Shortcut for:
     * <p>
     *	 <code>
     *	   {@link #format(String,int,String,String,boolean) format}
     *	   (text, width, "", "", forceBreak);
     *	 </code>
     * </p>
     */
    public static String format(String text, int width, boolean forceBreak) {
	return format(text, width, "", "", forceBreak);
    }

    public static boolean isPrintable(char c) {
	return c >= 32 && c <= 126;
    }

    public static String join(String delim, Object... list) {
	StringBuilder buffer = new StringBuilder();

	for (int i = 0; i < list.length; i++) {
	    if (i != 0 && delim != null) {
		buffer.append(delim);
	    }
	    if (list[i] != null) {
		buffer.append(list[i]);
	    }
	}

	return buffer.toString();
    }

    public static String join(String delim, byte... list) {
	Byte[] array = new Byte[list.length];
	for (int i = 0; i < array.length; i++) {
	    array[i] = list[i];
	}
	return join(delim, (Object[])array);
    }

    public static String join(String delim, char... list) {
	Character[] array = new Character[list.length];
	for (int i = 0; i < array.length; i++) {
	    array[i] = list[i];
	}
	return join(delim, (Object[])array);
    }

    public static String join(String delim, double... list) {
	Double[] array = new Double[list.length];
	for (int i = 0; i < array.length; i++) {
	    array[i] = list[i];
	}
	return join(delim, (Object[])array);
    }

    public static String join(String delim, float... list) {
	Float[] array = new Float[list.length];
	for (int i = 0; i < array.length; i++) {
	    array[i] = list[i];
	}
	return join(delim, (Object[])array);
    }

    public static String join(String delim, int... list) {
	Integer[] array = new Integer[list.length];
	for (int i = 0; i < array.length; i++) {
	    array[i] = list[i];
	}
	return join(delim, (Object[])array);
    }

    public static String join(String delim, long... list) {
	Long[] array = new Long[list.length];
	for (int i = 0; i < array.length; i++) {
	    array[i] = list[i];
	}
	return join(delim, (Object[])array);
    }

    public static String join(String delim, short... list) {
	Short[] array = new Short[list.length];
	for (int i = 0; i < array.length; i++) {
	    array[i] = list[i];
	}
	return join(delim, (Object[])array);
    }

    public static String join(String delim, Collection list) {
	return join(delim, list.toArray());
    }

    /**
     * Matches the given string against the given regular expression,
     * returning an array of the matched regular expression groups.
     *
     * @param	    text
     *		    the String to which to apply the regular
     *		    expression
     *
     * @param	    regex
     *		    a regular expression containing groups
     *
     * @return	    an array of the matched regular expression groups
     *		    (group 0 is the entire pattern), if the given
     *		    pattern matched, or {@code null} if the
     *		    pattern did not match
     */
    public static String[] match(String text, Pattern regex) {
	Matcher matcher = regex.matcher(text);
	if (!matcher.matches()) {
	    return null;
	}

	String[] groups = new String[matcher.groupCount() + 1];
	for (int i = 0; i < groups.length; i++) {
	    groups[i] = matcher.group(i);
	}

	return groups;
    }

    /**
     * Compiles the given regular expression and calls {@link
     * #match(String,Pattern)}.
     *
     * @exception   PatternSyntaxException
     *		    if the given pattern was malformed
     */
    public static String[] match(String text, String regex)
	throws PatternSyntaxException {

	return match(text, Pattern.compile(regex));
    }

    /**
     * Converts {@code str} to a Java identifier by replacing any illegal
     * characters with {@code repl}.
     */
    public static String toJavaIdentifier(String str, String repl) {
	StringBuilder buffer = new StringBuilder();
	for (char c : str.toCharArray()) {
	    boolean empty = buffer.length() == 0;
	    if ((empty && Character.isJavaIdentifierStart(c)) ||
		(!empty && Character.isJavaIdentifierPart(c))) {
		buffer.append(c);
	    } else {
		buffer.append(repl);
	    }
	}
	return buffer.toString();
    }

    public static String toJavaMethodName(String... words) {
	StringBuilder buffer = new StringBuilder();
	for (String word : words) {
	    try {
		buffer.append(word.substring(0, 1).toUpperCase());
		buffer.append(word.substring(1).toLowerCase());
	    } catch (IndexOutOfBoundsException ignore) {
	    }
	}
	return buffer.toString();
    }
}
