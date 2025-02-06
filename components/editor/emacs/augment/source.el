;;; Path to Emacs C Sources.
(when (string-match (regexp-quote "COMPONENT_VERSION") emacs-version)
  (setq find-function-C-source-directory
        "/usr/share/emacs/COMPONENT_VERSION/src"))
