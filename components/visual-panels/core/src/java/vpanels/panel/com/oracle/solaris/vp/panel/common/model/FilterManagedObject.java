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

package com.oracle.solaris.vp.panel.common.model;

import java.beans.*;
import java.util.*;
import com.oracle.solaris.vp.util.misc.event.*;
import com.oracle.solaris.vp.util.misc.predicate.*;

/**
 * Generic {@code ManagedObject} implementation that filters the children of
 * a {@code ManagedObject}.  Only those children that satisfy a provided
 * {@code Predicate} appear to be children of the {@code FilterManagedObject}.
 */
public class FilterManagedObject<T extends ManagedObject>
    extends ManagedObjectMonitor<T>
    implements ManagedObject<T>, PropertyChangeListener
{
    private Predicate<? super T> pred_;	/** The selection predicate */

    private IntervalListeners iListeners_ = new IntervalListeners();

    /*
     * These four are protected by synchronizing on "children_"
     */
    private List<Integer> childMap_ = new ArrayList<Integer>();
    private final List<T> children_ = new ArrayList<T>();
    private List<T> roChildren_ = Collections.unmodifiableList(children_);

    /**
     * Constructs a FilterManagedObject.
     *
     * @param wrappee the {@code ManagedObject} whose children are to
     * be filtered
     * @param predicate the {@code Predicate} that determines which children
     * are seen
     */
    public FilterManagedObject(ManagedObject<T> wrappee,
	Predicate<? super T> predicate)
    {
	super(wrappee);

	pred_ = predicate;

	/*
	 * Should probably be implemented in terms of intervalAdded(), like
	 * setManagedObject() is.
	 */
	synchronized (getManagedObject().getChildrenLock()) {
	    List<T> children = getManagedObject().getChildren();
	    int loc = 0;
	    for (T child : children) {
		if (pred_.test(child)) {
		    children_.add(child);
		    childMap_.add(loc);
		    loc++;
		} else {
		    childMap_.add(null);
		}
	    }

	    getManagedObject().addPropertyChangeListener(this);
	}
    }

    public FilterManagedObject(ManagedObject<T> wrappee) {
	this(wrappee, new TruePredicate<T>());
    }

    /**
     * Replaces the predicate used by the FilterManagedObject.
     *
     * @param predicate the new {@code Predicate} to use
     */
    public void setPredicate(Predicate<? super T> predicate)
    {
	IntervalEventQueue ieq = new IntervalEventQueue(this, iListeners_);

	synchronized (getManagedObject().getChildrenLock()) {
	    synchronized (children_) {
		List<T> children = getManagedObject().getChildren();

		int loc = 0;
		int size = children.size();
		for (int i = 0; i < size; i++) {
		    T o = children.get(i);
		    boolean matches = predicate.test(o);
		    Integer mapping = childMap_.get(i);
		    if (mapping != null) {
			if (matches) {
			    if (mapping != loc)
				childMap_.set(i, loc);
			    loc++;
			} else {
			    ieq.addIndex(loc, IntervalEventQueue.Type.REMOVE);
			    children_.remove(loc);
			    childMap_.set(i, null);
			}
		    } else {
			if (matches) {
			    ieq.addIndex(loc, IntervalEventQueue.Type.ADD);
			    children_.add(loc, o);
			    childMap_.set(i, loc);
			    loc++;
			} /* else do nothing */
		    }
		}
		ieq.flush();
		pred_ = predicate;
	    }
	}
    }

    /**
     * Refreshes the child view.  Used if the behavior of the
     * predicate changes.
     */
    public void refreshPredicate()
    {
	setPredicate(pred_);
    }

    /**
     * Given the index of an entry to add to the inbound children list,
     * find the appropriate location in the outbound children list.
     *
     * @param index the index of the new inbound child
     * @return the index of the corresponding outbound child
     */
    private int findNewMapping(int index)
    {
	int oldsize = childMap_.size();
	int result;

	assert (index <= oldsize);

	if (oldsize == 0) {
	    /* Adding to an empty list; the first index must be 0 */
	    result = 0;
	} else {
	    Integer mapping;
	    result = -1;

	    /* Find the last non-null entry... */
	    if (index > 0) {
		for (int i = index - 1; i >= 0; i--)
		    if ((mapping = childMap_.get(i)) != null) {
			result = mapping + 1;
			break;
		    }
	    }

	    /* ...failing that, the next non-null entry. */
	    if (result == -1 && index < oldsize) {
		for (int i = index; i < oldsize; i++)
		    if ((mapping = childMap_.get(i)) != null) {
			result = mapping;
			break;
		    }
	    }

	    /* Our mapping is empty; start at the beginning. */
	    if (result == -1)
		result = 0;
	}

	return (result);
    }

    /**
     * Shifts all non-null mappings after a point by the specified amount.
     *
     * @param start the first index whose value should be adjusted
     * @param delta the amount by which values should be adjusted
     */
    private void adjustMappings(int start, int delta)
    {
	int size = childMap_.size();
	for (int i = start; i < size; i++) {
	    Integer mapping = childMap_.get(i);
	    if (mapping != null) {
		assert (mapping + delta >= 0);
		childMap_.set(i, mapping + delta);
	    }
	}
    }

    /*
     * ManagedObject methods
     */

    @Override
    public void dispose() {
    }

    @Override
    public String getId()
    {
	return (getManagedObject().getId());
    }

    @Override
    public String getDescription()
    {
	return (getManagedObject().getDescription());
    }

    @Override
    public List<T> getChildren()
    {
	return (roChildren_);
    }

    @Override
    public Object getChildrenLock()
    {
	return (children_);
    }

    @Override
    public String getName()
    {
	return (getManagedObject().getName());
    }

    @Override
    public ManagedObjectStatus getStatus()
    {
	return (getManagedObject().getStatus());
    }

    @Override
    public String getStatusText()
    {
	return (getManagedObject().getStatusText());
    }

    @Override
    public void addIntervalListener(IntervalListener l)
    {
	iListeners_.add(l);
    }

    @Override
    public boolean removeIntervalListener(IntervalListener l)
    {
	return (iListeners_.remove(l));
    }

    /*
     * PropertyChangeListener methods
     */

    @Override
    public void propertyChange(PropertyChangeEvent evt)
    {
	Object source = evt.getSource();

	/* Throw away events from children we aren't exposing. */
	synchronized (children_) {
	    if (listenees_.contains(source) && !children_.contains(source))
		return;

	    pListeners_.propertyChange(evt);
	}
    }

    /*
     * IntervalListener methods
     */

    @Override
    public void intervalAdded(IntervalEvent e)
    {
	/* synchronized (getManagedObject().getChildrenLock()) implied */
	synchronized (children_) {
	    super.intervalAdded(e);

	    int f = e.getFirstIndex();
	    int l = e.getLastIndex();
	    int first = findNewMapping(f);
	    int last = first;
	    int i;

	    List<T> adds = listenees_.subList(f, l + 1);
	    i = f;
	    for (T o : adds) {
		if (pred_.test(o)) {
		    childMap_.add(i, last);
		    children_.add(last, o);
		    last++;
		} else {
		    childMap_.add(i, null);
		}
		i++;
	    }

	    if (--last >= first) {
		adjustMappings(l + 1, last - first + 1);
		iListeners_.intervalAdded(new IntervalEvent(this, first, last));
	    }
	}
    }

    @Override
    public void intervalRemoved(IntervalEvent e)
    {
	/* synchronized (inner_.getChildrenLock()) implied */
	synchronized (children_) {
	    int f = e.getFirstIndex();
	    int l = e.getLastIndex();

	    super.intervalRemoved(e);

	    /* Find mapping in codomain, remove from domain */
	    int first = children_.size();
	    int last = -1;
	    for (int i = f; i <= l; i++) {
		Integer mapping = childMap_.get(f);
		childMap_.remove(f);
		if (mapping != null) {
		    if (mapping < first)
			first = mapping;
		    if (mapping > last)
			last = mapping;
		}
	    }

	    /* Remove from codomain */
	    children_.subList(first, last + 1).clear();

	    if (first <= last) {
		adjustMappings(f, - (last - first + 1));
		iListeners_.intervalRemoved(
		    new IntervalEvent(this, first, last));
	    }
	}
    }

    //
    // ManagedObjectMonitor methods
    //

    @Override
    public void setManagedObject(ManagedObject<T> mo) {
	synchronized (this) {
	    getManagedObject().removePropertyChangeListener(this);
	    super.setManagedObject(mo);
	    mo.addPropertyChangeListener(this);
	}
    }

    /**
     * Called by the PropertyChangeListener registered with inbound
     * children.  Makes appropriate change to outbound children list.
     */
    @Override
    protected void managedObjectPropertyChange(T child, PropertyChangeEvent evt)
    {
	synchronized (children_) {
	    int index = listenees_.indexOf(child);
	    boolean match = pred_.test(child);
	    Integer mapping = childMap_.get(index);
	    if (match && mapping == null) {
		/* Needs to be added to exported model */
		mapping = findNewMapping(index);
		children_.add(mapping, child);
		childMap_.set(index, mapping);
		adjustMappings(index + 1, 1);
		iListeners_.intervalAdded(
		    new IntervalEvent(this, mapping, mapping));
	    } else if (!match && mapping != null) {
		/* Needs to be removed from exported model */
		children_.remove(mapping.intValue());
		childMap_.set(index, null);
		adjustMappings(index + 1, -1);
		iListeners_.intervalRemoved(
		    new IntervalEvent(this, mapping, mapping));
	    }
	}
    }
}
