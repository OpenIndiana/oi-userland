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
import java.beans.*;
import java.util.Map;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.swing.action.SwingStructuredAction;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

public class SwingControl<P extends PanelDescriptor, C extends Component>
    extends DefaultControl<P> implements HasComponent<C>,
    PropertyChangeListener {

    //
    // Instance data
    //

    private ManagedObject propSource;
    private String[] propNames;
    private boolean ignorePropChange;

    private C comp;
    private Stackable<Component> stack;

    private SwingStructuredAction<Object, Object, Object> resetAction =
	new SwingStructuredAction<Object, Object, Object>(null, null, null,
	    this) {

	    @Override
	    public Object workBusy(Object pInput, Object rtInput)
		throws ActionAbortedException, ActionFailedException,
		ActionUnauthorizedException {

		resetAll();
		return null;
	    }
	};

    private SwingStructuredAction<Object, Object, Object> saveAction =
	new SwingStructuredAction<Object, Object, Object>(null, null, null,
	    this) {

	    @Override
	    public Object workBusy(Object pInput, Object rtInput)
		throws ActionAbortedException, ActionFailedException,
		ActionUnauthorizedException {

		saveAll();
		return null;
	    }
	};

    //
    // Constructors
    //

    public SwingControl(String id, String name, ClientContext context) {
	super(id, name, context);
    }

    public SwingControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
    }

    //
    // HasComponent methods
    //

    /**
     * Gets the {@code Component} for this {@code SwingControl}.
     *
     * @return	    a {@code Component}, or {@code null} if this {@code
     *		    SwingControl} has no {@code Component}.
     *
     * @see	    #setComponent
     */
    @Override
    public C getComponent() {
	return comp;
    }

    //
    // PropertyChangeListener methods
    //

    /**
     * Convenience implementation that calls {@link #initComponentOnEventThread}
     * if property changes are not temporarilty being {@link
     * #getPropertyChangeIgnore ignored}.  If this {@link SwingControl}'s
     * component displayed the properties of a {@link ManagedObject}, for
     * example, it may make sense to add this {@code SwingControl} as a {@code
     * PropertyListener} to that object.
     */
    @Override
    public void propertyChange(PropertyChangeEvent event) {
	if (!ignorePropChange && getComponent() != null) {
	    initComponentOnEventThread();
	}
    }

    //
    // Control methods
    //

    /**
     * If a) this {@code SwingControl} defines a {@link #getComponentStack
     * Component stack}, b) the just-started {@link Control} implements {@link
     * HasComponent}, and c) its {@code Component} does not yet have a parent,
     * this method adds that {@code Component} to the stack.
     */
    @Override
    public void descendantStarted(Control[] path) {
	super.descendantStarted(path);

	final Stackable<Component> stack = getComponentStack();
	if (stack != null) {
	    Control control = path[path.length - 1];
	    if (control instanceof HasComponent) {
		final Component comp = ((HasComponent)control).getComponent();
		if (comp != null && !(comp instanceof Window) &&
		    comp.getParent() == null) {

		    GUIUtil.invokeAndWait(
			new Runnable() {
			    @Override
			    public void run() {
				stack.push(comp);
			    }
			});
		}
	    }
	}
    }

    /**
     * If a) this {@code SwingControl} defines a {@link #getComponentStack
     * Component stack}, b) the just-stopped {@link Control} implements {@link
     * HasComponent}, and c) its {@code Component} is at the top of the stack,
     * this method removes that {@code Component} from the stack.
     */
    @Override
    public void descendantStopped(Control[] path) {
	super.descendantStopped(path);

	final Stackable<Component> stack = getComponentStack();
	if (stack != null) {
	    Control control = path[path.length - 1];
	    if (control instanceof HasComponent) {
		final Component comp = ((HasComponent)control).getComponent();
		if (comp != null && !(comp instanceof Window)) {
		    GUIUtil.invokeAndWait(
			new Runnable() {
			    @Override
			    public void run() {
				StackUtil.popIfAtTop(stack, comp);
			    }
			});
		}
	    }
	}
    }

    /**
     * Gets a {@link SwingStructuredAction} that invokes {@link #resetAll},
     * displaying errors.
     */
    @Override
    public SwingStructuredAction<?, ?, ?> getResetAction() {
	return resetAction;
    }

    /**
     * Gets a {@link SwingStructuredAction} that invokes {@link #saveAll},
     * displaying errors and prompting for login on {@code
     * ActionUnauthorizedException}s.
     */
    @Override
    public SwingStructuredAction<?, ?, ?> getSaveAction() {
	return saveAction;
    }

    /**
     * Prompts the user to save changes, discard changes, or cancel navigation,
     * when navigating away from a {@code Control} with unsaved changes.
     *
     * @see	    #getUnsavedChangesMessage
     */
    @Override
    protected UnsavedChangesAction getUnsavedChangesAction() {
	String message = getUnsavedChangesMessage();
	if (message == null) {
	    message = Finder.getString("settings.unsavedchanges.message");
	}

	String title = Finder.getString("settings.unsavedchanges.title");
	int messageType = JOptionPane.WARNING_MESSAGE;
	int optionType = JOptionPane.DEFAULT_OPTION;
	Icon icon = GUIUtil.getIcon(JOptionPane.WARNING_MESSAGE);

	Object[] options = {
	    Finder.getString("settings.unsavedchanges.button.cancel"),
	    Finder.getString("settings.unsavedchanges.button.discard"),
	    Finder.getString("settings.unsavedchanges.button.save"),
	};

	Object defaultOption = options[0];

	int result = JOptionPane.showOptionDialog(getComponent(), message,
	    title, optionType, messageType, icon, options, defaultOption);

	switch (result) {
	    default:
	    case 0: return UnsavedChangesAction.CANCEL;
	    case 1: return UnsavedChangesAction.DISCARD;
	    case 2: return UnsavedChangesAction.SAVE;
	}
    }

    /**
     * If this {@code SwingControl} has a {@link #getChangeableAggregator
     * ChangeableAggregator}, returns the value from the aggregator's {@link
     * ChangeableAggregator#isChanged isChanged} method.  Otherwise, returns
     * {@code false}.
     */
    @Override
    protected boolean isChanged() {
	ChangeableAggregator aggregator = getChangeableAggregator();
	if (aggregator != null) {
	    return aggregator.isChanged();
	}
	return false;
    }

    /**
     * If this {@code SwingControl} has a {@link #getChangeableAggregator
     * ChangeableAggregator}, calls its {@link ChangeableAggregator#reset}
     * method on the AWT event thread and waits for its completion.
     */
    @Override
    protected void reset() throws ActionAbortedException, ActionFailedException
    {
	final ChangeableAggregator aggregator = getChangeableAggregator();
	if (aggregator != null) {
	    GUIUtil.invokeAndWait(
		new Runnable() {
		    @Override
		    public void run() {
			aggregator.reset();
		    }
		});
	}
    }

    /**
     * If this {@code SwingControl} has a {@link #getChangeableAggregator
     * ChangeableAggregator}, calls its {@link ChangeableAggregator#save}
     * method on the AWT event thread and waits for its completion.
     */
    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	final ChangeableAggregator aggregator = getChangeableAggregator();
	if (aggregator != null) {
	    GUIUtil.invokeAndWait(
		new Runnable() {
		    @Override
		    public void run() {
			aggregator.save();
		    }
		});
	}
    }

    /**
     * Calls the superclass implementation, {@link #getComponentCreate creates}
     * this {@code SwingControl}'s {@code Component} if necessary, then
     * {@link #initComponentOnEventThread initializes} it.
     */
    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	super.start(navigator, parameters);

	if (propSource != null) {
	    if (propNames == null) {
		propSource.addPropertyChangeListener(this);
	    } else {
		for (String propName : propNames) {
		    propSource.addPropertyChangeListener(propName, this);
		}
	    }
	}

	Component comp = getComponentCreate();
	if (comp != null) {
	    initComponentOnEventThread();
	}
    }

    /**
     * Calls the superclass implementation, then {@link
     * #deinitComponentOnEventThread deinitializes} this {@code SwingControl}'s
     * {@code Component}.
     *
     * @exception   NavigationAbortedException
     *		    if the navigation is cancelled, or a save fails
     */
    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	Component comp = getComponent();
	if (comp != null) {
	    deinitComponentOnEventThread();
	}

	if (propSource != null) {
	    propSource.removePropertyChangeListener(this);
	    propSource = null;
	    propNames = null;
	}
    }

    //
    // SwingControl methods
    //

    /**
     * Configures the just-{@code #createComponent created} {@code Component}
     * for this {@code SwingControl}.  This method is called automatically just
     * after {@code createComponent}.
     * <p/>
     * Most subclasses can do all configuration in {@link #createComponent}.
     * Only implementors that wish to provide a common configuration for all
     * {@code Component}s created by their subclasses need to implement this
     * method.
     * <p/>
     * Subclasses that override this method should call {@code
     * super.configComponent(comp)} to ensure that any present or future
     * functionality in any superclass implementation is executed.
     * <p/>
     * This default implementation does nothing.
     *
     * @param	    comp
     *		    the newly-created {@code Component}
     */
    protected void configComponent(C comp) {
    }

    /**
     * Creates the {@code Component} for this {@code SwingControl}.
     * <p/>
     * This default implementation does nothing and returns {@code null}.
     *
     * @return	    the newly-created {@code Component}
     */
    protected C createComponent() {
	return null;
    }

    /**
     * De-initializes the {@code Component} for this {@code SwingControl}.  This
     * method is called automatically when this {@code Control} is stopped.
     * <p/>
     * This default implementation does nothing.
     */
    protected void deinitComponent() {
    }

    /**
     * Calls {@link #deinitComponent} on the event queue thread and waits until
     * it has completed.  This method is called automatically when this {@code
     * Control} is stopped.
     */
    protected void deinitComponentOnEventThread() {
	GUIUtil.invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    deinitComponent();
		}
	    });
    }

    /**
     * Gets the {@link ChangeableAggregator}, if any, for this class.  This is
     * used in the default implementation of some {@link Control} methods to
     * track changes to this {@code Control}.
     * <p/>
     * This default implementation returns {@code null}.
     *
     * @return	    a {@link ChangeableAggregator}, or {@code null} if this
     *		    {@code SwingControl} has none
     */
    public ChangeableAggregator getChangeableAggregator() {
	return null;
    }

    /**
     * Gets the {@code Component} for this {@code SwingControl}, {@link
     * #createComponent creating} it, {@code #configComponent configuring} it,
     * and {@code #setComponent setting} it first if necessary.
     * <p/>
     * This method is not thread-safe; external locking may be necessary to
     * ensure that {@link #createComponent} is not called by multiple threads.
     *
     * @return	    a {@code Component}, or {@code null} if this {@code
     *		    SwingControl} has no {@code Component}.
     */
    public C getComponentCreate() {
	C comp = getComponent();
	if (comp == null) {
	    comp = createComponent();
	    if (comp != null) {
		setComponent(comp);
		configComponent(comp);
	    }
	}
	return comp;
    }

    /**
     * Gets the {@code {@link Stackable}<Component>} to which {@code Component}s
     * of descendant {@code SwingControl}s may be added.
     *
     * @return	    a {@code {@link Stackable}<Component>}, or {@code null} to
     *		    defer to {@code SwingControl}s higher in the navigation
     *		    stack
     */
    public Stackable<Component> getComponentStack() {
	return stack;
    }

    /**
     * Gets whether property changes to the {@link #setPropertyChangeSource
     * property change source} are temporarily ignored.
     *
     * @see	    #setPropertyChangeIgnore
     */
    public boolean getPropertyChangeIgnore() {
	return ignorePropChange;
    }

    /**
     * Gets a custom message to display in the dialog that prompts the user to
     * {@link #getUnsavedChangesAction handle unsaved changes}.
     * <p/>
     * This default implementation returns {@code null}.
     *
     * @return	    a {@code String}, or {@code null} to use the default message
     */
    protected String getUnsavedChangesMessage() {
	return null;
    }

    /**
     * Initializes the {@code Component} for this {@code SwingControl}.  This
     * method is called automatically when this {@code Control} is started.
     * <p/>
     * This default implementation does nothing.
     */
    protected void initComponent() {
    }

    /**
     * Calls {@link #initComponent} on the event queue thread and waits until it
     * has completed.  This method is called automatically when this {@code
     * Control} is started.
     */
    protected void initComponentOnEventThread() {
	GUIUtil.invokeAndWait(
	    new Runnable() {
		@Override
		public void run() {
		    initComponent();
		}
	    });
    }

    /**
     * Gets the {@code Component} for this {@code SwingControl}.
     *
     * @param	    comp
     *		    a {@code Component}, or {@code null} if this {@code
     *		    SwingControl} has no {@code Component}.
     *
     * @see	    #getComponent
     */
    protected void setComponent(C comp) {
	this.comp = comp;
    }

    /**
     * Sets the {@code {@link Stackable}<Component>} to which {@code Component}s
     * of descendant {@code SwingControl}s may be added.
     *
     * @param	    stack
     *		    a {@code {@link Stackable}<Component>} or {@code null} to
     *		    defer to {@code SwingControl}s higher in the navigation
     *		    stack
     */
    protected void setComponentStack(Stackable<Component> stack) {
	this.stack = stack;
    }

    /**
     * Sets whether property changes to the {@link #setPropertyChangeSource
     * property change source} are temporarily ignored.
     *
     * @see	    #getPropertyChangeIgnore
     */
    public void setPropertyChangeIgnore(boolean ignorePropChange) {
	this.ignorePropChange = ignorePropChange;
    }

    /**
     * Sets a {@link ManagedObject} to which this control should listen
     * for {@code PropertyChangeEvent}s once it is started.  Should not
     * be called while the control is started.
     *
     * @param	    propSource
     *		    the {@link ManagedObject} to listen to
     *
     * @param	    propNames
     *		    the names of the properties in which to listen for changes,
     *		    or an empty array to listen for changes in all properties on
     *		    {@code propSource}
     */
    protected void setPropertyChangeSource(ManagedObject propSource,
	String... propNames) {

	assert !isStarted();
	this.propSource = propSource;
	this.propNames = propNames == null || propNames.length == 0 ? null :
	    propNames;
    }
}
