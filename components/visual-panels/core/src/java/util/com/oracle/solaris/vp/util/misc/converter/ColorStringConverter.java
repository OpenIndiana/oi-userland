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

package com.oracle.solaris.vp.util.misc.converter;

import java.awt.Color;
import java.util.*;
import com.oracle.solaris.vp.util.misc.TextUtil;

public class ColorStringConverter extends StringConverter<Color> {
    //
    // Static data
    //

    public static final ColorStringConverter INSTANCE =
	new ColorStringConverter();

    //
    // Converter methods
    //

    /**
     * Converts the given {@code String} to a {@code Color}.
     *
     * @param	    s
     *		    the {@code String} to convert: a list of one, three, or four
     *		    integers, separated by whitespace and/or commas; these
     *		    correspond to the arguments of the various {@code Color}
     *		    constructors.
     *
     * @return	    {@code null} if {@code s} is {@code null}, a {@code Color}
     *		    otherwise
     *
     * @exception   IllegalArgumentException
     *		    if the given {@code String} could not be converted to a
     *		    {@code Color}
     */
    @Override
    public Color convert(String s) {
	if (s == null) {
	    return null;
	}

	List<Integer> list = new ArrayList<Integer>();
	String[] groups;

	String remaining = s;
	while ((groups = TextUtil.match(
	    remaining, "^[\\s,]*(\\d+)(.*)")) != null) {
	    list.add(new Integer(groups[1]));
	    remaining = groups[2];
	}

	switch (list.size()) {
	    // Single RGB int
	    case 1:
		return new Color((int)list.get(0));

	    // R, G, B
	    case 3:
		return new Color((int)list.get(0), (int)list.get(1),
		    (int)list.get(2));

	    // R, G, B, A
	    case 4:
		return new Color((int)list.get(0), (int)list.get(1),
		    (int)list.get(2), (int)list.get(3));
	}

	throw new IllegalArgumentException(
	    String.format("invalid color: %s", s));
    }

    //
    // DualConverter methods
    //

    @Override
    public String revert(Color c) {
	return String.format("%d, %d, %d, %d",
	    c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha());
    }
}
