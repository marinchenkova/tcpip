#include <sys/types.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include <conio.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")


int main() {
    struct sockaddr_in peer;
    int s ;
    int rc;
    char buf [ 1024 ];

    // Initialize Winsock.
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %ld\n", iResult);
        return 1;
    }

    peer.sin_family = AF_INET;
    peer.sin_port = htons( 7500 );
    peer.sin_addr.s_addr = inet_addr( "127.0.0.1" );

    s = socket ( AF_INET, SOCK_STREAM, 0 );
    if (s < 0) {
        perror( "Error calling socket" );
        exit ( 1 );
    }

    rc = connect( s, ( struct sockaddr * )&peer, sizeof( peer ) );
    if (rc) {
        perror( "Error calling connect" );
        exit( 1 );
    }


    while (true) {
        cin >> buf;

        if (buf[0] == '$') break;

        rc = send(s, buf, 5, 0 );
        if ( rc <= 0 ) {
            perror( "Error calling send" );
            exit ( 1 );
        }
    }

    exit( 0 );
}

