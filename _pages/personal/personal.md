---
permalink: /personal/plan
title: Project plan
---

## Introduction

The personal project in this specialisation is not strictly tied to our personal specialisation. Therefore, I have decided to put my efforts into learning about 
the Go programming language by researching the BitTorrent protocol.

Go is becoming an increasingly popular choice for backends and cloud environments. Developed at Google in 2007, Go was aimed to solve
some engineering problems that the company was facing back then. Since its inception, the language has proven to be fast, maintainable and easily scalable.

## Research questions

In order to structure the learning process, I have defined a the main research question that represents the goal of the project and a set of sub-questions
that are going to help me to achieve this goal.

**How could the security of the BitTorrent protocol could be improved?**

- What are the main security concerns of the BitTorrent protocol?
- What risk is associated with using a distributed hash tables?
- How to address the lack of encryption in the protocol?

## Research strategies

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
  the Library research strategy. Then, I will combine the Lab and Workshop strategies to try and exploit the vulnerability.

- **How to address the lack of encryption in the protocol?**

  The protocol is an old standard, which was built on plain TCP and HTTP. This means that the traffic between nodes in completely unencrypted and could be easily sniffed
  upon. I want to try and come up with recommendations for implementing encryption in crucial interfaces of the protocol. To do that, I would need the Library research on
  finding current encryption standards and then providing the recommendation on how it could be applied in the protocol.
    
## Project management

In order to efficiently work on the project, I have decided to use Scrum framework for planning and management. I split the semester into three 3 week long sprints:

- Sprint 1 - 03.10 - 24.10
- Sprint 2 - 24.10 - 14.11
- Sprint 3 - 14.11 - 05.12
- Sprint 4 - 05.12 - 12.01.2023

# What are the main security concerns of the BitTorrent protocol?

