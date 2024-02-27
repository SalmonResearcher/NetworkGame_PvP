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

int main()
{
	IPlayer::SPlayerComp* comp1;
	IPlayer::SPlayerComp* compO;
	int sock;

	InitWinSock();
	sock = UDPSock();
	NonBlocking(sock);
	// ����ƂȂ�T�[�o�̃\�P�b�g�A�h���X���̊��蓖��
	struct sockaddr_in toAddr;
	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons(SERVERPORT);
	inet_pton(AF_INET, "127.0.0.1", &toAddr.sin_addr.s_addr);

	Debug::Log("Success: connect()",true);

	while (true)
	{
		//���M
		Send(sock, comp1);

		// ��M
		Recv(sock, compO);
		std::cout << "��M����̈ʒu = { " << compO->size.x << ", " << compO->size.y << ", " << compO->size.z << " }" << std::endl;

		comp1->size.x += 1;
	}

}

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
bool Client::Recv(int sock, IPlayer::SPlayerComp* recvComp)
{
	IPlayer::GPlayerComp recvVal;	// ��M�f�[�^�̊i�[�̈�...�l�b�g���[�N�o�C�g�I�[�_�[���
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
	recvComp->size.x = ntohl(recvVal.size.x);								// int �o�C�g�I�[�_�[�ϊ�
	recvComp->size.y = ntohl(recvVal.size.y);								// int �o�C�g�I�[�_�[�ϊ�
	recvComp->size.y = ntohl(recvVal.size.z);								// int �o�C�g�I�[�_�[�ϊ�

	return true;
}

// unsigned int�̃f�[�^���o�C�g�I�[�_�[��ϊ����Ă��瑗�M
//	����
//		sock  : ���M�Ɏg�p����\�P�b�g�̃\�P�b�g�f�B�X�N���v�^
//		value : ���M�f�[�^
//	�߂�l
//		���� : true
//		���s : false
bool Client::Send(int sock, IPlayer::SPlayerComp* sendComp)
{
	IPlayer::SPlayerComp sendData;				// ���M�f�[�^ ... �l�b�g���[�N�o�C�g�I�[�_�[�ɕϊ���̒l���i�[
	sendData.size.x = htonl(sendComp->size.x);	// int �o�C�g�I�[�_�[�ϊ�
	sendData.size.y = htonl(sendComp->size.y);	// int �o�C�g�I�[�_�[�ϊ�
	sendData.size.z = htonl(sendComp->size.z);	// int �o�C�g�I�[�_�[�ϊ�

	int ret;		// ���ۂ̔���p
	// ���M
	ret = send(sock, (char*)&sendComp, sizeof(sendComp), 0);
	// ���s
	if (ret != sizeof(sendComp))
	{
		std::cout << "------���M���s------" << std::endl;

		return false;
	}

	std::cout << "------���M����------" << std::endl;
	// ����
	return true;
}