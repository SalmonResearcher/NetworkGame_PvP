#include "Client.h"
#include "IPlayer.h"

#include "Engine/Debug.h"

// �w�b�_�E���C�u����
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <DirectXMath.h>
#include <direct.h>

#pragma comment( lib, "ws2_32.lib" )

bool Send(int sock, IPlayer::SPlayerComp* value);
bool Recv(int sock, IPlayer::SPlayerComp* value);

// �|�[�g�ԍ�
const unsigned short SERVERPORT = 8888;
// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGELENGTH = 1024;


// 1�Awinsocket����
int Client::InitWinSock()
{
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		//�G���[�\��
		Debug::Log("Error: InitWinSock ( ErrorCode:");
		Debug::Log(WSAGetLastError());
		Debug::Log(")", true);
		return 1;	// �I������
	}
	Debug::Log("Success: InitWinSock",true);
	return ret;
}

// 2�AUDP�\�P�b�g�̍쐬
int Client::UDPSock()
{
	int sock;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		//�G���[�\��
		Debug::Log("Error: socket ( ErrorCode:");
		Debug::Log(WSAGetLastError());
		Debug::Log(")", true);
		return 1;	//�I��
	}
	Debug::Log("Success: socket", true);

	// ����ƂȂ�T�[�o�̃\�P�b�g�A�h���X���̊��蓖��
	struct sockaddr_in toAddr;
	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons(SERVERPORT);
	inet_pton(AF_INET, "127.0.0.1", &toAddr.sin_addr.s_addr);

	return sock;
}

// �\�P�b�gsock���m���u���b�L���O�\�P�b�g�ɂ���
int Client::NonBlocking(int sock)
{
	unsigned long cmdarg = 0x01;
	int ret = ioctlsocket(sock, FIONBIO, &cmdarg);

	if (ret == SOCKET_ERROR)
	{
		// �G���[����
		Debug::Log("Error: ioctlsocket(ErrorCode:");
		Debug::Log(WSAGetLastError());
		Debug::Log(")",true);
		return 1;
	}
	Debug::Log("Success: ioctlsocket()");

}

// struct IPlayer����M�A�o�C�g�I�[�_�[��ϊ�
//	����
//		sock  : ��M�Ɏg�p����\�P�b�g�̃\�P�b�g�f�B�X�N���v�^
//		value : ��M�f�[�^�̊i�[�̈�̐擪�A�h���X
//	�߂�l
//		���� : true
//		���s : false
bool Client::Recv(int sock, IPlayer::DATA* recvComp)
{
	IPlayer::DATA recvVal;	// ��M�f�[�^�̊i�[�̈�...�l�b�g���[�N�o�C�g�I�[�_�[���
	int ret;		// ���ۂ̔���p
	// ��M
	ret = recv(sock, (char*)&recvVal, sizeof(recvVal), 0);
	// ���s
	if (ret != sizeof(recvVal))
	{
		Debug::Log("------�N���C�A���g��M���s------", true);
		return false;
	}

	// �������̏���
	recvComp->posX = ntohl(recvVal.posX);								// int �o�C�g�I�[�_�[�ϊ�
	recvComp->posY = ntohl(recvVal.posY);								// int �o�C�g�I�[�_�[�ϊ�
	recvComp->posZ = ntohl(recvVal.posZ);								// int �o�C�g�I�[�_�[�ϊ�
	recvComp->rotateY = ntohl(recvVal.rotateY);								// int �o�C�g�I�[�_�[�ϊ�
	recvComp->attack = ntohl(recvVal.attack);								// int �o�C�g�I�[�_�[�ϊ�

	return true;
}

// unsigned int�̃f�[�^���o�C�g�I�[�_�[��ϊ����Ă��瑗�M
//	����
//		sock  : ���M�Ɏg�p����\�P�b�g�̃\�P�b�g�f�B�X�N���v�^
//		value : ���M�f�[�^
//	�߂�l
//		���� : true
//		���s : false
bool Client::Send(int sock, IPlayer::DATA* sendComp)
{
	IPlayer::DATA sendData;				// ���M�f�[�^ ... �l�b�g���[�N�o�C�g�I�[�_�[�ɕϊ���̒l���i�[
	sendData.posX = htonl(sendComp->posX);	//�o�C�g�I�[�_�[�ϊ�
	sendData.posY = htonl(sendComp->posY);	//�o�C�g�I�[�_�[�ϊ�
	sendData.posZ = htonl(sendComp->posZ);	//�o�C�g�I�[�_�[�ϊ�
	sendData.rotateY = htonl(sendComp->rotateY);	//�o�C�g�I�[�_�[�ϊ�
	sendData.attack = htonl(sendComp->attack);	//�o�C�g�I�[�_�[�ϊ�

	int ret;		// ���ۂ̔���p
	// ���M
	ret = send(sock, (char*)&sendComp, sizeof(sendComp), 0);
	// ���s
	if (ret != sizeof(sendComp))
	{
		OutputDebugString("���M���s\n");

		return false;
	}

	OutputDebugString("���M����\n");
		// ����
	return true;
}