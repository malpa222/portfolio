---
permalink: /personal
title: Personal project
---

## Project plan

The personal project in this specialization is not strictly tied to our personal track. Therefore, I have decided to explore the peer-to-peer file
sharing network created by the BitTorrent protocol. I have always found torrents interesting, and I believe it is a good exercise for this semester
to look at file sharing from a security perspective. Since BitTorrent was initially created in 2001, a lot of things in the world of computer
security have changed. The protocol's  security has remained fairly the same throughout the years, so I want to explore what and how could be
changed in the specification.

I want to use the Go programming language for developing a couple of proof-of-concepts for the project. The language is becoming more and more popular
in the industry, because of it's small learning curve, automatic garbage collection and speed. Therefore, I will try to use Go in different use cases to
discover the potential of the language.

### Research questions

In order to structure the learning process, I have defined a the main research question that represents the goal of the project and a set of sub-questions
that are going to help me to achieve this goal.

**How could the security of the BitTorrent protocol could be improved?**

- What are the main security concerns of the BitTorrent protocol?
- What risk is associated with using a distributed hash tables?
- How to address the lack of encryption in the protocol?

### Research strategies

In order to compute an answer for the main research question, each sub-question needs to be researched. To do that I am going to use different research
strategies from the DOT framework.

**How could the security of the BitTorrent protocol could be improved?**

- **What are the main security concerns of the BitTorrent protocol?**

  This question is focused on learning about the internals of the BitTorrent protocol. The protocol has been developed in 2001, but it lacks some of the features that
  are crucial for modern network infrastructures. I will approach this research question by applying the Library research to learn about the protocol. To get some
  hands-on experience, I will combine the Lab and the Workshop strategies by implementing the protocol in Golang. That way, it might be easier for me to visualize 
  security holes.

- **What risk is associated with using a distributed hash tables?**

  This question tries to analyze the de-facto standard of peer discovery: distributed hash tables. The hash tables can be used for trackerless peer discovery, making 
  the network completely decentralized, but they also introduce some threats for the DHT nodes. I will try to answer this question by analysing the need for DHTs using 
  the Library research strategy. Then, I will combine the Lab and Workshop strategies to try and come up with proposals to fix the vulnerabilities.

- **How to address the lack of encryption in the protocol?**

  The protocol is an old standard, which was built on plain TCP and HTTP. This means that the traffic between nodes in completely unencrypted and could be easily sniffed
  upon. I want to try and come up with recommendations for implementing encryption in crucial interfaces of the protocol. To do that, I would need the Library research on
  finding current encryption standards and then providing the recommendation on how it could be applied in the protocol.

### Project management

In order to efficiently work on the project, I have decided to use Scrum framework for planning and management. I split the semester into three 3 week long sprints:

- Sprint 1 - 03.10 - 24.10
- Sprint 2 - 24.10 - 14.11
- Sprint 3 - 14.11 - 05.12
- Sprint 4 - 05.12 - 12.01.2023

## What are the main security concerns of the BitTorrent protocol?

The first major peer to peer (P2P) network implementation was Napster. Napster created a network in which users could share files with each other directly instead
of having to access a website that hosted files. This was really convenient for internet pirates as websites with pirate media were quickly taken down for
copyright reasons. However, Napster had a big problem with speed. It was 1999 when the application was created, so the dial-up modems were still very much in use.
The main idea of the application was to enable sharing files by connecting directly to another peer in the network and downloading the whole file. In the most
optimistic case, a client could choose the peer with the best connection and then download the file, but that was not the case in most of the situations;
downloading an mp3 file could take around 20 minutes (if not more). Therefore, the BitTorrent protocol was created.

### How does it work?

The BitTorrent protocol worked on a basis of splitting up files into multiple parts and the redistributing them across the network of peers that are interested
in this file; either downloading or *seeding* (sharing the file with other peers). When downloading a file, the peer begins to share the downloaded parts with other
peers of the network. That way, instead of downloading a piece of data from one computer, it is obtained from many peers at once. Not only it is faster than Napster,
but also creates a decentralized network that becomes faster the more peers are taking part in it.

| ![BitTorrent network diagram](../assets/img/personal/bittorrent_diagram.png) |
| BitTorrent network diagram |

To participate in the network users need to use a program that implements the protocol, so unlike Napster, the protocol allows for custom implementations. Then,
if a user wants to download a file, they need to use a torrent sharing server. From that server, users will obtain a torrent file or a magnet link, containing
the information about a *tracker* server that will be used by their BitTorrent client to get the list of peers, parts of the file, size, name etc. This allows
for almost completely decentralized file sharing network.

### Encryption

The main problem with the protocol is the lack of encryption. The concept was created back in 2001, when encryption of network communications was not the main
priority of protocol designers, as the amount of cyber attacks was much lower than in 2022. However, even today the protocol is not using encryption and it
does not seem that anything is going to change about it soon.


| ![Wireshark capture](../assets/img/personal/bt_capture.png) |
| Wireshark capture |

| ![Handshake](../assets/img/personal/handshake.png) |
| Handshake |

Wireshark has a built in BitTorrent protocol support, so the filter can be easily applied to the capture. As you can see in the *Handshake* image, the protocol
handshake was intercepted. The message was sent in plain text, just as the response with the list of peers:

| ![Peers](../assets/img/personal/bt_peers_capture.png) |
| Peers |

This is what makes the protocol very unsecure: virtually anybody can sniff on the network and get a list of IP addresses and the ports they are listening to. It
can be used for disclosing the torrenting computers on a massive scale or exploiting that in some different way. Apart from disclosing the IPs, lack of encryption
makes it much easier for man in the middle attacks. A hacker could implement the protocol easily and then announce himself as the router in the network and capture
only the BitTorrent related packets. Then, they would be able to give any kind of response to the users and possibly send their malware instead of the original
files.
