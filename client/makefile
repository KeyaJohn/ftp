ftp_client:ftp_client.o  send_cmd_fork.o deal_str.o  recv_cmd_fork.o login.o
	gcc -o ftp_client -g ftp_client.o  send_cmd_fork.o deal_str.o  recv_cmd_fork.o login.o -lcrypt

ftp_client.o:ftp_client.c 
	gcc -c ftp_client.c 

send_cmd_fork.o:send_cmd_fork.c ftp.h deal_str.c recv_cmd_fork.c 
	gcc -c  send_cmd_fork.c ftp.h deal_str.c  recv_cmd_fork.c 

deal_str.o:deal_str.c ftp.h
	gcc -c deal_str.c ftp.h
login.o:login.c login.h
	gcc -c login.c login.h -lcrypt

recv_cmd_fork.o:recv_cmd_fork.c ftp.h
	gcc -c recv_cmd_fork.c ftp.h  
clean:
	rm -rf ftp_client login.o  send_cmd_fork.o ftp_client.o ftp.h.gch deal_str.o
