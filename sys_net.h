/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
// server.h

#include "q_shared.h"

#ifndef __SYS_NET_H__
#define __SYS_NET_H__
/*
==============================================================

NET

==============================================================
*/

#define NET_ENABLEV4            0x01
#define NET_ENABLEV6            0x02
// if this flag is set, always attempt ipv6 connections instead of ipv4 if a v6 address is found.
#define NET_PRIOV6              0x04
// disables ipv6 multicast support if set.
#define NET_DISABLEMCAST        0x08
#define	PORT_ANY		-1

typedef enum {
	NA_BAD = 0,					// an address lookup failed
	NA_BOT = 0,
	NA_LOOPBACK = 2,
	NA_BROADCAST = 3,
	NA_IP = 4,
	NA_IP6 = 5,
	NA_TCP = 6,
	NA_TCP6 = 7,
	NA_MULTICAST6 = 8,
	NA_UNSPEC = 9,
	NA_DOWN = 10,
} netadrtype_t;

typedef enum {
	NS_CLIENT,
	NS_SERVER
} netsrc_t;

#define NET_ADDRSTRMAXLEN 48	// maximum length of an IPv6 address string including trailing '\0'

typedef struct {
	byte	type;
	byte	scope_id;
	unsigned short	port;
	short sock;		//Socket FD. 0 = any socket
        union{
	    byte	ip[4];
	    byte	ipx[10];
	    byte	ip6[16];
	};
}netadr_t;


void		NET_Init( void );
void		NET_Shutdown( void );
void		NET_Restart_f( void );
void		NET_Config( qboolean enableNetworking );
void		NET_FlushPacketQueue(void);
qboolean	NET_SendPacket (netsrc_t sock, int length, const void *data, netadr_t *to);
void		QDECL NET_OutOfBandPrint( netsrc_t net_socket, netadr_t *adr, const char *format, ...) __attribute__ ((format (printf, 3, 4)));
void		QDECL NET_OutOfBandData( netsrc_t sock, netadr_t *adr, byte *format, int len );
void		QDECL NET_PrintData( int *sock, const char *format, ... );
void		NET_SendData( int *sock, byte *data, int len );
void		NET_RegisterDefaultCommunicationSocket(netadr_t *adr);
netadr_t*	NET_GetDefaultCommunicationSocket();
qboolean	NET_CompareAdr (netadr_t *a, netadr_t *b);
qboolean	NET_CompareBaseAdrMask(netadr_t *a, netadr_t *b, int netmask);
qboolean	NET_CompareBaseAdr (netadr_t *a, netadr_t *b);
qboolean	NET_IsLocalAddress (netadr_t adr);
const char	*NET_AdrToString (netadr_t *a);
const char	*NET_AdrToStringShort (netadr_t *a);
const char	*NET_AdrToStringwPort (netadr_t *a);
netadr_t	*NET_SockToAdr(int socket);
const char	*NET_AdrToConnectionString(netadr_t *a);
const char	*NET_AdrToConnectionStringShort(netadr_t *a);
const char	*NET_AdrToConnectionStringMask(netadr_t *a);
int		NET_StringToAdr ( const char *s, netadr_t *a, netadrtype_t family);
//qboolean	NET_GetLoopPacket (netsrc_t sock, netadr_t *net_from, msg_t *net_message);
void		NET_JoinMulticast6(void);
void		NET_LeaveMulticast6(void);
__optimize3 __regparm1 qboolean	NET_Sleep(unsigned int usec);
void NET_Clear(void);
const char*	NET_AdrMaskToString(netadr_t *adr);
void		NET_TcpPacketEventLoop();
qboolean	Sys_SendPacket( int length, const void *data, netadr_t *to );

qboolean	Sys_StringToAdr( const char *s, netadr_t *a, netadrtype_t family );

//Does NOT parse port numbers, only base addresses.
qboolean	Sys_IsLANAddress (netadr_t *adr);
void		Sys_ShowIP(void);




typedef enum {
	TCP_AUTHWAIT,
	TCP_AUTHNOTME,
	TCP_AUTHBAD,
	TCP_AUTHAGAIN,
	TCP_AUTHSUCCESSFULL
}tcpclientstate_t;


#endif