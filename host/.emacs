
;; Added by Package.el.  This must come before configurations of
;; installed packages.  Don't delete this line.  If you don't want it,
;; just comment it out by adding a semicolon to the start of the line.
;; You may delete these explanatory comments.
(package-initialize)

(setq inhibit-splash-screen t)

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

;; C-style comments in C++
(add-hook 'c++-mode-hook (lambda () (setq comment-start "/* " comment-end   " */")))

;; Org mode HTML5
(setq org-html-doctype "html5")
(setq org-html-html5-fancy t)

;; Minimal indentation for HTML and XML that require _many_ levels of
;; indentation.
(add-hook 'html-mode-hook (lambda() (setq tab-width 2)))
(add-hook 'nxml-mode-hook (lambda() (setq tab-width 2)))

;; Keyboard shorcuts
(global-set-key [f5] 'rgrep)
(global-set-key [f6] 'find-name-dired)
(global-set-key [f7] 'compile)
(global-set-key [f8] 'recompile)
(global-set-key [f9] 'next-error)
(global-set-key [f10] 'previous-error)
(global-set-key [f11] 'imenu)
(global-set-key [f12] 'kill-this-buffer)
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages (quote (magit zenburn-theme smart-tabs-mode glsl-mode))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
