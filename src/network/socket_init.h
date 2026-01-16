#pragma once

//ifdef-->if defined  
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef SOCKET socket_t;
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    typedef int socket_t;
#endif

inline bool init_socket()
{
#ifdef _WIN32
    WSADATA wsa;
    //WSADATA ek structure (struct) hai jo Windows Socket (Winsock) system ki information rakhta hai.WSADATA = Winsock ka info-card
    return WSAStartup(MAKEWORD(2,2), &wsa) == 0;
#else
    return true;
#endif
}

inline void cleanup_socket()
{
#ifdef _WIN32
    WSACleanup();
#endif
}
//socket_t sock--> Ye ek variable hai jo ek open network connection ko represent karta hai.
inline void close_socket(socket_t sock)
{
#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif
}
