#pragma once

class IPlayer;

//テストシーンを管理するクラス
class Server
{
private:
	IPlayer* pID = new IPlayer;
public:
	int InitWinSock(int ret);
	int CriateListenSock(int listen);
	int CriateSocket(int sock, int listen);
	bool Recv(int sock, struct value);
	bool Send(int sock, struct TestStruct value);
	int Shutdown(int sock, int listen, int ret);
};