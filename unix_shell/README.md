This project consists of designing a program to serve as a shell interface that accepts user commands
and then executes each command in a separate process. This implementation will support input and output
redirection, as well as pipes as a form of IPC between a pair of commands.

I'll call the shell 'lash' (LA-wrence SH-ell)

build: g++ -g -o out.exe main.c