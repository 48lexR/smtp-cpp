# C++ SMTP

This is an implementation of the SMTP protocol in C++. Feel free to use this code for whatever. It's just a personal project.

Description of SMTP
---

SMTP is **originally** outlined in [RFC 821](www.rfc-editor.org/info/rfc821/), I will still describe it here (for my sake.) THIS RFC DOCUMENT HAS LONG BEEN OBSELETED, so this isn't a real mailserver! (It is, but there's no encryption or anything, so it's not practical any more.)

SMTP is a **state machine** that allows for a push-protocol between servers and clients. Each client command has the same basic format: 

`<command> <arguments>`

and each response basically looks like this: 

`<3-digit-code> <message>`

(The `message` should be IGNORED. The `code` is the only part that matters.)

Here are the basic states:

## Initial State
After a HELO is sent and a response received, both client and server enter the initial state. Today, this has been almost exclusively replaced with EHLO, but in the olden days, servers would first send a HELO message. The HELO message is used to identify the SMTP sender. The client will send a HELO, and the server will respond with one. Its message format is this: 

`HELO <domain>`

And its response SHOULD look like this:

`221 OK <message>`

Traditionally, the `message` field reads, `<domain>, it's nice to meet you.` At this point, a transaction has not yet begun.

## Transaction State

The transaction state consists of two parts: the `ENVELOPE` and the `DATA`. The `ENVELOPE` consists of two parts: the `MAIL` message and the `RCPT` message.

### MAIL FROM

First, the client will send a `MAIL FROM` message. It has the following description:

`MAIL FROM: <reverse-path>`

I will detail a `path` later, but for my sake (because this won't be used with any relays) the `path` will simply have the format: `<mailbox>@<domain>`. (In practice, the "reverse path" may actually be a list of hosts, since mail may be forwarded many times. This is outlined in RFC 821.) There are a couple possible replies: 

* `220 <message>` if successful
* `550 <message>` 
* `551 <message>`

### RCPT TO

Once a MAIL FROM has been sent and a 220 message received, the sender will send a `RCPT TO` message, which has the following form: 

`RCPT TO: <forward-path>`

The `forward-path`, similar to the `reverse-path`, is also a path that will be `<mailbox>@<domain>`. (Similar to before, it may actually be a list of hosts.) Here, the possible replies are the same as above. Any number of RCPT TO messages may be sent. (Think about it this way: shouldn't my email be able to be received by multiple users?)

### DATA

Once an RCPT reply has been successfully received, the sender should send a `DATA` message. When the `DATA` message is received, the possible responses are: 

* `354 <message>` if successful

Once the response is received, the message should be sent. It should be ASCII-encoded. ([MIME](https://www.rfc-editor.org/info/rfc2045/) is a protocol designed to add support for other things, such as files, UTF-8 encoding, &c... I will not be implementing MIME right now.) The data should be terminated by the character sequence 

`<CRLF>.<CRLF>`

Technically, once a message is received, the final data should contain a timestamp for each server through which it passed, as well as beginning with a return path. The actual format for the DATA is arbitrary, but generally begins with some headers, followed by `<CRLF><CRLF>`, then the message data. As an example, consider this well-formed message: 

```
From: <cage@cagebullard.net>
To: <cbull358@gmail.com>
Cc:
Bcc:
Date: 9 Oct 2026, 12:01:00 EDT
Subject: Testing email

I just wanted to let you know that I'm testing my email client. 
- Cage
```

Technically, the Return-Path is supposed to be included at the top of the message, but since I'm not doing any mail forwarding, there's no need for any of that.

Once `<CRLF>.<CRLF>` is received, the receiver should respond with  `220 <message>` if successful. Then, both should return to the initial state (from above.)

### QUIT

The SMTP connection shouldn't be closed until the client sends a `QUIT` command. The sender will move to the `QUIT_SENT` state, and the server should respond with `221 <message>` confirming that the connection is closed, at which point both hosts should move to the `CLOSED` state, and the connection will be closed.

## Other Commands

Maybe I'll implement these at some other point, but for right now, I have no plans to. These commands may always be sent at any time.

### NOOP

Does nothing. Receiver should send `220` as a reply.

### HELP

Receiver should send helpful information to the sender. "It may take an argument (e.g. a command name.) and return more specific information as a response" (RFC 821). Should have no effect on any variables.

### VRFY

"This command asks the receiver to confirm that the argument identifies a user. If it is a user name, the full name of th euser (if known) and the fully specified mailbox are returned. This command has no effect on [anything]" (RFC 821).

### RESET

"This command speficies that the curent mail transaction is to be aborted" (RFC 821). Everything should be deleted.

### EXPN

"This command asks the receiver to confirm that the argument identifies a mailing list" (RFC 821). It is basically VRFY for all members of a mailing list.

## Other Notes

* Any case should be accepted, per RFC 821. I'm kinda lazy, so I might start by just accepting all uppercase and all lowercase, but `MAIL Mail mail MaIl` and `mAIl` are all acceptable MAIL commands. (However, paths are case-sensitive.)
* The argument field must be followed by `<CRLF>`

## List of common reply codes 

### Successes

| code | status |
| --- | --- |
| 211 | System status/help reply |
| 214 | Help message |
| 220 | <domain> |
| 221 | <domain> Service closing channel |
| 250 | Completed |
| 251 | User not local; will forward |
| 354 | Start mail input |

### Failures

| code | status |
| --- | --- |
| 421| Service not available; closing channel |
| 450 | mailbox unavailable (it is busy) |
| 451 | local error in processing |
| 452 | Insufficient system storage |
| 500 | Syntax error, unrecognized |
| 501 | Syntax error in parameters or arguments |
| 502 | command not implemented |
| 503 | bad sequence of commands |
| 504 | Command parameter not implemented |
| 550 | mailbox unavailable (does not exist) |
| 551 | User not local (please try <forward-path> ) |
| 552 | Exceeded storage allocation | 
| 553 | Requested action not taken (mailbox named not allowed) |
| 554 | transaction failed |

