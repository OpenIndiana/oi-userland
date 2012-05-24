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

import com.oracle.solaris.vp.util.misc.TextUtil;

public class StringArrayStringConverter extends StringConverter<String[]> {
    //
    // Static data
    //

    public static final StringArrayStringConverter INSTANCE =
	new StringArrayStringConverter();

    public static final String _SEPARATOR = ", ";
    public static final String _SEP_REGEX = "[\\s,]+";

    //
    // Instance data
    //

    private String separator;
    private String sepRegex;

    //
    // Constructors
    //

    public StringArrayStringConverter(String separator, String sepRegex) {
	this.separator = separator;
	this.sepRegex = sepRegex;
    }

    public StringArrayStringConverter() {
	this(_SEPARATOR, _SEP_REGEX);
    }

    //
    // Converter methods
    //

    @Override
    public String[] convert(String s) {
	return s == null ? null : s.replaceFirst("^" + sepRegex, "").split(
	    sepRegex, 0);
    }

    //
    // DualConverter methods
    //

    @Override
    public String revert(String[] value) {
	return value == null ? null : TextUtil.join(separator, (Object[])value);
    }

    //
    // StringArrayStringConverter methods
    //

    /**
     * Gets the literal separator string used to convert a {@code String} array
     * to a {@code String}.
     */
    public String getSeparator() {
	return separator;
    }

    /**
     * Gets the separator regular expression used to convert a {@code String} to
     * a {@code String} array.
     */
    public String getSepRegex() {
	return sepRegex;
    }
}
