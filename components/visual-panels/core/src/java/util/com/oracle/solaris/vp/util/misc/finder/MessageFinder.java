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

import java.text.MessageFormat;
import java.util.*;
import com.oracle.solaris.vp.util.misc.TextUtil;

public class MessageFinder extends ItemFinder {
    //
    // Static data
    //

    /**
     * The default base name suffix ("{@code resources.Resources}") to append to
     * package names when searching for a {@code ResourceBundle}.
     */
    public static final String DEFAULT_BASE_NAME_SUFFIX = "resources.Resources";

    //
    // Instance data
    //

    // Additional paths to search for resource strings
    private List<String> addlPaths = new ArrayList<String>();
    private List<String> roAddlPaths = Collections.unmodifiableList(addlPaths);

    private String baseNameSuffix = DEFAULT_BASE_NAME_SUFFIX;
    private Locale locale;

    //
    // MessageFinder methods
    //

    /**
     * Add a base path to search for {@code ResourceBundle}s.
     *
     * @param	    path
     *		    a base path suitable for construction of a
     *		    {@code ResourceBundle}
     */
    public void addSearchPath(String path) {
	synchronized (addlPaths) {
	    if (addlPaths.indexOf(path) == -1) {
		addlPaths.add(path);
	    }
	}
    }

    /**
     * Gets the additional paths to search for {@code ResourceBundle}s.
     *
     * @return	    an unmodifiable {@code List}
     */
    public List<String> getSearchPaths() {
	return roAddlPaths;
    }

    /**
     * Get the base name suffix that is appended to package names when searching
     * for a {@code ResourceBundle}.
     */
    public String getBaseNameSuffix() {
	return baseNameSuffix;
    }

    /**
     * Gets the {@code Locale} used when retrieving {@code ResourceBundle}s.
     * The default value is the {@code Locale} returned by {@code
     * Locale.getDefault()}.
     */
    public Locale getLocale() {
	return locale == null ? Locale.getDefault() : locale;
    }

    /**
     * Return a parameterized localized string for the given key.  See the class
     * notes for details on the search algorithm.
     *
     * @param	    loader
     *		    the {@code ClassLoader} to load the resource, or {@code
     *		    null} to use the system {@code ClassLoader}
     *
     * @param	    pkg
     *		    a point in the package hierarchy to search for resources, or
     *		    {@code null} to search only from the top
     *
     * @param	    key
     *		    the identifying key in the {@code ResourceBundle}, which may
     *		    contain an optional numerical suffix (.[0-9]+) that will be
     *		    stripped off to form a backup key in case this key is not
     *		    found
     *
     * @param	    args
     *		    parameters to place into the localized string, per
     *		    the {@code java.text.MessageFormat} class.
     *
     * @return	    a parameterized localized string for the given key, or
     *		    {@code null} if no such resource is found
     */
    public String getString(ClassLoader loader, String pkg, String key,
	Object... args) {

	Locale locale = getLocale();
	String suffix = getBaseNameSuffix();

	List<String> paths = getSearchPathsFromPackage(pkg);
	paths.addAll(getSearchPaths());

	// If key ends with a numerical element, strip it off to form a backup
	// key in case this key doesn't match
	List<String> keys = new ArrayList<String>(2);
	keys.add(key);
	String altKey = key.replaceFirst("\\.\\d+$", "");
	if (!altKey.equals(key)) {
	    keys.add(altKey);
	}

	for (String path : paths) {
	    String bundleName = path.isEmpty() ? suffix : (path + "." + suffix);

	    try {
		ResourceBundle bundle = ResourceBundle.getBundle(
		    bundleName, locale, loader);

		for (String k : keys) {
		    try {
			// Throws a MissingResourceException
			String value = bundle.getString(k);

			String[] groups = TextUtil.match(value,
			    "^@forward:(((\\w+\\.)*\\w+):)?((\\w+\\.)*\\w+)");
			if (groups != null) {
			    String fPkg = groups[2] == null ? pkg : groups[2];
			    String fKey = groups[4];
			    return getString(loader, fPkg, fKey, args);
			}

			if (args != null) {
			    value = MessageFormat.format(value, args);
			}
			return value;

		    } catch (MissingResourceException ignore) {
		    }
		}

	    // Thrown by getBundle
	    } catch (MissingResourceException ignore) {
	    }
	}

	// Track down missing/bad resources during development;
	// vpanels.debug.messages is a system property containing a regular
	// expression matching all keys that should NOT be reported when no
	// message is found.
	String regex = System.getProperty("vpanels.debug.messages");
	if (regex != null && !key.matches(regex)) {
	    System.err.printf("Returning null for key: %s\n", key);
	    Thread.currentThread().dumpStack();
	}

	return null;
    }

    /**
     * Return a parameterized localized string for the given key.  See the class
     * notes for details on the search algorithm.
     *
     * @param	    pkg
     *		    a point in the package hierarchy to search for resources
     *
     * @param	    key
     *		    the identifying key in the {@code ResourceBundle}
     *
     * @param	    args
     *		    parameters to place into the localized string, per
     *		    the {@code java.text.MessageFormat} class.
     *
     * @return	    a parameterized localized string for the given key, or
     *		    {@code null} if no such resource is found
     */
    public String getStringFromPackage(String pkg, String key, Object... args) {
	return getString(getCallerClass().getClassLoader(), pkg, key, args);
    }

    /**
     * Return a parameterized localized string for the given key.  All
     * {@code ResourceBundle}s of the form {@code resources/Resources} in the
     * package hierarchy above the calling class are searched.
     *
     * @param	    key
     *		    the identifying key in the {@code ResourceBundle}
     *
     * @param	    args
     *		    parameters to place into the localized string, per
     *		    the {@code java.text.MessageFormat} class.
     *
     * @return	    a parameterized localized string for the given key, or
     *		    {@code null} if no such resource is found
     */
    public String getString(String key, Object... args) {
	Class caller = getCallerClass();
        return getString(caller.getClassLoader(), caller.getPackage().getName(),
	    key, args);
    }

    /**
     * Set the base name suffix to append to package names when searching for a
     * {@code ResourceBundle}.	The default value is identified by the {@link
     * #DEFAULT_BASE_NAME_SUFFIX DEFAULT_BASE_NAME_SUFFIX} static field.
     */
    public void setBaseNameSuffix(String baseNameSuffix) {
	this.baseNameSuffix = baseNameSuffix;
    }

    /**
     * Sets the {@code Locale} used when retrieving {@code ResourceBundle}s.
     *
     * @param	    locale
     *		    a {@code Locale} object, or {@code null} to use the
     *		    default {@code Locale}
     */
    public void setLocale(Locale locale) {
	this.locale = locale;
    }

    //
    // Private methods
    //

    private List<String> getSearchPathsFromPackage(String pkg) {
	if (pkg == null) {
	    pkg = "";
	}

	List<String> paths = new ArrayList<String>();
	while (!pkg.isEmpty()) {
	    paths.add(pkg);
	    pkg = TextUtil.getPackageName(pkg);
	}
	paths.add(pkg);

	return paths;
    }
}
