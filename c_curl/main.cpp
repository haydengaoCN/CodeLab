#include <stdio.h>
#include <cstring>  // memcpy
#include <iostream>
#include <vector>

#include "st_file.h"

int StrReplace(std::string & strInput, const std::string & strTobeReplaced, const std::string & strNew )
{
	std::string::size_type iPos = strInput.find(strTobeReplaced);
	if(iPos == std::string::npos)
		return -1;
	strInput.replace(iPos, strTobeReplaced.size(), strNew);
	return 0;
}

void *myrealloc(void *ptr, size_t size)
{
/* There might be a realloc() out there that doesn't like reallocing
     NULL pointers, so we take care of it here */
	if(ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

uint WriteCallBack(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	if(realsize <= 0)
		return 1;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;
	mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}else{
		printf("malloc error: cur size: %zd, real size: %zd\n", mem->size, realsize);
	}
	return realsize;
}

int GetPage(const std::string & strUrl, std::string & strContent)
{
	int iRet;

	STCurl stCurl;
	stCurl.Init();
	stCurl.Debug();

	struct MemoryStruct chunk;
	chunk.Init();

	
	curl_easy_setopt(stCurl.m_pCurl, CURLOPT_URL, strUrl.c_str());

	curl_easy_setopt(stCurl.m_pCurl, CURLOPT_CONNECTTIMEOUT, 60);
	curl_easy_setopt(stCurl.m_pCurl, CURLOPT_TIMEOUT, 60);
	curl_easy_setopt(stCurl.m_pCurl, CURLOPT_HEADER, 0);
	
	curl_easy_setopt(stCurl.m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallBack);
	curl_easy_setopt(stCurl.m_pCurl, CURLOPT_WRITEDATA, &chunk);

	iRet = curl_easy_perform(stCurl.m_pCurl);

	if(iRet == 0)
	{
		if(chunk.memory)
			strContent = std::string(chunk.memory);
	}else{
		printf("%s, ret : %d, curl error: \n",__FUNCTION__, iRet);
	}

	curl_easy_cleanup(stCurl.m_pCurl);
	chunk.Clean();


	return iRet;
}

// g++ -std=c++17 main.cpp st_file.h debug.h -lcurl  -o main
int main() {
  std::vector<std::string> vid_tids{"98", "1250", "1375"};
  std::vector<std::string> cid_tids{"97", "1249"};
  std::vector<std::string> col_tids{"96", "1209"};
  constexpr char union_curl[] =
      "http://data.video.qq.com/fcgi-bin/data?tid=${tid}&idlist=${idlist}&"
      "appid=20001018&appkey=fadab37ce35a5a71&otype=json";
  constexpr char union_curl2[] =
      "http://union.video.qq.com/fcgi-bin/data?tid=${tid}&idlist=${idlist}&"
      "appid=20001018&appkey=fadab37ce35a5a71&otype=json";
  std::string vid_list = "s32344vzlx0";  // sepa by comma ','
  std::string cid_list = "kkp0025hj0kjyri";  // sepa by comma ','

  auto getpage = [union_curl](const std::string& tid, const std::string& tid_list) {
    std::string curl = union_curl;
    StrReplace(curl, "${tid}", tid);
    StrReplace(curl, "${idlist}", tid_list);
    std::cout << "full curl:\n" << curl << std::endl;

    std::string contents;
    auto iret = GetPage(curl, contents);
    if (iret != 0) {
      std::cout << "failed to get page." << std::endl;
    }
    return contents;
  };

  std::cout << getpage(vid_tids[0], vid_list) << std::endl;
/*
  std::cout << getpage(vid_tids[1], vid_list) << std::endl;
  std::cout << getpage(vid_tids[2], vid_list) << std::endl;
  std::cout << getpage(cid_tids[0], cid_list) << std::endl;
  std::cout << getpage(cid_tids[1], cid_list) << std::endl;
*/
  
  return 0;
}
