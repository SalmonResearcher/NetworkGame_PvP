#pragma once

class IPlayer;

//テストシーンを管理するクラス
class ClientPlayer
{
private:
	uint8_t ID = 0;

public:
	int WSASetup();
	int CreateSocket();
	int ConnectToServer(int sock);
	int SetSocketNonBlocking(int sock);
	void SendMessage(int sock);
	void ReceiveMessage(int sock);
	void CleanUp(int sock);
};