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
import java.util.*;

public class ResourceFinder extends ItemFinder {
    //
    // Instance data
    //

    // Additional paths to search
    private Set<String> addlPaths = new HashSet<String>();

    //
    // ResourceFinder methods
    //

    /**
     * Add a base path to search for resources.
     *
     * @param	    path
     *		    a base path suitable for construction of a
     *		    {@code String}
     */
    public void addSearchPath(String path) {
	// Remove leading '/'s, canonicalize trailing '/'s
	path = path.replaceFirst("^/+", "").replaceFirst("/*$", "/");

	synchronized (addlPaths) {
	    addlPaths.add(path);
	}
    }

    /**
     * Return a resource URL for the given resource name.  All packages in the
     * hierarchy above the given package are searched, using the given {@code
     * ClassLoader}.  See the class notes for details on the search algorithm.
     *
     * @param	    loader
     *		    the {@code ClassLoader} to load the resource, or {@code
     *		    null} to use the system {@code ClassLoader}
     *
     * @param	    pkg
     *		    a point in the package hierarchy to search for the resource
     *
     * @param	    name
     *		    the name of the resource
     *
     * @return	    a {@code URL} object, or {@code null} if no resource with
     *		    this name is found
     */
    public URL getResource(ClassLoader loader, String pkg, String name) {
	// Remove leading/trailing '/'s
	name = name.replaceFirst("^/+|/+$", "");

	// Convert package to resource directory
	String dir = pkg == null ? "" : pkg.replace('.', '/');
	if (!dir.isEmpty()) {
	    dir += "/";
	}

	// First search up the package hierarchy
	while (true) {
	    String path = dir + name;

	    URL url = loader == null ?
		ClassLoader.getSystemResource(path) :
		loader.getResource(path);
	    if (url != null) {
		return url;
	    }

	    if (dir.isEmpty()) {
		break;
	    } else {
		dir = dir.replaceFirst("[^/]*/$", "");
	    }
	}

	// Next search any additional paths
	synchronized (addlPaths) {
	    for (String path : addlPaths) {
		path += name;
		URL url = loader == null ?
		    ClassLoader.getSystemResource(path) :
		    loader.getResource(path);
		if (url != null) {
		    return url;
		}
	    }
	}

	return null;
    }

    /**
     * Return a resource URL for the given resource name.  All packages in the
     * hierarchy above the given package are searched, using the caller's {@code
     * ClassLoader}.  See the class notes for details on the search algorithm.
     *
     * @param	    pkg
     *		    a point in the package hierarchy to search for the resource
     *
     * @param	    name
     *		    the name of the resource
     *
     * @return	    a {@code URL} object, or {@code null} if no resource with
     *		    this name is found
     */
    public URL getResource(String pkg, String name) {
	return getResource(getCallerClass().getClassLoader(), pkg, name);
    }

    /**
     * Return a resource URL for the given resource name.  All packages in the
     * hierarchy above the calling class are searched, using the caller's
     * {@code ClassLoader}.  See the class notes for details on the search
     * algorithm.
     *
     * @param	    name
     *		    the name of the resource
     *
     * @return	    a {@code URL} object, or {@code null} if no resource with
     *		    this name is found
     */
    public URL getResource(String name) {
	Class caller = getCallerClass();
        return getResource(caller.getClassLoader(),
	    caller.getPackage().getName(), name);
    }
}
