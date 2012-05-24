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
 * Copyright (c) 2004, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;

import java.util.*;

import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * SMC code adapted for Visual Panels
 *
 * ActionString interposes between the application code and it's resource
 * bundle, but parses the returned string for the mnemonic indicator and
 * removes it.  The mnemonic character is '&', as used in Windows.  This
 * class make it easy to localize the text and associated mnemonics in a
 * resource properties file - mnemonics can be embedded within the string,
 * obviating the need for seperate resource strings for the mnemonics.
 *
 * Note: many Swing components can now take in HTML encoded text in addition
 * to plain text. To encode a mnemonic in HTML the '&' has to be encoded
 * in the HTML escaped form '&amp;'. Otherwise the HTML processing within
 * Swing will remove the a single '&'.
 *
 */
public class ActionString {

    private String  string;
    private int mnemonic = 0;

    /**
     * Returns the localized message associated with the specified message key
     * from the default resource bundle.  Strip out the mnemonic indicator.
     * Users of this class can then use getString() and getMnemonic().
     *
     * @param	key	message lookup key
     */
    public ActionString(String key) {

	string = Finder.getString(key);
	split();

    } // constructor

    /*
     * Returns the text string without the mnemonic indicator
     *
     * @return the text string without the mnemonic character
     */
    public String getString() {

	return string;

    } // getString


    /*
     * Returns the mnemonic character
     *
     * @return the mnemonic character
     */
    public int getMnemonic() {

	return mnemonic;

    } // getMnemonic


    /**
     * Split the retrieved message into its string and mnemonic parts.
     */
    private void split() {

	/*
	 * Simple check to see if the text is HTML or plain text. If the text
	 * is HTML the mnemonic indicator will be encoded as '&amp;' and not
	 * the plain text '&'. Therefore extraction of the mnemonic itself
	 * is a little more interesting. Also the underline tags need to
	 * be inserted to ensure that the mnemonic character is correctly
	 * displayed underlined when the text is HTML.
	 */
	boolean isHtml =
		(string.startsWith("<html>") && string.endsWith("</html>"));

	String ampString = null;

	if (isHtml) {
	    ampString = "&amp;";
	} else {
	    ampString = "&";
	}

	int ampStringLen = ampString.length();
	int i = string.indexOf(ampString);

	if (i > -1) {
	    String sUpper = string.toUpperCase();
	    mnemonic = sUpper.charAt(i + ampStringLen);

	    StringBuffer s = new StringBuffer();
	    s.append(string.substring(0, i));

	    if (isHtml) {
		s.append("<u>");
	    }

	    s.append(string.substring(i + ampStringLen, i+ ampStringLen + 1));

	    if (isHtml) {
		s.append("</u>");
	    }

	    s.append(string.substring(i + ampStringLen + 1, string.length()));

	    string = s.toString();
	}

    } // split

} // ActionString
