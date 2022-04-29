#include <stdio.h>
#include <WinSock2.h>
#include <cstring>
#include <string>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#pragma warning(disable:4700)

int main(int argc, char *argv[]) {

	char* target_ip = argv[1];
	unsigned short target_port = 0;
	for (int i = 0; argv[2][i]; i++) {
		target_port = target_port * 10 + argv[2][i] - '0';
	}
	
	printf("%s %hu\n", target_ip, target_port);
	
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);


	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr(target_ip);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(target_port);

	SOCKET client_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_TCP);

	int ret = connect(client_sock, (sockaddr*)&addr, sizeof(addr));
	if (ret <= 0) {
		printf("Connection fail!");
		ret = WSAGetLastError();
		return 0;
	}


	char buf[10];
	while (1) {
		fgets(buf, sizeof(buf), stdin);
		printf("%s", buf);
		if (strcmp(buf, "end")) return 0;
	}
	


}