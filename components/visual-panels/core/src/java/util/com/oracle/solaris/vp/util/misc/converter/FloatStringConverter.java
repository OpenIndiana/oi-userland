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

public class FloatStringConverter extends StringConverter<Float> {
    //
    // Static data
    //

    public static final FloatStringConverter INSTANCE =
	new FloatStringConverter();

    //
    // Converter methods
    //

    /**
     * Converts the given {@code String} to a {@code Float}.
     *
     * @param	    s
     *		    the {@code String} to convert
     *
     * @return	    {@code null} if {@code s} is {@code null}, a {@code Float}
     *		    otherwise
     *
     * @exception   NumberFormatException
     *		    if the given {@code String} could not be converted to a
     *		    {@code Float}
     */
    @Override
    public Float convert(String s) {
	if (s == null) {
	    return null;
	}

	return Float.parseFloat(s);
    }
}
