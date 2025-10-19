%% Project Files %%

    server.c - The server application

    client.c - The client application

!! How to Run !!

You need two separate terminal windows running simultaneously.

Step 1: Compilation
In both terminals, compile the programs:

Terminal 1 (for server):
gcc server.c -o server

Terminal 2 (for client):
gcc client.c -o client

Now you have two executable files: server and client

Step 2: Execution

Terminal 1 - Start the server first:
./server

Terminal 2 - Run the client with required arguments:
./client <IP_ADDRESS> 41139

Important Notes:

    The port number must be exactly 41139 - otherwise the program won't start

    Replace <IP_ADDRESS> with:

        127.0.0.1 or localhost if running on the same machine

        The actual server IP address if running on different machines

    The server must be running before starting the client

Step 3: Usage
Once both programs are running:

    Enter mathematical expressions in the client terminal

    The server will calculate and return the results

    That's it!

Example Usage

Terminal 1:
gcc server.c -o server
./server

Terminal 2:
gcc client.c -o client
./client 127.0.0.1 41139

Then enter your mathematical expression when prompted.



