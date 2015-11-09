# Simple-RPC 
Remote Procedure Calls (RPC) are a linguistic approach based on a fundamental
concept, procedure call. RPC allows distributed programs to be written in the same
conventional style as for centralized computer systems. The idea is based on the
observation that in the client-server interaction, the client sends a request and then
blocks until the remote server sends a reply. This behavior is similar to the classical
interaction between main programs and procedures.

HOW TO RUN

1. git clone https://github.com/zzh730/Simple-RPC.git 
2. cd Simple-RPC
3. gcc -o compiler gen.c
4. ./compiler
5. make
6. ./server
7. ./directory
8. ./client localhost 8888
