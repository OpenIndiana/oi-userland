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

package com.oracle.solaris.vp.util.misc.finder;

import java.net.URL;
import java.util.Locale;
import javax.help.*;

public class HelpSetFinder extends ItemFinder {
    /**
     * Gets the requested help set for the given parameters.
     *
     * @param	    loader
     *		    the {@code ClassLoader} to use, or {@code null} to use the
     *		    {@code ClassLoader} of the calling class. <addtext>
     *
     * @param	    name
     *		    the name of the resource
     *
     * @return	    a {@code HelpSet}, or {@code null} if no {@code HelpSet} was
     *		    found
     *
     * @exception   HelpSetException
     *		    if there were problems parsing the helpset
     */
    public HelpSet getHelpSet(ClassLoader loader, String name)
	throws HelpSetException {

	if (loader == null) {
	    loader = getCallerClass().getClassLoader();
	}

	URL url = HelpSet.findHelpSet(loader, name);
	return url == null ? null : new HelpSet(loader, url);
    }

    /**
     * Gets the requested help set for the given parameters.
     *
     * @param	    loader
     *		    the {@code ClassLoader} to use, or {@code null} to use the
     *		    {@code ClassLoader} of the calling class. <addtext>
     *
     * @param	    name
     *		    the name of the resource
     *
     * @param	    locale
     *		    the desired locale
     *
     * @return	    a {@code HelpSet}, or {@code null} if no {@code HelpSet} was
     *		    found
     *
     * @exception   HelpSetException
     *		    if there were problems parsing the helpset
     */
    public HelpSet getHelpSet(ClassLoader loader, String name, Locale locale)
	throws HelpSetException {

	if (loader == null) {
	    loader = getCallerClass().getClassLoader();
	}

	URL url = HelpSet.findHelpSet(loader, name, locale);
	return url == null ? null : new HelpSet(loader, url);
    }

    /**
     * Gets the requested help set for the given parameters.
     *
     * @param	    loader
     *		    the {@code ClassLoader} to use, or {@code null} to use the
     *		    {@code ClassLoader} of the calling class. <addtext>
     *
     * @param	    shortName
     *		    the short name of the resource
     *
     * @param	    extension
     *		    the extension of the resource
     *
     * @param	    locale
     *		    the desired locale
     *
     * @return	    a {@code HelpSet}, or {@code null} if no {@code HelpSet} was
     *		    found
     *
     * @exception   HelpSetException
     *		    if there were problems parsing the helpset
     */
    public HelpSet getHelpSet(ClassLoader loader, String shortName,
	String extension, Locale locale) throws HelpSetException {

	if (loader == null) {
	    loader = getCallerClass().getClassLoader();
	}

	URL url = HelpSet.findHelpSet(loader, shortName, extension, locale);
	return url == null ? null : new HelpSet(loader, url);
    }
}
