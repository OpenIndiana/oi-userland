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

package com.oracle.solaris.vp.util.swing;

/**
 * The {@code DescendantEnabler} interface indicates that the implementing
 * class, presumably a subclass of {@code Container}, propagates its enabled
 * status onto any descendent {@code Component}s.
 * <p>
 * Methods like {@link GUIUtil#setEnabledRecursive(Component,boolean)} may abort
 * recursion into the {@code Component} hierarchy when a {@code
 * DescendantEnabler} is encountered.
 */
public interface DescendantEnabler {
}
