#include <Windows.h>

#include "curl/curl.h"

static size_t readfunc ( void * ptr, size_t size, size_t nmemb, void * stream )
{
	char* buf = (char *) malloc(size*nmemb + 1);
	memcpy(buf, ptr, size*nmemb);
	buf[size*nmemb] = 0;
	OutputDebugStringA(buf);
	free(buf);

	return size*nmemb;
}

int main(int argc, char* argv[])
{
	CURL *curl;
	CURLcode curlres;

	curl = curl_easy_init();
	if(curl)
	{
//		curl_easy_setopt(curl, CURLOPT_URL, "http://www.bitrabbit.net");
//		curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.fr");
//		curl_easy_setopt(curl, CURLOPT_URL, "https://graph.facebook.com/oauth/access_token?client_id=206446646074589&client_secret=0caea19e921c70b1479f854d8bbb50d6&redirect_uri=http%3A%2F%2Fwww.zeonecompany.fr&grant_type=client_credentials");
		curl_easy_setopt(curl, CURLOPT_URL, "https://msp.f-secure.com/web-test/common/test.html");
		curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, readfunc);
		curlres = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	return 0;
}