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

package com.oracle.solaris.vp.panel.common.control;

import java.io.UnsupportedEncodingException;
import java.net.*;
import java.util.*;
import java.util.Map;
import java.util.logging.*;
import javax.help.*;
import com.oracle.solaris.vp.panel.common.action.*;

/**
 * The {@code Control} class encapsulates the control over all aspects of a
 * single point in a navigation hierarchy.
 */
public abstract class Control implements Navigable, HasControl {
    //
    // Enums
    //

    public enum UnsavedChangesAction {
	CANCEL, DISCARD, SAVE
    }

    //
    // Static data
    //

    /**
     * The encoding used to encode/decode Control IDs and parameters in a path
     * string.
     */
    public static final String ENCODING = "UTF-8";

    //
    // Instance data
    //

    private String id;
    private String name;
    private Navigator navigator;
    private Map<String, String> parameters;
    private Control child;

    private StructuredAction<?, ?, ?> resetAction =
	new StructuredAction<Object, Object, Object>(null) {
	    @Override
	    public Object work(Object pInput, Object rtInput)
		throws ActionAbortedException, ActionFailedException {

		resetAll();
		return null;
	    }
	};

    private StructuredAction<?, ?, ?> saveAction =
	new StructuredAction<Object, Object, Object>(null) {
	    @Override
	    public Object work(Object pInput, Object rtInput)
		throws ActionAbortedException, ActionFailedException {

		try {
		    saveAll();
		} catch (ActionUnauthorizedException e) {
		    throw new ActionFailedException(e);
		}
		return null;
	    }
	};

    //
    // Constructors
    //

    /**
     * Constructs a {@code Control} with the given identifier and name.
     */
    public Control(String id, String name) {
	setId(id);
	setName(name);
    }

    /**
     * Constructs a {@code Control} with a {@code null} identifier and name.
     */
    public Control() {
	this(null, null);
    }

    //
    // HasId methods
    //

    /**
     * Gets an identifier for this {@code Control}, sufficiently unique as to
     * distinguish itself from its siblings.
     */
    @Override
    public String getId() {
	return id;
    }

    //
    // Navigable methods
    //

    /**
     * Gets the localized name of this {@code Control}.
     */
    @Override
    public String getName() {
	return name;
    }

    /**
     * Gets the initialization parameters passed to the {@link #start} method,
     * if this {@code Control} is started, or {@code null} if this {@code
     * Control} is stopped.
     */
    @Override
    public Map<String, String> getParameters() {
	return parameters;
    }

    //
    // HasControl methods
    //

    @Override
    public Control getControl() {
	return this;
    }

    //
    // Object methods
    //

    @Override
    public String toString() {
	return getName();
    }

    //
    // Control methods
    //

    /**
     * Saves the given child as the {@link #getRunningChild running child}.
     * Called by {@link #descendantStarted} when a child of this {@code Control}
     * is started.
     *
     * @exception   IllegalStateException
     *		    if the running child has already been set
     */
    public void childStarted(Control child) {
	if (this.child != null) {
	    throw new IllegalStateException("child already started");
	}

	this.child = child;
    }

    /**
     * Removes the given child as the {@link #getRunningChild running child}.
     * Called by {@link #descendantStopped} when a child of this {@code Control}
     * is stopped.
     *
     * @exception   IllegalStateException
     *		    if the given control is not the running child
     */
    public void childStopped(Control child) {
	if (this.child != child) {
	    throw new IllegalStateException("not running child");
	}

	this.child = null;
    }

    /**
     * Calls {@link #childStarted} iff the given path refers to an immediate
     * child of this {@code Control}.
     * <p/>
     * Called by the {@link Navigator} just after a descendant {@code Control}
     * of this {@code Control} has been started and pushed onto the {@link
     * Navigator}'s {@code Control} stack.
     *
     * @param	    path
     *		    the path to the descendant {@code Control}, relative to this
     *		    {@code Control} (with the just-started {@code Control} as
     *		    the last element)
     */
    public void descendantStarted(Control[] path) {
	if (path.length == 1) {
	    childStarted(path[0]);
	}
    }

    /**
     * Calls {@link #childStopped} iff the given path refers to an immediate
     * child of this {@code Control}.
     * <p/>
     * Called by the {@link Navigator} just after a descendant {@code Control}
     * of this {@code Control} has been stopped and popped off the {@link
     * Navigator}'s {@code Control} stack.
     *
     * @param	    path
     *		    the path to the descendant {@code Control}, relative to this
     *		    {@code Control} (with the just-stopped {@code Control} as
     *		    the last element)
     */
    public void descendantStopped(Control[] path) {
	if (path.length == 1) {
	    childStopped(path[0]);
	}
    }

    /**
     * Asynchronously navigates up one level above this {@code Control} in the
     * navigation stack.  The {@link #stop stop methods} of all affected {@code
     * Control}s are called with a {@code true} argument.
     */
    public void doCancel() {
	getNavigator().goToAsync(true, this, Navigator.PARENT_NAVIGABLE);
    }

    /**
     * Asynchronously invokes this {@link Control}'s save action, then navigates
     * up one level in the navigation stack.
     */
    public void doOkay() {
	final StructuredAction<?, ?, ?> saveAction = getSaveAction();
	saveAction.asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    try {
			saveAction.invoke();

			getNavigator().goToAsync(false, Control.this,
			    Navigator.PARENT_NAVIGABLE);
		    } catch (ActionException ignore) {
		    }
		}
	    });
    }

    /**
     * Gets a list of {@code Navigable}s that resolve to a child {@code Control}
     * of this {@code Control}.
     *
     * @return	    a non-{@code null} (but possibly empty) {@code Collection}
     */
    public abstract List<Navigable> getBrowsable();

    /**
     * Gets the child {@code Control} with the given identifier, creating it if
     * necessary.
     *
     * @param	    id
     *		    a unique identifier, as reported by the child {@code
     *		    Control}'s {@link #getId} method.
     *
     * @return	    a {@code Control} object, or {@code null} if no such child
     *		    is known
     */
    public abstract Control getChildControl(String id);

    /**
     * Gets a {@link Navigable} path to navigate to automatically when this
     * {@code Control} is the final destination of a navigation (not an
     * intermediate stop to another {@code Control}).  This method is called by
     * the {@link Navigator} <strong>after</strong> this {@code Control} has
     * been started.
     * <p/>
     * If the first element is {@code null}, the returned path is considered
     * absolute.  Otherwise, it is relative to this {@code Control}.
     * <p/>
     * This default implementation returns {@code null}.
     *
     * @param	    childStopped
     *		    {@code true} if navigation stopped here because a child
     *		    {@code Control} of this {@code Control} stopped, {@code
     *		    false} if this {@code Control} was started as part of this
     *		    specific navigation
     *
     * @return	    a {@link Navigable} array, or {@code null} if no automatic
     *		    forwarding should occur
     */
    public Navigable[] getForwardingPath(boolean childStopped) {
	return null;
    }

    /**
     * Used by {@link #getHelpURL}, returns a {@code HelpSet} map identifier
     * that corresponds to a help URL for this {@code Control}.
     * <p/>
     * This default implementation returns {@code null}.
     *
     * @return	    an ID, or {@code null} if no specific topic in the {@code
     *		    HelpSet} applies to this {@code Control}
     */
    public String getHelpMapID() {
	return null;
    }

    /**
     * Gets the help URL for this {@code Control}.
     * <p/>
     * This default implementation attempts to retrieve a URL corresponding to
     * the {@link #getHelpMapID help ID}, if any, in the value map of the given
     * localized {@code HelpSet}.
     *
     * @return	    a URL, or {@code null} if no URL applies
     *
     * @param	    helpSet
     *		    a localized {@code HelpSet}
     *
     * @return	    a URL, or {@code null} if no URL is appropriate for this
     *        	    {@code Control}
     */
    public URL getHelpURL(HelpSet helpSet) {
	String id = getHelpMapID();
	if (id != null) {
	    // JavaHelp provides no hash into Map values, sigh...
	    @SuppressWarnings({"unchecked"})
	    Enumeration<javax.help.Map.ID> ids =
		helpSet.getCombinedMap().getAllIDs();

	    for (; ids.hasMoreElements();) {
		javax.help.Map.ID mid = ids.nextElement();
		if (mid.getIDString().equals(id)) {
		    try {
			return mid.getURL();
		    } catch (MalformedURLException ignore) {
			getLog().log(Level.SEVERE, String.format(
			    "id \"%s\" invalid for help set: %s", id,
			    helpSet.getHelpSetURL()));
		    }
		    break;
		}
	    }
	}

	return null;
    }

    /**
     * Gets a {@code Logger} for this class.  The {@code Logger}'s name is
     * derived from the class package name.
     */
    protected Logger getLog() {
	return Logger.getLogger(getClass().getPackage().getName());
    }

    /**
     * Gets the {@link Navigator} passed to the {@link #start} method, if
     * this {@code Control} is started, or {@code null} if this {@code Control}
     * is stopped.
     */
    public Navigator getNavigator() {
	return navigator;
    }

    /**
     * Gets a {@link StructuredAction} that invokes {@link #resetAll}.
     */
    public StructuredAction<?, ?, ?> getResetAction() {
	return resetAction;
    }

    /**
     * Gets the child {@code Control} currently running, or {@code null} if
     * there is none.
     */
    public Control getRunningChild() {
	return child;
    }

    /**
     * Gets a {@link StructuredAction} that invokes {@link #saveAll}.
     */
    public StructuredAction<?, ?, ?> getSaveAction() {
	return saveAction;
    }

    /**
     * Called by {@link #stop} when there are unsaved changes, gets the action
     * that should be taken to handle them.
     * <p/>
     * This default implementation returns {@link UnsavedChangesAction#DISCARD}.
     * Subclasses may wish to prompt the user to determine the appropriate
     * action to take.
     */
    protected UnsavedChangesAction getUnsavedChangesAction() {
	return UnsavedChangesAction.DISCARD;
    }

    /**
     * Gets a hint as to whether this {@code Control} should be returned by a
     * parent {@code Control}'s {@link #getBrowsable} method.  The parent may
     * choose to ignore this hint.
     * <p/>
     * This default implementation returns {@code true}.
     */
    public boolean isBrowsable() {
	return true;
    }

    /**
     * Indicates whether there are any unsaved changes in this {@code Control}.
     * <p/>
     * This default implementation returns {@code false}.
     */
    protected boolean isChanged() {
	return false;
    }

    public boolean isStarted() {
	return navigator != null;
    }

    /**
     * If appropriate, resets this {@code Control}, discarding any pending
     * changes.
     * <p/>
     * This default implementation does nothing.
     *
     * @exception   ActionAbortedException
     *		    if this operation is cancelled
     *
     * @exception   ActionFailedException
     *		    if this operation fails
     */
    protected void reset() throws ActionAbortedException, ActionFailedException
    {
    }

    /**
     * {@link #reset Reset}s all {@code Control}s from the top of the navigation
     * stack to this {@link Control}, discarding any pending changes.
     *
     * @exception   ActionAbortedException
     *		    see {@link #reset}
     *
     * @exception   ActionFailedException
     *		    see {@link #reset}
     *
     * @exception   IllegalStateException
     *		    if this {@link Control} is not started
     */
    protected void resetAll() throws ActionAbortedException,
	ActionFailedException {

	assertStartState(true);

	List<Control> path = navigator.getPath();
	if (!path.contains(this)) {
	    throw new IllegalStateException();
	}

	for (int i = path.size() - 1; i >= 0; i--) {
	    Control control = path.get(i);
	    control.reset();
	    if (control == this) {
		break;
	    }
	}
    }

    /**
     * If appropriate, saves any changes made while this {@code Control} is
     * running.
     * <p/>
     * This default implementation does nothing.
     *
     * @exception   ActionAbortedException
     *		    if this operation is cancelled
     *
     * @exception   ActionFailedException
     *		    if this operation fails
     *
     * @exception   ActionUnauthorizedException
     *		    if the current user has insufficient privileges for this
     *		    operation
     */
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {
    }

    /**
     * {@link #save Save}s all {@code Control}s from the top of the navigation
     * stack to this {@link Control}.
     *
     * @exception   ActionAbortedException
     *		    see {@link #save}
     *
     * @exception   ActionFailedException
     *		    see {@link #save}
     *
     * @exception   ActionUnauthorizedException
     *		    see {@link #save}
     *
     * @exception   IllegalStateException
     *		    if this {@link Control} is not started
     */
    protected void saveAll() throws ActionAbortedException,
	ActionFailedException, ActionUnauthorizedException {

	assertStartState(true);

	List<Control> path = navigator.getPath();
	if (!path.contains(this)) {
	    throw new IllegalStateException();
	}

	for (int i = path.size() - 1; i >= 0; i--) {
	    Control control = path.get(i);
	    if (control.isChanged()) {
		control.save();
	    }
	    if (control == this) {
		break;
	    }
	}
    }

    /**
     * Sets the identifier for this {@code Control}.
     */
    protected void setId(String id) {
	this.id = id;
    }

    /**
     * Sets the name for this {@code Control}.
     */
    protected void setName(String name) {
	this.name = name;
    }

    /**
     * Saves references to the given {@link #getNavigator Navigator} and {@link
     * #getParameters initialization parameters}.
     * <p/>
     * Called by the {@link Navigator} when this {@code Control} is pushed onto
     * the {@code Control} stack.
     *
     * @param	    navigator
     *		    the {@link Navigator} that handles navigation to/from this
     *		    {@code Controls}
     *
     * @param	    parameters
     *		    non-{@code null}, but optional (may be empty) initialization
     *		    parameters
     *
     * @exception   NavigationAbortedException
     *		    if this action is cancelled or vetoed
     *
     * @exception   InvalidParameterException
     *		    if this action fails due to invalid initialization
     *		    parameters
     *
     * @exception   NavigationFailedException
     *		    if this action fails for some other reason
     *
     * @exception   IllegalStateException
     *		    if this {@link Control} is already started
     */
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	assertStartState(false);
	this.navigator = navigator;
	this.parameters = parameters;
    }

    /**
     * If {@code isCancel} is {@code false}, saves, resets, or cancels changes
     * {@link #isChanged if necessary}, based on the return value of {@link
     * #getUnsavedChangesAction}.  Then resets the references to the {@link
     * #getNavigator Navigator} and {@link #getParameters initialization
     * parameters}.
     * <p/>
     * Called by the {@link Navigator} prior to this {@code Control} being
     * removed as the current {@code Control}.
     *
     * @param	    isCancel
     *		    {@code true} if this {@code Control} is being stopped as
     *		    part of a {@code cancel} operation, {@code false} otherwise
     *
     * @exception   NavigationAbortedException
     *		    if this {@code Control} should remain the current {@code
     *		    Control}
     *
     * @exception   IllegalStateException
     *		    if this {@link Control} is not started
     */
    public void stop(boolean isCancel) throws NavigationAbortedException {
	assertStartState(true);

	if (!isCancel && isChanged()) {
	    try {
		switch (getUnsavedChangesAction()) {
		    case SAVE:
			getSaveAction().invoke();
			break;

		    case DISCARD:
			getResetAction().invoke();
			break;

		    default:
		    case CANCEL:
			throw new NavigationAbortedException();
		}

	    // Thrown by invoke()
	    } catch (ActionException e) {
		throw new NavigationAbortedException(e);
	    }
	}

	this.navigator = null;
	this.parameters = null;
    }

    //
    // Private methods
    //

    private void assertStartState(boolean started) {
	if (isStarted() != started) {
	    throw new IllegalStateException(started ? "control started" :
		"control not started");
	}
    }

    //
    // Static methods
    //

    /**
     * Decodes the given encoded {@code String} into an identifier and
     * parameters, encapsulated by a {@link SimpleNavigable}.
     *
     * @param	    encoded
     *		    an {@link #encode encode}d {@code String}
     *
     * @return	    a {@link SimpleNavigable}
     */
    public static SimpleNavigable decode(String encoded) {
	String[] elements = encoded.split("\\?", 2);
	String id = elements[0];
	Map<String, String> parameters = new HashMap<String, String>();

	try {
	    id = URLDecoder.decode(elements[0], ENCODING);
	} catch (UnsupportedEncodingException ignore) {
	}

	if (elements.length >= 2 && !elements[1].isEmpty()) {
	    String[] keyEqVals = elements[1].split("&");

	    for (String keyEqVal : keyEqVals) {
		String[] nvPair = keyEqVal.split("=", 2);
		String key = nvPair[0];
		String value = nvPair.length < 2 ? "" : nvPair[1];

		try {
		    key = URLDecoder.decode(key, ENCODING);
		    value = URLDecoder.decode(value, ENCODING);
		} catch (UnsupportedEncodingException ignore) {
		}

		parameters.put(key, value);
	    }
	}

	return new SimpleNavigable(id, null, parameters);
    }

    /**
     * Encodes the given identifier and parameters.
     *
     * @param	    id
     *		    a {@link Control#getId Control identifier}
     *
     * @param	    parameters
     *		    initialization parameters, or {@code null} if no parameters
     *		    apply
     *
     * @return	    an encoded String
     */
    public static String encode(String id, Map<String, String> parameters) {
	StringBuilder buffer = new StringBuilder();

	try {
	    buffer.append(URLEncoder.encode(id, ENCODING));

	    if (parameters != null && !parameters.isEmpty()) {
		buffer.append("?");
		boolean first = true;

		for (String key : parameters.keySet()) {
		    if (first) {
			first = false;
		    } else {
			buffer.append("&");
		    }

		    String value = parameters.get(key);
		    if (value == null) {
			value = "";
		    } else {
			value = URLEncoder.encode(value, ENCODING);
		    }

		    key = URLEncoder.encode(key, ENCODING);

		    buffer.append(key).append("=").append(value);
		}
	    }
	} catch (UnsupportedEncodingException ignore) {
	}

	return buffer.toString();
    }
}
