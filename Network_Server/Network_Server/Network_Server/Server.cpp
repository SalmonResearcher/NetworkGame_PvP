// �w�b�_�E���C�u����
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

// �|�[�g�ԍ�
const unsigned short SERVERPORT = 8888;
// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGELENGTH = 1024;

int main()
{
	std::cout << "Chat Server" << std::endl;

	// WinSock������
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		std::cout << "Error: WSAStartup ( ErrorCode:" << ret << " )" << std::endl;
		return 1;
	}
	std::cout << "Success: WSAStartup" << std::endl;

	// ���X���\�P�b�g�̍쐬
	int listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, 0);	// 0�Ŏ����ݒ�
	// ���X���\�P�b�g�쐬���s
	if (listenSock < 0)
	{
		// �G���[�R�[�h���o��
		std::cout << "Error: socket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
		// �I��
		return 1;
	}
	std::cout << "Success: socket()" << std::endl;

	// bind
	struct sockaddr_in bindAddr;	// bind�p�̃\�P�b�g�A�h���X���
	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_port = htons(SERVERPORT);
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// �\�P�b�g�A�h���X���ݒ�	���Œ�̃|�[�g�ԍ��ݒ�
	if (bind(listenSock, (struct sockaddr*)&bindAddr, sizeof(bindAddr)) != 0)
	{
		// �G���[�R�[�h���o��
		std::cout << "Error: bind( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
		// �I��
		return 1;
	}
	std::cout << "Success: bind()" << std::endl;

	// ���X����Ԃɐݒ�	�L���[�̃T�C�Y:1
	if (listen(listenSock, 1) != 0)
	{
		// �G���[�R�[�h���o��
		std::cout << "Error: listen( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
		// �I��
		return 1;
	}
	std::cout << "Success: listen()" << std::endl;

	std::cout << "---wait connect---" << std::endl;

	// �ʐM�p�\�P�b�g ( �N���C�A���g�̃\�P�b�g�Ƃ��̃\�P�b�g�ԂɃR�l�N�V�������m�� )
	int sock;


	struct sockaddr_in clientAddr;		// �ڑ��v�������Ă����N���C�A���g�̃\�P�b�g�A�h���X���i�[�̈�
	int addrlen = sizeof(clientAddr);	// clientAddr�̃T�C�Y

	// �N���C�A���g�����connect()���󂯂āA�R�l�N�V�����m���ς݂̃\�P�b�g�쐬
	sock = accept(listenSock, (struct sockaddr*)&clientAddr, &addrlen);
	if (sock < 0)
	{
		// �G���[�R�[�h���o��
		std::cout << "Error: accept( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
		// �I��
		return 1;
	}
	std::cout << "Success: accept() " << std::endl;


	// ����M��
	while (true)
	{
		char buff[MESSAGELENGTH];	// ����M���b�Z�[�W�̊i�[�̈�

		std::cout << "---wait message---" << std::endl;
		// �N���C�A���g����̃��b�Z�[�W��M
		ret = recv(sock, buff, sizeof(buff) - 1, 0);
		if (ret < 0)
		{
			// �G���[�R�[�h���o��
			std::cout << "Error: recv( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
			// �ʂ���
			break;
		}
		// �I�[�L���̒ǉ�
		buff[ret] = '\0';

		// �o��
		std::cout << "Receive message : " << buff << std::endl;


		// ���M���b�Z�[�W�̓���
		std::cout << "Input message:";
		std::cin >> buff;

		// ���M
		ret = send(sock, buff, strlen(buff), 0);
		if (ret != strlen(buff))
		{
			// �G���[�R�[�h���o��
			std::cout << "Error: recv( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
			// �ʂ���
			break;
		}
	}

	// ����M�Ƃ��ɐؒf
	// shutdown(sock, 0x02);
	if (shutdown(sock, SD_BOTH) != 0)
	{
		// �G���[�R�[�h���o��
		std::cout << "Error: shutdown( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
	}
	std::cout << "Success: shutdown() " << std::endl;


	// �\�P�b�g�̔j��
	if (closesocket(sock) != 0)
	{
		// �G���[�R�[�h���o��
		std::cout << "Error: closesocket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
	}
	std::cout << "Success: closesocket() " << std::endl;

	if (closesocket(listenSock) != 0)
	{
		// �G���[�R�[�h���o��
		std::cout << "Error: closesocket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
	}
	std::cout << "Success: closesocket() " << std::endl;

	// WinSock�I������
	if (WSACleanup() != 0)
	{
		std::cout << "Error: WSACleanup ( ErrorCode:" << ret << " )" << std::endl;
	}
	std::cout << "Success: WSACleanup" << std::endl;




	return 0;
}

