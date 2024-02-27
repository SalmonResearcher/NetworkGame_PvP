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


    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
    {
        std::cout << "Error: InitWinSock ( ErrorCode:" << ret << " )" << std::endl;
        return 1;	// ���[���I
    }
    std::cout << "Success: InitWinSock" << std::endl;


    // UDP�\�P�b�g�̍쐬
    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cout << "Error: socket ( ErrorCode:" << WSAGetLastError() << " )" << std::endl;
        return 1;	// ���[���I
    }
    std::cout << "Success: socket" << std::endl;


    // �Œ�A�h���X�ɂ��邽�߂Ƀ\�P�b�g�A�h���X���̊��蓖��
    struct sockaddr_in bindAddr;
    memset(&bindAddr, 0, sizeof(bindAddr));
    bindAddr.sin_family = AF_INET;
    bindAddr.sin_port = htons(SERVERPORT);
    bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr*)&bindAddr, sizeof(bindAddr)) < 0)
    {
        std::cout << "Error: bind ( ErrorCode:" << WSAGetLastError() << " )" << std::endl;
        return 1;
    }
    std::cout << "Success: bind" << std::endl;


    while (true)
    {
        char buff[MESSAGELENGTH];			// ����M���b�Z�[�W�̊i�[�̈�
        struct sockaddr_in fromAddr;		// ���M���A�h���X�̊i�[�̈�
        int fromlen = sizeof(fromAddr);		// fromAddr�̃T�C�Y

        // ��M�҂�
        std::cout << "wait..." << std::endl;

        // ��M	\0�͑����Ă��Ȃ��o�[�W����
        ret = recvfrom(sock, buff, sizeof(buff) - 1, 0, (struct sockaddr*)&fromAddr, &fromlen);
        if (ret < 0)
        {
            std::cout << "Error: recvfrom ( ErrorCode:" << WSAGetLastError() << " )" << std::endl;
            return 1;
        }
        buff[ret] = '\0';	// �I�[�L���ǉ�
        std::cout << "Receive message : " << buff << std::endl;

        // ���M�p���b�Z�[�W�̓���
        std::cout << "Input message : ";
        std::cin >> buff;

        // ���M�I
        ret = sendto(sock, buff, strlen(buff), 0, (struct sockaddr*)&fromAddr, fromlen);
        if (ret != strlen(buff))
        {
            std::cout << "Error: sendto ( ErrorCode:" << WSAGetLastError() << " )" << std::endl;
            return 1;
        }
    }

    return 0;
}

/*//�C���N���[�h���C�u����
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Server.h"
#include "IPlayer.h"

#pragma comment( lib, "ws2_32.lib" )

// �|�[�g�ԍ�
const unsigned short SERVERPORT = 8888;
// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGELENGTH = 1024;


int Server::InitWinSock(){
    // WinSock������
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
    {
        //WSADATA�Z�b�g�A�b�v�@���s�I
        return 1;
    }
    //WSADATA�̃Z�b�g�A�b�v����
    return ret;
    }

int Server::CriateListenSock() {
    // ���X���\�P�b�g�̍쐬
    int listenSock;
    listenSock = socket(AF_INET, SOCK_STREAM, 0);	// 0�Ŏ����ݒ�
    // ���X���\�P�b�g�쐬���s
    if (listenSock < 0)
    {
        // �G���[�R�[�h���o��
        //std::cout << "Error: socket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // �I��
        return 1;
    }
    //�\�P�b�g�̍쐬����

    struct sockaddr_in bindAddr;	// bind�p�̃\�P�b�g�A�h���X���
    memset(&bindAddr, 0, sizeof(bindAddr));
    bindAddr.sin_family = AF_INET;
    bindAddr.sin_port = htons(SERVERPORT);
    bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // �\�P�b�g�A�h���X���ݒ�	���Œ�̃|�[�g�ԍ��ݒ�
    if (bind(listenSock, (struct sockaddr*)&bindAddr, sizeof(bindAddr)) != 0)
    {
        //�o�C���h���s
        // �I��
        return 1;
    }

    //�o�C���h����

    // ���X����Ԃɐݒ�	�L���[�̃T�C�Y:1
    if ((listenSock, 1) != 0)
    {
        // �G���[�R�[�h���o��
        //std::cout << "Error: listen( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // �I��
        return 1;
    }
    //���X���\�P�b�gOK
    //������̐ڑ��҂�

}

int Server::CriateSocket(int listen) {
    struct sockaddr_in clientAddr;		// �ڑ��v�������Ă����N���C�A���g�̃\�P�b�g�A�h���X���i�[�̈�
    int addrlen = sizeof(clientAddr);	// clientAddr�̃T�C�Y

    // �N���C�A���g�����connect()���󂯂āA�R�l�N�V�����m���ς݂̃\�P�b�g�쐬

    int sock = accept(listen, (struct sockaddr*)&clientAddr, &addrlen);
    if (sock < 0)
    {
        // �G���[�R�[�h���o��
        //std::cout << "Error: accept( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // �I��
        return 1;
    }
    //std::cout << "Success: accept() " << std::endl;

}

bool Recv(int sock, struct IPlayer* playerID)
{
    IPlayer* recvplayerID = new IPlayer;	// ��M�f�[�^�̊i�[�̈�...�l�b�g���[�N�o�C�g�I�[�_�[���
    int ret;		// ���ۂ̔���p
    // ��M
    ret = recv(sock, (char*)&recvplayerID, sizeof(recvplayerID), 0);
    // ���s
    if (ret != sizeof(recvplayerID))
    {
        return false;
    }

    // �������̏���
    recvplayerID->comp.pos.x = ntohl(playerID->comp.pos.x);
    recvplayerID->comp.pos.y = ntohl(playerID->comp.pos.y);
    recvplayerID->comp.pos.z = ntohl(playerID->comp.pos.z);

    return true;
}

bool Server::Send(int sock, IPlayer* playerID)
{
    struct IPlayer sendplayerID;	// ���M�f�[�^ ... �l�b�g���[�N�o�C�g�I�[�_�[�ɕϊ���̒l���i�[

    // ���M
    int ret = send(sock, (char*)&sendplayerID, sizeof(sendplayerID), 0);
    // ���s
    if (ret != sizeof(sendplayerID))
    {
        return false;
    }

    // ����
    return true;
}

int Server::Shutdown(int sock, int listen,int ret){
    // ����M�Ƃ��ɐؒf
    // shutdown(sock, 0x02);
    if (shutdown(sock, SD_BOTH) != 0)
    {
        // �G���[�R�[�h���o��
        //std::cout << "Error: shutdown( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
    }
    //std::cout << "Success: shutdown() " << std::endl;


    // �\�P�b�g�̔j��
    if (closesocket(sock) != 0)
    {
        // �G���[�R�[�h���o��
        //std::cout << "Error: closesocket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
    }
    //std::cout << "Success: closesocket() " << std::endl;

    if (closesocket(listen) != 0)
    {
        // �G���[�R�[�h���o��
        //std::cout << "Error: closesocket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
    }
    //std::cout << "Success: closesocket() " << std::endl;

    // WinSock�I������
    if (WSACleanup() != 0)
    {
        //std::cout << "Error: WSACleanup ( ErrorCode:" << ret << " )" << std::endl;
    }
    //std::cout << "Success: WSACleanup" << std::endl;




    return 0;
}*/