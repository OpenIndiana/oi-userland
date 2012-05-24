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
import javax.swing.event.*;
import javax.swing.JFormattedTextField;
import java.text.ParseException;

@SuppressWarnings({"serial"})
public class IPMaskFormatter extends DefaultFormatter implements
    DocumentListener  {

    //
    // Static data
    //

    private static String netPlaceholder =  "   .   .   .   /  ";

    private static final int MAX_CHAR_COUNT = netPlaceholder.length();
    private static final String VALID_CHARS = "[ \\d\\.\\/]*";
    private static final String ADDRESS_MASK =
	"(([\\d ]{0,3})\\.){3}[\\d ]{0,3}(\\/[\\d ]{0,2})?";

    /**
     * Inner IPDocumentFilter class
     *
     */
    private class IPDocumentFilter extends DocumentFilter {

	@Override
	public void remove(FilterBypass fb, int offset, int length)
	    throws BadLocationException {
	    Document doc = fb.getDocument();
	    String curText = doc.getText(0, doc.getLength());
	    String remText = curText.substring(offset, offset + length);

	    //
	    // Don't allow remove of three periods, '.'
	    //
	    if (remText.indexOf(".") != -1)
            	return;

	    fb.remove(offset, length);
	}

	@Override
	public void insertString(FilterBypass fb, int offset,
	    String text, AttributeSet attr) throws BadLocationException {
	    replace(fb, offset, 0, text, attr);
	}

	@Override
	public void replace(FilterBypass fb, int offset, int length,
	    String text, AttributeSet attr) throws BadLocationException {

	    if (text == null) {
		fb.replace(offset, length, text, attr);
		return;
	    }

	    //
	    // Don't allow invalid characters
	    //
	    if (!text.matches(VALID_CHARS))
		return;

	    clearSpace(fb, offset, length, text);
	    Document doc = fb.getDocument();
	    String curText = doc.getText(0, doc.getLength());
	    String newText = getReplaceString(curText, offset, length, text);

	    //
	    // Resulting text can't exceed max character count
	    //
	    if (newText.length() > MAX_CHAR_COUNT ||
		!newText.matches(ADDRESS_MASK))
		return;

	    // bypass the filter
	    fb.replace(offset, length, text, attr);
	}

	//
	// IPDocumentFilter methods
	//

	private void clearSpace(FilterBypass fb, int off, int deleteLen,
	    String txt) throws BadLocationException {

	    if (deleteLen > 0)
		return;

	    int textLen = txt.length();
	    Document doc = fb.getDocument();
	    if ((off + textLen) > doc.getLength())
		return;

	    String curText = doc.getText(0, doc.getLength());
	    String replacedText = curText.substring(off, off + textLen);

	    for (int i = 0; i < textLen; i++) {
		if (replacedText.charAt(i) != ' ')
		    return;
	    }

	    fb.remove(off, textLen);
	}

	private String getReplaceString(String orig, int offset, int len,
	    String text) {
	    return (orig.substring(0, offset) + text +
		orig.substring(offset + len));
	}
    } // End of IPDocumentFilter

    //
    // Instance data
    //

    private DocumentFilter filter;

    //
    // Constructors
    //

    public IPMaskFormatter() {

    }

    //
    // DocumentListener methods
    //

    @Override
    public void changedUpdate(DocumentEvent e) {
    }

    //
    // After insertion, update cursor when appropriate
    //

    @Override
    public void insertUpdate(DocumentEvent e) {
        JFormattedTextField field = getFormattedTextField();
        int insertPos = field.getCaretPosition() + 1;

        String text = field.getText();
        if (insertPos < 3 || insertPos >= text.length())
            return;

        String nextChar = text.substring(insertPos, insertPos + 1);
        String prevOctet = text.substring(insertPos - 3, insertPos);

	if (nextChar.matches("[.\\/]") && prevOctet.indexOf(".") < 0) {
            field.setCaretPosition(insertPos++);
        }
    }

    @Override
    public void removeUpdate(DocumentEvent e) {
    }

    //
    // DefaultFormatter methods
    //

    //
    // Convert the text string to value string
    //

    @Override
    public Object stringToValue(String text) throws ParseException {
	if (text == null || text.isEmpty())
	    return netPlaceholder;

	return text;
    }

    //
    // Convert the value to  text string
    //
    @Override
    public String valueToString(Object value) throws ParseException {
	return (value == null ? netPlaceholder : ((String) value));
    }

    @Override
    public DocumentFilter getDocumentFilter() {
	if (filter == null)
	    filter = new IPDocumentFilter();
	return filter;
    }

    @Override
    public void install(JFormattedTextField ftf) {
        super.install(ftf);
        ftf.getDocument().addDocumentListener(this);
    }
}
