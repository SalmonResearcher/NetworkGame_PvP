#pragma once

//�e�X�g�V�[�����Ǘ�����N���X
class Server
{
private:
	int InitWinSock(int ret);
	int CriateListenSock(int listen);
	int CriateSocket(int sock, int listen);
	bool Recv(int sock, struct PlayerStates* value)
	bool Send();
public:
};