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

package com.oracle.solaris.vp.util.misc.finder;

import java.net.URL;
import java.security.*;
import java.util.*;
import javax.help.*;
import javax.swing.ImageIcon;

/**
 * The {@code Finder} class is a convenience class for finding message strings,
 * icons, and other resources from the default *{@code Finder} classes.
 */
public class Finder implements FindingClass {
    //
    // Static data
    //

    public static final HelpSetFinder hFinder = new HelpSetFinder();
    public static final IconFinder iFinder = new IconFinder();
    public static final MessageFinder mFinder = new MessageFinder();
    public static final ResourceFinder rFinder = new ResourceFinder();

    //
    // Static methods
    //

    /**
     * Gets the requested help set for the given parameters, using the security
     * context of this class.
     *
     * @see	    HelpSetFinder#getHelpSet(ClassLoader,String)
     */
    public static HelpSet getHelpSet(final ClassLoader loader,
	final String name) throws HelpSetException {

	// Using PrivilegedExceptionAction offers no compile-time checking of
	// thrown Exceptions, so use this mildly awkward method instead

	final HelpSetException[] err = new HelpSetException[1];

	HelpSet helpSet = AccessController.doPrivileged(
	    new PrivilegedAction<HelpSet>() {
		@Override
		public HelpSet run() {
		    try {
			return hFinder.getHelpSet(loader, name);
		    } catch (HelpSetException e) {
			err[0] = e;
		    }
		    return null;
		}
	    });

	if (err[0] != null) {
	    throw err[0];
	}

	return helpSet;
    }

    /**
     * Gets the requested icon using the security context of this class.
     *
     * @see	    IconFinder#getIcon(String)
     */
    public static ImageIcon getIcon(final String name) {
	return AccessController.doPrivileged(
	    new PrivilegedAction<ImageIcon>() {
		@Override
		public ImageIcon run() {
		    return iFinder.getIcon(name);
		}
	    });
    }

    /**
     * Gets the requested icons using the security context of this class.
     *
     * @see	    IconFinder#getIcon(String)
     */
    public static List<ImageIcon> getIcons(final String... names) {
	return AccessController.doPrivileged(
	    new PrivilegedAction<List<ImageIcon>>() {
		@Override
		public List<ImageIcon> run() {
		    List<ImageIcon> icons = new ArrayList<ImageIcon>();

		    for (String name : names) {
			ImageIcon icon = iFinder.getIcon(name);
			if (icon != null) {
			    icons.add(icon);
			}
		    }

		    return icons;
		}
	    });
    }

    /**
     * Gets the requested resource using the security context of this class.
     *
     * @see	    ResourceFinder#getResource(String)
     */
    public static URL getResource(final String name) {
	return AccessController.doPrivileged(
	    new PrivilegedAction<URL>() {
		@Override
		public URL run() {
		    return rFinder.getResource(name);
		}
	    });
    }

    /**
     * Gets the requested parameterized {@code String} resource.
     *
     * @see	    MessageFinder#getString(String,Object[])
     */
    public static String getString(String key, Object... args) {
	return mFinder.getString(key, args);
    }
}
