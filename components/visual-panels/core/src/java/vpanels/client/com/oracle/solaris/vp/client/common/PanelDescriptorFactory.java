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

package com.oracle.solaris.vp.client.common;

import java.lang.reflect.*;
import java.net.URL;
import java.security.*;
import java.util.logging.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.ActionAbortedException;
import com.oracle.solaris.vp.panel.common.api.panel.CustomPanel;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public abstract class PanelDescriptorFactory {
    //
    // Instance data
    //

    private ClientContext context;
    private PanelResourceManager manager;

    //
    // Constructors
    //

    /**
     * Constructs a {@link PanelDescriptorFactory}.
     *
     * @param	    context
     *		    required data to create a {@link PanelDescriptor}
     *
     * @param	    manager
     *		    used to download resources for custom panels
     */
    public PanelDescriptorFactory(ClientContext context,
	PanelResourceManager manager) {

	this.context = context;
	this.manager = manager;
    }

    //
    // PanelDescriptorFactory methods
    //

    public ClientContext getClientContext() {
	return context;
    }

    public PanelResourceManager getPanelResourceManager() {
	return manager;
    }

    /**
     * Get a client-specific {@code ErrorPanelDescriptor} that communicates
     * information about why its {@code CustomPanel}s failed to load.
     */
    protected abstract ErrorPanelDescriptor getErrorPanelDescriptor(
	String name, ClientContext context);

    /**
     * Get a {@link PanelDescriptor} from the given {@link CustomPanel}.
     *
     * @param	    panel
     *		    a {@code CustomPanel}
     *
     * @return	    an instance of {@code panel}'s {@code PanelDescriptor}
     *		    if found, or an {@link ErrorPanelDescriptor} if an error
     *		    occurred
     *
     * @exception   ActionAbortedException
     *		    if the download is cancelled
     *
     * @exception   PanelResourceException
     *		    if a resource could not be downloaded
     */
    public PanelDescriptor getPanelDescriptor(CustomPanel panel)
	throws ActionAbortedException, PanelResourceException {

	ClientContext context = getClientContext();
	ConnectionInfo info = context.getConnectionInfo();

	Logger log = Logger.getLogger(getClass().getName());
	String pName = panel.getName();
	ErrorPanelDescriptor epd = getErrorPanelDescriptor(pName, context);

	final URL[] urls = getPanelResourceManager().downloadAll(info, panel);
	String className = panel.getPanelDescriptorClassName();

	try {
	    ClassLoader loader = AccessController.doPrivileged(
		new PrivilegedAction<ClassLoader>() {
		    @Override
		    public ClassLoader run() {
			return new PanelClassLoader(urls);
		    }
		});

	    Class clazz = loader.loadClass(className);

	    if (!PanelDescriptor.class.isAssignableFrom(clazz)) {
		String message = Finder.getString(
		    "panelload.error.class.wrongtype",
		    clazz.getName(), PanelDescriptor.class.getName());
		log.log(Level.WARNING, message);

	    } else {
		// PanelDescriptors must have a constructor that
		// takes a String ID and a ClientContext as arguments
		@SuppressWarnings({"unchecked"})
		Constructor<PanelDescriptor> constructor =
		    ((Class<PanelDescriptor>)clazz).getConstructor(
		    String.class, ClientContext.class);

		return constructor.newInstance(pName, context);
	    }
	}

	// Thrown by loadClass
	catch (ClassNotFoundException e) {
	    String message = Finder.getString(
		"panelload.error.class.notfound", className);
	    log.log(Level.WARNING, message);
	    epd.addError(panel, e);
	}

	// Thrown by getConstructor
	catch (NoSuchMethodException e) {
	    String message = Finder.getString(
		"panelload.error.class.constructor", className,
		ClientContext.class.getName());
	    log.log(Level.WARNING, message, e);
	    epd.addError(panel, e);
	}

	// Thrown by newInstance
	catch (IllegalAccessException e) {
	    String message = Finder.getString(
		"panelload.error.class.cantinstantiate", className);
	    log.log(Level.WARNING, message, e);
	    epd.addError(panel, e);
	}

	// Thrown by newInstance
	catch (InstantiationException e) {
	    Throwable cause = e.getCause();

	    String message = Finder.getString(
		"panelload.error.class.cantinstantiate", className);
	    log.log(Level.WARNING, message, cause);
	    epd.addError(panel, cause);
	}

	// Thrown by newInstance
	catch (InvocationTargetException e) {
	    Throwable target = e.getTargetException();

	    String message = Finder.getString(
		"panelload.error.class.cantinstantiate", className);
	    log.log(Level.WARNING, message, target);
	    epd.addError(panel, target);
	}

	// Thrown by newInstance
	catch (ExceptionInInitializerError e) {
	    Throwable cause = e.getCause();

	    String message = Finder.getString(
		"panelload.error.class.cantinstantiate", className);
	    log.log(Level.WARNING, message, cause);
	    epd.addError(panel, cause);
	}

	// Thrown by getConstructor
	catch (SecurityException e) {
	    String message = Finder.getString(
		"panelload.error.class.cantinstantiate", className);
	    log.log(Level.WARNING, message, e);
	    epd.addError(panel, e);
	}

	if (epd.getErrorCount() > 0) {
	    return epd;
	}

	return null;
    }
}
