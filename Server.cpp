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
    return ret;
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

bool Server::Recv(int sock, IPlayer::SPlayerComp* value)
{
    //IPlayer::DATA recvValue;
    IPlayer::SPlayerComp recvValue[2];	//��M�f�[�^�̊i�[�̈�...�l�b�g���[�N�o�C�g�I�[�_�[���
    int ret;		//���ۂ̔���p

    //��M
    ret = recv(sock, (char*)&recvValue, sizeof(recvValue), 0);

    //���s
    if (ret != sizeof(recvValue))
    {
        //����ꂽ���A�f�[�^���Ȃ�������
        if (WSAGetLastError() == WSAEWOULDBLOCK)
        {
            Debug::Log("Recv EMPTY Data!", true);
            return true;
        }
        //�����������������Ȃ�������
        else
        {
            Debug::Log("Error : Recv!", true);
            return false;
        }
    }

    int size = sizeof(recvValue);
    char* buff = new char[size];

    //
    for()
    {
        for(int l = 0; l < size; l++)
        {
            buff[l] = ;
        }
    }

        //����ꂽ���A�f�[�^�������Ă����鐬�����̏���
        

        //value->posX = ntohl(recvValue.posX);        //�o�C�g�I�[�_�[�ϊ�
        //value->posY = ntohl(recvValue.posY);        //�o�C�g�I�[�_�[�ϊ�
        //value->posZ = ntohl(recvValue.posZ);        //�o�C�g�I�[�_�[�ϊ�
        //
        //value->rotateY = ntohl(recvValue.rotateY);  //�o�C�g�I�[�_�[�ϊ�
        //value->attack = ntohl(recvValue.attack);    //�o�C�g�I�[�_�[�ϊ�
        return true;
}

bool Server::Send(int sock, IPlayer::DATA* value)
{
    IPlayer::DATA sendValue;

    //�o�C�g�I�[�_�[�ϊ�
    sendValue.posX = htonl(value->posX);
    sendValue.posY = htonl(value->posY);
    sendValue.posZ = htonl(value->posZ);

    sendValue.rotateY = htonl(value->rotateY);
    sendValue.attack = htonl(value->attack);
    
    int ret;
    ret = send(sock, (char*)&sendValue, sizeof(sendValue), 0);
    if (ret != 0)
    {
        OutputDebugString("Error : Send\n");
        return false;
    }
    return 1;
}
