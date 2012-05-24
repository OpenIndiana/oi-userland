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

package com.oracle.solaris.vp.panel.common;

public class LoginProperty<T> {
    //
    // Instance data
    //

    private String name;
    private T value;
    private boolean editable;
    private boolean editableOnError;
    private boolean errored;

    //
    // Constructors
    //

    public LoginProperty(String name, T value, boolean editable) {
	this.name = name;
	this.value = value;
	this.editable = editable;
    }

    public LoginProperty(T value, boolean editable) {
	this(null, value, editable);
    }

    public LoginProperty(T value) {
	this(null, value, true);
    }

    //
    // Object methods
    //

    @Override
    public String toString() {
	return String.format(
	    "name=%s, value=%s, editable=%b, editableOnError=%b, errored=%b",
	    name, value, editable, editableOnError, errored);
    }

    //
    // LoginProperty methods
    //

    /**
     * Gets the name of this {@code LoginProperty}.
     *
     * @return	    a {@code String}, or {@code null} if no name is appropriate
     *		    or necessary
     */
    public String getName() {
	return name;
    }

    /**
     * Gets the value of this {@code LoginProperty} as a {@code T}.
     */
    public T getValue() {
	return value;
    }

    /**
     * Gets whether this {@code LoginProperty} is editable.
     */
    public boolean isEditable() {
	return editable;
    }

    /**
     * Gets whether this {@code LoginProperty} is editable in an errored state.
     */
    public boolean isEditableOnError() {
	return editableOnError;
    }

    /**
     * Gets whether this {@code LoginProperty} is in an errored state.
     */
    public boolean isErrored() {
	return errored;
    }

    /**
     * Sets whether this {@code LoginProperty} is editable.
     */
    public void setEditable(boolean editable) {
	this.editable = editable;
    }

    /**
     * Sets whether this {@code LoginProperty} is editable in an errored state.
     */
    public void setEditableOnError(boolean editableOnError) {
	this.editableOnError = editableOnError;
    }

    /**
     * Sets whether this {@code LoginProperty} is in an errored state.
     */
    public void setErrored(boolean errored) {
	if (this.errored != errored) {
	    this.errored = errored;
	    if (errored && isEditableOnError()) {
		setEditable(true);
	    }
	}
    }

    /**
     * Sets the value of this {@code LoginProperty}.
     *
     * @throws	    IllegalStateException
     *		    if this {@code LoginProperty} is not editable
     */
    public void setValue(T value) {
	if (!editable) {
	    throw new IllegalStateException();
	}

	this.value = value;
    }

    /**
     * Validates the {@link #getValue set value} of this {@code LoginProperty}.
     * This default implementation does nothing.
     *
     * @param	    request
     *		    the request, if any, of which this {@code LoginProperty} is
     *		    part
     *
     * @param	    valid
     *		    optional set of valid values, if appropriate for this {@code
     *		    LoginProperty}
     *
     * @exception   LoginPropertyException
     *		    if the set value is invalid
     */
    public void validate(LoginRequest request, T... valid)
	throws LoginPropertyException {
    }
}
