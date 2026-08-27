# C++ SMTP

This is an implementation of the SMTP protocol in C++. Feel free to use this code for whatever. It's just a personal project.

Description of SMTP
---

Although SMTP is outlined in its own RFC documents, I will still describe it here (for my sake).

SMTP operates as a state machine, receiving commands and transitioning to and from states. The client sends commands and the server responds to commands with status codes. Here is a helpful graph:

HELO -> MAIL -> RCPT -> DATA ----
         ^        ^  |    ^  |  |
         |        |--|    |--|  |
         |                      |
         |----------------------|

Any state may transition immediately to the QUIT state (which closes the client socket.)

There are other steps (like VRFY or OPTIONS) but these are the basic ones that I will be implementing.

Example
-----

--- Connection established ---
C: HELO cs.unc.edu
S: 220 It's nice to meet you

C: MAIL FROM:<cage@cs.unc.edu>
S: 250 OK

C: RCPT TO:<ben@cs.unc.edu>
S: 250 OK

C: DATA
S: 354 End with <CRLF>.<CRLF>

C: 
From: Cage Bullard <cage@cs.unc.edu>
To: Ben Bullard <ben@cs.unc.edu>
Cc: Mom <mom@cs.unc.edu>
Date: 08-24-2026 11:53:00
Subject: Coursework

I just wanted to follow up and see if there was any coursework due next week? Please let me know.
-Micajah Bullard
.
S: 250 OK

C: QUIT
S: 221 Connection disconnected
--- Connection disconnected --- 
