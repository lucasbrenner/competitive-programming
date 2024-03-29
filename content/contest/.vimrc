inoremap jk <ESC>
inoremap {<CR> {<CR>}<C-O>O

set number relativenumber noswapfile hlsearch ignorecase incsearch showcmd
set tabstop=8 softtabstop=0 expandtab shiftwidth=4 smarttab autoindent

autocmd filetype cpp nnoremap <F7> :w <bar> !g++ % -Wall -Wextra -Wshadow -Wconversion -Wlogical-op -Wshift-overflow=2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector -std=c++20 -o %:r && ./%:r <CR>
autocmd filetype cpp nnoremap <F8> :w <bar> !g++ % (flags) -o %:r && ./%:r < ./in.txt <CR>

syntax on
syntax enable
filetype plugin indent on

