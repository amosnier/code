;; My own little Emacs manual:
;; - Show white spaces: M-x whitespace-mode
;; - List packages: M-x list-packages
;; - Display variable value. Example: C-h v package-archives

(setq inhibit-splash-screen t)

;; Load theme
(load-theme 'wombat)

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

;; Keyboard shorcuts
(global-set-key [f5] 'gdb)
(global-set-key [f6] 'gdb-many-windows)
(global-set-key [f7] 'compile)
(global-set-key [f8] 'recompile)
(global-set-key [f9] 'kill-this-buffer)
(global-set-key [f10] 'magit-status)

;; GDB command
(setq gud-gdb-command-name "arm-none-eabi-gdb -i=mi")

;; Enable ggtags
(add-hook 'c-mode-common-hook
	  (lambda ()
	    (when (derived-mode-p 'c-mode 'c++-mode)
	      (ggtags-mode 1))))
(add-hook 'asm-mode-hook
	  (lambda ()
	      (ggtags-mode 1)))

;; Enable company-mode
(add-hook 'after-init-hook 'global-company-mode)

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
