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

/**
 * The {@code SimpleNavigable} class provides a default implementation of
 * the {@link Navigable} interface.
 */
public class SimpleNavigable implements Navigable {
    //
    // Instance data
    //

    private String id;
    private String name;
    private Map<String, String> parameters = Collections.emptyMap();

    //
    // Constructors
    //

    /**
     * Constructs a {@code SimpleNavigable} from the given identifier and
     * initialization parameters.
     *
     * @param	    id
     *		    a {@link Control#getId Control identifier}
     *
     * @param	    name
     *		    the name of this {@link Navigable}, or {@code null} for no
     *		    name
     *
     * @param	    parameters
     *		    initialization parameters for the {@link Control} with the
     *		    given id, or {@code null} if no parameters apply
     */
    public SimpleNavigable(String id, String name,
	Map<String, String> parameters) {

	this.id = id;
	this.name = name;
	this.parameters = parameters;
    }

    /**
     * Constructs a {@code SimpleNavigable} from the given identifier and
     * initialization parameters.
     *
     * @param	    id
     *		    a {@link Control#getId Control identifier}
     *
     * @param	    name
     *		    the name of this {@link Navigable}, or {@code null} for no
     *		    name
     *
     * @param	    parameters
     *		    initialization parameters (in {@link #toMap array form}) for
     *		    the {@link Control} with the given id
     *
     * @exception   ArrayIndexOutOfBoundsException
     *		    see {@link #toMap}
     */
    public SimpleNavigable(String id, String name, String... parameters) {
	this(id, name, toMap(parameters));
    }

    //
    // HasId methods
    //

    @Override
    public String getId() {
	return id;
    }

    //
    // Navigable methods
    //

    @Override
    public String getName() {
	return name;
    }

    @Override
    public Map<String, String> getParameters() {
	return parameters;
    }

    //
    // Object methods
    //

    @Override
    public String toString() {
	return Control.encode(getId(), getParameters());
    }

    //
    // Static methods
    //

    /**
     * Converts the given parameter array to a map.
     *
     * @param	    parameters
     *		    an array of the form {@code [name1, value1, name2, value2,
     *		    ...]}
     *
     * @exception   ArrayIndexOutOfBoundsException
     *		    if the given array does not take the above form
     */
    public static Map<String, String> toMap(String... parameters) {
	if (parameters == null) {
	    return null;
	}

	Map<String, String> map = new HashMap<String, String>();
	for (int i = 0; i < parameters.length; i += 2) {
	    map.put(parameters[i], parameters[i + 1]);
	}

	return map;
    }
}
