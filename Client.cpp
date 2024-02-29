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

/// <summary>
/// ��̍\���̂��T�[�o�[�ɑ���܂�
/// </summary>
/// <param name="sock">�\�P�b�g</param>
/// <param name="value1">�R���|�[�l���g�P</param>
/// <param name="value2">�R���|�[�l���g�Q</param>
/// <returns></returns>
bool Client::Recv(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2)
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

    // ��M�����f�[�^�������Ŏw�肳�ꂽ�\���̂ɃR�s�[
    *value1 = recvValue1;
    *value2 = recvValue2;

    return true;
}

/// <summary>
/// �v���C���[�̃R���|�[�l���g���Q�󂯎��܂�
/// </summary>
/// <param name="sock">�\�P�b�g</param>
/// <param name="value1">�R���|�[�l���g�P</param>
/// <param name="value2">�R���|�[�l���g�Q</param>
/// <returns></returns>
bool Client::Send(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2)
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