Question :
2: Develop a game , where multiuser participate in the game. Server has 5 question with each question four options. if users connected to the server, server start sending the question one by one with a timestamp reply of 1 minute. If multiuser playing the game, then winner decided by the server based on the average minimum time taken a client to reply all answers. If  client gives a wrong reply to anyone of the answers, then server send a message to client "better luck next time" and terminate the connection of the client.

Note:
Waits for 5 valid finishers(all answers correct), then round is complete and winner is choosen and server needs to be restarted
If answer after 1 minute, then discarded, isn't automatically disconnected after 1 min, waits for a answer
