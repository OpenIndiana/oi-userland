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

package com.oracle.solaris.vp.panels.smf.client.swing;

import java.util.*;
import javax.swing.ListModel;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.view.ManagedObjectTableModel;
import com.oracle.solaris.vp.util.misc.ObjectUtil;

@SuppressWarnings({"serial"})
public class MainListModel implements ListModel {
    //
    // Inner classes
    //

    public class ListDataListenerWrapper implements ListDataListener {
	//
	// Instance data
	//

	private ListDataListener listener;

	//
	// Constructors
	//

	public ListDataListenerWrapper(ListDataListener listener) {
	    this.listener = listener;
	}

	//
	// ListDataListener methods
	//

	@Override
	public void contentsChanged(ListDataEvent e) {
	    listener.contentsChanged(convert(e));
	}

	@Override
	public void intervalAdded(ListDataEvent e) {
	    listener.intervalAdded(convert(e));
	}

	@Override
	public void intervalRemoved(ListDataEvent e) {
	    listener.intervalRemoved(convert(e));
	}

	//
	// ListDataListenerWrapper methods
	//

	public ListDataListener getWrappedListener() {
	    return listener;
	}

	//
	// Private methods
	//

	private ListDataEvent convert(ListDataEvent e) {
	    return new ListDataEvent(e.getSource(), e.getType(),
		e.getIndex0() + 1, e.getIndex1() + 1);
	}
    }

    //
    // Instance data
    //

    private ServiceManagedObject service;
    private ManagedObjectTableModel<InstanceManagedObject> model;

    private Map<ListDataListener, ListDataListenerWrapper> listenerMap =
	new HashMap<ListDataListener, ListDataListenerWrapper>();

    //
    // Constructors
    //

    public MainListModel(ServiceManagedObject service,
	ManagedObject<InstanceManagedObject> instances) {

	this.service = service;
	model = new ManagedObjectTableModel<InstanceManagedObject>(instances);
    }

    //
    // ListModel methods
    //

    @Override
    public void addListDataListener(ListDataListener l) {
	ListDataListenerWrapper wrapper = new ListDataListenerWrapper(l);
	listenerMap.put(l, wrapper);
	model.addListDataListener(wrapper);
    }

    @Override
    public Object getElementAt(int index) {
	if (index == 0) {
	    return service;
	}
	return model.getElementAt(index - 1);
    }

    @Override
    public int getSize() {
	return model.getSize() + 1;
    }

    @Override
    public void removeListDataListener(ListDataListener l)  {
	ListDataListenerWrapper wrapper = listenerMap.get(l);
	if (wrapper != null) {
	    model.removeListDataListener(wrapper);
	    listenerMap.remove(l);
	}
    }

    //
    // MainListModel methods
    //

    public int indexOf(Object o) {
	for (int i = 0, n = getSize(); i < n; i++) {
	    if (ObjectUtil.equals(o, getElementAt(i))) {
		return i;
	    }
	}
	return -1;
    }
}
