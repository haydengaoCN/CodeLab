import requests as reqs
import os

payload_dict = {"list" : [{"ctype":1,"id":"xxxx","idtype":900}]}
response = reqs.post('http://9.146.64.170/cgi-bin/getVideoInfo', data = payload_dict)
print(response.url)
print(response.text)

#response2 = os.system('curl "https://api.github.com/events"')
#print(response2)
