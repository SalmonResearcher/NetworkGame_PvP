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

/// <summary>
/// 二つの構造体をサーバーに送ります
/// </summary>
/// <param name="sock">ソケット</param>
/// <param name="value1">コンポーネント１</param>
/// <param name="value2">コンポーネント２</param>
/// <returns></returns>
bool Client::Recv(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2)
{
    IPlayer::SPlayerComp recvValue1, recvValue2;
    int ret;

    // データを1バイトずつ受信する
    char* buff1 = reinterpret_cast<char*>(&recvValue1);
    char* buff2 = reinterpret_cast<char*>(&recvValue2);

    // 1つ目のデータを受信
    for (int i = 0; i < sizeof(recvValue1); )
    {
        ret = recv(sock, &buff1[i], sizeof(recvValue1) - i, 0);

        if (ret <= 0)
        {
            Debug::Log("recv1でエラーまたは接続が閉じられました", true);
            return false;
        }

        i += ret;
    }


    // 2つ目のデータを受信
    for (int i = 0; i < sizeof(recvValue2); )
    {
        ret = recv(sock, &buff2[i], sizeof(recvValue2) - i, 0);

        if (ret <= 0)
        {
            Debug::Log("recv2でエラーまたは接続が閉じられました", true);
            return false;
        }

        i += ret;
    }

    // 受信したデータを引数で指定された構造体にコピー
    *value1 = recvValue1;
    *value2 = recvValue2;

    return true;
}

/// <summary>
/// プレイヤーのコンポーネントを２つ受け取ります
/// </summary>
/// <param name="sock">ソケット</param>
/// <param name="value1">コンポーネント１</param>
/// <param name="value2">コンポーネント２</param>
/// <returns></returns>
bool Client::Send(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2)
{
    int ret;
    // 1つ目のデータを送信
    ret = send(sock, reinterpret_cast<char*>(value1), sizeof(IPlayer::SPlayerComp), 0);
    if (ret != sizeof(IPlayer::SPlayerComp))
    {
        Debug::Log("Error: Send\n");
        return false;
    }

    // 2つ目のデータを送信
    ret = send(sock, reinterpret_cast<char*>(value2), sizeof(IPlayer::SPlayerComp), 0);
    if (ret != sizeof(IPlayer::SPlayerComp))
    {
        Debug::Log("Error: Send\n");
        return false;
    }
    return true;
}