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
import java.util.Comparator;
import javax.swing.*;
import javax.swing.table.*;
import com.oracle.solaris.vp.panel.common.api.smf_old.SmfState;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class StatePropInfo extends SMOPropInfo<InstanceManagedObject, SmfState>
{
    /*
     * Static data
     */

    @SuppressWarnings({"serial"})
    private static final TableCellRenderer renderer =
	new DefaultTableCellRenderer() {
	    @Override
	    public Component getTableCellRendererComponent(
		JTable table, Object value, boolean isSelected,
		boolean hasFocus, int row, int column)
	    {
		SmfState state = (SmfState)value;
		String statestr = ServiceUtil.getStateString(state);
		JLabel label = (JLabel)super.getTableCellRendererComponent(
		    table, statestr, isSelected, hasFocus, row, column);

		return (label);
	    }
	};

    private static final Comparator<SmfState> comparator =
	new Comparator<SmfState>() {
	    @Override
	    public int compare(SmfState o1, SmfState o2)
	    {
		return (o1.compareTo(o2));
	    }
	};

    /**
     * Available instance to mitigate object creation
     */
    public static final StatePropInfo instance = new StatePropInfo();

    /*
     * Constructors
     */

    public StatePropInfo() {
	super(Finder.getString("smf.objects.label.state"),
	    Finder.getString("smf.objects.description.state"),
	    renderer, comparator);
    }

    public SmfState getValue(InstanceManagedObject o) {
	return (o.getSMFState());
    }
}
