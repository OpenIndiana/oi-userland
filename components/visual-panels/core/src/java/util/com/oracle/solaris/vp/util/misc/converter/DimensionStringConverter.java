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

import java.awt.Dimension;
import com.oracle.solaris.vp.util.misc.TextUtil;

public class DimensionStringConverter extends StringConverter<Dimension> {
    //
    // Static data
    //

    public static final DimensionStringConverter INSTANCE =
	new DimensionStringConverter();

    //
    // Converter methods
    //

    /**
     * Converts the given {@code String} to a {@code Dimension}.
     *
     * @param	    s
     *		    the {@code String} to convert: two integers (width and
     *		    height) separated by whitespace and/or commas
     *
     * @return	    {@code null} if {@code s} is {@code null}, a {@code
     *		    Dimension} otherwise
     *
     * @exception   IllegalArgumentException if the given {@code String} could
     *		    not be converted to a {@code Dimension}
     */
    @Override
    public Dimension convert(String s) {
	if (s == null) {
	    return null;
	}

	String[] groups = TextUtil.match(
	    s, "^\\s*(\\d+)[\\s,]+(\\d+)\\s*$");

	if (groups != null) {
	    return new Dimension(Integer.parseInt(groups[1]),
		Integer.parseInt(groups[2]));
	}

	throw new IllegalArgumentException(String.format(
	    "invalid dimension: %s", s));
    }

    //
    // DualConverter methods
    //

    @Override
    public String revert(Dimension d) {
	return d.width + ", " + d.height;
    }
}
