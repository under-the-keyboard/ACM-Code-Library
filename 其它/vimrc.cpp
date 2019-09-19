set nu sw=2 ts=2 et mouse=a cin
nmap<F9> :w <cr> :!g++ % -o %< -Wall -O2 <cr> :!./%< <cr>
