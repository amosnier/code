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

;; Keyboard shorcuts
(global-set-key [f5] 'rgrep)
(global-set-key [f7] 'compile)
(global-set-key [f8] 'recompile)
(global-set-key [f9] 'next-error)
(global-set-key [f10] 'previous-error)
(global-set-key [f12] 'kill-this-buffer)
