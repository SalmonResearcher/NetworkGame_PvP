#pragma once
#include "IPlayer.h"

//テストシーンを管理するクラス
class ClientPlayer
{
private:
	uint8_t ID = 0;
	struct IPlayer* pIPlayer = new IPlayer;

public:
	int WSASetup();
	int CreateSocket();
	int ConnectToServer(int sock);
	int SetSocketNonBlocking(int sock);
	void SendMessa(int sock);
	void ReceiveMessage(int sock);
	void CleanUp(int sock);
};