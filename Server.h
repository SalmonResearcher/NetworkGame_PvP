#pragma once
#include "IPlayer.h"


//テストシーンを管理するクラス
class Server :IPlayer
{
private:

public:
	int InitWinSock();
	int UDPSock();
	int Bind(int sock);
	bool Recv(int sock, DATA* value);
	bool Send(int sock, DATA* value);
};