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

package com.oracle.solaris.vp.panel.swing.view;

import java.awt.*;
import java.beans.*;
import java.util.*;
import java.util.List;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.action.StructuredAction;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

/**
 * The {@code ObjectsPanel} class provides the skeleton for a panel to
 * display the children or other ancestors of a {@code ManagedObject}.
 */
@SuppressWarnings({"serial"})
public class ObjectsPanel<C extends ManagedObject> extends JPanel {
    //
    // Inner classes
    //

    protected class ViewModel extends DefaultComboBoxModel {
	//
	// ListModel methods
	//

	@Override
	@SuppressWarnings({"unchecked"})
	public ObjectsView<C> getElementAt(int index) {
	    return (ObjectsView<C>)super.getElementAt(index);
	}

	//
	// ComboBoxModel methods
	//

	@Override
	public void addElement(Object o) {
	    insertElementAt(o, getSize());
	}

	@Override
	@SuppressWarnings({"unchecked"})
	public ObjectsView<C> getSelectedItem() {
	    return (ObjectsView<C>)super.getSelectedItem();
	}

	@Override
	@SuppressWarnings({"unchecked"})
	public void insertElementAt(Object o, int index) {
	    ObjectsView<C> view = (ObjectsView<C>)o;
	    view.addPropertyChangeListener(viewListener);
	    super.insertElementAt(o, index);
	}

	//
	// MutableComboBoxModel methods
	//

	@Override
	public void removeAllElements() {
	    for (int i = getSize() - 1; i >= 0; i--) {
		ObjectsView<C> view = getElementAt(i);
		view.removePropertyChangeListener(viewListener);
	    }
	    super.removeAllElements();
	}

	@Override
	public void removeElement(Object o) {
	    int index = getIndexOf(o);
	    if (index != -1) {
		removeElementAt(index);
	    }
	}

	@Override
	public void removeElementAt(int index) {
	    ObjectsView<C> view = getElementAt(index);
	    view.removePropertyChangeListener(viewListener);
	    super.removeElementAt(index);
	}
    }

    //
    // Static data
    //

//  public static final Color COLOR_BACKGROUND = new Color(190, 199, 204);
//  public static final Color COLOR_HEADER_START = new Color(115, 130, 140);
//  public static final Color COLOR_HEADER_END = new Color(66, 85, 99);

    public static final Color COLOR_HEADER_START = new Color(133, 144, 165);
    public static final Color COLOR_HEADER_END = new Color(37, 44, 61);
    public static final Color COLOR_BACKGROUND =
	ColorUtil.lighter(COLOR_HEADER_START, .4f);
//  public static final Color COLOR_FILTER = new Color(233, 238, 255);

    public static final Color COLOR_BORDER =
	ColorUtil.darker(COLOR_BACKGROUND, .25f);

    public static final Border BORDER_CONTENT_LINE =
	BorderFactory.createLineBorder(COLOR_BORDER, 1);

    public static final Border BORDER_CONTENT =
	BorderFactory.createCompoundBorder(
	BORDER_CONTENT_LINE, GUIUtil.getEmptyHalfBorder());

    public static final Border BORDER_CONTENT_HEADER =
	new ClippedBorder(BORDER_CONTENT, false, true, true, true);

    //
    // Instance data
    //

    private FilterManagedObject<C> fObject;
    private StructuredAction<List<C>, ?, ?>[] mActions;
    private StructuredAction<List<C>, ?, ?> dmAction;

    private ViewModel viewModel;

    private JPanel viewPane;
    private ObjectsHeader header;
    private ObjectsToolBar toolBar;
    private String title;
    private JPanel content;

    private PropertyChangeListener viewListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent e) {
		if (e.getSource() == getView()) {
		    String pName = e.getPropertyName();

		    if (ObjectsView.PROPERTY_OBJECT_COUNT.equals(pName)) {
			updateTitle();

		    } else if (ObjectsView.PROPERTY_SELECTION.equals(pName)) {
			updateActions();
		    }
		}
	    }
	};

    //
    // Constructors
    //

    public ObjectsPanel(ManagedObject<C> pObject,
	StructuredAction<List<C>, ?, ?>[] mActions,
	StructuredAction<List<C>, ?, ?> dmAction, String title, String help) {

	FilterManagedObject<C> f = new FilterManagedObject<C>(pObject);

	fObject = f;

	this.mActions = mActions;
	this.dmAction = dmAction;
	this.title = title;

	viewModel = new ViewModel();
	viewModel.addListDataListener(
	    new ListDataListener() {
		@Override
		public void contentsChanged(ListDataEvent e) {
		    updateView();
		}

		@Override
		public void intervalAdded(ListDataEvent e) {
		    viewIntervalAdded(e.getIndex0(), e.getIndex1());
		}

		@Override
		public void intervalRemoved(ListDataEvent e) {
		    viewIntervalRemoved(e.getIndex0(), e.getIndex1());
		}
	    });

	header = new ObjectsHeader();
	header.setHelp(help);

	toolBar = mActions == null ?
	    new ObjectsToolBar(viewModel) :
	    new ObjectsToolBar(viewModel, mActions);

	viewPane = new JPanel(new CardLayout());

	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL);

	content = new JPanel(new ColumnLayout(VerticalAnchor.FILL));
	content.setOpaque(false);
	content.add(toolBar, c);
	content.add(viewPane, c.setWeight(1));

	setOpaque(false);
	setLayout(new BorderLayout());
	add(header, BorderLayout.NORTH);
	add(content, BorderLayout.CENTER);

	setShowContentBorder(true);
	setHeaderVisible(true);
    }

    //
    // ObjectsPanel methods
    //

    public void addView(ObjectsView<C> view) {
	viewModel.addElement(view);
    }

    public StructuredAction<List<C>, ?, ?>[] getActions() {
	return mActions;
    }

    public StructuredAction<List<C>, ?, ?> getDefaultAction() {
	return dmAction;
    }

    public FilterManagedObject<C> getFilterManagedObject() {
	return fObject;
    }

    public ObjectsHeader getHeader() {
	return header;
    }

    public boolean getShowContentBorder() {
	return content.getBorder() != null;
    }

    public ObjectsToolBar getToolBar() {
	return toolBar;
    }

    public ObjectsView<C> getView() {
	return viewModel.getSelectedItem();
    }

    protected MutableComboBoxModel getViewModel() {
	return viewModel;
    }

    public void removeView(ObjectsView<C> view) {
	viewModel.removeElement(view);
    }

    public void setHeaderVisible(boolean visible) {
	header.setVisible(visible);
	setShowContentBorder(getShowContentBorder());
    }

    public void setShowContentBorder(boolean showContentBorder) {
	content.setBorder(!showContentBorder ? null :
	    header.isVisible() ? BORDER_CONTENT_HEADER : BORDER_CONTENT);
    }

    /**
     * Sets the currently displayed view.
     *
     * @see	    #addView
     */
    public void setSelectedView(ObjectsView<C> view) {
	viewModel.setSelectedItem(view);
    }

    protected void updateActions() {
	ObjectsView<C> view = getView();
	List<C> objects;

	if (view == null) {
	    objects = Collections.emptyList();
	} else {
	    objects = view.getSelection();
	}

	if (mActions != null) {
	    for (StructuredAction<List<C>, ?, ?> action : mActions) {
		if (action != null && action != dmAction) {
		    action.setPresetInput(objects);
		}
	    }
	}

	if (dmAction != null) {
	    dmAction.setPresetInput(objects);
	}
    }

    protected void updateTitle() {
	ObjectsView<C> view = getView();
	int count = view == null ? 0 : view.getObjectCount();
	header.setTitle(Finder.getString("objects.header.label", title, count));
    }

    //
    // Private methods
    //

    private void updateView() {
	ObjectsView<C> view = viewModel.getSelectedItem();

	if (view != null) {
	    ((CardLayout)viewPane.getLayout()).show(viewPane, view.getId());
	    updateActions();
	    updateTitle();

	} else if (viewModel.getSize() > 0) {
	    viewModel.setSelectedItem(viewModel.getElementAt(0));
	}
    }

    private void viewIntervalAdded(int first, int last) {
	for (int i = first; i <= last; i++) {
	    ObjectsView<C> view = viewModel.getElementAt(i);
	    Component c = view.getComponent();
	    String id = view.getId();
	    viewPane.add(c, id, i);
	}

	updateView();
    }

    private void viewIntervalRemoved(int first, int last) {
	for (int i = first; i >= last; i--) {
	    assert (viewModel.getElementAt(i).getComponent() ==
		viewPane.getComponent(i));

	    viewPane.remove(i);
	}

	updateView();
    }
}
