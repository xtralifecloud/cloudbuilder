//
//  testsocketio.cpp
//  testCloudBuilder
//
//  Created by Roland Van Leeuwen on 19/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

/***************************************************************************
 *								  _   _ ____  _
 *  Project					 ___| | | |  _ \| |
 *							 / __| | | | |_) | |
 *							| (__| |_| |  _ <| |___
 *							 \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2012, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* An example of curl_easy_send() and curl_easy_recv() usage. */

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>


/* Auxiliary function that waits on the socket. */
static int wait_on_socket(curl_socket_t sockfd, int for_recv, long timeout_ms)
{
	struct timeval tv;
	fd_set infd, outfd, errfd;
	int res;
	
	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec= (timeout_ms % 1000) * 1000;
	
	FD_ZERO(&infd);
	FD_ZERO(&outfd);
	FD_ZERO(&errfd);
	
	FD_SET(sockfd, &errfd); /* always check for error */
	
	if(for_recv)
	{
		FD_SET(sockfd, &infd);
	}
	else
	{
		FD_SET(sockfd, &outfd);
	}
	
	/* select() returns the number of signalled sockets or -1 */
	res = select(sockfd + 1, &infd, &outfd, &errfd, &tv);
	return res;
}

int sendjson(CURL *curl, curl_socket_t sockfd, const char* json)
{
	CURLcode res;
	size_t iolen;
	
	/* wait for the socket to become ready for sending */
	if(!wait_on_socket(sockfd, 0, 60000L))
	{
		printf("Error: timeout.\n");
		return 1;
	}


	puts("Sending json.");

	res = curl_easy_send(curl, json, strlen(json), &iolen);

	if(CURLE_OK != res)
	{
		printf("Error: %s\n", curl_easy_strerror(res));
		return 1;
	}

	return 0;
}

int readjson(CURL *curl, curl_socket_t sockfd, char *json)
{
	CURLcode res;
	size_t iolen;

	wait_on_socket(sockfd, 1, 60000L);
	
	res = curl_easy_recv(curl, json, 1024, &iolen);
	
	if(CURLE_OK != res)
	{
		printf("Error = %d\n", res);
		return 1;
	}
	
	json[iolen]=0;
	
	return 0;
}


int main_curl(void)
{
	CURL *curl;
	CURLcode res;
	/* Minimalistic http request */
	curl_socket_t sockfd; /* socket */
	long sockextr;
	
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8124");
		/* Do not do the transfer - only connect to host */
		curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
		res = curl_easy_perform(curl);
		
		if(CURLE_OK != res)
		{
			printf("Error: %s\n", strerror(res));
			return 1;
		}
		
		/* Extract the socket from the curl handle - we'll need it for waiting.
		 * Note that this API takes a pointer to a 'long' while we use
		 * curl_socket_t for sockets otherwise.
		 */
		res = curl_easy_getinfo(curl, CURLINFO_LASTSOCKET, &sockextr);
		
		if(CURLE_OK != res)
		{
			printf("Error: %s\n", curl_easy_strerror(res));
			return 1;
		}
		
		sockfd = sockextr;
		
		sendjson(curl, sockfd, "{'type':'message', 'data':'content'}");
		
		int exit;
		do 	{		
		char json[1024];
		exit = readjson(curl, sockfd, json);
		if (!exit) printf("received : %s\n", json);
		} while (!exit);
		
		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	return 0;
}