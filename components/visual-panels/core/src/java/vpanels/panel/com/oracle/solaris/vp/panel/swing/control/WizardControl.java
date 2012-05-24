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

package com.oracle.solaris.vp.panel.swing.control;

import java.awt.Component;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.panel.swing.view.WizardPanel;
import com.oracle.solaris.vp.util.misc.Stackable;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.GUIUtil;
import com.oracle.solaris.vp.util.swing.event.ChangeListeners;

/**
 * Implements a simple linear wizard out of a list of other controls.
 */
public abstract class WizardControl<P extends PanelDescriptor>
    extends SwingControl<P, WizardPanel> implements WizardStepSequence {

    //
    // Inner classes
    //

    private class WizardRootControl extends SwingControl<P, Component> {
	//
	// Instance data
	//

	private boolean successful;

	//
	// Constructors
	//

	public WizardRootControl(Stackable<Component> stack) {
	    super(WizardControl.this.getId(), WizardControl.this.getName(),
		WizardControl.this.getPanelDescriptor());

	    children = WizardControl.this.children;
	    setComponentStack(stack);
	}

	//
	// Control methods
	//

	@Override
	public void start(Navigator navigator, Map<String, String> parameters)
	    throws NavigationAbortedException, InvalidParameterException,
	    NavigationFailedException {

	    successful = false;
	    super.start(navigator, parameters);
	}

	@Override
	public void stop(boolean isCancel) throws NavigationAbortedException {
	    wizardStopped(successful);
	}
    };

    //
    // Instance data
    //

    private Navigator wNavigator;
    private WizardRootControl rootControl;

    @SuppressWarnings({"unchecked"})
    private List<Navigable> roChildren =
	(List<Navigable>)(List)Collections.unmodifiableList(children);

    private ChangeListeners listeners = new ChangeListeners();
    private ChangeEvent changeEvent = new ChangeEvent(this);

    //
    // Constructors
    //

    public WizardControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	// Create WizardPanel
	super.start(navigator, parameters);

	if (rootControl == null) {
	    rootControl = new WizardRootControl(getComponentStack());
	}

	if (wNavigator == null) {
	    wNavigator = new SwingNavigator();

	    // Resize windows on each navigation
	    wNavigator.addNavigationListener(new NavigationWindowResizer());

	    wNavigator.addNavigationListener(
		new NavigationListener() {
		    @Override
		    public void navigationStarted(NavigationStartEvent e) {
		    }

		    @Override
		    public void navigationStopped(NavigationStopEvent e) {
			GUIUtil.invokeAndWait(
			    new Runnable() {
				@Override
				public void run() {
				    fireChanged();
				}
			    });
		    }
		});
	}

	try {
	    Navigable first = getFirstStep();
	    if (first != null) {
		// Go to the beginning of the wizard
		wNavigator.goToAsyncAndWait(false, null, rootControl, first);
	    }
	} catch (InvalidAddressException impossible) {
	} catch (EmptyNavigationStackException impossible) {
	} catch (RootNavigableNotControlException impossible) {
	}
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	if (rootControl.getRunningChild() != null && !confirmCancelWizard()) {
	    throw new NavigationAbortedException();
	}

	try {
	    // Make sure the wizard is stopped before we are
	    cancelWizardSync();
	} catch (NavigationException e) {
	    throw new NavigationAbortedException(e);
	}

	super.stop(isCancel);
    }

    //
    // SwingControl methods
    //

    @Override
    protected WizardPanel createComponent() {
	WizardPanel panel = createWizardPanel();

	setComponentStack(panel.getComponentStack());

	return panel;
    }

    //
    // WizardStepSequence methods
    //

    @Override
    public void addChangeListener(ChangeListener l) {
	listeners.add(l);
    }

    @Override
    public void cancelWizard() {
	wNavigator.asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    try {
			cancelWizardSync();
		    } catch (NavigationException ignore) {
		    }
		}
	    });
    }

    /**
     * Default implementation that returns the running child {@link Control}'s
     * index in the {@link #getSteps step list}.
     */
    @Override
    public int getSelectedIndex() {
	int index = -1;
	Control control = rootControl.getRunningChild();
	if (control != null) {
	    index = getSteps().indexOf(control);
	}
	return index;
    }

    /**
     * Default implementation that returns a live, unmodifiable copy of the
     * child {@link Control} list.  Subclasses may wish to override this
     * behavior.
     */
    @Override
    public List<Navigable> getSteps() {
	ensureChildrenCreated();
	return roChildren;
    }

    @Override
    public void goToStep(final int index) {
	final int selected = getSelectedIndex();

	if (selected == index) {
	    return;
	}

	int max = selected + 1;
	if (index < 0 || index > max) {
	    throw new IndexOutOfBoundsException(
		String.format("%d out of range (0 - %d)", index, max));
	}

	final List<Navigable> steps = getSteps();

	wNavigator.asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    try {
			// First, save current step
			if (selected >= 0) {
			    Control cur = rootControl.getRunningChild();
			    if (index > selected) {
				cur.getSaveAction().invoke();
			    } else {
				cur.getResetAction().invoke();
			    }
			}

			// Last step?
			if (index == steps.size()) {
			    // Stop wizard
			    rootControl.successful = true;
			    wNavigator.goTo(false, null);
			} else {
			    Navigable next = steps.get(index);
			    wNavigator.goTo(false, rootControl, next);
			}

		    // Thrown by invoke
		    } catch (ActionAbortedException ignore) {
		    } catch (ActionFailedException ignore) {

		    // Thrown by goTo
		    } catch (NavigationException ignore) {
		    }
		}
	    });
    }

    @Override
    public void removeChangeListener(ChangeListener l) {
	listeners.add(l);
    }

    //
    // WizardControl methods
    //

    protected WizardPanel createWizardPanel() {
	return new WizardPanel(this);
    }

    protected void fireChanged() {
	listeners.stateChanged(changeEvent);
    }

    /**
     * Gets a custom message to display in the dialog that prompts the user to
     * confirm cancellation of the wizard, when navigating away from this
     * {@link WizardControl}.
     * <p>
     * This default implementation returns {@code null}.
     *
     * @return	    a {@code String}, or {@code null} to use the default message
     */
    protected String getCancelWizardMessage() {
	return null;
    }

    public Navigator getWizardNavigator() {
	return wNavigator;
    }

    /**
     * Prompts the user to onfirm cancellation of the wizard.  This is done only
     * when navigating away from this {@link WizardControl}; explicit cancelling
     * (as when the user hits "Cancel") does NOT require confirmation.
     *
     * @return	    {@code true} if the operation was confirmed, {@code false}
     *		    otherwise
     */
    protected boolean confirmCancelWizard() {
	String message = getCancelWizardMessage();
	if (message == null) {
	    message = Finder.getString("wizard.cancel.confirm.message");
	}

	String title = Finder.getString("wizard.cancel.confirm.title");
	int messageType = JOptionPane.WARNING_MESSAGE;
	int optionType = JOptionPane.YES_NO_OPTION;
	Icon icon = GUIUtil.getIcon(JOptionPane.WARNING_MESSAGE);

	return JOptionPane.showConfirmDialog(getComponent(), message, title,
	    optionType, messageType, icon) == JOptionPane.YES_OPTION;
    }

    /**
     * Indicates that the wizard has completed.  Subclasses should override this
     * method to navigate away (and thus close) this {@link Control}.
     * <p/>
     * This default implementation asynchronously attempts to navigate to the
     * parent {@link Control} of this {@link WizardControl} in the navigation
     * stack, ignoring any errors.
     *
     * @param	    successful
     *		    {@code true} if the wizard completed normally, {@code false}
     *		    if it was cancelled
     */
    public void wizardStopped(boolean successful) {
	try {
	    getNavigator().goToAsync(false, this, Navigator.PARENT_NAVIGABLE);
	} catch (Throwable ignore) {
	}
    }

    //
    // Private methods
    //

    private Navigable getFirstStep() {
	try {
	    return getSteps().get(0);
	} catch (IndexOutOfBoundsException e) {
	}

	// No steps in this wizard?
	return null;
    }

    private void cancelWizardSync() throws NavigationAbortedException,
	InvalidAddressException, MissingParameterException,
        InvalidParameterException, NavigationFailedException,
        EmptyNavigationStackException, RootNavigableNotControlException {

	wNavigator.asyncExecAndWait(
	    new NavRunnable() {
		@Override
		public void run() throws NavigationAbortedException,
		    InvalidAddressException, MissingParameterException,
		    InvalidParameterException, NavigationFailedException,
                    EmptyNavigationStackException,
                    RootNavigableNotControlException {

		    try {
			// First, reset current step
			Control cur = rootControl.getRunningChild();
			if (cur != null) {
			    cur.getResetAction().invoke();
			}

			// Stop wizard
			rootControl.successful = false;
			wNavigator.goTo(true, null);

		    // Thrown by invoke
		    } catch (ActionException e) {
			throw new NavigationAbortedException(e);
		    }
		}
	    });
    }
}
