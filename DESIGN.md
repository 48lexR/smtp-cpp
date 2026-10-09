# DESIGN SPECIFICATIONS

This is a brief design sheet for how I will go about implementing this project. It is best to separate it out into layers, so that it can be properly scaled and developed without much headache. 

## Connection manager

The connection manager isn't concerned with exactly what's being sent, or how. It exists solely to abstract the actual connection away from the rest of the application. That way, later layers can just use it to write data and be done with it.

## Parser 

The parser should parse commands and then pass them up to the Client. That way the Client is only concerned with managing the actual SMTP state machine. The parser will do the actual hard work here.

## Client

The Client is the easiest part, it will use the connection manager and the parser to manage the SMTP state machine (as outlined in RFC 821.) 
