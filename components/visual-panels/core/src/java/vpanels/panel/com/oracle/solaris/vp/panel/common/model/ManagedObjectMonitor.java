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

package com.oracle.solaris.vp.panel.common.model;

import java.beans.*;
import java.util.*;
import com.oracle.solaris.vp.util.misc.event.*;

/**
 * An abstract superclass for classes that need the ability to monitor
 * the existence of and property changes in children of a managed object.
 * The essential functionality provided by this class is registering
 * {@code PropertyChangeListener}s with all children, and keeping track of
 * which children it is listening to so it can property deregister itself
 * on interval updates (which come too late to reference the managed
 * object's children list).
 *
 * Also includes PropertyChangeEventSource functionality.  This is primarily
 * a convenience to the classes's two subclasses, so we might ultimately
 * deem it extravagant and want to pull it out.
 *
 * {@code AbstractManagedObject} already listens to all its children for
 * status and sorting purposes, so another possibility would be to add child
 * event aggregation to the managed object interface.  The question is
 * whether we want to force that on all {@code ManagedObject}s.
 */
public abstract class ManagedObjectMonitor<T extends ManagedObject>
    implements IntervalListener, PropertyChangeEventSource
{
    protected ManagedObject<T> objects_;
    protected final List<T> listenees_ = new ArrayList<T>();
    protected final PropertyChangeListeners pListeners_ =
	new PropertyChangeListeners();

    private PropertyChangeListener managedObjectListener_ =
	new PropertyChangeListener() {

	@SuppressWarnings("unchecked")
	public void propertyChange(PropertyChangeEvent evt) {
	    Object source = evt.getSource();

	    /*
	     * Whether this is correct or not depends on whether we
	     * insist on a convention where managed objects only emit
	     * PropertyChangeEvents that originate from themselves (or
	     * managed objects of the same type).
	     *
	     * It's probably worth doing so.
	     */
	    managedObjectPropertyChange((T)source, evt);
	}
    };

    public ManagedObjectMonitor(ManagedObject<T> objects)
    {
	objects_ = objects;
	synchronized (objects_.getChildrenLock()) {
	    objects_.addIntervalListener(this);
	    listenees_.addAll(objects_.getChildren());
	    for (T obj : objects_.getChildren())
		obj.addPropertyChangeListener(managedObjectListener_);
	}
    }

    public ManagedObjectMonitor()
    {
	this(new EmptyManagedObject<T>());
    }


    protected void managedObjectPropertyChange(T obj, PropertyChangeEvent evt)
    {
	/* Empty implementation; don't force subclasses to implement */
    }

    public ManagedObject<T> getManagedObject()
    {
	return objects_;
    }

    public void setManagedObject(ManagedObject<T> mo)
    {
	synchronized (this) {
	    /*
	     * Detach ourselves from the inner managed object
	     */
	    if (objects_ != null) {
		synchronized (objects_.getChildrenLock()) {
		    objects_.removeIntervalListener(this);
		    int size = objects_.getChildren().size();
		    if (size > 0)
			intervalRemoved(
			    new IntervalEvent(objects_, 0, size - 1));
		}
		objects_ = null;
	    }

	    /*
	     * Attach ourselves to the new inner managed object
	     */
	    objects_ = (mo == null) ? new EmptyManagedObject<T>() : mo;
	    synchronized (objects_.getChildrenLock()) {
		int size = objects_.getChildren().size();
		if (size > 0)
		    intervalAdded(new IntervalEvent(objects_, 0, size - 1));
		objects_.addIntervalListener(this);
	    }
	}
    }

    /*
     * IntervalListener methods
     */

    @Override
    public void intervalAdded(IntervalEvent event) {
	List<T> inserted = objects_.getChildren().subList(event.getFirstIndex(),
	    event.getLastIndex() + 1);
	for (T obj : inserted)
	    obj.addPropertyChangeListener(managedObjectListener_);
	synchronized (listenees_) {
	    listenees_.addAll(event.getFirstIndex(), inserted);
	}
    }

    @Override
    public void intervalRemoved(IntervalEvent event) {
	synchronized (listenees_) {
	    List<T> deleted = listenees_.subList(event.getFirstIndex(),
		event.getLastIndex() + 1);
	    for (T obj : deleted)
		obj.removePropertyChangeListener(managedObjectListener_);
	    deleted.clear();
	}
    }

    /*
     * PropertyChangeEventSource methods
     */

    public void addPropertyChangeListener(PropertyChangeListener l)
    {
	pListeners_.add(l);
    }

    public void addPropertyChangeListener(String property,
	PropertyChangeListener l)
    {
	pListeners_.add(property, l);
    }

    public boolean removePropertyChangeListener(String property,
	PropertyChangeListener l)
    {
	return (pListeners_.remove(property, l));
    }

    public boolean removePropertyChangeListener(PropertyChangeListener l)
    {
	return (pListeners_.remove(l));
    }
}
