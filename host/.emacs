;; My own little Emacs manual:
;; - Show white spaces: M-x whitespace-mode
;; - List packages: M-x list-packages
;; - Display variable value. Example: C-h v package-archives
;;
;; Search and replace in multiple files
;; http://stackoverflow.com/questions/270930/using-emacs-to-recursively-find-and-replace-in-text-files-not-already-open
;; 1. M-x find-name-dired: you will be prompted for a root directory and a filename pattern.
;; 2. Press t to "toggle mark" for all files found.
;; 3. Press Q for "Query-Replace in Files...": you will be prompted for query/substitution regexps.
;; 4. Proceed as with query-replace-regexp: SPACE to replace and move to next match, n to skip a match, etc.

(setq inhibit-splash-screen t)

;; Avoid magit warning at every start
(setq magit-last-seen-setup-instructions "1.4.0")
(setq magit-push-always-verify nil)

;; Load theme
(defun theme-init ()
  (load-theme 'zenburn t)
)

(add-hook 'after-init-hook 'theme-init)

;; Configure font
(set-face-attribute 'default (selected-frame) :height 100)

;; Display columns
(column-number-mode)

;; Better c-style
(setq c-default-style "linux")

;; Choose package sources
(setq package-archives '(("gnu" . "http://elpa.gnu.org/packages/")
                         ("melpa" . "http://melpa.milkbox.net/packages/")))

;; Smart tabs
(add-hook 'c-mode-common-hook (lambda() (smart-tabs-insinuate 'c 'c++)))

;; IPython
(setq python-shell-interpreter "ipython3")

;; Keyboard shorcuts
(global-set-key [f1] '(lambda () (interactive) (ansi-term "/bin/bash")))
(global-set-key [f2] 'run-python)
(global-set-key [f4] 'tuareg-run-ocaml)
(global-set-key [f5] 'gdb)
(global-set-key [f6] 'gdb-many-windows)
(global-set-key [f7] 'compile)
(global-set-key [f8] 'recompile)
(global-set-key [f9] 'next-error)
(global-set-key [f10] 'magit-status)
(global-set-key [f12] 'kill-this-buffer)

;; GDB command
(setq gud-gdb-command-name "arm-none-eabi-gdb -i=mi")

;; Enable various programming language support
(add-hook 'c-mode-common-hook
	  (lambda ()
	    (when (derived-mode-p 'c-mode 'c++-mode)
	      (ggtags-mode 1))))
(add-hook 'asm-mode-hook
	  (lambda ()
	    (ggtags-mode 1)))

;; Org mode
(setq org-html-doctype "html5")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; HACK BEGIN
;; This hack fixes indentation for C++11's "enum class" in Emacs.
;; http://stackoverflow.com/questions/6497374/emacs-cc-mode-indentation-problem-with-c0x-enum-class/6550361#6550361

(defun inside-class-enum-p (pos)
  "Checks if POS is within the braces of a C++ \"enum class\"."
  (ignore-errors
    (save-excursion
      (goto-char pos)
      (up-list -1)
      (backward-sexp 1)
      (looking-back "enum[ \t]+class[ \t]+[^}]*"))))
 
(defun align-enum-class (langelem)
  (if (inside-class-enum-p (c-langelem-pos langelem))
      0
    (c-lineup-topmost-intro-cont langelem)))
 
(defun align-enum-class-closing-brace (langelem)
  (if (inside-class-enum-p (c-langelem-pos langelem))
      '-
    '+))
 
(defun fix-enum-class ()
  "Setup `c++-mode' to better handle \"class enum\"."
  (add-to-list 'c-offsets-alist '(topmost-intro-cont . align-enum-class))
  (add-to-list 'c-offsets-alist
	       '(statement-cont . align-enum-class-closing-brace)))
 
(add-hook 'c++-mode-hook 'fix-enum-class)

;;
;; HACK END
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
