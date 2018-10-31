(package-initialize)

(setq inhibit-splash-screen t)
(menu-bar-mode 0)
(tool-bar-mode 0)
(ido-mode 1)

;; Load theme
(add-hook 'after-init-hook (lambda() (load-theme 'zenburn t)))

;; Global company mode
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

;; Irony
(add-hook 'c++-mode-hook 'irony-mode)
(add-hook 'c-mode-hook 'irony-mode)
(add-hook 'irony-mode-hook 'irony-cdb-autosetup-compile-options)

;; Various settings for text-mode. Inherited among others by org-mode
(defun configure-text-mode ()
  (turn-on-auto-fill)
  (flyspell-mode)
  )
(add-hook 'text-mode-hook 'configure-text-mode)

(defun ispell-select-english ()
  (interactive)
  (ispell-change-dictionary "en")
  )
(defun ispell-select-french ()
  (interactive)
  (ispell-change-dictionary "fr")
  )
(defun ispell-select-swedish ()
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

;; web-mode for HTML
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
(global-set-key (kbd "M-x") 'smex)
(global-set-key (kbd "M-X") 'smex-major-mode-commands)
;; Old M-x.
(global-set-key (kbd "C-c C-c M-x") 'execute-extended-command)


(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages
   (quote
    (irony elpy smex company web-mode magit zenburn-theme smart-tabs-mode glsl-mode))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
