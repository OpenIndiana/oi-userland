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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import javax.swing.text.*;
import javax.swing.JFormattedTextField;
import java.text.ParseException;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class HostMaskFormatter extends DefaultFormatter {

    //
    // Static data
    //

    private static final String VALID_CHARS = "[\\w\\.-]*";
    private static final int MAX_HNAME_LENGTH = 255;

    /**
     * Inner HostNameDocumentFilter class
     *
     */
    private class HostDocumentFilter extends DocumentFilter {

	public void replace(FilterBypass fb, int offset, int length,
	    String text, AttributeSet attr) throws BadLocationException {

	    if (text == null) {
		super.replace(fb, offset, length, text, attr);
		return;
	    }

	    //
	    // Don't allow invalid characters
	    //
	    if (!text.matches(VALID_CHARS)) {
		return;
	    }

	    Document doc = fb.getDocument();
	    String curText = doc.getText(0, doc.getLength());
	    String newText = getReplaceString(curText, offset, length, text);

	    //
	    // Resulting text can't exceed max character count
	    //
	    if (newText.length() > MAX_HNAME_LENGTH)
		return;

	    // bypass the filter
	    fb.replace(offset, length, text, attr);
	}

	//
	// HostNameDocumentFilter methods
	//

	private String getReplaceString(String orig, int offset, int len,
	    String text) {
	    return (orig.substring(0, offset) + text +
		orig.substring(offset + len));
	}
    }

    //
    // Instance data
    //

    private DocumentFilter filter;

    //
    // Constructors
    //

    public HostMaskFormatter() { }

    //
    // DefaultFormatter methods
    //

    //
    // Convert the text string to value string
    //

    @Override
    public Object stringToValue(String text) throws ParseException {
	if (text == null || text.isEmpty())
	    return null;

	return text;
    }

    //
    // Convert the value to text string
    //
    @Override
    public String valueToString(Object value) throws ParseException {
	return (value == null ? null : ((String) value));
    }

    public DocumentFilter getDocumentFilter() {
	if (filter == null)
	    filter = new HostDocumentFilter();
	return filter;
    }
}
