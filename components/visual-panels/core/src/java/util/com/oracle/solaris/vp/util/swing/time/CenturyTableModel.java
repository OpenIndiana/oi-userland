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
public class CenturyTableModel extends CalendarTableModel {
    //
    // Static data
    //

    private static DateFormat[] mFormat = {
	new SimpleDateFormat(Finder.getString("date.format.century.title.0")),
	new SimpleDateFormat(Finder.getString("date.format.century.title.1")),
    };

    private static DateFormat[] eFormat = {
	new SimpleDateFormat(Finder.getString("date.format.century.element.0")),
	new SimpleDateFormat(Finder.getString("date.format.century.element.1")),
    };

    //
    // Constructors
    //

    public CenturyTableModel(Calendar cal) {
	super(cal);
    }

    public CenturyTableModel() {
	this(null);
    }

    //
    // CalendarTableModel methods
    //

    @Override
    public int compare(Calendar cal, Calendar cal2) {
	if (cal.get(Calendar.YEAR) / 10 == cal2.get(Calendar.YEAR) / 10) {
	    return 0;
	}
	return cal.compareTo(cal2);
    }

    @Override
    protected Calendar[][] createData() {
	Calendar[][] decades = new Calendar[3][4];
	int offset = cal.get(Calendar.YEAR) % 100 + 10;

	for (int r = 0; r < decades.length; r++) {
	    Calendar[] row = decades[r];
	    for (int c = 0; c < row.length; c++) {
		row[c] = (Calendar)cal.clone();
		row[c].add(Calendar.YEAR, 10 * (r * row.length + c) - offset);
	    }
	}

	return decades;
    }

    @Override
    public long getMillis(int intervals) {
	Calendar cal = getCalendar();
	long before = cal.getTimeInMillis();

	cal = (Calendar)cal.clone();
	cal.add(Calendar.YEAR, 100 * intervals);
	long after = cal.getTimeInMillis();

	return after - before;
    }

    @Override
    public String getTitle() {
	Calendar cal = (Calendar)this.cal.clone();
	String[] params = new String[2];

	int offset = cal.get(Calendar.YEAR) % 100;
	cal.add(Calendar.YEAR, -offset);
	params[0] = format(mFormat[0], cal);

	cal.add(Calendar.YEAR, 99);
	params[1] = format(mFormat[1], cal);

	return Finder.getString("date.format.century.title", (Object[])params);
    }

    @Override
    public boolean isInMainRange(Calendar cal) {
	return this.cal.get(Calendar.YEAR) / 100 ==
	    cal.get(Calendar.YEAR) / 100;
    }

    @Override
    public String toString(Calendar cal) {
	cal = (Calendar)cal.clone();
	String[] params = new String[2];

	int offset = cal.get(Calendar.YEAR) % 10;
	cal.add(Calendar.YEAR, -offset);
	params[0] = format(eFormat[0], cal);

	cal.add(Calendar.YEAR, 9);
	params[1] = format(eFormat[1], cal);

	return Finder.getString("date.format.century.element",
	    (Object[])params);
    }
}
