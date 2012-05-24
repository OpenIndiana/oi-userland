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

package com.oracle.solaris.vp.panel.swing.smf;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.event.ChangeListeners;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public abstract class ComponentList<C extends Component> extends JPanel {
    //
    // Inner classes
    //

    private class ComponentListItem extends CollapsiblePane {
	//
	// Instance data
	//

	private boolean remove;
	private JMenuItem removeItem;

	//
	// Constructors
	//

	public ComponentListItem(Component comp) {
	    super(comp);
	    setOpaque(false);

	    JMenuItem addItem = new JMenuItem(Finder.getString(
		"service.settings.menu.add"));

	    addItem.addActionListener(
		new ActionListener() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			ComponentList list = ComponentList.this;
			Component[] comps = list.getComponents();
			int index;
			for (index = comps.length - 1; index >= 0; index--) {
			    if (comps[index] == ComponentListItem.this) {
				break;
			    }
			}

			list.add(index + 1);
		    }
		});

	    removeItem = new JMenuItem(Finder.getString(
		"service.settings.menu.remove"));

	    removeItem.addActionListener(
		new ActionListener() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			if (ComponentList.this.getComponentCount() > 1) {
			    // Mark for removal
			    remove = true;
			    setCollapsed(true);
			}
		    }
		});

	    JPopupMenu menu = new JPopupMenu();
	    menu.add(addItem);
	    menu.add(removeItem);
	    setComponentPopupMenu(menu);
	}

	//
	// CollapsiblePane methods
	//

	@Override
	public void end() {
	    if (remove) {
		Container parent = getParent();
		if (parent != null) {
		    parent.remove(this);
		}
	    }
	}
    }

    //
    // Instance data
    //

    private ChangeListeners listeners = new ChangeListeners();

    //
    // Constructors
    //

    public ComponentList(LayoutManager layout) {
	super(layout);
	setOpaque(false);

	JMenuItem addItem = new JMenuItem(Finder.getString(
	    "service.settings.menu.add"));

	addItem.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    add(0);
		}
	    });

	JPopupMenu menu = new JPopupMenu();
	menu.add(addItem);
	setComponentPopupMenu(menu);

	addContainerListener(
	    new ContainerAdapter() {
		@Override
		public void componentAdded(ContainerEvent e) {
		    setRemoveMenuItemEnabled();
		    fireStateChanged();
		}

		@Override
		public void componentRemoved(ContainerEvent e) {
		    Component comp = e.getChild();
		    try {
			ComponentListItem item = (ComponentListItem)comp;
			@SuppressWarnings({"unchecked"})
			C view = (C)item.getView();
			disposeListComponent(view);
		    } catch (ClassCastException ignore) {
		    }

		    setRemoveMenuItemEnabled();
		    fireStateChanged();
		}
	    });
    }

    public ComponentList(int gap) {
	this(createDefaultLayout(gap));
    }

    public ComponentList() {
	this(GUIUtil.getHalfGap());
    }

    //
    // Container methods
    //

    @Override
    public ComponentListItem add(Component comp) {
	return add(comp, getComponentCount());
    }

    @Override
    public ComponentListItem add(Component comp, int index) {
	ComponentListItem item = createItem(comp);
	item.setCollapsed(true);
	super.add(item, index);
	item.setCollapsed(false);
	return item;
    }

    //
    // ComponentList methods
    //

    public void add() {
	int index = getComponentCount();
	add(createListComponent(index), index);
    }

    public void add(int index) {
	add(createListComponent(index), index);
    }

    public void addChangeListener(ChangeListener listener) {
	listeners.add(listener);
    }

    protected abstract C createListComponent(int index);

    protected void disposeListComponent(C comp) {
    }

    protected void fireStateChanged() {
	ChangeEvent e = new ChangeEvent(this);
	listeners.stateChanged(e);
    }

    @SuppressWarnings({"unchecked"})
    protected C getListComponent(int index) {
	ComponentListItem item = (ComponentListItem)getComponent(index);
	return (C)item.getView();
    }

    public void removeChangeListener(ChangeListener listener) {
	listeners.remove(listener);
    }

    protected void setRemoveMenuItemEnabled() {
	Component[] comps = getComponents();
	boolean enabled = comps.length > 1;
	for (Component comp : comps) {
	    ((ComponentListItem)comp).removeItem.setEnabled(enabled);
	}
    }

    //
    // Private methods
    //

    private ComponentListItem createItem(Component comp) {
	if (comp instanceof JComponent) {
	    JComponent jComp = (JComponent)comp;
	    if (!jComp.getInheritsPopupMenu() &&
		jComp.getComponentPopupMenu() == null) {
		jComp.setInheritsPopupMenu(true);
	    }
	}
	return new ComponentListItem(comp);
    }

    //
    // Static methods
    //

    private static LayoutManager createDefaultLayout(int gap) {
	ColumnLayout layout = new ColumnLayout(VerticalAnchor.FILL);

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, gap);

	layout.setDefaultConstraint(c);

	return layout;
    }
}
