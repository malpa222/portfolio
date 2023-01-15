---
permalink: /portfolio/lo1
title: LO1 - The security specialist
---

The goal of this learning outcome is to show that I know and understand what is red teaming and that I have learned the offensive skills that are sought
after in the job market and that I can apply them in a professional setting. I will prove that by showing what I learned about red teaming in my trends,
research, my hands-on experience of the offensive skills that I got in the projects and while solving CTFs and how I have applied the said skills in
professional settings.

## Red teamer specialization

For the specialization of this course, I have chosen the red teamer track. I wanted to learn about the offensive perspective of cybersecurity as I feel,
that this is the best place for utilizing my skills from software development courses. Compared to the previous cybersecurity semester, this one gave me
a clearer overview of what is red teaming, what skills it needs and how it is used in modern companies.

### What is red teaming?

Red team means roughly a group that plays a role of an enemy to provide a security feedback from that side. The term was coined in the military, but now
is used in the cybersecurity world to denote a designated group of security specialists that are trying to breach security measures put up by the blue team
(system administrators and defensive security specialists). Major companies, such as Microsoft or other FAANG giants, usually have a highly sophisticated
red teaming operations set up.

Typically, a red teaming operation will involve combining penetration testing techniques to try and detect any vulnerabilities that could grant them entrance
to the system or disclose sensitive information. These usually follow the Unified Kill Chain methodology for establishing the flow of the attack. Then, red
teamers usually refer to Mitre's ATT&CK framework to establish what hacking techniques might be most suitable for given reconnaissance, hacking or
post-exploitation phases. You can find more detailed description in my
[Trends Research](https://malpa222.github.io/portfolio/redt/trends#what-standards-and-methodologies-are-used-in-red-teaming-by-cybersecurity-companies).

While ransomware attacks are usually out of scope of red teaming operations, security specialists will often try to deliver malware loaders (described in
my [trends research](https://malpa222.github.io/portfolio/redt/trends#what-kind-of-malware-is-on-the-rise-right-now)) to the inside of the
system by the means of social engineering or exploiting other security holes. Apart from, software and people hacking, red teaming also includes assessing
the physical security of the company. It means that the red teamers will try to break into the building, or find pieces sensitive information left by
employees by accident.

### Why do companies need red teaming operations?

As mentioned in the previous paragraphs, the red team operations usually combine multiple ethical hacking activities to achieve a bigger goal by gaining
a persistance in a system and then traversing and exploring the infrastructure under the radars of threat detection software. This presents a lot of
benefits for the company:

- Increased employee awareness

    Social engineering and physical security assessments usually result in increasing the employee awareness about what information are they sharing with
    outsiders and their trust levels. However, these exercises need to be performed periodically and on every levels of the hierarchy, as people tend to
    forget or not pay attention about the security of the company.

- Identifying parts of the infrastructure at risk

    By performing multiple ethical hacking techniques, red teamers are able to identify which areas of the system's infrastructure. While cooperating
    with the blue team, both groups can benefit by learning on each other's mistakes thus increasing the security of the system and the most
    sensitive parts.

Security professionals with red teaming knowledge are sought after by big companies. An employee with either software development skills (for creating
custom tooling), social engineering abilities (for hacking employees) and penetration testing knowledge for vulnerability discovery and exploitation.

## Hands-on learning

A good red teamer needs to know how to work their way around a system so that they can bypass security measures and reach their goal. This type
of knowledge requires hands-on practice, since computer software is constantly changing and only reading about it in the books will never be
the same as trying out the theory in real life. Throughout the semester I have engaged in multiple activities that taught me new hacking methods
and technologies.

### Phishing at Hoefnagels

IT-Workz, the company at which we did our project tasked us with doing a penetration test at an external company. We got contact to Hoefnagels, a
fire safety company that wanted a security assessment. After establishing the scope and splitting up the tasks, I chose to work on conducting a
phishing attack.

This was a very challenging but fun task. I worked together with my teammate, Georgi Minchev. Together we discovered that modern internet is a very
secure place and it makes phishing almost impossible on the spot, and requires some pre-existing infrastructure that can be deemed as trustworthy
in the network. In essence, I learned how to: create phishing emails, create fake landing pages, use Beef-XSS for cross site scripting attacks,
use SocialPhish/GoPhish for managing phishing campaigns and how to set up DNS servers so that they can forward the mail to correct adresses.

I believe this is a valuable knowledge, that is hard to obtain without breaking ethical and legal rules. Having the opportunity to do it in
Hoefnagels was a great chance to learn more about social engineering and phishing. I learned about data exfiltration using cross site scripting,
and used OSINT to get very detailed information about our targets. You can find more details
[in my writeup](https://malpa222.github.io/portfolio/handson/hoefnagels) on the phishing activities.

### Defense evasion

Defense evasion is an important part of malware development. Not only it allows attackers to stay hidden in the infected system, but it also
prevents their software to be registered in anti virus databases. For red teamers this is also useful, as they can use their tools for a longer
period of time, without the need to ditch and develop new programs. Since my in-depth research was focused on obfuscating LLVM based software,
I wanted to extend that and see what can be done with obfuscation.

First, I have done a small study on how the products of my in-depth research can work in real life, by trying to obfuscate a C program using my
plugin for control flow flattening. However, I felt that it was not enough, so I wanted to see if scripting languages can evade antivirus software
as well. To do that, I tried to obfuscate a PowerShell script that opened a reverse shell. By default, these scripts are blocked by Windows
Defender so I wanted to try and evade it.

I think that this taught me that evading defenses will always be possible, but it will just be more and more complex over time. Overall, it was
a good thing to learn and exercise, since now I have some basic knowledge how all of it works. You can find more details in my
[defense evasion writeup](https://malpa222.github.io/portfolio/handson/evasion/).

### Hacking boxes

## In-depth research

The most interesting subject in my trends research was the Ransomware as a Service bit. I learned that it is usually done with new languages,
that are not easily reversible and that have good cross-compiling features. Therefore I decided to investigate the LLVM's compiler infrastructure
and how it can be used for malware development.

I have defined the following research question and split it into sub-questions that would guide me throughout the research:

**How can LLVM compiler infrastructure be used to aid malware development?**

- Why would a malware developer choose an LLVM based language?
- Are plugin development results worth the time spent learning the LLVM infrastructure?
- How effective is the control flow flattening obfuscation?

The first question required using the Library strategy, but the second and the third ones were also based on the Lab and Workshop to actually
implement the software and see the results. For more details about my research planning see the
[research section](https://malpa222.github.io/portfolio/redt/in-depth) of my in-depth research.

### Improving malware development with compiler-level obfuscation

I was always interested in binary exploitation and reverse engineering. In my first cybersecurity semester I did a research project on buffer
overflows and tried to apply them in practice. This time, I wanted to approach the binary exploitation from the defensive side and learn
how to efficiently obfuscate executables. The LLVM project was the best choice for creating such tooling.

While reading about the LLVM, I stumbled upon a video that showed how to write a plugin for the compiler. I thought that it might be interesting
to write a plugin that will automatically obfuscate the executable file during the compilation, so that the developer does not need to make their
code unreadable and unmaintainable. Some more research showed that there were already some attempts at obfuscation with LLVM, however they were
done long time ago and didn't quite stand the test of time. Based on [a research paper](https://ac.inf.elte.hu/Vol_030_2009/003.pdf) about control
flow flattening and the [old obfuscation project](https://github.com/obfuscator-llvm/obfuscator), I have decided to implement the algorithm to
create a guide and a proof of concept on how to write obfuscation plugins.

It was quite a hard task, because first I needed to learn about the LLVM project to be able to write a plugin. Almost every open source developer
knows that contributing to an open source project first requires quite some time to
[understand the architecture](https://malpa222.github.io/portfolio/redt/in-depth#why-would-a-malware-developer-choose-a-language-built-on-llvm)
of the project and how it works. After that, I had to learn basics of C++ (I have only had some experience with C before), LLVM's assembly language
and basics of reverse engineering. Nevertheless I was able to learn all of the things and successfully develop the obfuscation plugin. More details
can be found in [my In-depth research](https://malpa222.github.io/portfolio/redt/in-depth).

### Reflections

The course of my research was fuzzy in the beginning - I have started researching what is cross-platform malware and how could it be used by hackers.
Over the course of this semester, I have shown my research to my peers and my teachers during a sessions of red teaming presentations or on
individual talks with the teachers. Their feedback was valuable and told me to narrow down the scope of my research so that my goal will become
clearer. Therefore, after spending some more time learning about the binary portability I stumbled upon LLVM, which led me to establishing the final
form of my research.

All in all, I believe it was a good project that taught me a lot about how to take a red teaming perspective into account while conducting research
on a technology or trying to create a new solution.

## Professional application

I have applied the gained knowledge in the group project assignments that I have performed throughout the semester. The main goal of our group project was
to research how a pen test can be provided as a service. The company that created the assignment was IT-Workz. They wanted us to conduct a penetration test
with a fire safety company Hoefnagels. The assignment was not big enough to be called a red teaming operation, however the penetration test required
using the common techniques used by the red teamers. We have planned our work using the DOT Research Framework, which allowed us to plan how are we going
to approach the requirements presented by the stakeholders. You can find more details about our research in in my
[group project research description](https://malpa222.github.io/portfolio/group/description#research-questions).

### Hoefnagels

My role in this assignment was to conduct a social engineering test by creating a phishing campaign and sending it to the employees of Hoefnagels. I had to
learn how to find the vulnerable areas of the employee awareness. The goal of our social engineering operation was to find how to benefit the company with
our findings.

In the project I have learned how to use phishing software such as Beef-XSS, SocialPhish. Moreover we had to come up with solutions for bypassing the
search engine security measures as well as setting up a dns and a mail server to send the phishing messages to the employees of Hoefnagels. You can find
more information about it in my [Hoefnagels pen test write-up](https://malpa222.github.io/portfolio/group/phishing).

### Pentesting as a Service

However, the main goal of our project was to tell IT-Workz how a pentest could be provided as a service. Since they only knew computer security from the
defensive side, our group had to prepare them a set of guidelines, procedures, best practices and resources on both technical and high, business level. My
role in preparing the deliverables was explaining about different categories of pen tests and social engineering in both technical and management documents.

For the technical staff, I focused on explaining how to conduct white, black or gray box pentests, why they would choose one over another and what is the
output of such test. Moreover, I have also provided a list of resources and necessary tools. I did the same for social engineering. For the management level,
I tried explaining what is the business value of each type of pentest and social engineering, so that the management staff can understand what is the business
value of the activities. You can find more details in my group project description -
[pentesting as a service](http://localhost:4000/group/description#pentesting-as-a-service).

## Validation

When conducting research, it is important to be sure to validate the progress and results constantly. Good feedback can and will improve the quality of the
study and can resolve any misunderstandings that might arise between the stakeholders of a project.

### Individual track

As mentioned before, the course of my project was uncertain in the beginning since I have chosen a very broad topic. However, because I have made
proactive efforts to show my results to my teachers, they were able to direct me on the right track. For the peer feedback, I have presented the
progress in my in-depth research to my peers and teachers from the red teaming track. Their opinions were very valuable and gave me hints that
improved my presentation skills. Moreover, by writing a short summary of my research through the means of publication, I was able to get very specific
peer feedback. Then, at the end of the research, I have created a working proof-of-concept that allowed me to confirm the validity of my research.

For the personal project, I have stayed in contact with my coach and my group mates to receive their feedback. Again, because I was interested in the
security of decentralized networks, it took me a bit longer to create a good scope for the research. After presenting my updated project to my group
mates, I received feedback from them that allowed me to get on with my project.

All in all, I have mainly validated my individual projects with peer and teacher feedback. Their opinions and impressions were mainly related to the
DOT Research Strategies and how I structured my projects to use them and the ways in which I presented my results.

### Group project

After initial contact with the stakeholders, we have translated their business requirements into a series of research questions and guidelines that
established the directions for our projects. As mentioned before, throughout the projects I have relied on the industry standards: Unified Kill Chain
and ATT&CK. Moreover, in the deliveries for the clients we have conducted risk analysis with the help of the CIA Matrix.

On every stage of the projects the results of our worked were validated with our teachers and project owners, so we could get immediate feedback and
apply it to the next phases of the research. When we have presented the results of our penetration test to the Hoefnagels management team, which
was was unaware of our project and received a very positive feedback. Moreover, we have presented our project to our peers, because the Hoefnagels
penetration test required a physical intrusion activities. That was also valuable for our team since we got feedback from other students and teachers
that were not involved in our project.

## Evaluation

This semester required a lot of effort from me. I had to spend a lot of time on my individual research topics which were quite challenging, but
nevertheless rewarding. I have worked with my group on a penetration test and providing valuable product for the project owners.

I think that I am most content with my effort to create an LLVM based obfuscator. This was quite technical and complex assignment, since it
required working with assembly language and compilers. However I managed, and created a piece of new/improved technology that can be used
in red-teaming operations. Personally I feel, that it might be the biggest achievement that I done during my course of the university and
this semester allowed me to do it.

In the group project I have also did something that was completely new to me, but nevertheless very rewarding - social engineering. It is
not common for university students to conduct phishing attacks as a part of a penetration test. I learned how to set up a phishing framework,
create appropriate infrastructure and got to try my social engineering skills.

However some things could have been different. One of the biggest challenges was communication with our project owner. They have not been
exactly communicative and that have impaired our progress in the research. Nevertheless, because of the proactive attitude, I was able to
push and deliver the penetration testing study to IT-Workz despite not being able to be in touch all of the time. As for the personal
reflections: I think that I could have improved to things - scope and time management. My in-depth research and personal project suffered
from the same problem. I have defined a scope which was a bit too broad, and then had to narrow down the scope as the semester passed, because
I did not spend enough time on formulating my research. This has impacted my time management, because I needed to work on my projects with
less time than other students. Nevertheless, it was not that big of an issue and I have managed to work out everything in time and deliver
quality results.

I believe that this semester taught me a lot about being a security professional. Throughout the course of the study I made heavy use of
research strategies and security standards and principles. This is a skill that was a bit lacking before, so now I have much better
understanding how to work in a structured manner. I learned a lot about red teaming and related techniques. Especially the ones that are
work well with my software development skills. I think that developing good tools is as important as learning exploitation techniques
and I think I managed to prove it. However, that does not mean that my learning is over. I want to become even better at binary exploitation,
reverse engineering and improve my exploitation techniques. Apart from that I want to improve my organizational skills even more,
so that I can understand my clients and that I can show them my progress in a way they could understand.
