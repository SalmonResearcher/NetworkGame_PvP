#pragma once
class Client
{
public:
	int InitWinSock();
	int UDPSock();
	int NonBlocking(int sock);
	bool Recv(int sock, IPlayer::SPlayerComp* recvComp);
	bool Send(int sock, IPlayer::SPlayerComp* sendComp);
};

