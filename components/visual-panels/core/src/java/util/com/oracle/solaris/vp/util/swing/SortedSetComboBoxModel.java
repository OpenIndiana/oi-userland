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

@SuppressWarnings({"serial"})
public class SortedSetComboBoxModel<T extends Comparable<T>>
    extends AbstractListModel implements ComboBoxModel {

    //
    // Instance data
    //

    private List<T> items = new ArrayList<T>();
    private T selected;

    //
    // ListModel methods
    //

    @Override
    public T getElementAt(int index) {
	return items.get(index);
    }

    @Override
    public int getSize() {
	return items.size();
    }

    //
    // ComboBoxModel methods
    //

    @Override
    public T getSelectedItem() {
	return selected;
    }

    /**
     * Adds the given item to the model.
     *
     * @exception   ClassCastException
     *		    if the given {@code Object} is not of this {@code
     *		    SortedSetComboBoxModel}'s type
     */
    @Override
    @SuppressWarnings({"unchecked"})
    public void setSelectedItem(Object selected) {
	this.selected = (T)selected;

	// Taken from DefaultComboBoxModel
	fireContentsChanged(this, -1, -1);
    }

    //
    // SortedSetComboBoxModel methods
    //

    public int add(T item) {
	int index = Collections.binarySearch(items, item);
	if (index < 0) {
	    index = -index - 1;
	    items.add(index, item);
	    fireIntervalAdded(this, index, index);
	}

	return index;
    }

    public List<T> getItems() {
	List<T> copy = new ArrayList<T>(items.size());
	copy.addAll(items);
	return copy;
    }

    public T remove(int index) {
	T item = null;

	if (index >= 0) {
	    item = items.remove(index);
	    fireIntervalRemoved(this, index, index);
	}

	return item;
    }

    public boolean remove(T item) {
	return remove(Collections.binarySearch(items, item)) != null;
    }
}
