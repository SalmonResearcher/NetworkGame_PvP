// ヘッダ・ライブラリ
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

// ポート番号
const unsigned short SERVERPORT = 8888;
// 送受信するメッセージの最大値
const unsigned int MESSAGELENGTH = 1024;

int main()
{
	std::cout << "Chat Server" << std::endl;

	// WinSock初期化
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		std::cout << "Error: WSAStartup ( ErrorCode:" << ret << " )" << std::endl;
		return 1;
	}
	std::cout << "Success: WSAStartup" << std::endl;

	// リスンソケットの作成
	int listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, 0);	// 0で自動設定
	// リスンソケット作成失敗
	if (listenSock < 0)
	{
		// エラーコードを出力
		std::cout << "Error: socket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
		// 終了
		return 1;
	}
	std::cout << "Success: socket()" << std::endl;

	// bind
	struct sockaddr_in bindAddr;	// bind用のソケットアドレス情報
	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_port = htons(SERVERPORT);
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// ソケットアドレス情報設定	※固定のポート番号設定
	if (bind(listenSock, (struct sockaddr*)&bindAddr, sizeof(bindAddr)) != 0)
	{
		// エラーコードを出力
		std::cout << "Error: bind( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
		// 終了
		return 1;
	}
	std::cout << "Success: bind()" << std::endl;

	// リスン状態に設定	キューのサイズ:1
	if (listen(listenSock, 1) != 0)
	{
		// エラーコードを出力
		std::cout << "Error: listen( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
		// 終了
		return 1;
	}
	std::cout << "Success: listen()" << std::endl;

	std::cout << "---wait connect---" << std::endl;

	// 通信用ソケット ( クライアントのソケットとこのソケット間にコネクションが確立 )
	int sock;


	struct sockaddr_in clientAddr;		// 接続要求をしてきたクライアントのソケットアドレス情報格納領域
	int addrlen = sizeof(clientAddr);	// clientAddrのサイズ

	// クライアントからのconnect()を受けて、コネクション確立済みのソケット作成
	sock = accept(listenSock, (struct sockaddr*)&clientAddr, &addrlen);
	if (sock < 0)
	{
		// エラーコードを出力
		std::cout << "Error: accept( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
		// 終了
		return 1;
	}
	std::cout << "Success: accept() " << std::endl;


	// 送受信部
	while (true)
	{
		char buff[MESSAGELENGTH];	// 送受信メッセージの格納領域

		std::cout << "---wait message---" << std::endl;
		// クライアントからのメッセージ受信
		ret = recv(sock, buff, sizeof(buff) - 1, 0);
		if (ret < 0)
		{
			// エラーコードを出力
			std::cout << "Error: recv( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
			// ぬける
			break;
		}
		// 終端記号の追加
		buff[ret] = '\0';

		// 出力
		std::cout << "Receive message : " << buff << std::endl;


		// 送信メッセージの入力
		std::cout << "Input message:";
		std::cin >> buff;

		// 送信
		ret = send(sock, buff, strlen(buff), 0);
		if (ret != strlen(buff))
		{
			// エラーコードを出力
			std::cout << "Error: recv( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
			// ぬける
			break;
		}
	}

	// 送受信ともに切断
	// shutdown(sock, 0x02);
	if (shutdown(sock, SD_BOTH) != 0)
	{
		// エラーコードを出力
		std::cout << "Error: shutdown( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
	}
	std::cout << "Success: shutdown() " << std::endl;


	// ソケットの破棄
	if (closesocket(sock) != 0)
	{
		// エラーコードを出力
		std::cout << "Error: closesocket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
	}
	std::cout << "Success: closesocket() " << std::endl;

	if (closesocket(listenSock) != 0)
	{
		// エラーコードを出力
		std::cout << "Error: closesocket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
	}
	std::cout << "Success: closesocket() " << std::endl;

	// WinSock終了処理
	if (WSACleanup() != 0)
	{
		std::cout << "Error: WSACleanup ( ErrorCode:" << ret << " )" << std::endl;
	}
	std::cout << "Success: WSACleanup" << std::endl;




	return 0;
}

