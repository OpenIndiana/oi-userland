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

package com.oracle.solaris.vp.util.swing;

import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.CollectionUtil;

/**
 * The {@code ListSelectionSynchronizer} class synchronizes two {@code
 * ListSelectionModel}s.  Useful if two or more components share a data model.
 */
public class ListSelectionSynchronizer implements ListSelectionListener {
    //
    // Inner classes
    //

    public static interface IndexMapper {
	public int map(int i);
    }

    //
    // Instance data
    //

    private ListSelectionModel tModel;
    private IndexMapper mapper;

    //
    // Constructors
    //

    public ListSelectionSynchronizer(
	ListSelectionModel tModel, IndexMapper mapper) {

	this.tModel = tModel;
	this.mapper = mapper;
    }

    public ListSelectionSynchronizer(ListSelectionModel tModel) {
	this(tModel, null);
    }

    //
    // ListSelectionListener methods
    //

    @Override
    public void valueChanged(ListSelectionEvent e) {
	if (!e.getValueIsAdjusting()) {
	    ListSelectionModel fModel = (ListSelectionModel)e.getSource();
	    List<Integer> fList = getSelectedIndexes(fModel, mapper);
	    List<Integer> tList = getSelectedIndexes(tModel, null);

	    List<Integer>[] interDiffs =
		CollectionUtil.getIntersectAndDiffs(tList, fList, null);

	    List<Integer> toRemove = interDiffs[1];
	    List<Integer> toAdd = interDiffs[2];

	    if (!toRemove.isEmpty() || !toAdd.isEmpty()) {
		tModel.setValueIsAdjusting(true);
		addOrRemove(toRemove, false);
		addOrRemove(toAdd, true);
		tModel.setValueIsAdjusting(false);
	    }
	}
    }

    //
    // Private methods
    //

    private void addOrRemove(List<Integer> iList, boolean add) {
	int n = iList.size();

	if (n > 0) {
	    int first = iList.get(0);

	    for (int i = 1; i < n; i++) {
		int last = iList.get(i - 1);
		int current = iList.get(i);

		if (current != last + 1) {
		    if (add) {
			tModel.addSelectionInterval(first, last);
		    } else {
			tModel.removeSelectionInterval(first, last);
		    }

		    first = current;
		}
	    }

	    if (add) {
		tModel.addSelectionInterval(first, iList.get(n - 1));
	    } else {
		tModel.removeSelectionInterval(first, iList.get(n - 1));
	    }
	}
    }

    private List<Integer> getSelectedIndexes(
	ListSelectionModel sModel, IndexMapper mapper) {

	List<Integer> iList = new ArrayList<Integer>();

	int iMin = sModel.getMinSelectionIndex();
	int iMax = sModel.getMaxSelectionIndex();

	for (int i = iMin; i <= iMax; i++) {
	    if (sModel.isSelectedIndex(i)) {
		iList.add(mapper == null ? i : mapper.map(i));
	    }
	}

	if (mapper != null) {
	    Collections.sort(iList);
	}

	return iList;
    }

    //
    // Static methods
    //

    /**
     * Synchronize a {@code JTable}'s selection model with that of {@code
     * JList}.  Changes in selection of either will be reflected in the other.
     * </p>
     * Note: unexpected behavior may result if the selection mode differs
     * between the two.
     *
     * @param	    table
     *		    a {@code JTable}
     *
     * @param	    list
     *		    {@code JList}
     */
    public static void syncSelection(final JTable table, JList list) {
	ListSelectionModel tsModel = table.getSelectionModel();
	ListSelectionModel lModel = list.getSelectionModel();

	// Sync changes to lModel with tsModel
	lModel.addListSelectionListener(
	    new ListSelectionSynchronizer(tsModel,
	    new ListSelectionSynchronizer.IndexMapper() {
		@Override
		public int map(int i) {
		    return table.convertRowIndexToView(i);
		}
	    }));

	// Sync changes to tsModel with lModel
	tsModel.addListSelectionListener(
	    new ListSelectionSynchronizer(lModel,
	    new ListSelectionSynchronizer.IndexMapper() {
		@Override
		public int map(int i) {
		    return table.convertRowIndexToModel(i);
		}
	    }));
    }

    /**
     * Synchronize two {@code JTable}s' selection models.  Changes in selection
     * of either will be reflected in the other.
     * </p>
     * Note: unexpected behavior may result if the selection mode differs
     * between the two.
     *
     * @param	    table1
     *		    a {@code JTable}
     *
     * @param	    table2
     *		    a {@code JTable}
     */
    public static void syncSelection(
	final JTable table1, final JTable table2) {

	ListSelectionModel model1 = table1.getSelectionModel();
	ListSelectionModel model2 = table2.getSelectionModel();

	// Sync changes to model2 with model1
	model2.addListSelectionListener(
	    new ListSelectionSynchronizer(model1,
	    new ListSelectionSynchronizer.IndexMapper() {
		@Override
		public int map(int i) {
		    return table1.convertRowIndexToView(
			table2.convertRowIndexToModel(i));
		}
	    }));

	// Sync changes to model1 with model2
	model1.addListSelectionListener(
	    new ListSelectionSynchronizer(model2,
	    new ListSelectionSynchronizer.IndexMapper() {
		@Override
		public int map(int i) {
		    return table2.convertRowIndexToView(
			table1.convertRowIndexToModel(i));
		}
	    }));
    }
}
