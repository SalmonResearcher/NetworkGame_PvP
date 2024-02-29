#pragma once
#include "IPlayer.h"

class Client
{
public:
	int InitWinSock();
	int UDPSock();
	int NonBlocking(int sock);
	bool Recv(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2);
	bool Send(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2);
	//bool Recv(int sock, IPlayer::DATA* recvComp);
	//bool Send(int sock, IPlayer::DATA* sendComp);
};

