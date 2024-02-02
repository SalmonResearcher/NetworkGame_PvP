//�C���N���[�h���C�u����
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Server.h"
#include "Engine/Text.h"
#include "IPlayer.h"

#pragma comment( lib, "ws2_32.lib" )

// �|�[�g�ԍ�
const unsigned short SERVERPORT = 8888;
// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGELENGTH = 1024;


int Server::InitWinSock(int _ret){
    // WinSock������
    WSADATA wsaData;
    _ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (_ret != 0)
    {
        //std::cout << "Error: WSAStartup ( ErrorCode:" << ret << " )" << std::endl;
        return 1;
    }
    //std::cout << "Success: WSAStartup" << std::endl;
    return _ret;
    }

int Server::CriateListenSock(int listen) {
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
    //std::cout << "Success: socket()" << std::endl;
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
        //std::cout << "Error: bind( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // �I��
        return 1;
    }

    //std::cout << "Success: bind()" << std::endl;

    // ���X����Ԃɐݒ�	�L���[�̃T�C�Y:1
    if ((listenSock, 1) != 0)
    {
        // �G���[�R�[�h���o��
        //std::cout << "Error: listen( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // �I��
        return 1;
    }
    //std::cout << "Success: listen()" << std::endl;
    //std::cout << "---wait connect---" << std::endl;
}

int Server::CriateSocket(int sock, int listen) {
    struct sockaddr_in clientAddr;		// �ڑ��v�������Ă����N���C�A���g�̃\�P�b�g�A�h���X���i�[�̈�
    int addrlen = sizeof(clientAddr);	// clientAddr�̃T�C�Y

    // �N���C�A���g�����connect()���󂯂āA�R�l�N�V�����m���ς݂̃\�P�b�g�쐬

    sock = accept(listen, (struct sockaddr*)&clientAddr, &addrlen);
    if (sock < 0)
    {
        // �G���[�R�[�h���o��
        //std::cout << "Error: accept( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // �I��
        return 1;
    }
    //std::cout << "Success: accept() " << std::endl;

}

bool Recv(int sock, struct TestStruct* value)
{
    struct TestStruct recvValue;	// ��M�f�[�^�̊i�[�̈�...�l�b�g���[�N�o�C�g�I�[�_�[���
    int ret;		// ���ۂ̔���p
    // ��M
    ret = recv(sock, (char*)&recvValue, sizeof(recvValue), 0);
    // ���s
    if (ret != sizeof(recvValue))
    {
        return false;
    }

    // �������̏���
    strcpy_s(value->name, sizeof(value->name), recvValue.name);	// ������̃R�s�[
    value->x = ntohl(recvValue.x);								// int �o�C�g�I�[�_�[�ϊ�
    value->y = ntohl(recvValue.y);								// int �o�C�g�I�[�_�[�ϊ�
    value->hp = ntohl(recvValue.hp);							// int �o�C�g�I�[�_�[�ϊ�
    return true;
}

bool Server::Send(int sock, TestStruct value)
{
    struct TestStruct sendValue;	// ���M�f�[�^ ... �l�b�g���[�N�o�C�g�I�[�_�[�ɕϊ���̒l���i�[
    strcpy_s(sendValue.name, sizeof(sendValue.name), value.name);	// ������̃R�s�[
    sendValue.x = htonl(value.position_.x);									// int �o�C�g�I�[�_�[�ϊ�
    sendValue.y = htonl(value.y);									// int �o�C�g�I�[�_�[�ϊ�
    sendValue.hp = htonl(value.hp);									// int �o�C�g�I�[�_�[�ϊ�

    int ret;		// ���ۂ̔���p
    // ���M
    ret = send(sock, (char*)&sendValue, sizeof(sendValue), 0);
    // ���s
    if (ret != sizeof(sendValue))
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
}