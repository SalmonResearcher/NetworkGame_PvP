#include "Server.h"
#include "IPlayer.h"
#include "Engine/Debug.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

// �|�[�g�ԍ�
const unsigned short SERVERPORT = 8888;
// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGELENGTH = 1024;


//1�CwinSock�쐬
int Server::InitWinSock()
{
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
    {
        Debug::Log("Error: InitWinSock ( ErrorCode:");
        Debug::Log(WSAGetLastError());
        Debug::Log(")", true);
        return 1;	// ���[���I
    }
    Debug::Log("Success: InitWinSock", true);
    return ret + playerID_;
    playerID_++;
}

//2�C���X���\�P�b�g�쐬
int Server::UDPSock()
{
    // UDP�\�P�b�g�̍쐬
    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        Debug::Log("Error: UDPSock ( ErrorCode:");
        Debug::Log(WSAGetLastError());
        Debug::Log(")", true);
        return 1;	// ���[���I
    }
    Debug::Log("Success: UDPSocket", true);
}

int Server::Bind(int sock)
{
    // �Œ�A�h���X�ɂ��邽�߂Ƀ\�P�b�g�A�h���X���̊��蓖��
    struct sockaddr_in bindAddr;
    memset(&bindAddr, 0, sizeof(bindAddr));
    bindAddr.sin_family = AF_INET;
    bindAddr.sin_port = htons(SERVERPORT);
    bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr*)&bindAddr, sizeof(bindAddr)) < 0)
    {
        Debug::Log("Error: bind ( ErrorCode:");
        Debug::Log(WSAGetLastError());
        Debug::Log(" )",true);
        return 1;
    }
    Debug::Log("Success: bind", true);
    // �\�P�b�gsock���m���u���b�L���O�\�P�b�g�ɂ���
        unsigned long cmdarg = 0x01;
    int ret = ioctlsocket(sock, FIONBIO, &cmdarg);
    if (ret == SOCKET_ERROR)
    {
        OutputDebugString("�m���u���b�L���O�\�P�b�g�����s\n");
        closesocket(sock);  // �\�P�b�g�����
        return false;
    }

    return true;

}

bool Server::Recv(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2)
{
    IPlayer::SPlayerComp recvValue1, recvValue2;
    int ret;

    // �f�[�^��1�o�C�g����M����
    char* buff1 = reinterpret_cast<char*>(&recvValue1);
    char* buff2 = reinterpret_cast<char*>(&recvValue2);

    // 1�ڂ̃f�[�^����M
    for (int i = 0; i < sizeof(recvValue1); )
    {
        ret = recv(sock, &buff1[i], sizeof(recvValue1) - i, 0);

        if (ret <= 0)
        {
            Debug::Log("recv1�ŃG���[�܂��͐ڑ��������܂���", true);
            return false;
        }

        i += ret;
    }

    // 2�ڂ̃f�[�^����M
    for (int i = 0; i < sizeof(recvValue2); )
    {
        ret = recv(sock, &buff2[i], sizeof(recvValue2) - i, 0);

        if (ret <= 0)
        {
            Debug::Log("recv2�ŃG���[�܂��͐ڑ��������܂���", true);
            return false;
        }

        i += ret;
    }

    //��΂�������Ȃ��Ղꂢ��[ID�ݒ�
    recvValue1.PID = 0;
    recvValue2.PID = 1;

    // ��M�����f�[�^�������Ŏw�肳�ꂽ�\���̂ɃR�s�[
    *value1 = recvValue1;
    *value2 = recvValue2;

    return true;
}

bool Server::Send(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2)
{
    int ret;

    // 1�ڂ̃f�[�^�𑗐M
    ret = send(sock, reinterpret_cast<char*>(value1), sizeof(IPlayer::SPlayerComp), 0);
    if (ret != sizeof(IPlayer::SPlayerComp))
    {
        Debug::Log("Error: Send\n");
        return false;
    }

    // 2�ڂ̃f�[�^�𑗐M
    ret = send(sock, reinterpret_cast<char*>(value2), sizeof(IPlayer::SPlayerComp), 0);
    if (ret != sizeof(IPlayer::SPlayerComp))
    {
        Debug::Log("Error: Send\n");
        return false;
    }

    return true;
}

