/*
 *  prowl.h
 *  prowl
 *
 *  Created by J. Dijkstra (abort@digitalise.net) on 29-04-10.
 *  Copyright 2010 Digitalise.NET. All rights reserved.
 *
 */

#ifndef PROWL_H_
#define PROWL_H_

#define STRICT

#define SSL_PORT 443
#define HOSTNAME "prowl.weks.net"
#define MESSAGESIZE 11400
#define BUFFERSIZE 512

/* priorities */
#define PROWL_PRIORITY_VERY_LOW -2
#define PROWL_PRIORITY_MODERATE -1
#define PROWL_PRIORITY_NORMAL 0
#define PROWL_PRIORITY_HIGH 1
#define PROWL_PRIORITY_EMERGENCY 2

#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")
#else
#define SOCKET int
#define SOCKET_ERROR -1
#define closesocket(socket) close(socket)
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#endif

#include <string.h>
#include <stdio.h>
#include <ctype.h>

/* openssl headers */
#include <openssl/ssl.h>
#include <openssl/err.h>

/* ssl/connection structure */
typedef struct {
    SOCKET socket;
    SSL* ssl_handle;
    SSL_CTX* ssl_context;
} prowl_connection;

int prowl_push_msg(char* api_key, int priority, char* application_name, char* event_name, char* description);

/* module specific functionality */
static SOCKET prowl_tcp_connect();
static prowl_connection* prowl_ssl_connect();
static void prowl_ssl_disconnect(prowl_connection* c);
static char* prowl_ssl_read(prowl_connection* c);
static int prowl_get_response_code(char* response);

/* credits to: http://www.geekhideout.com/urlcode.shtml */
static char prowl_int_to_hex(char code);
static char* prowl_url_encode(char* str);

#endif