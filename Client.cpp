#include "Client.h"
#include "IPlayer.h"

#include "Engine/Debug.h"

// ヘッダ・ライブラリ
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <DirectXMath.h>
#include <direct.h>

#pragma comment( lib, "ws2_32.lib" )

// ポート番号
const unsigned short SERVERPORT = 8888;
// 送受信するメッセージの最大値
const unsigned int MESSAGELENGTH = 1024;


// 1、winsocket準備
int Client::InitWinSock()
{
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		//エラー表示
		Debug::Log("Error: InitWinSock ( ErrorCode:");
		Debug::Log(WSAGetLastError());
		Debug::Log(")", true);
		return 1;	// 終了処理
	}
	Debug::Log("Success: InitWinSock",true);
	return ret;
}

// 2、UDPソケットの作成
int Client::UDPSock()
{
	int sock;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		//エラー表示
		Debug::Log("Error: socket ( ErrorCode:");
		Debug::Log(WSAGetLastError());
		Debug::Log(")", true);
		return 1;	//終了
	}
	Debug::Log("Success: socket", true);

	// 宛先となるサーバのソケットアドレス情報の割り当て
	struct sockaddr_in toAddr;
	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons(SERVERPORT);
	inet_pton(AF_INET, "127.0.0.1", &toAddr.sin_addr.s_addr);

	return sock;
}

// ソケットsockをノンブロッキングソケットにする
int Client::NonBlocking(int sock)
{
	unsigned long cmdarg = 0x01;
	int ret = ioctlsocket(sock, FIONBIO, &cmdarg);

	if (ret == SOCKET_ERROR)
	{
		// エラー処理
		Debug::Log("Error: ioctlsocket(ErrorCode:");
		Debug::Log(WSAGetLastError());
		Debug::Log(")",true);
		return 1;
	}
	Debug::Log("Success: ioctlsocket()");

}

// struct IPlayerを受信、バイトオーダーを変換
//	引数
//		sock  : 受信に使用するソケットのソケットディスクリプタ
//		value : 受信データの格納領域の先頭アドレス
//	戻り値
//		成功 : true
//		失敗 : false
bool Client::Recv(int sock, IPlayer::DATA* recvComp)
{
	IPlayer::DATA recvVal;	// 受信データの格納領域...ネットワークバイトオーダー状態
	int ret;		// 成否の判定用
	// 受信
	ret = recv(sock, (char*)&recvVal, sizeof(recvVal), 0);
	// 失敗
	if (ret != sizeof(recvVal))
	{
		Debug::Log("------クライアント受信失敗------", true);
		return false;
	}

	// 成功時の処理
	recvComp->posX = ntohl(recvVal.posX);								// バイトオーダー変換
	recvComp->posY = ntohl(recvVal.posY);
	recvComp->posZ = ntohl(recvVal.posZ);
	recvComp->rotateY = ntohl(recvVal.rotateY);
	recvComp->attack = ntohl(recvVal.attack);

	return true;
}

// unsigned intのデータをバイトオーダーを変換してから送信
//	引数
//		sock  : 送信に使用するソケットのソケットディスクリプタ
//		value : 送信データ
//	戻り値
//		成功 : true
//		失敗 : false
bool Client::Send(int sock, IPlayer::DATA* sendComp)
{
	IPlayer::DATA sendData;				// 送信データ ... ネットワークバイトオーダーに変換後の値を格納

	sendData.posX = htonl(sendComp->posX);
	sendData.posY = htonl(sendComp->posY);
	sendData.posZ = htonl(sendComp->posZ);
	sendData.rotateY = htonl(sendComp->rotateY);
	sendData.attack = htonl(sendComp->attack);

	int ret;		// 成否の判定用
	// 送信
	ret = send(sock, (char*)&sendComp, sizeof(sendComp), 0);
	// 失敗
	if (ret != sizeof(sendComp))
	{
		OutputDebugString("送信失敗\n");

		return false;
	}

	OutputDebugString("送信成功\n");
		// 成功
	return true;
}