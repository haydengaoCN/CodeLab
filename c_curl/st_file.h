#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <curl/curl.h>

#include "debug.h"

struct MemoryStruct {
	char *memory;
	size_t size;
	void Init()
	{
		memory = NULL;
		size = 0;
	}
	void Clean()
	{
		if(memory)
			free(memory);
		memory = NULL;
		size = 0;
	}
};

typedef struct _STUCurl
{
	CURL * m_pCurl;
	char szCurlErrbuf[CURL_ERROR_SIZE];
	
	void Init()
	{
		m_pCurl = curl_easy_init();
		
		curl_easy_setopt(m_pCurl, CURLOPT_ERRORBUFFER, szCurlErrbuf);
		curl_easy_setopt(m_pCurl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(m_pCurl, CURLOPT_VERBOSE, 0L);//若为1则显示详细的操作信息
		//curl_easy_setopt(m_pCurl, CURLOPT_HTTP_CONTENT_DECODING, 1L); //内容需要解压缩
		//curl_easy_setopt(m_pCurl, CURLOPT_HTTP_TRANSFER_DECODING, 1L);
		curl_easy_setopt(m_pCurl, CURLOPT_ENCODING, ""); //header中"Accept-Encoding: "部分的内容，支持的编码格式为："identity"，"deflate"，"gzip"。如果设置为空字符串，则表示支持所有的编码格式
		//curl_easy_setopt(m_pCurl, CURLOPT_TIMEOUT, 30); //超时为30s
		curl_easy_setopt(m_pCurl, CURLOPT_NOSIGNAL, 1L);


		curl_easy_setopt(m_pCurl, CURLOPT_FORBID_REUSE, 1L);
		curl_easy_setopt(m_pCurl, CURLOPT_FOLLOWLOCATION, 1L); //允许跳转

		/* curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallBack); */
		
	}
	
	void Init(const int iTimeOut)
	{
		m_pCurl = curl_easy_init();
		curl_easy_setopt(m_pCurl, CURLOPT_ERRORBUFFER, szCurlErrbuf);
		curl_easy_setopt(m_pCurl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(m_pCurl, CURLOPT_VERBOSE, 0L);

		//curl_easy_setopt(m_pCurl, CURLOPT_HTTP_CONTENT_DECODING, 1L); //内容需要解压缩
		//curl_easy_setopt(m_pCurl, CURLOPT_HTTP_TRANSFER_DECODING, 1L);
		curl_easy_setopt(m_pCurl, CURLOPT_ENCODING, ""); //header中"Accept-Encoding: "部分的内容，支持的编码格式为："identity"，"deflate"，"gzip"。如果设置为空字符串，则表示支持所有的编码格式
		
		
		curl_easy_setopt(m_pCurl, CURLOPT_NOSIGNAL, 1L);
		
		/* curl_easy_setopt(m_pCurl, CURLOPT_FORBID_REUSE, 1L); */
		/* curl_easy_setopt(m_pCurl, CURLOPT_FOLLOWLOCATION, 1L); //允许跳转 */

		/* curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallBack); */
		
		curl_easy_setopt(m_pCurl, CURLOPT_CONNECTTIMEOUT, iTimeOut);
		curl_easy_setopt(m_pCurl, CURLOPT_TIMEOUT, iTimeOut);//超时秒数

	}

	void Debug() {
		struct data config;
    config.trace_ascii = 1; /* enable ascii tracing */ 

    curl_easy_setopt(m_pCurl, CURLOPT_DEBUGDATA, &config);
 
    /* the DEBUGFUNCTION has no effect until we enable VERBOSE */ 
    curl_easy_setopt(m_pCurl, CURLOPT_VERBOSE, 1L);
 
    /*tell libcurl to follow redirection */ 
    curl_easy_setopt(m_pCurl, CURLOPT_FOLLOWLOCATION, 1L);
	}
	
	
	void setTimeOut(const int iTimeOut)
	{
		curl_easy_setopt(m_pCurl, CURLOPT_CONNECTTIMEOUT, iTimeOut);
		curl_easy_setopt(m_pCurl, CURLOPT_TIMEOUT, iTimeOut);
	}
	
	
}STCurl;

