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
import javax.swing.ListModel;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.CollectionUtil;
import com.oracle.solaris.vp.util.misc.predicate.*;
import com.oracle.solaris.vp.util.swing.event.ListDataListeners;

/**
 * The {@code FilteredListModel} class applies a {@link Predicate} filter to a
 * {@code Collection} to produce the contents of a {@code ListModel}.
 */
public class FilteredListModel<T> implements ListModel {
    //
    // Instance data
    //

    private ListDataListeners listeners = new ListDataListeners();
    private Collection<T> items;
    private List<T> filtered = Collections.emptyList();
    private Predicate<T> predicate;

    //
    // Constructors
    //

    /**
     * Constructs a {@code FilteredListModel} for the given items and filter.
     * Note: the behavior of this class is undefined if the given {@code
     * Collection} changes after this object's construction.
     *
     * @param	    items
     *		    the unfiltered data {@code Collection}
     *
     * @param	    predicate
     *		    an initial filter to apply, or {@code null} to apply no
     *		    filter
     */
    public FilteredListModel(Collection<T> items, Predicate<T> predicate) {
	this.items = items;
	setPredicate(predicate);
    }

    /**
     * Constructs a {@code FilteredListModel} for the given items and no filter.
     *
     * @param	    items
     *		    the unfiltered data {@code Collection}
     */
    public FilteredListModel(Collection<T> items) {
	this(items, null);
    }

    //
    // ListModel methods
    //

    @Override
    public void addListDataListener(ListDataListener l) {
	listeners.add(l);
    }

    @Override
    public T getElementAt(int index) {
	return filtered.get(index);
    }

    @Override
    public int getSize() {
	return filtered.size();
    }

    @Override
    public void removeListDataListener(ListDataListener l) {
	listeners.remove(l);
    }

    //
    // FilteredListModel methods
    //

    protected void fireContentsChanged(int start, int end) {
	ListDataEvent event = new ListDataEvent(this,
	    ListDataEvent.CONTENTS_CHANGED, start, end);
	listeners.contentsChanged(event);
    }

    protected void fireIntervalAdded(int start, int end) {
	ListDataEvent event = new ListDataEvent(this,
	    ListDataEvent.INTERVAL_ADDED, start, end);
	listeners.intervalAdded(event);
    }

    protected void fireIntervalRemoved(int start, int end) {
	ListDataEvent event = new ListDataEvent(this,
	    ListDataEvent.INTERVAL_REMOVED, start, end);
	listeners.intervalRemoved(event);
    }

    protected List<T> getFiltered() {
	return Collections.unmodifiableList(filtered);
    }

    protected ListDataListeners getListeners() {
	return listeners;
    }

    /**
     * Gets the {@link Predicate} applied to the data {@code Collection} for
     * this {@code FilteredListModel}.
     *
     * @return	    a {@link Predicate}, or {@code null} if no filter is applied
     */
    public Predicate<T> getPredicate() {
	return predicate;
    }

    /**
     * Sets the {@link Predicate} to apply to the data {@code Collection} for
     * this {@code FilteredListModel}.
     *
     * @param	    predicate
     *		    a {@link Predicate}, or {@code null} if no filter should be
     *		    applied
     */
    public void setPredicate(Predicate<T> predicate) {
	this.predicate = predicate;

	if (predicate == null) {
	    predicate = TruePredicate.getInstance();
	}

	int size = filtered.size();
	if (size > 0) {
	    filtered = Collections.emptyList();
	    fireIntervalRemoved(0, size - 1);
	}

	filtered = CollectionUtil.filter(items, predicate);
	size = filtered.size();
	if (size > 0) {
	    fireIntervalAdded(0, size - 1);
	}
    }
}
