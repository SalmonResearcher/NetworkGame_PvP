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

bool Send(int sock, IPlayer::SPlayerComp* value);
bool Recv(int sock, IPlayer::SPlayerComp* value);

// ポート番号
const unsigned short SERVERPORT = 8888;
// 送受信するメッセージの最大値
const unsigned int MESSAGELENGTH = 1024;

int main()
{
	IPlayer::SPlayerComp* comp1;
	IPlayer::SPlayerComp* compO;
	int sock;

	InitWinSock();
	sock = UDPSock();
	NonBlocking(sock);
	// 宛先となるサーバのソケットアドレス情報の割り当て
	struct sockaddr_in toAddr;
	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons(SERVERPORT);
	inet_pton(AF_INET, "127.0.0.1", &toAddr.sin_addr.s_addr);

	Debug::Log("Success: connect()",true);

	while (true)
	{
		//送信
		Send(sock, comp1);

		// 受信
		Recv(sock, compO);
		std::cout << "受信相手の位置 = { " << compO->size.x << ", " << compO->size.y << ", " << compO->size.z << " }" << std::endl;

		comp1->size.x += 1;
	}

}

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
bool Client::Recv(int sock, IPlayer::SPlayerComp* recvComp)
{
	IPlayer::GPlayerComp recvVal;	// 受信データの格納領域...ネットワークバイトオーダー状態
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
	recvComp->size.x = ntohl(recvVal.size.x);								// int バイトオーダー変換
	recvComp->size.y = ntohl(recvVal.size.y);								// int バイトオーダー変換
	recvComp->size.y = ntohl(recvVal.size.z);								// int バイトオーダー変換

	return true;
}

// unsigned intのデータをバイトオーダーを変換してから送信
//	引数
//		sock  : 送信に使用するソケットのソケットディスクリプタ
//		value : 送信データ
//	戻り値
//		成功 : true
//		失敗 : false
bool Client::Send(int sock, IPlayer::SPlayerComp* sendComp)
{
	IPlayer::SPlayerComp sendData;				// 送信データ ... ネットワークバイトオーダーに変換後の値を格納
	sendData.size.x = htonl(sendComp->size.x);	// int バイトオーダー変換
	sendData.size.y = htonl(sendComp->size.y);	// int バイトオーダー変換
	sendData.size.z = htonl(sendComp->size.z);	// int バイトオーダー変換

	int ret;		// 成否の判定用
	// 送信
	ret = send(sock, (char*)&sendComp, sizeof(sendComp), 0);
	// 失敗
	if (ret != sizeof(sendComp))
	{
		std::cout << "------送信失敗------" << std::endl;

		return false;
	}

	std::cout << "------送信成功------" << std::endl;
	// 成功
	return true;
}