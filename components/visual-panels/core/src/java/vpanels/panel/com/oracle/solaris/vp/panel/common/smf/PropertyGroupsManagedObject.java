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

package com.oracle.solaris.vp.panel.common.smf;

import java.beans.*;
import java.util.*;
import java.util.logging.*;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.api.smf_old.PropertyGroup;
import com.oracle.solaris.vp.panel.common.model.AbstractManagedObject;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class PropertyGroupsManagedObject
    extends AbstractManagedObject<PropertyGroupManagedObject> {

    //
    // Static data
    //

    public static final String ID = "properties";
    public static final String NAME = Finder.getString("properties.name");

    public static final Comparator<Object> COMPARATOR =
	new Comparator<Object>() {
	    @Override
	    public int compare(Object o1, Object o2) {
		if (o1 == null) {
		    return o2 == null ? 0 : -1;
		}

		if (o2 == null) {
		    return 1;
		}

		String name1 = o1 instanceof PropertyGroupManagedObject ?
                    ((PropertyGroupManagedObject)o1).getName() :
		    o1 instanceof PropertyGroup ?
                    ((PropertyGroup)o1).getName() : null;

		String name2 = o2 instanceof PropertyGroupManagedObject ?
                    ((PropertyGroupManagedObject)o2).getName() :
		    o2 instanceof PropertyGroup ?
                    ((PropertyGroup)o2).getName() : null;

		return ObjectUtil.compare(name1, name2);
	    }
	};

    private static final String PROPERTY_GROUP_APP = "application";

    //
    // Instance data
    //

    private ServiceTracker tracker;

    private PropertyChangeListener serviceListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent event) {
		try {
		    refresh(false);
		} catch (ScfException e) {
		    Logger log = Logger.getLogger(getClass().getName());
                    log.log(Level.WARNING, "error gathering SMF property info",
			e);
		}
	    }
	};

    //
    // Constructors
    //

    PropertyGroupsManagedObject(ServiceTracker tracker) throws ScfException {
	super(ID);
	this.tracker = tracker;
	setName(NAME);
	setComparator(COMPARATOR);

        tracker.addPropertyChangeListener(
	    ServiceTracker.PROPERTY_SERVICE, serviceListener);
	refresh(true);
    }

    //
    // PropertyGroupsManagedObject methods
    //

    public PropertyGroupManagedObject getChild(PropertyGroup group) {
	synchronized (children) {
	    int index = Collections.binarySearch(
		getChildren(), group, COMPARATOR);

	    if (index >= 0) {
		return children.get(index);
	    }

	    return null;
	}
    }

    public ServiceTracker getServiceTracker() {
	return tracker;
    }

    public void refresh(boolean force) throws ScfException {
	ServiceMXBean service = tracker.getService();
	if (service == null) {
	    return;
	}

	synchronized (children) {
	    List<PropertyGroupManagedObject> toRemove =
		new LinkedList<PropertyGroupManagedObject>(children);

	    List<PropertyGroup> groups = service.getPropertyGroups();
	    for (PropertyGroup group : groups) {
		if (!group.getType().equals(PROPERTY_GROUP_APP)) {
		    continue;
		}

		PropertyGroupManagedObject child = getChild(group);
		if (child == null) {
		    child = new PropertyGroupManagedObject(this, group);
		    addChildren(child);
		} else {
		    toRemove.remove(child);
		    child.refresh(force);
		}
	    }

	    // Minimize IntervalEvents by removing en masse
	    if (!toRemove.isEmpty()) {
		removeChildren(toRemove.toArray(
		    new PropertyGroupManagedObject[toRemove.size()]));
	    }
	}
    }
}
