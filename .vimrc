""" MAPPINGS
inoremap jk <ESC>
inoremap JK <ESC>
inoremap {<CR> {<CR>x<C-O>o}<ESC>kwxA
inoremap <C-A> <ESC>ggVG

noremap <C-C> "+y
noremap EE ZZ
noremap EQ ZQ
nnoremap <C-0> :set hlsearch!<CR>
nnoremap <C-J> gT
nnoremap <C-K> gt
nnoremap <C-I> :NERDTreeToggle<CR>
nnoremap <C-A> ggVG

autocmd filetype cpp nnoremap <F5> :w <bar> !g++ % -o %:r && ./%:r < ./in.txt <CR>
autocmd filetype cpp nnoremap <F6> :w <bar> !g++ % -o %:r && ./%:r <CR>

""" SETS

let mapleader = "'"

set number
set relativenumber
set noswapfile
set hlsearch
set ignorecase
set incsearch
set showcmd

set tabstop=8 softtabstop=0 expandtab shiftwidth=4 smarttab autoindent

execute pathogen#infect()
filetype plugin indent on

""" NERDTree

"autocmd VimEnter * NERDTree

""" SYNSTATIC

set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_wq = 0

""" VIM COLORS

syntax on
syntax enable
set t_Co=256
let g:solarized_termcolors=256
set background=dark
colorscheme solarized
