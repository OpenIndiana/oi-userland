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

package com.oracle.solaris.vp.util.misc;

import java.io.IOException;
import org.xml.sax.EntityResolver;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

/**
 * A simple EntityResolver that tracks whether a particular external entity
 * is referenced by the document.
 */
public class DTDChecker implements EntityResolver
{
    private boolean match_ = false;
    private String system_;

    /**
     * Contructs a {@code DTDChecker} that looks for references to
     * {@code SystemId}.
     *
     * @param system path of the external entity to track
     */
    public DTDChecker(String system)
    {
	system_ = "file://" + system;
    }

    /**
     * Returns whether the specified entity was referenced or not.
     *
     * @return {@code true} if the entity was referenced, {@code false} if not.
     */
    public boolean isUsed()
    {
	return (match_);
    }

    /**
     * Resets the {@code DTDChecker} so it can used again.
     */
    public void reset()
    {
	match_ = false;
    }

    /*
     * EntityResolver methods
     */

    @Override
    public InputSource resolveEntity(String publicId, String systemId)
	throws SAXException, IOException
    {
	if (publicId == null && systemId.equals(system_))
	    match_ = true;
	return (null);
    }
}
