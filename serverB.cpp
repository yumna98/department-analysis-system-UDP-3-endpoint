// Client side B implementation of UDP client-server model

#include<iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <errno.h>
#include <string.h>
#include <string>
#include <vector>
#include <set>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_PORT 32526
#define PORTB 31526
#define MAXLINE 1024

using namespace std;

struct message {
    char buf[MAXLINE];
    uint16_t port;
    };
    
    
// Driver code
int main(void) {
	int sockfd, sockfdB, sockfdA;
	char buffer[MAXLINE];
	//const char *hello = "Hello from client";
	struct sockaddr_in servaddrB, servaddr;
	struct message msg; //instance for the department list and port to be sent
	char hello ;
	int n;
	socklen_t len;
	len = sizeof(servaddrB);
	string str1 , str2;

	
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	//Flie descriptor for B
        if ( (sockfdB = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket A creation failed");
		exit(EXIT_FAILURE);
	}
	

	 memset(&servaddr, 0, sizeof(servaddr));
         memset(&servaddrB, 0, sizeof(servaddrB));
   
    
	// Filling servermain information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	   // Filling backend server B information
	    servaddrB.sin_family = AF_INET; // IPv4
	    servaddrB.sin_addr.s_addr = INADDR_ANY;
	    servaddrB.sin_port = htons(PORTB);
    
    
   // Bind the socket with the client address
	   if (bind(sockfd, (const struct sockaddr *)&servaddrB, sizeof(servaddrB)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	    }
	
	std::cout<<"Server B is up and running on UDP on port "<<PORTB<<endl;

len = sizeof(servaddrB);

//------------receive some data from servermain-------------------	
	n = recvfrom(sockfd,(char *)buffer, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
	buffer[n] = '\0';
	str1=buffer;
	//std::cout<<"Client received first message :"<<str1<<std::endl;

//------------------------------------------------------------------
	
	//-------Reading and storing dataA.txt file---------------
	    
	    string result = "";
	    
	    
	    
	    ifstream infile("dataB.txt");
	    if (!infile.is_open()) {
		cerr << "Failed to open file\n";
		return 1;
	    }

	    // Read the data from the file into a vector
	    vector<string> data;
	    string line;
	    while (getline(infile, line)) {
		data.push_back(line);
	    }
	    
	    // Store the department names in a vector
	    vector<string> dept_names;
	    for (int i = 0; i < data.size(); i += 2) {
		dept_names.push_back(data[i]);
	    }

	    //Creating a map to store the data 
	    map<string, vector<int>> dataMap;
	    
	    // Parse the vector and store data in the map
    for (size_t i = 0; i < data.size(); i += 2) {
        string key = data[i];
        stringstream ss(data[i + 1]);
        int id;
        while (ss >> id) {
            dataMap[key].push_back(id);
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
       }
	    
	    stringstream ss;
	    int count = 0;
		for (const auto& s : dept_names) {
		    ss << s;
		    if (++count != dept_names.size()) {
			ss << ",";
		    }
		}
		string str_data = ss.str();
		//char buf[str_data.length() + 1];
		strcpy(msg.buf, str_data.c_str());
		msg.port = PORTB;

	    
	    
//------------------------------------------------------------------------	    
	string s;
	
	sendto(sockfd, &msg, sizeof(msg),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	//std::cout<<"The buffer is sending "<<msg.buf<<endl;
	cout<<"Server B has sent a department list to Main Server"<<endl;
		
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
	buffer[n] = '\0';
	s = buffer;
	
	//to search the element in the list and send the corresponding 
	//student ids to the main server
	string lastWord;

    // Find the position of the last space character
    size_t found = s.find_last_of(" ");
    if (found != std::string::npos) {
        // Extract the last word using substr()
        lastWord = s.substr(found + 1);
    } else {
        // If no space character found, the entire string is the last word
        lastWord = s;
    }
cout<<"Server B has received a request for "<<lastWord<<endl;
    //std::cout << "Last word: " << lastWord << std::endl;
    
    if (dataMap.count(lastWord) > 0) {
        cout << "IDs for " << lastWord << ": ";
        for (int id : dataMap[lastWord]) {
            cout << id << " ";
        }
        cout << endl;
    } else {
        cout << "Key not found\n";
    }
//-----------did the extraction od dept_name----
	
	// Search for a key and print its unique IDs
    
    // Search for a key and print its unique IDs
    
    auto it = dataMap.find(lastWord);
    if (it != dataMap.end()) {
        vector<int>& ids = it->second;
        sort(ids.begin(), ids.end());
        ids.erase(unique(ids.begin(), ids.end()), ids.end());

        ostringstream oss;
        oss << "There are " << ids.size() << " distinct students in  "<<lastWord<<" ";
        for (int i = 0; i < ids.size(); ++i) {
            oss << ids[i];
            if (i != ids.size() - 1) {
                oss << ", ";
            }
        }
        
        cout<<endl;
        string result = oss.str();
        cout<<"Server B found "<<ids.size() << " distinct students which are ";
        
        //cout<<"result is "<<result;
        
        sendto(sockfd, result.c_str(), sizeof(result),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
        cout <<endl <<"Server B has sent the result to the Main Server" << endl;
    } 
    
    else {
        cout << "No data found for key: " << lastWord << endl;
    }
	close(sockfd);
	return 0;
}

