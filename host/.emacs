(package-initialize)

(setq inhibit-splash-screen t)
(menu-bar-mode 0)
(tool-bar-mode 0)

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

;; RTags
(add-hook 'c-mode-hook 'rtags-start-process-unless-running)
(add-hook 'c++-mode-hook 'rtags-start-process-unless-running)
(defun rtags-goto-symbol ()
  (interactive)
  (deactivate-mark)
  (ring-insert find-tag-marker-ring (point-marker))
  (and (require 'rtags nil t)
       (rtags-find-symbol-at-point))
  )
(define-key global-map (kbd "M-.") (function rtags-goto-symbol))
(require 'flycheck-rtags)
(defun flycheck-rtags-setup ()
  (flycheck-select-checker 'rtags)
  (setq-local flycheck-highlighting-mode nil) ;; RTags creates more accurate overlays.
  (setq-local flycheck-check-syntax-automatically nil))
(add-hook 'c-mode-hook #'flycheck-rtags-setup)
(add-hook 'c++-mode-hook #'flycheck-rtags-setup)

;; Irony
(add-hook 'c++-mode-hook 'irony-mode)
(add-hook 'c-mode-hook 'irony-mode)
(add-hook 'c++-mode-hook 'flycheck-mode)
(add-hook 'c-mode-hook 'flycheck-mode)
(add-hook 'irony-mode-hook 'irony-cdb-autosetup-compile-options)
(eval-after-load 'company
  '(add-to-list 'company-backends 'company-irony))
(add-hook 'irony-mode-hook #'irony-eldoc)

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
(global-set-key "\C-s" 'swiper)
(global-set-key [f5] 'rgrep)
(global-set-key [f6] 'find-name-dired)
(global-set-key [f7] 'compile)
(global-set-key [f8] 'recompile)
(global-set-key [f9] 'previous-error)
(global-set-key [f10] 'next-error)
(global-set-key [f11] 'imenu)
(global-set-key [f12] 'kill-this-buffer)

(ivy-mode 1)
(setq ivy-use-virtual-buffers t)
(setq enable-recursive-minibuffers t)
(global-set-key "\C-s" 'swiper)
(global-set-key (kbd "C-c C-r") 'ivy-resume)
(global-set-key (kbd "<f6>") 'ivy-resume)
(global-set-key (kbd "M-x") 'counsel-M-x)
(global-set-key (kbd "C-x C-f") 'counsel-find-file)
(global-set-key (kbd "<f1> f") 'counsel-describe-function)
(global-set-key (kbd "<f1> v") 'counsel-describe-variable)
(global-set-key (kbd "<f1> l") 'counsel-find-library)
(global-set-key (kbd "<f2> i") 'counsel-info-lookup-symbol)
(global-set-key (kbd "<f2> u") 'counsel-unicode-char)
(global-set-key (kbd "C-c g") 'counsel-git)
(global-set-key (kbd "C-c j") 'counsel-git-grep)
(global-set-key (kbd "C-c k") 'counsel-ag)
(global-set-key (kbd "C-x l") 'counsel-locate)
(global-set-key (kbd "C-S-o") 'counsel-rhythmbox)
(define-key minibuffer-local-map (kbd "C-r") 'counsel-minibuffer-history)(counsel-mode 1)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages
   (quote
    (flycheck-rtags rtags swiper counsel ivy irony-eldoc flycheck flycheck-irony company-irony irony elpy smex company web-mode magit zenburn-theme smart-tabs-mode glsl-mode)))
 '(rtags-periodic-reparse-timeout 1.0))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
