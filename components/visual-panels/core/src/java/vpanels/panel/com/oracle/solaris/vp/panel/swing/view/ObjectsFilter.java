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

package com.oracle.solaris.vp.panel.swing.view;

import com.oracle.solaris.vp.panel.common.model.ManagedObject;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.predicate.*;

/**
 * The {@code ObjectsFilter} class encapsulates a predicate filter and a
 * displayable name.
 */
public class ObjectsFilter<C extends ManagedObject> {
    //
    // Static data
    //

    private static final String TEXT = Finder.getString(
	"objects.header.filter.all.label");

    //
    // Instance data
    //

    private String text_;
    private Predicate<? super C> predicate_;

    //
    // Constructors
    //

    /**
     * Constructs an {@code ObjectsFilter} with the given text.
     */
    public ObjectsFilter(String text, Predicate<? super C> predicate) {
	text_ = text;
	predicate_ = predicate;
    }

    /**
     * Constructs an {@code ObjectsFilter} with the given text.
     */
    public ObjectsFilter(String text) {
	this(text, TruePredicate.getInstance());
    }

    /**
     * Constructs an {@code ObjectsFilter} with default text indicating that all
     * items are accepted.
     */
    public ObjectsFilter() {
	this(TEXT);
    }

    //
    // Object methods
    //

    /**
     * Forwards to {@link #getText}().
     */
    @Override
    public String toString() {
	return getText();
    }

    //
    // ObjectsFilter methods
    //

    /**
     * Gets a {@link Predicate} to test whether any given {@code ManagedObject}
     * should be included in the result of the filter.
     * <p/>
     * This default implementation returns an instance of {@link TruePredicate}.
     */
    public Predicate<? super C> getPredicate() {
	assert (predicate_ != null);
	return predicate_;
    }

    public String getText() {
	return text_;
    }

    protected void setText(String text) {
	text_ = text;
    }
}
