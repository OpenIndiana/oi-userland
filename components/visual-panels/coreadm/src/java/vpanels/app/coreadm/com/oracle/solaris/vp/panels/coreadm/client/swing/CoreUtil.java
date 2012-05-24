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

package com.oracle.solaris.vp.panels.coreadm.client.swing;

import java.util.*;
import java.util.regex.Pattern;

/**
 * Contains utility routines for managing core files and patterns.
 */
public class CoreUtil
{
    /*
     * Though I'm a card-carrying enum whore, I have to admit using
     * one doesn't make sense here.
     */
    public static final char FMT_DIR = 'd';
    public static final char FMT_FILE = 'f';
    public static final char FMT_GID = 'g';
    public static final char FMT_MACHINE = 'm';
    public static final char FMT_NODE = 'n';
    public static final char FMT_PID = 'p';
    public static final char FMT_TIME = 't';
    public static final char FMT_UID = 'u';
    public static final char FMT_ZONE = 'z';
    public static final char FMT_PERCENT = '%';

    private static final HashMap<Character, String> MAP_REGEX =
	new HashMap<Character, String>(10);
    static {
	MAP_REGEX.put(FMT_DIR, ".+");
	MAP_REGEX.put(FMT_FILE, "[^/]+");
	MAP_REGEX.put(FMT_GID, "[0-9]+");
	MAP_REGEX.put(FMT_MACHINE, "[^/]+");
	MAP_REGEX.put(FMT_NODE, "[^/]+");
	MAP_REGEX.put(FMT_PID, "[0-9]+");
	MAP_REGEX.put(FMT_TIME, "[0-9]+");
	MAP_REGEX.put(FMT_UID, "[0-9]+");
	MAP_REGEX.put(FMT_ZONE, "[^/]+");
	MAP_REGEX.put(FMT_PERCENT, Pattern.quote("%"));
    }

    public static String mapPath(Map<Character, String> mappings, String path)
    {
	/* assert(mappings.keySet().containsAll(MAP_REGEX.keySet())); */

	StringBuilder buffer = new StringBuilder();
	char[] chars = path.toCharArray();
	for (int i = 0; i < chars.length; i++) {
	    if (i != chars.length - 1 && chars[i] == '%') {
		String sub = mappings.get(chars[i + 1]);
		if (sub != null) {
		    buffer.append(sub);
		    i++;
		    continue;
		}
	    }
	    buffer.append(chars[i]);
	}

	return (buffer.toString());
    }

    public static class PathElement
    {
	public String element_;	    /** the path component string */
	public boolean isRegex_;    /** if this element is a regex */
	public boolean isDir_;	    /** if this element has a %d */

	private PathElement(String e, boolean r, boolean d)
	{
	    element_ = e;
	    isRegex_ = r;
	    isDir_ = d;
	}
    }

    public static PathElement[] pathToRegex(String path)
    {
	/*
	 * We need to armor the path against coincidental regular
	 * expressions.  Unfortunately, we can neither quote the
	 * entire path (quoting could break up percent-letter pairs)
	 * or the post substitution path (we'd we quoting the regular
	 * expressions we added).  Instead, we must split at and
	 * quote between token boundaries.
	 */
	String[] elements = path.split("/", -1);
	PathElement[] result = new PathElement[elements.length];

	for (int e = 0; e < elements.length; e++) {
	    String[] bits = elements[e].split("%[dfgmnptuz%]", -1);
	    if (bits.length == 1) {
		result[e] = new PathElement(elements[e], false, false);
		continue;
	    }

	    StringBuilder buffer = new StringBuilder();
	    char[] chars = elements[e].toCharArray();
	    int pos = 0;
	    boolean isDir = false;
	    for (String b : bits) {
		buffer.append(Pattern.quote(b));
		pos += b.length();
		if (pos < chars.length) {
		    char format = chars[pos + 1];
		    if (format == FMT_DIR)
			isDir = true;
		    buffer.append(MAP_REGEX.get(format));
		    pos += 2;
		}
	    }
	    result[e] = new PathElement(buffer.toString(), true, isDir);
	}

	return (result);
    }
}
