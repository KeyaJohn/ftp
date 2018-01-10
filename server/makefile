ftp_server:ftp_server.o send_cmd_fork.o deal_str.o recv_cmd_fork.o
	gcc -o ftp_server -g ftp_server.o recv_cmd_fork.o send_cmd_fork.o deal_str.o

ftp_server.o:ftp_server.c 
	gcc -c ftp_server.c 

recv_cmd_fork.o:recv_cmd_fork.c ftp.h send_cmd_fork.c
	gcc -c  recv_cmd_fork.c  ftp.h send_cmd_fork.c 

send_cmd_fork.o:send_cmd_fork.c deal_str.c  ftp.h
	gcc -c  send_cmd_fork.c ftp.h deal_str.c

deal_str.o:deal_str.c ftp.h
	gcc -c deal_str.c ftp.h
clean:
	rm -rf ftp_server recv_cmd_fork.o send_cmd_fork.o ftp_server.o ftp.h.gch deal_str.o
