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

package com.oracle.solaris.vp.util.misc.event;

import java.beans.*;
import java.util.*;

public class PropertyChangeListeners
    extends EventListeners<PropertyChangeListener>
    implements EventDispatcher<PropertyChangeEvent, PropertyChangeListener>,
    PropertyChangeListener {

    //
    // Instance data
    //

    // Map of PropertyChangeListeners interested only in a single property
    private Map<PropertyChangeListener, List<String>> map =
	new HashMap<PropertyChangeListener, List<String>>();

    //
    // EventDispatcher methods
    //

    @Override
    public void dispatch(PropertyChangeListener listener,
	PropertyChangeEvent event) {

	List<String> propNames = map.get(listener);

	// Dispatch if listener is not property-specific, or is specific to the
	// changed property
	if (propNames == null || propNames.contains(event.getPropertyName())) {
	    listener.propertyChange(event);
	}
    }

    //
    // PropertyChangeListener methods
    //

    @Override
    public void propertyChange(PropertyChangeEvent event) {
	dispatch((EventDispatcher<PropertyChangeEvent, PropertyChangeListener>)
	    this, event);
    }

    //
    // EventListeners methods
    //

    @Override
    public boolean remove(PropertyChangeListener listener) {
	boolean removed = super.remove(listener);
	if (removed) {
	    map.remove(listener);
	}
	return removed;
    }

    //
    // PropertyChangeListeners methods
    //

    public void add(String propName, PropertyChangeListener listener) {
	add(listener);

	List<String> propNames = map.get(listener);
	if (propNames == null) {
	    propNames = new LinkedList<String>();
	    map.put(listener, propNames);
	}

	int index = Collections.binarySearch(propNames, propName);
	if (index < 0) {
	    index = -1 - index;
	    propNames.add(index, propName);
	}
    }

    public boolean remove(String propName, PropertyChangeListener listener) {
	List<String> propNames = map.get(listener);
	if (propNames != null) {
	    propNames.remove(propName);
	    if (propNames.isEmpty()) {
		map.remove(listener);
	    } else {
		return false;
	    }
	}
	return super.remove(listener);
    }
}
