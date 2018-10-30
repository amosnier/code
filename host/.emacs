
;; Added by Package.el.  This must come before configurations of
;; installed packages.  Don't delete this line.  If you don't want it,
;; just comment it out by adding a semicolon to the start of the line.
;; You may delete these explanatory comments.
(package-initialize)

(setq inhibit-splash-screen t)
(menu-bar-mode -1)
(tool-bar-mode -1)

;; Load theme
(add-hook 'after-init-hook (lambda() (load-theme 'zenburn t)))

;; Global company-mode
(add-hook 'after-init-hook 'global-company-mode)

;; Configure font
(set-face-attribute 'default nil :height 100)

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

;; No indent for name-spaces,
(add-hook 'c++-mode-hook (lambda () (c-set-offset 'innamespace [0])))

;; Various settings for text-mode. Inherited among others by org-mode
(defun configure-text-mode ()
  (turn-on-auto-fill)
  (flyspell-mode)
  )
(add-hook 'text-mode-hook 'configure-text-mode)

(defun english ()
  (interactive)
  (ispell-change-dictionary "en")
  )
(defun french ()
  (interactive)
  (ispell-change-dictionary "fr")
  )
(defun swedish ()
  (interactive)
  (ispell-change-dictionary "sv")
  )

;; Org mode HTML5
(setq org-html-doctype "html5")
(setq org-html-html5-fancy t)

;; Company mode in elisp mode
(add-hook 'emacs-lisp-mode-hook 'company-mode)
(add-hook 'emacs-lisp-mode-hook 'flyspell-prog-mode)

;; Elpy for Python IDE
(elpy-enable)

;; web-mode for HTML templates
(add-to-list 'auto-mode-alist '("\\.html\\'" . web-mode))
(defun configure-web-mode ()
  (setq web-mode-markup-indent-offset 2)
  (setq tab-width 2)
)
(add-hook 'web-mode-hook  'configure-web-mode)

;; Keyboard shortcuts
(global-set-key [f5] 'rgrep)
(global-set-key [f6] 'find-name-dired)
(global-set-key [f7] 'compile)
(global-set-key [f8] 'recompile)
(global-set-key [f9] 'previous-error)
(global-set-key [f10] 'next-error)
(global-set-key [f11] 'imenu)
(global-set-key [f12] 'kill-this-buffer)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages
   (quote
    (company web-mode docker-compose-mode dockerfile-mode magit zenburn-theme smart-tabs-mode glsl-mode))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )

