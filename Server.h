#pragma once

//テストシーンを管理するクラス
class Server
{
private:
	struct TestStruct {
		Transform trans;
	};
public:
	int InitWinSock(int ret);
	int CriateListenSock(int listen);
	int CriateSocket(int sock, int listen);
	bool Recv(int sock, struct TestStruct* value);
	bool Send(int sock, struct TestStruct value);
	void SendRecv(int ret, int sock, struct Trans* pos_);

	int Shutdown(int sock, int listen, int ret);
};