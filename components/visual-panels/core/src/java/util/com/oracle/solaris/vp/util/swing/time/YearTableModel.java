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
import java.util.Calendar;
import com.oracle.solaris.vp.util.misc.finder.Finder;

@SuppressWarnings({"serial"})
public class YearTableModel extends CalendarTableModel {
    //
    // Static data
    //

    private static DateFormat mFormat = new SimpleDateFormat(Finder.getString(
	"date.format.year.title"));

    private static DateFormat eFormat = new SimpleDateFormat(Finder.getString(
	"date.format.year.element"));

    //
    // Constructors
    //

    public YearTableModel(Calendar cal) {
	super(cal);
    }

    public YearTableModel() {
	this(null);
    }

    //
    // CalendarTableModel methods
    //

    @Override
    public int compare(Calendar cal, Calendar cal2) {
	if (cal.get(Calendar.YEAR) == cal2.get(Calendar.YEAR) &&
	    cal.get(Calendar.MONTH) == cal2.get(Calendar.MONTH)) {
	    return 0;
	}
	return cal.compareTo(cal2);
    }

    @Override
    protected Calendar[][] createData() {
	Calendar[][] months = new Calendar[3][4];
	int offset = cal.get(Calendar.MONTH);

	for (int r = 0; r < months.length; r++) {
	    Calendar[] row = months[r];
	    for (int c = 0; c < row.length; c++) {
		row[c] = (Calendar)cal.clone();
		row[c].add(Calendar.MONTH, r * row.length + c - offset);
	    }
	}

	return months;
    }

    @Override
    public long getMillis(int intervals) {
	Calendar cal = getCalendar();
	long before = cal.getTimeInMillis();

	cal = (Calendar)cal.clone();
	cal.add(Calendar.YEAR, intervals);
	long after = cal.getTimeInMillis();

	return after - before;
    }

    @Override
    public String getTitle() {
	return format(mFormat, cal);
    }

    @Override
    public boolean isInMainRange(Calendar cal) {
	return this.cal.get(Calendar.YEAR) == cal.get(Calendar.YEAR);
    }

    @Override
    public String toString(Calendar cal) {
	return format(eFormat, cal);
    }
}
