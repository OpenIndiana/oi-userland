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
import java.util.logging.Logger;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.event.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;

public abstract class AbstractManagedObject<C extends ManagedObject>
    implements ManagedObject<C> {

    //
    // Instance data
    //

    private String id;
    private String name;
    private ManagedObjectStatus status = ManagedObjectStatus.HEALTHY;
    private String statusText;

    private IntervalListeners iListeners = new IntervalListeners();
    private IntervalEventQueue eventQueue =
	new IntervalEventQueue(this, iListeners);

    private PropertyChangeListeners pListeners =
	new PropertyChangeListeners();

    protected final List<C> children = new ArrayList<C>();
    private List<C> roChildren = Collections.unmodifiableList(children);

    private Comparator<? super C> comparator;

    protected PropertyChangeListener sortListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent e) {
		resortChildren();
	    }
	};

    protected PropertyChangeListener statusListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent e) {
		setStatus();
	    }
	};

    private Map<String, MutableProperty<?>> properties =
	new HashMap<String, MutableProperty<?>>();

    private PropertyChangeListener propFwdListener =
	new PropertyChangeForwarder(this);

    private ChangeableAggregator aggregator = new ChangeableAggregator(
	DebugUtil.toBaseName(this));

    //
    // Constructors
    //

    public AbstractManagedObject(String id) {
	this.id = id;
	setStatus();
    }

    public AbstractManagedObject() {
	this(null);
    }

    //
    // PropertyChangeEventSource methods
    //

    @Override
    public void addPropertyChangeListener(PropertyChangeListener l) {
	pListeners.add(l);
    }

    @Override
    public void addPropertyChangeListener(String property,
	PropertyChangeListener l) {

	pListeners.add(property, l);
    }

    @Override
    public boolean removePropertyChangeListener(PropertyChangeListener l) {
	return (pListeners.remove(l));
    }

    @Override
    public boolean removePropertyChangeListener(String property,
	PropertyChangeListener l) {

	return (pListeners.remove(property, l));
    }

    //
    // ManagedObject methods
    //

    /**
     * Removes this {@code AbstractManagedObject}'s children.
     */
    @Override
    public void dispose() {
	clearChildren();
    }

    /**
     * Returns a read-only wrapper around the list of children maintained by
     * this class via the {@link #addChildren} and {@link #removeChildren}
     * methods.
     */
    @Override
    public List<C> getChildren() {
	return roChildren;
    }

    @Override
    public Object getChildrenLock() {
	return children;
    }

    /**
     * Default implementation that returns {@code null}.
     */
    @Override
    public String getDescription() {
	return null;
    }

    /**
     * Returns the ID passed to the constructor of this {@code
     * AbstractManagedObject}.
     */
    @Override
    public String getId() {
	return id;
    }

    /**
     * Returns the name of this {@code AbstractManagedObject} if it is {@link
     * #setName set} and non-{@code null}, {@code null} otherwise.
     */
    @Override
    public String getName() {
	return name == null ? getId() : name;
    }

    /**
     * Returns the value set with {@link #setStatus(ManagedObjectStatus)}.
     */
    @Override
    public ManagedObjectStatus getStatus() {
	return status;
    }

    /**
     * Returns the value set with {@link #setStatusText}.
     */
    @Override
    public String getStatusText() {
	return statusText;
    }

    //
    // IntervalEventSource methods
    //

    @Override
    public void addIntervalListener(IntervalListener l) {
	iListeners.add(l);
    }

    @Override
    public boolean removeIntervalListener(IntervalListener l) {
	return (iListeners.remove(l));
    }

    //
    // Object methods
    //

    @Override
    public String toString() {
	return getName();
    }

    //
    // AbstractManagedObject methods
    //

    /**
     * Adds the given {@link ManagedObject}s to this {@code
     * AbstractManagedObject}'s child list.
     */
    public void addChildren(C... toAdd) {
	Comparator<? super C> comparator = getComparator();
	if (comparator != null) {
	    Arrays.sort(toAdd, comparator);
	}

	synchronized (children) {
	    try {
		// Iterate through, adding the given children.  Minimize
		// notifications by grouping additions into intervals.
		for (C child : toAdd) {
		    // Insertion point in list
		    int index;

		    if (comparator == null) {
			index = children.size();
		    } else {
			index = Collections.binarySearch(
			    children, child, comparator);
			if (index < 0) {
			    index = -1 - index;
			}
		    }

		    child.addPropertyChangeListener(sortListener);
		    child.addPropertyChangeListener(statusListener);

		    eventQueue.addIndex(index,
			IntervalEventQueue.Type.ADD);
		    children.add(index, child);
		}
	    } finally {
		eventQueue.flush();
	    }

	    setStatus();
	}
    }

    /**
     * Adds the given {@link MutableProperty}s to the {@link #getProperties
     * list} of such.  Changes in the given properties are forwarded to {@code
     * PropertyChangeListener}s of this class.  These properties are
     * automatically added to this {@code AbstractManagedObject}'s {@link
     * #getChangeableAggregator ChangeableAggregator}.
     */
    protected void addProperties(MutableProperty<?>... properties) {
	for (MutableProperty<?> property : properties) {
	    this.properties.put(property.getPropertyName(), property);
	    property.addPropertyChangeListener(propFwdListener);
	    aggregator.addChangeables(property);
	}
    }

    /**
     * Removes all children.
     *
     * @see	    #removeChildren
     */
    public void clearChildren() {
	synchronized (children) {
	    @SuppressWarnings({"unchecked"})
	    C[] array = (C[])new ManagedObject[children.size()];
	    array = children.toArray(array);

	    removeChildren(array);
	}
    }

    protected void firePropertyChange(PropertyChangeEvent e) {
	pListeners.propertyChange(e);
    }

    protected void firePropertyChange(String property, Object oldValue,
	Object newValue) {

	PropertyChangeEvent e = new PropertyChangeEvent(
	    this, property, oldValue, newValue);

	firePropertyChange(e);
    }

    /**
     * Calculates the status of this {@code ManagedObject} based on the status
     * of its children.
     */
    protected ManagedObjectStatus getCalculatedStatus() {
	return (Util.getMostSevereStatus(getChildren()));
    }

    /**
     * Calculates the status text of this {@code ManagedObject} based on its
     * status.
     */
    protected String getCalculatedStatusText() {
	ManagedObjectStatus status = getStatus();
	String resource = "status." +
	    (status == null ? "unknonwn" : status.toString().toLowerCase());
	return Finder.getString(resource);
    }

    /**
     * Gets the {@link ChangeableAggregator} that can be used to track changes
     * to this {@code AbstractManagedObject}.  This aggregator tracks changes to
     * {@link #addProperties properties} of this object by default.
     */
    public ChangeableAggregator getChangeableAggregator() {
	return aggregator;
    }

    /**
     * Gets the {@code Comparator} to use when sorting or searching for
     * children.
     *
     * @return	    a {@code Comparator}, or {@code null} if the child list
     *		    should remain in the order in which its elements were added
     */
    public Comparator<? super C> getComparator() {
	return comparator;
    }

    /**
     * Gets the {@link MutableProperty} of the given name from this
     * ManagedObject's list of such.
     *
     * @return	    a {@code MutableProperty}, or {@code null} if this {@code
     *		    ManagedObject} has no such property
     */
    public MutableProperty<?> getProperty(String name) {
	return properties.get(name);
    }

    /**
     * Gets an unmodifiable wrapper around this {@link ManagedObject}'s list of
     * properties.
     */
    public Collection<MutableProperty<?>> getProperties() {
	return Collections.unmodifiableCollection(properties.values());
    }

    /**
     * Returns the index of the given child in this {@code
     * AbstractManagedObject}'s child list.
     *
     * @param	    child
     *		    the child to search for
     *
     * @return	    the index, or a negative value if {@code child} is not found
     */
    public int indexOf(C child) {
	synchronized (children) {
	    return comparator == null ?
		children.indexOf(child) :
		Collections.binarySearch(children, child, comparator);
	}
    }

    /**
     * Removes the given children if they are present.
     */
    public void removeChildren(C... toRemove) {
	Comparator<? super C> comparator = getComparator();
	if (comparator != null) {
	    Arrays.sort(toRemove, comparator);
	}

	synchronized (children) {
	    try {
		// Iterate through, removing the given children.  Minimze
		// notifications by grouping removals into intervals.
		for (C child : toRemove) {
		    int index = comparator == null ?
			children.indexOf(child) :
			Collections.binarySearch(children, child, comparator);

		    if (index >= 0) {
			child.removePropertyChangeListener(sortListener);
			child.removePropertyChangeListener(statusListener);

			eventQueue.addIndex(index,
			    IntervalEventQueue.Type.REMOVE);
			children.remove(index);
		    }
		}
	    } finally {
		eventQueue.flush();
	    }

	    setStatus();
	}
    }

    /**
     * Removes the given {@link MutableProperty}s from the list of such.
     */
    protected void removeProperties(MutableProperty<?>... properties) {
	for (MutableProperty<?> property : properties) {
	    property.removePropertyChangeListener(propFwdListener);
	    this.properties.remove(property.getPropertyName());
	    aggregator.removeChangeable(property);
	}
    }

    /**
     * Resorts the child {@link ManagedObject}s according to the set {@link
     * Comparator}, if any.  This method is called automatically when any child
     * {@code ManagedObject} changes.
     */
    protected void resortChildren() {
	Comparator<? super C> comparator = getComparator();
	if (comparator != null) {
	    synchronized (children) {
		List<C> sorted = new ArrayList<C>(children);
		Collections.sort(sorted, comparator);

		// Now transform children into sorted via add/remove so that the
		// appropriate IntervalEvents can be sent out
		int length = children.size();
		for (int i = 0; i < length; i++) {
		    C current = sorted.get(i);

                    // Group 1 is the group of children from index i, inclusive,
                    // to the child that should be at index i, exclusive
		    int group1Len = 0;
		    for (; children.get(i + group1Len) != current; group1Len++);

		    if (group1Len != 0) {
                        // Group 2 is the group of children between group 1 and
                        // the next child that is out of order, exclusive
			int group2Len = 1;
			for (; i + group1Len + group2Len < length &&
			    children.get(i + group1Len + group2Len) ==
			    sorted.get(i + group2Len); group2Len++);

			int delFrom;
			int addFrom;
			int grpLen;

			// Move the smallest group
			if (group1Len < group2Len) {
			    delFrom = i;
			    addFrom = i + group2Len;
			    grpLen = group1Len;
			} else {
			    delFrom = i + group1Len;
			    addFrom = i;
			    grpLen = group2Len;
			}

			List<C> sub = children.subList(delFrom,
			    delFrom + grpLen);
			List<C> moved = new ArrayList<C>(sub);
			sub.clear();
                        eventQueue.addInterval(delFrom, delFrom + grpLen - 1,
			    IntervalEventQueue.Type.REMOVE);

			children.addAll(addFrom, moved);
                        eventQueue.addInterval(addFrom, addFrom + grpLen - 1,
			    IntervalEventQueue.Type.ADD);
			eventQueue.flush();

			i += group2Len - 1;
		    }
		}
	    }
	}
    }

    /**
     * Sets the {@code Comparator} to use when sorting or searching for
     * children.
     *
     * @param	    comparator
     *		    a {@code Comparator}, or {@code null} if the child list
     *		    should remain in the order in which its elements were added
     */
    protected void setComparator(Comparator<? super C> comparator) {
	synchronized (children) {
	    this.comparator = comparator;
	    resortChildren();
	}
    }

    protected void setName(String name) {
	if (!ObjectUtil.equals(this.name, name)) {
	    Object old = name;
	    this.name = name;
	    firePropertyChange(PROPERTY_NAME, old, name);
	}
    }

    /**
     * {@link #getCalculatedStatus Calculates} and {@link
     * #setStatus(ManagedObjectStatus) sets} the status of this {@link
     * ManagedObject}.
     */
    public void setStatus() {
	ManagedObjectStatus status = getCalculatedStatus();
	setStatus(status);
    }

    /**
     * Sets the status of this {@link ManagedObject}.
     */
    public void setStatus(ManagedObjectStatus status) {
	if (this.status != status) {
	    Object old = status;
	    this.status = status;
	    firePropertyChange(PROPERTY_STATUS, old, status);
	}
    }

    /**
     * {@link #getCalculatedStatusText Calculates} and {@link
     * #setStatusText(String) sets} the status text of this {@link
     * ManagedObject}.
     */
    public void setStatusText() {
	String text = getCalculatedStatusText();
	setStatusText(text);
    }

    /**
     * Sets the status text of this {@link ManagedObject}.
     */
    public void setStatusText(String statusText) {
	if (!ObjectUtil.equals(this.statusText, statusText)) {
	    Object old = statusText;
	    this.statusText = statusText;
	    firePropertyChange(PROPERTY_STATUS_TEXT, old, statusText);
	}
    }

    /**
     * Gets the {@code Logger} for the client. Note that the Logger name shall
     * be derived from the class package name. If this class is extended, the
     * subclass package name is used.
     */
    protected Logger getLog() {
	return Logger.getLogger(getClass().getPackage().getName());
    }

    //
    // Private methods
    //

    private int indexOf(List<C> children, C child) {
	return comparator == null ?
	    children.indexOf(child) :
	    Collections.binarySearch(children, child, comparator);
    }
}
