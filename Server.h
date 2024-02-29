#pragma once
#include "IPlayer.h"


//テストシーンを管理するクラス
class Server
{
private:
	int playerID_ = 0;
public:
	int InitWinSock();
	int UDPSock();
	int Bind(int sock);
	bool Recv(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2);
	bool Send(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2);
	bool Update();
	//bool Recv(int sock, IPlayer::SPlayerComp* value);
	//bool Send(int sock, IPlayer::SPlayerComp* value);
};