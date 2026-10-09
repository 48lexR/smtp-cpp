# DESIGN SPECIFICATIONS

This is a brief design sheet for how I will go about implementing this project. It is best to separate it out into layers, so that it can be properly scaled and developed without much headache. 

## Connection manager

The connection manager isn't concerned with exactly what's being sent, or how. It exists solely to abstract the actual connection away from the rest of the application. That way, later layers can just use it to write data and be done with it.

## Parser 

The parser should expose a couple mechanisms for converting between 

