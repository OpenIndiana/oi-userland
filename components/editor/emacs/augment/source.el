;; -*- lexical-binding: nil -*-

;; load-path is not correctly set by build process. Thus, add default load-path entries.
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/vc"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/use-package"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/url"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/textmodes"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/progmodes"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/play"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/org"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/nxml"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/net"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/mh-e"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/mail"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/leim"))
;;(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/leim/quail"))
;;(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/leim/ja-dic"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/language"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/international"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/image"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/gnus"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/eshell"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/erc"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/emulation"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/emacs-lisp"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/cedet"))
;;(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/cedet/srecode"))
;;(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/cedet/semantic"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/calendar"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/calc"))
(add-to-list 'load-path (expand-file-name "/usr/share/emacs/31.1/lisp/obsolete"))

(set-variable 'find-program "/usr/gnu/bin/find")

(setopt Man-sed-command "/usr/gnu/bin/sed"
        insert-directory-program "/usr/gnu/bin/ls")

;;; Path to Emacs C Sources.
(when (string-match (regexp-quote "COMPONENT_VERSION") emacs-version)
  (setq find-function-C-source-directory
        "/usr/share/emacs/COMPONENT_VERSION/src"))
