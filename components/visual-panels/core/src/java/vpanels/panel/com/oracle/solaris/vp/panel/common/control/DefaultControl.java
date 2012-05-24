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

package com.oracle.solaris.vp.panel.common.control;

import java.util.*;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.model.*;

/**
 * The {@code DefaultControl} class is a {@link Control} that provides a
 * list-based implementation of {@link #getChildControl}.
 */
public class DefaultControl<P extends PanelDescriptor> extends Control
    implements HasPanelDescriptor<P> {

    //
    // Instance data
    //

    private P descriptor;
    private ClientContext context;
    protected List<Control> children = new ArrayList<Control>();

    private DefaultStructuredAction resetAction;
    private DefaultStructuredAction saveAction;

    //
    // Constructors
    //

    public DefaultControl(String id, String name, ClientContext context) {
	super(id, name);
	this.context = context;

	resetAction =
	    new DefaultStructuredAction(null, context) {
		@Override
		public Object workBusy(Object pInput, Object rtInput)
		    throws ActionAbortedException, ActionFailedException,
		    ActionUnauthorizedException {

		    resetAll();
		    return null;
		}
	    };

	saveAction =
	    new DefaultStructuredAction(null, context) {
		@Override
		public Object workBusy(Object pInput, Object rtInput)
		    throws ActionAbortedException, ActionFailedException,
		    ActionUnauthorizedException {

		    saveAll();
		    return null;
		}
	    };
    }

    public DefaultControl(String id, String name, P descriptor) {
	this(id, name, descriptor.getClientContext());
	this.descriptor = descriptor;
    }

    //
    // HasPanelDescriptor methods
    //

    @Override
    public P getPanelDescriptor() {
	return descriptor;
    }

    //
    // Control methods
    //

    /**
     * Calls {@link #ensureChildrenCreated}, then iterates through all {@link
     * Control}s added via {@link #addChildren addChildren} until it finds one
     * whose {@link Control#getId getId} method returns a value matching {@code
     * id}.
     */
    @Override
    public Control getChildControl(String id) {
	synchronized (children) {
	    ensureChildrenCreated();

	    for (Control child : children) {
		if (child.getId().equals(id)) {
		    return child;
		}
	    }
	}

	return null;
    }

    /**
     * Calls {@link #ensureChildrenCreated}, then returns a list of all child
     * {@link Control}s that return {@code true} from their {@link #isBrowsable}
     * methods.
     * <p/>
     * Subclasses may wish to override this method to apply different criteria
     * to the returned list.
     */
    @Override
    public List<Navigable> getBrowsable() {
	synchronized (children) {
	    ensureChildrenCreated();

	    List<Navigable> navigables = new ArrayList<Navigable>();
	    for (Control child : children) {
		if (child.isBrowsable()) {
		    navigables.add(child);
		}
	    }

	    return navigables;
	}
    }

    /**
     * Gets a {@link DefaultStructuredAction} that invokes {@link #resetAll},
     * logging errors.
     */
    @Override
    public DefaultStructuredAction<?, ?, ?> getResetAction() {
	return resetAction;
    }

    /**
     * Gets a {@link DefaultStructuredAction} that invokes {@link #saveAll},
     * logging errors and prompting for login on {@code
     * ActionUnauthorizedException}s.
     */
    @Override
    public DefaultStructuredAction<?, ?, ?> getSaveAction() {
	return saveAction;
    }

    //
    // DefaultControl methods
    //

    public void addChildren(Control... controls) {
	synchronized (children) {
	    for (Control child : controls) {
		if (!children.contains(child)) {
		    children.add(child);
		}
	    }
	}
    }

    /**
     * Asynchronously closes this instance.
     */
    public void doQuit() {
	getResetAction().asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    try {
			getClientContext().closeInstance(true);
		    } catch (ActionException ignore) {
		    }
		}
	    });
    }

    /**
     * Asynchronously invokes this {@link Control}'s save action, then closes
     * this instance.
     */
    public void doSaveAndQuit() {
	final StructuredAction<?, ?, ?> saveAction = getSaveAction();
	saveAction.asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    try {
			saveAction.invoke();
			getClientContext().closeInstance(false);
		    } catch (ActionException ignore) {
		    }
		}
	    });
    }

    /**
     * Ensures that any child {@link Control}s that should be available from the
     * {@link #getChildControl} method have been created.  This method is called
     * from the {@link #getChildControl} and {@link #getBrowsable} methods.
     * <p/>
     * This default implementation does nothing.
     */
    protected void ensureChildrenCreated() {
    }

    public ClientContext getClientContext() {
	return descriptor != null ? descriptor.getClientContext() : context;
    }

    /**
     * Convenience method to retrieve a parameter from a given parameter {@code
     * Map}, or throw a {@link MissingParameterException} if the parameter does
     * not exist.  Intended to be called from within {@link #start}.
     */
    protected String getParameter(Map<String, String> parameters,
	String parameter) throws MissingParameterException {

	if (!parameters.containsKey(parameter)) {
	    throw new MissingParameterException(getId(), parameter);
	}

	return parameters.get(parameter);
    }

    protected void removeChild(int index) {
	synchronized (children) {
	    children.remove(index);
	}
    }
}
