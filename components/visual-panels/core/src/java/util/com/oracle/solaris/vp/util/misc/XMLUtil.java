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

import java.util.NoSuchElementException;
import org.w3c.dom.*;

public class XMLUtil {
    public static String getTextContent(Element element) {
	StringBuilder buffer = new StringBuilder();

	element.normalize();
	NodeList children = element.getChildNodes();
	for (int i = 0, n = children.getLength(); i < n; i++) {
	    Node child = children.item(i);
	    if (child.getNodeType() == Node.TEXT_NODE) {
		buffer.append(child.getNodeValue());
	    }
	}

	return buffer.toString().trim();
    }

    public static String getFullPath(Node node) {
	StringBuilder buffer = new StringBuilder();
	while (node != null) {
	    buffer.insert(0, node.getNodeName());
	    char separator = '/';
	    if (node instanceof Attr) {
		separator = '@';
	    }
	    buffer.insert(0, separator);
	    node = node.getParentNode();
	}
	return buffer.toString();
    }

    public static String getAttribute(Element element, String name) {
	String value = element.getAttribute(name);
	if (value != null && !value.isEmpty()) {
	    return value;
	}
	throw new NoSuchElementException(String.format(
	    "Element <%s> has no \"%s\" attribute", element, name));
    }

    public static boolean getBooleanAttribute(Element element, String name) {
	return Boolean.parseBoolean(getAttribute(element, name));
    }

    public static int getIntegerAttribute(Element element, String name) {
	return Integer.parseInt(getAttribute(element, name));
    }
}
