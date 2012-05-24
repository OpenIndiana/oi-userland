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
 * Copyright (c) 2008, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.swing.view;

import java.util.*;
import javax.swing.RowSorter;
import javax.swing.RowSorter.SortKey;
import javax.swing.table.*;

@SuppressWarnings({"serial"})
public class SortableComparatorTableRowSorter<M extends TableModel>
    extends TableRowSorter<M> {

    //
    // Constructors
    //

    public SortableComparatorTableRowSorter() {
    }

    public SortableComparatorTableRowSorter(M model) {
	super(model);
    }

    //
    // DefaultRowSorter methods
    //

    @Override
    public void setSortKeys(List<? extends RowSorter.SortKey> keys) {
	for (RowSorter.SortKey key : keys) {
	    int column = key.getColumn();
	    Comparator comparator = getComparator(column);
	    if (comparator instanceof Sortable) {
		((Sortable)comparator).setSortOrder(
		    key.getSortOrder());
	    }
	}
	super.setSortKeys(keys);
    }
}
