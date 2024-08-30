
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#include <chrono>
#pragma warning(disable: 4996)
using namespace std;


bool is_number(const string& s) 
{
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0)
    {
        cout << "error#1" << endl;
        exit(1);
    }
    SOCKADDR_IN addr;

    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8888);
    addr.sin_family = AF_INET;

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
    {
        cout << "ERROR" << endl;

        return 1;
    }
    cout << "Connected!" << endl;
    while (true) {
        char msg_get[256];
        memset(msg_get, 0, sizeof(msg_get));
        recv(Connection, msg_get, sizeof(msg_get), NULL);

    
        string str_msg;
        for (char c : msg_get)
        {
            if (c != '\0')
            {
                str_msg.push_back(c);
            }
        }

        if (str_msg.size() > 2 && str_msg.size() % 32 == 0) {
            cout << "Data: " << str_msg << endl;
            break;
        }
        else
        {
            cout << "Error: incorrect data" << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
        

    }
    
    closesocket(Connection);
    WSACleanup();

    return 0;
} 

