#pragma once

class IPlayer;

//テストシーンを管理するクラス
class Server
{
private:
	uint8_t ID = 0;

public:
	int InitWinSock();
	int CriateListenSock();
	int CriateSocket(int listen);
	bool Recv(int sock, IPlayer* playerID);
	bool Send(int sock, IPlayer* playerID);
	int Shutdown(int sock, int listen, int ret);
};