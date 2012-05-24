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
import java.util.*;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;

@SuppressWarnings({"serial"})
public class MonthTableModel extends CalendarTableModel {
    //
    // Static data
    //

    private static DateFormat mFormat = new SimpleDateFormat(Finder.getString(
	"date.format.month.title"));

    private static DateFormat eFormat = new SimpleDateFormat(Finder.getString(
	"date.format.month.element"));

    private static final int[] INDEX_TO_DAY_OF_WEEK = {
	Calendar.SUNDAY, Calendar.MONDAY, Calendar.TUESDAY, Calendar.WEDNESDAY,
	Calendar.THURSDAY, Calendar.FRIDAY, Calendar.SATURDAY,
    };

    //
    // Instance data
    //

    private String[] days;
    private int dayOffset;
    private boolean compact;
    private int firstDayOfWeek;

    //
    // Constructors
    //

    public MonthTableModel() {
	setCompact(false);
    }

    //
    // TableModel methods
    //

    @Override
    public String getColumnName(int colIndex) {
	return days[INDEX_TO_DAY_OF_WEEK[(colIndex + dayOffset) %
	    INDEX_TO_DAY_OF_WEEK.length]];
    }

    //
    // CalendarTableModel methods
    //

    @Override
    public int compare(Calendar cal, Calendar cal2) {
	if (cal == null) {
	    return cal2 == null ? 0 : -1;
	}

	if (cal2 == null) {
	    return 1;
	}

	if (cal.get(Calendar.YEAR) == cal2.get(Calendar.YEAR) &&
	    cal.get(Calendar.MONTH) == cal2.get(Calendar.MONTH) &&
	    cal.get(Calendar.DAY_OF_MONTH) == cal2.get(Calendar.DAY_OF_MONTH)) {
	    return 0;
	}

	return cal.compareTo(cal2);
    }

    @Override
    protected Calendar[][] createData() {
	Calendar cal = (Calendar)getCalendar().clone();
	cal.set(Calendar.DAY_OF_MONTH, 1);
	cal.setFirstDayOfWeek(firstDayOfWeek);

	int firstDay = getFirstDayOfWeek();
	dayOffset = 0;
	for (; dayOffset < INDEX_TO_DAY_OF_WEEK.length
	    && firstDay != INDEX_TO_DAY_OF_WEEK[dayOffset]; dayOffset++);

	int nWeeks = compact ?
	    cal.getActualMaximum(Calendar.WEEK_OF_MONTH) :
	    cal.getMaximum(Calendar.WEEK_OF_MONTH);

	// 7
	int weekLen = cal.getMaximum(Calendar.DAY_OF_WEEK);

	Calendar[][] days = new Calendar[nWeeks][weekLen];

	int month = cal.get(Calendar.MONTH);
	int firstDayOfWeek = cal.getFirstDayOfWeek();
	int curDayOfWeek = cal.get(Calendar.DAY_OF_WEEK);
	int curCol = (curDayOfWeek - firstDayOfWeek + weekLen) % weekLen;
	int wOfM = cal.get(Calendar.WEEK_OF_MONTH);

	// Adjust calendar to first day of first week of the month
	cal.add(Calendar.DAY_OF_MONTH, weekLen * (1 - wOfM) - curCol);

	// "Center" data among outliers
	if (!compact && cal.get(Calendar.DAY_OF_MONTH) == 1) {
	    cal.add(Calendar.DAY_OF_MONTH, -weekLen);
	}

	for (int w = 0; w < days.length; w++) {
	    Calendar[] week = days[w];
	    for (int d = 0; d < week.length; d++) {
		week[d] = (Calendar)cal.clone();
		cal.add(Calendar.DAY_OF_MONTH, 1);
	    }
	}

	return days;
    }

    @Override
    public long getMillis(int intervals) {
	Calendar cal = getCalendar();
	long before = cal.getTimeInMillis();

	cal = (Calendar)cal.clone();
	cal.add(Calendar.MONTH, intervals);
	long after = cal.getTimeInMillis();

	return after - before;
    }

    @Override
    public String getTitle() {
	return format(mFormat, getCalendar());
    }

    @Override
    public boolean isInMainRange(Calendar cal) {
	Calendar thisCal = getCalendar();
	return thisCal.get(Calendar.YEAR) == cal.get(Calendar.YEAR) &&
	    thisCal.get(Calendar.MONTH) == cal.get(Calendar.MONTH);
    }

    @Override
    public void setLocale(Locale locale) {
	if (!ObjectUtil.equals(getLocale(), locale)) {
	    days = DateFormatSymbols.getInstance(locale).getShortWeekdays();
	    setFirstDayOfWeek(Calendar.getInstance(locale).getFirstDayOfWeek());
	    super.setLocale(locale);
	}
    }

    @Override
    public String toString(Calendar cal) {
	return format(eFormat, cal);
    }

    //
    // MonthTableModel methods
    //

    /**
     * Gets whether the number of rows in the model are the number of unique
     * weeks in the month ({@code true}), or the maximum number of unique weeks
     * in any month ({@code false}).
     */
    public boolean getCompact() {
	return compact;
    }

    public int getFirstDayOfWeek() {
	return firstDayOfWeek;
    }

    /**
     * Sets whether the number of rows in the model are the number of unique
     * weeks in the month ({@code true}), or the maximum number of unique weeks
     * in any month ({@code false}).
     */
    public void setCompact(boolean compact) {
	if (this.compact != compact) {
	    this.compact = compact;
	    invalidate();
	}
    }

    public void setFirstDayOfWeek(int firstDayOfWeek) {
	if (this.firstDayOfWeek != firstDayOfWeek) {
	    this.firstDayOfWeek = firstDayOfWeek;
	    invalidate();
	}
    }
}
