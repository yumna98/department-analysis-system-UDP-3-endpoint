#include <bits/stdc++.h>
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
#include <stdlib.h>
#include <unistd.h>
#include <cstdint>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 32526
#define PORTA 30526
#define PORTB 31526
#define MAXLINE 10240

using namespace std;

struct messageA{

	char dataA[MAXLINE];
	uint16_t portA;
 
};

struct messageB{

	char dataB[MAXLINE];
	uint16_t portB;
 
};

// Driver code
int main() {
    int sockfd, sockfdB, sockfdA;
    char buffer[MAXLINE],buf[MAXLINE];
    const char *hello = "Hello from server";
    struct sockaddr_in	 servaddrA, servaddrB, servaddr;
    string str="dummy string";
    struct messageA msgA;
    struct messageB msgB;
    socklen_t lenA, lenB;
    int nA,nB;
    lenA = sizeof(servaddrA);
    lenB = sizeof(servaddrB);

    // Creating socket file descriptor for mainserver
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    //Flie descriptor for server A
    if ( (sockfdA = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket A creation failed");
		exit(EXIT_FAILURE);
	}
		
    //File descriptor for serverB
    if ( (sockfdB = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket B creation failed");
		exit(EXIT_FAILURE);
	}

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&servaddrA, 0, sizeof(servaddrA));
    memset(&servaddrB, 0, sizeof(servaddrB));
    

    // Filling servermain information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    
    // Filling backend server A information
    servaddrA.sin_family = AF_INET; // IPv4
    servaddrA.sin_addr.s_addr = INADDR_ANY;
    servaddrA.sin_port = htons(PORTA);
    
    // Filling backend Server B information
    servaddrB.sin_family = AF_INET; // IPv4
    servaddrB.sin_addr.s_addr = INADDR_ANY;
    servaddrB.sin_port = htons(PORTB);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    cout<<"Main server is up and running"<<endl;
	
    
    
  while (1) {  
//------sending some data to client A and client B

sendto(sockfdA, str.c_str(), str.length(), 0, (const struct sockaddr *) &servaddrA, sizeof(servaddrA));
sendto(sockfdB, str.c_str(), str.length(), 0, (const struct sockaddr *) &servaddrB, sizeof(servaddrB));

//------------------------------------------------
	

    
        //--------------extracting data from received message------

	
        nA = recvfrom(sockfdA, &msgA, sizeof(msgA),
                     MSG_WAITALL, (struct sockaddr *)&servaddrA,
                     &lenA);
                     
        nB = recvfrom(sockfdB, &msgB, sizeof(msgB),
                     MSG_WAITALL, (struct sockaddr *)&servaddrB,
                     &lenB);
	if (nA > 0) {
        cout <<"Main server has received the department list from server A using UDP over port "<<PORT<<endl;
} else {
    std::cout << "No data received" << std::endl;
}

if (nB > 0) {
        cout <<"Main server has received the department list from server B using UDP over port "<<PORT<<endl;
} else {
    std::cout << "No data received" << std::endl;
}
	
        
        char dataA[MAXLINE];
        strcpy(dataA, msgA.dataA);
        uint16_t portA = msgA.portA;
        
        char dataB[MAXLINE];
        strcpy(dataB, msgB.dataB);
        uint16_t portB = msgB.portB;
        
        vector <string> d_listA;
	string str_dataA(dataA);
	stringstream ssA(str_dataA);
	string itemA;
	while (getline(ssA, itemA, ',')) {
		d_listA.push_back(itemA);
	}
	
	vector <string> d_listB;
	string str_dataB(dataB);
	stringstream ssB(str_dataB);
	string itemB;
	while (getline(ssB, itemB, ',')) {
		d_listB.push_back(itemB);
	}
	
	
	
	int port;
	//Print the department list
	
		
		cout<<"Server A"<<endl;
		for(const auto& s : d_listA){
		cout<<s<<" ";
		cout<<endl;
		}
		
	cout<<endl;
        
              
		cout<<"Server B "<<endl;
		for(const auto& s : d_listB){
		cout<<s<<" ";
		cout<<endl;
		}
		
		cout<<endl;
	
//---------------------------------------------------------

 	string searchElement;
        cout<<"Enter Department Name:"<<endl;
        cin>>searchElement;
        string s;
        int count1 = 0, count2 = 0;
        
    auto iterA = std::find(d_listA.begin(), d_listA.end(), searchElement);
    auto iterB = std::find(d_listB.begin(), d_listB.end(), searchElement);
    
    if (iterA != d_listA.end()) {
        cout <<searchElement<<" shows up in server A" <<endl;
        s = "Server A has received a request for " + searchElement;
        count1++;
    } 
        
 
     else if (iterB != d_listB.end()) {
        cout <<searchElement<<" shows up in server B" <<endl;
        s = "Server A has received a request for " + searchElement;
        count2++;
 	}
    
    else{
    	cout<<searchElement<<" does not show up in server A&B"<<endl;
    }
 
 
        //sendto() for server A
        
        if(count1>0)
        sendto(sockfdA, s.c_str(), s.length(), 0, (const struct sockaddr *) &servaddrA, sizeof(servaddrA));   	
    
    	//sendto() for server B
        if(count2>0)
        sendto(sockfdB, s.c_str(), s.length(), 0, (const struct sockaddr *) &servaddrB, sizeof(servaddrB));
    	
    	if(count1>0)
    	cout<<"Main server has sent request for "<<searchElement<<" to server A using UDP over port "<<PORT<<endl;

        if(count2>0)
    	cout<<"Main server has sent request for "<<searchElement<<" to server B using UDP over port "<<PORT<<endl;
    
   	string s1, s2;
   	char buffer1[MAXLINE];
   	char buffer2[MAXLINE];
   	
   	nA = recvfrom(sockfdA, (char *)buffer1, sizeof(msgA),
                     MSG_WAITALL, (struct sockaddr *)&servaddrA,
                     &lenA);
                     buffer1[nA] = '\0';
                     s1=buffer1;
                     
                     cout<<s1<<endl;
                     
        nB = recvfrom(sockfdB, (char *)buffer2, sizeof(msgB),
                     MSG_WAITALL, (struct sockaddr *)&servaddrB,
                     &lenB);
   	buffer2[nB] = '\0';
   	s2=buffer2;
                     
                     cout<<s2<<endl;
   	
    }
    

    return 0;
}

