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

package com.oracle.solaris.vp.client.swing;

import java.security.*;
import java.security.cert.*;
import java.security.cert.Certificate;
import javax.swing.JEditorPane;
import com.oracle.solaris.vp.util.misc.TextUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;

@SuppressWarnings({"serial"})
public class CertificateEditorPane extends JEditorPane {
    //
    // Instance data
    //

    private Certificate certificate;

    //
    // Constructors
    //

    public CertificateEditorPane() {
	setContentType("text/html");
	setEditable(false);
    }

    public CertificateEditorPane(Certificate certificate) {
	this();
	setCertificate(certificate);
    }

    //
    // JTextComponent methods
    //

    @Override
    public void setText(String text) {
	super.setText(text);

	// Scroll to top
	setCaretPosition(0);
    }

    //
    // CertificateEditorPane methods
    //

    public Certificate getCertificate() {
	return certificate;
    }

    /**
     * Sets the {@code Certificate} to display in this {@code
     * ExpandableCertificatePanel}.
     *
     * @param	    certificate
     *		    the {@code Certificate} object to display in this {@code
     *		    ExpandableCertificatePanel}
     */
    public void setCertificate(Certificate certificate) {
	this.certificate = certificate;

	String html;
	if (certificate instanceof X509Certificate) {
	    X509Certificate x509 = (X509Certificate)certificate;

	    Object[] args = {
		TextUtil.escapeHTMLChars(x509.getSubjectDN().toString()),
		TextUtil.escapeHTMLChars(x509.getIssuerDN().toString()),
		TextUtil.escapeHTMLChars(x509.getSerialNumber().toString(16)),
		x509.getNotBefore(),
		x509.getNotAfter(),
		TextUtil.escapeHTMLChars(getCertFingerPrint("MD5", x509)),
		TextUtil.escapeHTMLChars(getCertFingerPrint("SHA1", x509)),
		TextUtil.escapeHTMLChars(x509.getSigAlgName()),
		(Integer)x509.getVersion()
	    };

	    html = Finder.getString("certificate.view.x509", args);
	} else {
	    html = Finder.getString("certificate.view.unknown",
		TextUtil.escapeHTMLChars(certificate.getType()),
		TextUtil.escapeHTMLChars(certificate.toString()));
	}

	setText(html);
    }

    //
    // Private methods
    //

    /**
     * Gets the requested fingerprint of the certificate.
     */
    private String getCertFingerPrint(String mdAlg, Certificate cert) {
	try {
	    byte[] encCertInfo = cert.getEncoded();
	    MessageDigest md = MessageDigest.getInstance(mdAlg);
	    byte[] digest = md.digest(encCertInfo);

	    char[] hexChars = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8',
		'9', 'A', 'B', 'C', 'D', 'E', 'F'
	    };

	    StringBuilder buffer = new StringBuilder();
	    for (int i = 0; i < digest.length; i++) {
		if (i != 0) {
		    buffer.append(':');
		}
		int high = (digest[i] & 0xf0) >> 4;
		int low = digest[i] & 0x0f;
		buffer.append(hexChars[high]).append(hexChars[low]);
	    }

	    return buffer.toString();
	} catch (CertificateEncodingException e) {
	    return e.getMessage();

	} catch (NoSuchAlgorithmException e) {
	    return e.getMessage();
	}
    }
}
