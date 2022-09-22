---
title: Trends research
layout: single
permalink: /lo1/trends
---

## What is a trend?

To me, a trend is a generic term, which can describe the things that are on the mouths of people or the current preferences/commodidities that a 
certain group sticks to. However, in the cybersecurity context, trends can be defined as the directions in which the industry is developing,
new attack techniques, exploits on new (and old) technologies as well as the legal aspects of hacking. 

Therefore, I have decided to inquire into different hacker 'groups', malware aggregators and social platforms to see which things are receiving more
traction in the red teaming world.

## What is a trend?

To me, a trend is a generic term, which can describe the things that are on the mouths of people or the current preferences/commodidities that a 
certain group sticks to. However, in the cybersecurity context, trends can be defined as the directions in which the industry is developing,
new attack techniques, exploits on new (and old) technologies as well as the legal aspects of hacking. 

Therefore, I have decided to inquire into different hacker 'groups', malware aggregators and cybersecurity reports to see which things are receiving more
traction in the red teaming world.

## Research questions

It is hard to create main research questsion for this document, since it focuses on exploring different trends and not trying to achieve a 'common goal'. 
Nevertheless, my research needs a direction, therefore I have decided to write down the research questions that I want to follow while conducting the 
investigation.

1. What kind of malware is on the rise right now?

2. Do new APT actors use currently trending malware families?

3. How do cybersecurity companies protect businessess and organisations agains cyber-attacks?

## What kind of malware is on the rise right now?

According to a *[Mid-year update](https://www.sonicwall.com/medialibrary/en/white-paper/mid-year-2022-cyber-threat-report.pdf)* conducted by Sonicwall,
in the first half of 2022, there has been a 11% increase in malware-related incidents compared to last year. Moreover, according to the company, the
increase in malware is real - there is more malware, because the number of attacks increased. The company explains that with the increase of on-site work,
the number of malware incident increases and when there is more offsite work, the numbers drop. However, when the offsite work ratio increased, the
malware incidents didn't decrease.

In order to look for recent malware discoveries I have turned to websites such as *[VX-Underground](https://vx-underground.org)* and 
*[Malpedia](https://malpedia.caad.fkie.fraunhofer.de)*. Both websites are databases containing malware examples, source code and research papers
on different topics regarding red teaming (as well as sytem hardening). The websites are being often updated with new discoveries, therefore I 
have decided to use them as my sources for providing examples of recent attacks.

1. Malware loaders - Bumblebee

	In march a new malware loader was discovered. The code was named 'BumbleBee', after an user agent string that the malware used to contact the command
	and control center. The discovery was made after a malware spread in a spear-phishing email campaign. The following graph shows an example of BumbleBee delivery

	![BumbleBee delivery graph](./assets/img/bumblebee_email.png)

	In late August, a new attempt to deliver malware was prevented. The detailed description can be found on Deep Instinct's 
	*[website](https://www.deepinstinct.com/blog/the-dark-side-of-bumblebee-malware-loader)*. The malware delivery chain forces user
	to extract a _.zip_ archive, thus the _.iso_ file is mounted on victim's machine. The disk image contains a _.dll_ with payload and 
	a _.lnk_ file which opens a PowerShell script. To ensure stealthy execution of the payload, the PowerShell script uses multiple evasion techniques, such as:

	* It breaks up command strings, to obfuscate code and evade static analysis. An excerpt from the malware PS script:

	```
		$maraDizo = "Get";  
		$maraDizo += "Current";
		$maraDizo += "Process";

		# I skipped over some code

		$cPr = [System.Diagnostics.Process]::$maraDizo;
	```

	* BumbleBee proactively checks for a virtual/sandboxed environment and tries to prevent analysis. It was found to have been using
	*[al-khaser](https://github.com/LordNoteworthy/al-khaser)* - an open-source project containing a plethora of different tools that check whether
	the malware is running in a VM, has a debugger attached, is being analysed etc.  

	According to Bleeping Computer, the malware is still in development and becomes more and more sophisticated with each update - for example, recent 
	versions, found in September, 
	*[load the payload directly into memory](https://www.bleepingcomputer.com/news/security/bumblebee-malware-adds-post-exploitation-tool-for-stealthy-infections/)*,
	reducing detection possibilities even more.

2. Ransomware as a Service - BlackCat

## Cyber-attack protection

The amount of cyber threats that can impact an organisation can be overwhelming for companies which do not have SoC teams or sophisticated anti-malware software.
To respond to the demand, big cybersecurity companies like *[Cloudflare](https://www.cloudflare.com/)*, *[Sonicwall](https://www.sonicwall.com/)* 
or *[Malwarebytes](https://www.malwarebytes.com/)*.
