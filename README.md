USC-EE450-Project_part1-sp23


1)  OS-Version: Ubuntu 22.04

2)  In this project, we are trying out socket programming using UDP in which we have one main server and two backend servers and the same main server will service 
requests of both the backend servers. The backend server is going to send the department name to the server, which in turn will search for that department 
name in its database or data stored and the send the corresponding data as response to the client that requested it. Also, there are two txt files from which the data of the departments have to be retrieved by the backend servers.

3)  Code Files:
    a)  servermain.cpp
        -   used to create a server that runs usinng UDP
        -   once the connection is set up with the client, it accepts data from that client i.e., department name.
        -   searches for the received departname name in its data and then sends the corresponding data i.e., server id which contains the 
            department, to its client by sending the status of found or not found in form of a message
        

    b)  serverA.cpp
        -   accepts department name from the user and sends a request to the server
        -   it then receives the response from server accordingly if the department name is found or not
        -   printing if the codeword can be pass or not pass
    
    c)  serverB.cpp
        -   accepts department name from the user and sends a request to the server
        -   it then receives the response from server accordingly if the department name is found or not
        -   printing if the codeword can be pass or not pass

    d) dataA.txt
        -  sample data file used for data for backend server A

    d) dataB.txt
        - sample data file used for data for backend server B


4)  The project fails when the memory is not enough for the data and functions to perform.

5)  Reused Code: There a few code snippets which have been used directly from the Geeks for Geeks socket programming and 
have been marked with the comments in the code






