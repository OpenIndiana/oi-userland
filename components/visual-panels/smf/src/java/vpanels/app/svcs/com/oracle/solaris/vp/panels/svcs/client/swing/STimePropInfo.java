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

package com.oracle.solaris.vp.panels.svcs.client.swing;

import java.awt.Component;
import java.text.DateFormat;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.panel.common.smf.InstanceManagedObject;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class STimePropInfo extends SMOPropInfo<InstanceManagedObject, Date>
{
    private static final DateFormat datefmt =
	DateFormat.getDateInstance(DateFormat.MEDIUM);
    private static final DateFormat timefmt =
	DateFormat.getTimeInstance(DateFormat.MEDIUM);

    @SuppressWarnings({"serial"})
    private static final TableCellRenderer renderer =
	new DefaultTableCellRenderer() {
	    private static final int MS_PER_DAY = 24 * 60 * 60 * 1000;

	    @Override
	    public Component getTableCellRendererComponent(
		JTable table, Object value, boolean isSelected,
		boolean hasFocus, int row, int column)
	    {
		Date date = (Date)value;
		Date then = new Date((new Date()).getTime() - MS_PER_DAY);
		String stimestr = date == null ? "unknown" : date.after(then) ?
		    timefmt.format(date) : datefmt.format(date);
		JLabel label = (JLabel)super.getTableCellRendererComponent(
		    table, stimestr, isSelected, hasFocus, row, column);

		return (label);
	    }
	};

    private static final Comparator<Date> comparator = new Comparator<Date>() {
	    @Override
	    public int compare(Date o1, Date o2)
	    {
		return (ObjectUtil.compare(o1, o2));
	    }
	};

    /**
     * Available instance to mitigate object creation
     */
    public static final STimePropInfo instance = new STimePropInfo();

    /*
     * Constructors
     */

    public STimePropInfo() {
	super(Finder.getString("smf.objects.label.stime"),
	    Finder.getString("smf.objects.description.stime"),
	    renderer, comparator);
    }

    public Date getValue(InstanceManagedObject o) {
	return (o.getLastChange());
    }
}
