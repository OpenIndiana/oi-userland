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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.swing.model;

import java.awt.Component;
import java.util.Comparator;
import javax.swing.JTable;
import javax.swing.table.TableCellRenderer;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.swing.view.ManagedObjectCellRenderer;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.SimpleCellRenderer;
import com.oracle.solaris.vp.util.swing.propinfo.AbstractSwingPropInfo;

public class ManagedObjectPropInfo<M extends ManagedObject>
    extends AbstractSwingPropInfo<M, M> {

    //
    // Static data
    //

    /**
     * Available instance to mitigate object creation
     */
    public static final ManagedObjectPropInfo instance =
	new ManagedObjectPropInfo();

    private static final SimpleCellRenderer renderer =
	new ManagedObjectCellRenderer() {

	@Override
	public String getStatusText(Component comp, ManagedObject obj,
	    boolean isSelected, boolean hasFocus) {

	    return (null);
	}
    };

    static {
	renderer.configureFor((JTable)null);
    }

    //
    // Instance data
    //

    private final Comparator<M> comparator =
	new Comparator<M>() {
	    @Override
	    public int compare(M o1, M o2) {
		return o1.getName().compareTo(o2.getName());
	    }
	};

    //
    // Constructors
    //

    public ManagedObjectPropInfo() {
	super(Finder.getString("property.name.label"),
	    Finder.getString("property.name.description"), true, false);
    }

    //
    // ManagedObjectPropInfo methods
    //

    @Override
    public Comparator<M> getComparator() {
	return comparator;
    }

    @Override
    public M getValue(M o) {
	return o;
    }

    //
    // SwingPropInfo methods
    //

    @Override
    public TableCellRenderer getTableCellRenderer() {
	return renderer;
    }
}
