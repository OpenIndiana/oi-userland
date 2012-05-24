
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

import java.awt.Point;
import java.text.DateFormat;
import java.util.*;
import javax.swing.table.AbstractTableModel;
import com.oracle.solaris.vp.util.misc.ObjectUtil;

@SuppressWarnings({"serial"})
public abstract class CalendarTableModel extends AbstractTableModel {
    //
    // Instance data
    //

    protected Calendar cal;
    private Locale locale;
    private Calendar[][] data;

    //
    // Constructors
    //

    public CalendarTableModel(Calendar cal) {
	this.cal = Calendar.getInstance();
	this.cal.setLenient(false);

	if (cal == null) {
	    cal = this.cal;
	} else {
	    setCalendar(cal);
	}

	setLocale(Locale.getDefault());
    }

    public CalendarTableModel() {
	this(null);
    }

    //
    // TableModel methods
    //

    @Override
    public int getColumnCount() {
	return getData()[0].length;
    }

    /**
     * Default implementation that returns {@code null}.
     */
    @Override
    public String getColumnName(int colIndex) {
	return null;
    }

    @Override
    public int getRowCount() {
	return getData().length;
    }

    @Override
    public Object getValueAt(int row, int col) {
	return getData()[row][col];
    }

    //
    // CalendarTableModel methods
    //

    /**
     * Compares the relevant fields of the given model elements.
     *
     * @param	    cal
     *		    an element of the model
     *
     * @param	    cal2
     *		    an element of the model
     *
     * @return	    a negative integer, zero, or a positive integer if {@code
     *		    cal} is less than, equal to, or greater than, respectively,
     *		    {@code cal2}
     */
    public abstract int compare(Calendar cal, Calendar cal2);

    /**
     * Creates the data shown in the table.
     */
    protected abstract Calendar[][] createData();

    /**
     * Gets a copy of the {@code Calendar} represented by this model.
     */
    public Calendar getCalendar() {
	return (Calendar)cal.clone();
    }

    public Calendar[][] getData() {
	if (data == null) {
	    data = createData();
	}
	return data;
    }

    public Locale getLocale() {
	return locale;
    }

    /**
     * Gets the number of milliseconds in the given number of intervals specific
     * to this {@code CalendarTableModel}.  For example, if this is a {@link
     * MonthTableModel} for 12/2008, {@code getMillis(2)} would return the
     * number of milliseconds between 12/1/2008 and 2/1/2009.  Note that {@code
     * getMillis(-n)} does not necessarily equal {@code -getMillis(n)}.
     */
    public abstract long getMillis(int intervals);

    /**
     * Gets the position of the given {@code Calendar} in this model.  Only
     * those fields in the {@code Calendar} that are relevant to this model are
     * {@link #compare compared}.
     *
     * @return	    a {@code Point}, or {@code null} if an equivalent {@code
     *		    Calendar} does not occur in the model
     */
    public Point getPosition(Calendar cal) {
	int nRows = getRowCount();
	int nCols = getColumnCount();

	for (int mRow = 0; mRow < nRows; mRow++) {
	    for (int mCol = 0; mCol < nCols; mCol++) {
		Calendar cal2 = (Calendar)getValueAt(mRow, mCol);
		if (compare(cal, cal2) == 0) {
		    return new Point(mCol, mRow);
		}
	    }
	}

	return null;
    }

    /**
     * Gets a localized title for this {@code CalendarTableModel}.
     */
    public abstract String getTitle();

    /**
     * If not already invalid, marks this {@code CalendarTableModel}'s {@link
     * #getData data} as needing to be rebuilt and calls {@link
     * #fireTableDataChanged}.
     */
    protected void invalidate() {
	if (data != null) {
	    data = null;
	    fireTableDataChanged();
	}
    }

    /**
     * Determines whether the given {@code Calendar} is in the <i>main range</i>
     * of this model.  For example, if this model is a {@link MonthTableModel}
     * modelling all of the days in 12/2008, then the main range is 12/01/2008 -
     * 12/31/2008.  12/14/2008, then, would be in the main range of this model,
     * whereas 11/30/2008, even though it may be contained by this model, would
     * not.
     */
    public abstract boolean isInMainRange(Calendar cal);

    /**
     * Indicates whether the the model would need to be rebuilt if the given
     * {@code Calendar} were set in the model.	This implementation returns
     * {@code true} if {@link #isInMainRange} returns {@code false} or the time
     * zones in the two {@code Calendar}s differ; {@code false} otherwise.
     */
    protected boolean wouldInvalidate(Calendar cal) {
	return cal == null || !isInMainRange(cal) ||
	    !this.cal.getTimeZone().equals(cal.getTimeZone());
    }

    /**
     * Sets the {@code Calendar} in this {@code CalendarTableModel}. Calls
     * {@link #invalidate} if {@link #isInMainRange} returns {@code false}.
     */
    public void setCalendar(Calendar cal) {
	boolean wouldInvalidate = wouldInvalidate(cal);
	this.cal = cal;
	if (wouldInvalidate) {
	    invalidate();
	}
    }

    /**
     * Sets the locale in this {@code CalendarTableModel} and calls
     * {@link #fireTableStructureChanged}.
     */
    public void setLocale(Locale locale) {
	if (!ObjectUtil.equals(this.locale, locale)) {
	    this.locale = locale;
	    fireTableStructureChanged();
	}
    }

    /**
     * Provides a default displayable value for the given {@code Calendar},
     * presumably contained in this model.
     */
    public abstract String toString(Calendar cal);

    //
    // Static methods
    //

    /**
     * Updates (if necessary) the given {@code DateFormat} with the time zone of
     * the given {@code Calendar}, then returns the formatted date string.
     */
    public static String format(DateFormat format, Calendar cal) {
	TimeZone zone = cal.getTimeZone();
	if (!format.getTimeZone().equals(zone)) {
	    format.setTimeZone(zone);
	}
	return format.format(cal.getTime());
    }
}
