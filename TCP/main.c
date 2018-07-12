/*
    C socket server example
	*/
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

	// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
	// #pragma comment (lib, "Mswsock.lib")
int ttttmain(int argc, char *argv[])
{
	WSADATA wsaData;   // if this doesn't work
					   //WSAData wsaData; // then try this instead

					   // MAKEWORD(1,1) for Winsock 1.1, MAKEWORD(2,0) for Winsock 2.0:

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed.\n");
		exit(1);
	}
	
	//struct addrinfo *result = NULL, *ptr = NULL, hints;
	/*
	struct addrinfo {
	int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
	int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
	int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
	int              ai_protocol;  // use 0 for "any"
	size_t           ai_addrlen;   // size of ai_addr in bytes
	|--->struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
	|	char            *ai_canonname; // full canonical hostname
	|	struct addrinfo *ai_next;      // linked list, next node
	|};
	|
	|-->struct sockaddr {
	unsigned short    sa_family;    // address family, AF_xxx
	char              sa_data[14];  // 14 bytes of protocol address
	};

	// (IPv4 only--see struct sockaddr_in6 for IPv6)

	struct sockaddr_in {
	short int          sin_family;  // Address family, AF_INET
	unsigned short int sin_port;    // Port number
	struct in_addr     sin_addr;    // Internet address
	unsigned char      sin_zero[8]; // Same size as struct sockaddr
	};
	// (IPv4 only--see struct in6_addr for IPv6)

	// Internet address (a structure for historical reasons)
	struct in_addr {
	uint32_t s_addr; // that's a 32-bit int (4 bytes)
	};
	// (IPv6 only--see struct sockaddr_in and struct in_addr for IPv4)

	struct sockaddr_in6 {
	u_int16_t       sin6_family;   // address family, AF_INET6
	u_int16_t       sin6_port;     // port number, Network Byte Order
	u_int32_t       sin6_flowinfo; // IPv6 flow information
	struct in6_addr sin6_addr;     // IPv6 address
	u_int32_t       sin6_scope_id; // Scope ID
	};

	struct in6_addr {
	unsigned char   s6_addr[16];   // IPv6 address
	};

	// (IPv6 AND IPv4)
	struct sockaddr_storage {
	sa_family_t  ss_family;     // address family

	// all this is padding, implementation specific, ignore it:
	char      __ss_pad1[_SS_PAD1SIZE];
	int64_t   __ss_align;
	char      __ss_pad2[_SS_PAD2SIZE];
	};
	*/


	//****Convert IP addresses
	//convert string IP addresses to their binary representations
	//struct sockaddr_in sa; // IPv4
	//struct sockaddr_in6 sa6; // IPv6
	/*
	See, inet_pton() returns -1 on error, or 0 if the address is messed up. 
	So check to make sure the result is greater than 0 before using!
	*/
	///inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr)); // IPv4
	///inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6
	
																	// IPv4:
	//convert from binary to it in numbers-and-dots notation
	///char ip4[INET_ADDRSTRLEN];  // space to hold the IPv4 string
	///struct sockaddr_in sa;      // pretend this is loaded with something

	//inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);

	//printf("The IPv4 address is: %s\n", ip4);


	// IPv6:

	//char ip6[INET6_ADDRSTRLEN]; // space to hold the IPv6 string
	//struct sockaddr_in6 sa6;    // pretend this is loaded with something

	///inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);

	///printf("The address is: %s\n", ip6);

	//First of all, try to use getaddrinfo() to get all the struct sockaddr info, instead of packing the structures by hand. This will keep you IP version-agnostic, and will eliminate many of the subsequent steps.
	//getaddrinfo() IPv4 & IPv6 friendly

	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo;  // will point to the results

	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
	

	if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}

	// servinfo now points to a linked list of 1 or more struct addrinfos

	// ... do everything until you don't need servinfo anymore ....

	freeaddrinfo(servinfo); // free the linked-list


	return 0;
}