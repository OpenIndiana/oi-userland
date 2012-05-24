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

package com.oracle.solaris.vp.util.swing.time;

import java.text.*;
import java.util.Locale;
import javax.swing.JSpinner;

@SuppressWarnings({"serial"})
public class DateSpinnerEditor extends TimeSpinnerEditor {
    //
    // Constructors
    //

    public DateSpinnerEditor(JSpinner spinner) {
	super((TimeSpinnerModel)spinner.getModel(), createDateFormat(spinner));
    }

    //
    // Static methods
    //

    protected static DateFormat createDateFormat(JSpinner spinner) {
	Locale locale = spinner.getLocale();

	DateFormat format = DateFormat.getDateInstance(DateFormat.SHORT,
	    locale == null ? Locale.getDefault() : locale);

	if (format instanceof SimpleDateFormat) {
	    SimpleDateFormat sFormat = (SimpleDateFormat)format;
	    padUnits(sFormat);

	    // Don't use two-character years
	    String pattern = sFormat.toPattern().replaceAll(
		"\\b(yy)\\b", "$1$1");

	    sFormat.applyPattern(pattern);
	}

	return format;
    }
}
