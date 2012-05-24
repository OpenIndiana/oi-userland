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

package com.oracle.solaris.vp.panel.swing.view;

import java.beans.*;
import java.util.*;
import javax.swing.ListModel;
import javax.swing.event.ListDataListener;
import javax.swing.table.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.common.propinfo.PropInfo;
import com.oracle.solaris.vp.util.misc.event.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.propinfo.SwingPropInfo;

@SuppressWarnings({"serial"})
public class ManagedObjectTableModel<C extends ManagedObject>
    extends AbstractTableModel implements ListModel {

    //
    // Instance data
    //

    private ManagedObject<C> pObject;
    private PropInfo<C, ?>[] props;
    private List<C> children = new ArrayList<C>();

    private Map<ListDataListener, ListDataListenerAdapter> listenerMap =
	new HashMap<ListDataListener, ListDataListenerAdapter>();

    private PropertyChangeListener pListener = new PropertyChangeListener() {
	@Override
	public void propertyChange(final PropertyChangeEvent e) {
	    // We are likely not on the event queue thread
	    GUIUtil.invokeAndWait(
		new Runnable() {
		    @Override
		    public void run() {
			int index = children.indexOf(e.getSource());
			if (index != -1) {
			    fireTableRowsUpdated(index, index);
			}
		    }
		});
	}
    };

    private IntervalListener iListener = new IntervalListener() {
	@Override
	public void intervalAdded(final IntervalEvent e) {
	    // We are likely not on the event queue thread
	    GUIUtil.invokeAndWait(
		new Runnable() {
		    @Override
		    public void run() {
			int f = e.getFirstIndex();
			int l = e.getLastIndex();

			/* synchronized pObject.getChildrenLock() implied */
			List<C> adds = pObject.getChildren().subList(f, l + 1);

			children.addAll(f, adds);

			for (C mo : adds) {
			    mo.addPropertyChangeListener(pListener);
			}

			fireTableRowsInserted(f, l);
		    }
		});
	}

	@Override
	public void intervalRemoved(final IntervalEvent e) {
	    // We are likely not on the event queue thread
	    GUIUtil.invokeAndWait(
		new Runnable() {
		    @Override
		    public void run() {
			/*
			 * It is likely the object being removed from the model
			 * will be dereferenced and freed, but it isn't
			 * guaranteed.  We need to remove ourselves so objects
			 * don't accumulate stale references on us.
			 */
			int f = e.getFirstIndex();
			int l = e.getLastIndex();
			List<C> rems = children.subList(f, l + 1);

			for (C mo : rems) {
			    mo.removePropertyChangeListener(pListener);
			}

			rems.clear();
			fireTableRowsDeleted(f, l);
		    }
		});
	}
    };

    //
    // Constructors
    //

    public ManagedObjectTableModel(ManagedObject<C> pObject,
	PropInfo<C, ?>[] props) {

	this.props = props;
	setParentObject(pObject);
    }

    public ManagedObjectTableModel(ManagedObject<C> pObject) {
	this(pObject, null);
    }

    //
    // TableModel methods
    //

    @Override
    public Class<?> getColumnClass(int column) {
	try {
	    return getValueAt(0, column).getClass();
	}

	// Most likely NullPointerException or IndexOutOfBoundsException
	catch (Throwable e) {
	    return Object.class;
	}
    }

    @Override
    public int getColumnCount() {
	return props == null ? 0 : props.length;
    }

    @Override
    public String getColumnName(int column) {
	return props[column].getLabel();
    }

    @Override
    public int getRowCount() {
	return children.size();
    }

    @Override
    public Object getValueAt(int row, int column) {
	// Throws IndexOutOfBoundsException
	C o = children.get(row);

	return props[column].getValue(o);
    }

    @Override
    public boolean isCellEditable(int row, int column) {
	// Throws IndexOutOfBoundsException
	C o = children.get(row);

	return props[column].isEditable(o);
    }

    @Override
    public void setValueAt(Object value, int row, int column) {
	// Throws IndexOutOfBoundsException
	C o = children.get(row);

	@SuppressWarnings({"unchecked"})
	PropInfo<C, Object> prop =
	    (PropInfo<C, Object>)props[column];

	prop.setValue(o, value);
    }

    //
    // ListModel methods
    //

    @Override
    public void addListDataListener(ListDataListener l) {
	synchronized (listenerMap) {
	    if (!listenerMap.containsKey(l)) {
		ListDataListenerAdapter adapter =
		    new ListDataListenerAdapter(l);

		addTableModelListener(adapter);
		listenerMap.put(l, adapter);
	    }
	}
    }

    @Override
    public C getElementAt(int index) {
	return children.get(index);
    }

    @Override
    public int getSize() {
	return getRowCount();
    }

    @Override
    public void removeListDataListener(ListDataListener l) {
	synchronized (listenerMap) {
	    ListDataListenerAdapter adapter = listenerMap.get(l);
	    if (adapter != null) {
		removeTableModelListener(adapter);
		listenerMap.remove(l);
	    }
	}
    }

    //
    // ManagedObjectTableModel methods
    //

    public ManagedObject<C> getParentObject() {
	return pObject;
    }

    public boolean isSortable(int column) {
	return props[column].isSortable();
    }

    public TableCellEditor getTableCellEditor(int column) {
	TableCellEditor editor = null;

	PropInfo d = props[column];
	if (d instanceof SwingPropInfo) {
	    editor = ((SwingPropInfo)d).getTableCellEditor();
	}

	return editor;
    }

    public TableCellRenderer getTableCellRenderer(int column) {
	TableCellRenderer renderer = null;

	PropInfo d = props[column];
	if (d instanceof SwingPropInfo) {
	    renderer = ((SwingPropInfo)d).getTableCellRenderer();
	}

	return renderer;
    }

    public Comparator<?> getComparator(int column) {
	return props[column].getComparator();
    }

    public boolean isCellEnabled(int row, int column) {
	// Throws IndexOutOfBoundsException
	C o = children.get(row);

	return props[column].isEnabled(o);
    }

    public void setParentObject(ManagedObject<C> pObject) {
	if (this.pObject != null) {
	    this.pObject.removeIntervalListener(iListener);
	    for (int i = children.size() - 1; i >= 0; i--) {
		C child = children.get(i);
		child.removePropertyChangeListener(pListener);
		children.remove(i);
	    }

	    fireTableRowsDeleted(0, children.size() - 1);
	}

	assert (children.isEmpty());

	this.pObject = pObject;

	if (pObject != null) {
	    for (C child : pObject.getChildren()) {
		child.addPropertyChangeListener(pListener);
		children.add(child);
	    }

	    fireTableRowsInserted(0, children.size() - 1);
	    pObject.addIntervalListener(iListener);
	}
    }
}
