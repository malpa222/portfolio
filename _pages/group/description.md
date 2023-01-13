---
permalink: /group/description
title: Project description
---

IT-Workz is a company which specializes in providing infrastructure solutions for educational institutions and other organizations which would
benefit from an outsourced IT solutions. They proposed an assignment - research how they could provide a penetration test as a service. The goal was
to find out about the current methodologies and techniques used in the red teaming field. Since IT-Workz wanted to introduce new product, we needed
to provide explanation on both technical and business levels.

Together with the project owner, we have decided that best way to tackle this assignment would be to conduct penetration tests on different companies,
which would give us a better overview on how a pen test is conducted and what are the requirements. Apart from that, we decided to research the current
framework and methodologies used in the field.

## Hoefnagels

We started the research by establishing a plan of action. The first item on our agenda was to contact Hoefnagels - a fire safety company based in the
Tilburg area. In our initial meeting, we found out that the company does not have much IT experience, and that they outsource their infrastructure
to an external ICT company. Hoefnagels wanted us to perform a rather black-box pen test which would encompass physical intrusions, wireless testing,
social engineering and an black-box test of their infrastructure. The main focus was on the physical, wireless and social engineering tests; The external
testing however, was not the most important item in the scope.

### Planning and execution

As one of the first stages of the Initial Foothold cycle of the Unified Killchain was reconnaissance, we decided to refer to Mitre ATT&CK framework.
We have decided to use the common reconnaissance activities from ATT&CK to gain information about our victim and to discover entry points into their
infrastructure and other vulnerabilities. As IT-Workz wanted to receive information on how to conduct pen tests, we have researched and reported on
the most common pen testing tools. We used that research as an input for our reconnaissance phase, and combined it with ATT&CK framework.

Our initial research gave us the IP ranges of their web shop and the LinkedIn accounts of their employees. During the initial on-site research, our
team managed to get the IP address of the company itself, which was a great finding since we could use it to target any open services directly.

We have split the tasks among us and delegated each other to different areas. Together with Georgi Minchev, I chose to work on the social engineering
part - which meant that we had to conduct a phishing campaign. A write-up on my progress is available in the
*[phishing](https://malpa222.github.io/portfolio/group/description)* section of my portfolio.

## Pentesting as a service

The main goal of the project however, was to establish what is required to provide penetration testing as a service. Since IT-Workz has never had any
penetration testing experience before, they wanted our group to give them a comprehensive guide on what is penetration testing and what skills and
resources are needed for providing it for other companies. Moreover, IT-Workz wanted to know if the reporting process could be somehow automated, so

In this phase of the project my task was to explain different categories of penetration testing and about social engineering to the technical
employees and to the management staff. I have decided to describe different areas of pentesting together with their goals in a way that suits each
of the audiences.

### Technical and management level documents

First, I started writing about pen test categories on the technical level. The results of the Hoefnagels pentest and gained knowledge were helpful, as
during the initial talks with the company we had to decide on the scope of the assessment. To do that I had to refresh my knowledge about white, black
and gray box testing as well as what kinds of tests the company might be interested in: external, internal, wireless, social engineering or physical
intrusions.

In the document I have explained how to conduct a white, black or grey box test and what are the required skills and tools for these assessments.
I have also showed what are the benefits of choosing each of the categories and what can be achieved by focusing on, for example, wireless testing
or social engineering. Then, I have explained the value of social engineering tests and how to execute such attacks based on my experience from
the Hoefnagels. I have provided the required tooling and tips and tricks mentioned in my [Hoefnagels phishing writeup](). I have also provided
references to useful resources that I have used to learn more about the testing.

For the management level document, I have taken a more abstract approach and focused on explaining the business value of each category and area of
pentest. Again, I have explained the benefits of choosing each category and briefly mentioned which types of pentests might be interesting for the
for the company to investigate. Additionally, I have explained the value of social engineering and the benefits of conducting such tests in a
company. Moreover, I have also provided a list of references to the resources that I have used for describing the problem.

For more details please refer to our group project documentation:

- Hoefnagels - technical level document
- Hoefnagels - management level document

## Reflections

In this project I have mainly focused on conducting social engineering assessments and explaining the value of them to the companies. I have also worked
on showing the management and technical staff what are the benefits of white, black or gray box testing and why would employers/technical staff choose
any of them.

Our group had communication issues with IT-Workz, as they have been late to respond to our messages. We kept our teacher informed about it and we stayed
proactive during the project, so that we can push the company to work with us. Hoefnagels however was very communicative and was very eager to give us
feedback during the each step of our penetration test.

Personally, I believe I learned how to manage expectations of stakeholders due to their lack of professionalism. This is something that every security
specialist will have to deal with sooner or later, so I am happy that I learned that in a controlled, university setting. I believe that the technical
knowledge I gained in the project allowed me to manage the IT-Workz expectations and create a good scope for the Hoefnagels pentest. Moreover, now
I know how to conduct a social engineering attack and how to explain its benefits to the clients.
