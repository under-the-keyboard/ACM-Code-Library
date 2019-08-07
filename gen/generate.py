import os

tex_head = open('head', 'r', encoding='utf-8').read()
tex_tail = open('tail', 'r', encoding='utf-8').read()
file = open('under_the_keyboard-code-library.tex', 'w', encoding='utf-8')

def gen(idx, dep):
    dirs = os.listdir(idx)
    dirs.sort(reverse=True)
    for dir in dirs:
        path = idx + '\\' + dir
        if dep == 0:
            if os.path.isfile(path) or dir == 'gen' or dir == '.git':
                continue
            str = '\\section{' + dir + '}\n'
            file.write(str)
            gen(path, dep + 1)
            str = '\\newpage\n'
            file.write(str)
        else:
            if os.path.isdir(path):
                str = '\\'
                for i in range(dep):
                    str = str + 'sub'
                str = str + 'section{' + dir + '}\n'
                file.write(str)
                gen(path, dep + 1)
            else:
                str = '\\'
                for i in range(dep):
                    str = str + 'sub'
                str = str + 'section{' + dir[:dir.rfind('.')] + '}\n'
                file.write(str)
                file.write('\\begin{lstlisting}\n')
                code = open(path, 'r', encoding='utf-8').read()
                file.write(code)
                file.write('\\end{lstlisting}\n')
    file.write('\n')

def work():
    idx = os.getcwd()
    idx = idx[:int(idx.rfind('\\'))]
    gen(idx, 0)

def run():
    os.system("xelatex -synctex=1 -interaction=nonstopmode under_the_keyboard-code-library.tex")
    os.system("xelatex -synctex=1 -interaction=nonstopmode under_the_keyboard-code-library.tex")
    os.system("del *.log *.gz *.aux *.toc *.tex")

def main():
    file.write(tex_head)
    work()
    file.write(tex_tail)
    file.close()
    run()

if __name__ == '__main__':
    main()