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

import java.awt.event.*;
import java.net.URL;
import java.util.List;
import java.util.logging.Level;
import javax.help.HelpSet;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.util.misc.ChangeableAggregator;
import com.oracle.solaris.vp.util.swing.SettingsPanel;

/**
 * {@code SettingsControl} extends class {@link SwingControl} to provide
 * support for {@link SettingsPanel}s.
 */
public class SettingsControl<P extends PanelDescriptor,
    C extends SettingsPanel> extends SwingControl<P, C> {

    //
    // Constructors
    //

    public SettingsControl(String id, String name, ClientContext context) {
	super(id, name, context);
    }

    public SettingsControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
    }

    //
    // SwingControl methods
    //

    /**
     * Returns {@code getComponent().getChangeableAggregator()}.
     */
    @Override
    public ChangeableAggregator getChangeableAggregator() {
	C comp = getComponent();
	if (comp != null) {
	    return comp.getChangeableAggregator();
	}
	return null;
    }

    //
    // SettingsControl methods
    //

    /**
     * Adds a listener to the <strong>Apply</strong> button of this {@code
     * SettingsControl}'s {@link SettingsPanel} to invoke this {@link
     * Control}'s save action.
     */
    protected void addDefaultApplyAction() {
	getComponent().getButtonBar().getApplyButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    getSaveAction().asyncInvoke();
		}
	    });
    }

    /**
     * Adds a listener to the <strong>Back</strong> button of this {@code
     * SettingsControl}'s {@link SettingsPanel} to navigate up one level in
     * the navigation stack.
     */
    protected void addDefaultBackAction() {
	getComponent().getButtonBar().getBackButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    getNavigator().goToAsync(false, SettingsControl.this,
			Navigator.PARENT_NAVIGABLE);
		}
	    });
    }

    /**
     * Adds a listener to the <strong>Cancel</strong> button of this {@code
     * SettingsControl}'s {@link SettingsPanel} to call {@link #doQuit}, if
     * {@code quit} is {@code true}, or {@link #doCancel}, if {@code quit} is
     * {@code false}.
     */
    protected void addDefaultCancelAction(final boolean quit) {
	getComponent().getButtonBar().getCancelButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    if (quit) {
			doQuit();
		    } else {
			doCancel();
		    }
		}
	    });
    }

    /**
     * Adds a listener to the <strong>Close</strong> button of this {@code
     * SettingsControl}'s {@link SettingsPanel} to call {@link
     * #doSaveAndQuit}, if {@code quit} is {@code true}, or {@link #doOkay}, if
     * {@code quit} is {@code false}.
     */
    protected void addDefaultCloseAction(final boolean quit) {
	getComponent().getButtonBar().getCloseButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    if (quit) {
			doSaveAndQuit();
		    } else {
			doOkay();
		    }
		}
	    });
    }

    /**
     * Adds a listener to the <strong>Help</strong> button of this {@code
     * SettingsControl}'s {@link SettingsPanel} to search through the navigation
     * stack, from top to bottom, for a {@code Control} with a non-{@code null}
     * {@link Control#getHelpURL help URL}, then show it.
     */
    protected void addDefaultHelpAction() {
	getComponent().getButtonBar().getHelpButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    PanelDescriptor descriptor = getPanelDescriptor();
		    HelpSet helpSet = descriptor.getHelpSet();
		    if (helpSet == null) {
			getLog().log(Level.SEVERE, "no help set found for " +
			    descriptor.getClass().getName());
			return;
		    }

		    URL url = null;

		    List<Control> controls = getNavigator().getPath();
		    for (int i = controls.size() - 1; i >= 0; i--) {
			Control control = controls.get(i);
			url = control.getHelpURL(helpSet);
			if (url != null) {
			    break;
			}
		    }

		    if (url == null) {
			getLog().log(Level.SEVERE, String.format(
			    "help set found but no URL provided: " +
			    helpSet.getHelpSetURL()));
			return;
		    }

		    ClientContext context = getClientContext();
		    context.getHelpBroker().setCurrentURL(url);
		    context.showHelp();
		}
	    });
    }

    /**
     * Adds a listener to the <strong>Okay</strong> button of this {@code
     * SettingsControl}'s {@link SettingsPanel} to call {@link
     * #doSaveAndQuit}, if {@code quit} is {@code true}, or {@link #doOkay}, if
     * {@code quit} is {@code false}.
     */
    protected void addDefaultOkayAction(final boolean quit) {
	getComponent().getButtonBar().getOkayButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    if (quit) {
			doSaveAndQuit();
		    } else {
			doOkay();
		    }
		}
	    });
    }

    /**
     * Adds a listener to the <strong>Quit</strong> button of this {@code
     * SettingsControl}'s {@link SettingsPanel} to close this instance.
     */
    protected void addDefaultQuitAction() {
	getComponent().getButtonBar().getQuitButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    doQuit();
		}
	    });
    }

    /**
     * Adds a listener to the <strong>Reset</strong> button of this {@code
     * SettingsControl}'s {@link SettingsPanel} to invoke this {@link
     * Control}'s reset action.
     */
    protected void addDefaultResetAction() {
	getComponent().getButtonBar().getResetButton().addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    getResetAction().asyncInvoke();
		}
	    });
    }
}
