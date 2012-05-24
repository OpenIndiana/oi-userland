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

package com.oracle.solaris.vp.panel.swing.control;

import java.awt.*;
import java.util.*;
import java.util.List;
import javax.swing.JPanel;
import com.oracle.solaris.vp.panel.common.action.StructuredAction;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.panel.swing.view.SelectorPanel;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public abstract class SelectorControl<P extends PanelDescriptor,
    C extends SelectorPanel, S> extends SettingsControl<P, C> {

    //
    // Instance data
    //

    private Component defaultContentView;

    private List<StructuredAction<List<S>, ?, ?>> mActions =
	new ArrayList<StructuredAction<List<S>, ?, ?>>();

    //
    // Constructors
    //

    public SelectorControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public void childStarted(Control child) {
	super.childStarted(child);

	if (child instanceof SwingControl) {
	    addToLayout((SwingControl)child);
	    JPanel contentCardPane = getComponent().getContentCardPane();
	    LayoutManager layout = contentCardPane.getLayout();
	    if (layout instanceof CardLayout) {
		CardLayout cards = (CardLayout)layout;
		cards.show(contentCardPane, child.getId());
	    }
	}

	selectRunningChild();
    }

    @Override
    public void childStopped(Control child) {
	super.childStopped(child);

	JPanel contentCardPane = getComponent().getContentCardPane();
	CardLayout cards = (CardLayout)contentCardPane.getLayout();
	cards.show(contentCardPane, getId());
    }

    @Override
    public List<Navigable> getBrowsable() {
	List<S> values = getSelectableValues();
	List<S> selection = new ArrayList<S>(1);
	List<Navigable> navigables = new ArrayList<Navigable>(values.size());

	for (S value : values) {
	    selection.clear();
	    selection.add(value);
	    Navigable[] path = getPathForSelection(selection);
	    if (path.length == 1) {
		navigables.add(path[0]);
	    }
	}

	return navigables;
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(C panel) {
	super.configComponent(panel);
	Component defaultContentView = getDefaultContentView();
	if (defaultContentView != null) {
	    addContent(null, defaultContentView, getId());
	}
    }

    //
    // SelectorControl methods
    //

    public void addAction(C panel, StructuredAction<List<S>, ?, ?> action,
	boolean addToButtons, boolean addToPopup) {

	if (addToButtons) {
	    panel.addButtonActions(action);
	}

	if (addToPopup) {
	    panel.addPopupMenuActions(action);
	}

	mActions.add(action);
    }

    /**
     * Adds the {@code Component}s of the given {@link SwingControl}s,
     * presumably children of this {@code SelectorControl}, to the layout of
     * the UI.	The {@code Component}s must not already be parented to be added.
     * <p>
     * This methid is called automatically by {@link #childStarted}, but
     * subclasses may call it when creating child {@link Control}s if there is a
     * need in the UI for those {@code Component}s before their respective
     * {@link Control}s are started.
     */
    protected void addToLayout(SwingControl... children) {
	final JPanel contentCardPane =
	    getComponentCreate().getContentCardPane();

	LayoutManager layout = contentCardPane.getLayout();
	if (layout instanceof CardLayout) {
	    final CardLayout cards = (CardLayout)layout;

	    for (final SwingControl child : children) {
		final Component comp = child.getComponentCreate();
		if (comp != null && comp.getParent() == null) {
		    final String id = child.getId();

		    GUIUtil.invokeAndWait(
			new Runnable() {
			    @Override
			    public void run() {
				addContent(child, comp, id);
			    }
			});
		}
	    }
	}
    }

    /**
     * Gets a {@code Component} to display in the {@link SelectorPanel}'s
     * content area when no {@code Component} of a child {@link SwingControl} is
     * shown.
     * <p/>
     * This default implementation returns {@code null}.
     *
     * @see	    #setDefaultContentView
     *
     * @return	    a {@code Component}, or {@code null} to not show a default
     */
    protected Component getDefaultContentView() {
	return defaultContentView;
    }

    /**
     * Gets a path, relative to this {@code SelectorControl}, to navigate to
     * when the given items are selected in the {@link SelectorPanel}.
     *
     * @param	    items
     *		    the selected items in the panel
     *
     * @return	    a {@code Navigable} array (empty to navigate back
     *		    to this {@code SelectorControl}), or {@code null} to do
     *		    no navigation
     */
    protected abstract Navigable[] getPathForSelection(List<S> items);

    /**
     * Gets the selectable values in the {@link SelectorPanel}.
     */
    protected abstract List<S> getSelectableValues();

    /**
     * Gets the selected values in the {@link SelectorPanel}.
     */
    protected abstract List<S> getSelectedValues();

    protected void goToSelected() {
	List<S> selection = getSelectedValues();
	final Navigable[] path = getPathForSelection(selection);

	if (path != null) {
	    final Navigator navigator = getNavigator();
	    navigator.asyncExec(
		new Runnable() {
		    @Override
		    public void run() {
			try {
			    navigator.goTo(false, SelectorControl.this,
				path);
			} catch (Throwable e) {
			    // Re-select the running child Control
			    selectRunningChild();
			}
		    }
		});
	}
    }

    /**
     * Determines whether the given child's {@code Component} should be placed
     * in a bordered inset panel within the content area.  Such a panel visually
     * distinguishes the content area from other parts of the UI, but may not be
     * appropriate for some {@code Component}s, like a {@code JTabbedPane},
     * which may naturally provide its own distinguishing border.
     * </p>
     * This default implementation returns {@code true}, if {@code Control} is
     * not a {@link TabbedControl}, {@code false} otherwise.
     *
     * @param	    child
     *		    a child {@link Control}, or {@code null} if getting a border
     *		    for the {@link #getDefaultContentView default content view}
     */
    protected boolean isInsettable(Control child) {
	return !(child instanceof TabbedControl);
    }

    /**
     * Selects the list item that corresponds to the running child {@code
     * Control}.
     */
    protected abstract void selectRunningChild();

    /**
     * Sets a {@code Component} to display in the {@link SelectorPanel}'s
     * content area when no {@code Component} of a child {@link SwingControl} is
     * shown.
     *
     * @param	    defaultContentView
     *		    a {@code Component}, or {@code null} to not show a default
     *
     * @see	    #getDefaultContentView
     */
    protected void setDefaultContentView(Component defaultContentView) {
	this.defaultContentView = defaultContentView;
    }

    /**
     * Sets the preset input of the {@link SelectorPanel}'s {@link
     * StructuredAction}s with the current selection.
     */
    protected void updateActions() {
	if (!mActions.isEmpty()) {
	    List<S> selection = Collections.unmodifiableList(
		getSelectedValues());

	    for (StructuredAction<List<S>, ?, ?> action : mActions) {
		action.setPresetInput(selection);
	    }
	}
    }

    //
    // Private methods
    //

    private void addContent(SwingControl control, Component comp, String id) {
	if (isInsettable(control)) {
	    InsetPanel panel = new InsetPanel(comp);
	    comp = panel;
	}
	getComponent().getContentCardPane().add(comp, id);
    }
}
