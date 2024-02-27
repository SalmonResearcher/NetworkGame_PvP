#pragma once
#include "IPlayer.h"

//テストシーンを管理するクラス
class ClientPlayer
{
private:
	uint8_t ID = 0;
	//IPlayer* pIP = new IPlayer;

public:
	int WSASetup();
	int CreateSocket();
	int ConnectToServer(int sock);
	int SetSocketNonBlocking(int sock);
	void SendStruct(int sock);
	void ReceiveStruct(int sock);
	void CleanUp(int sock);
};