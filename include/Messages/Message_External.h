//
//  Message_External.h
//  Message_External
//
//  Created by Seth on 02/09/2017.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef MESSAGE_EXTERNAL
#define MESSAGE_EXTERNAL

#include "MessageID.h"

class Message_External {
public:
    
    union Header_Union {
        struct Header_Struct {
            unsigned int packetVersionNumber : 3; //Always 0
            unsigned int packetType : 1;  // Reporting 0, Requesting 1
            unsigned int secondaryHeader : 1; // 0
            unsigned int applicationProcessID : 11; // Idle Packets all 1s
            // Configured for S/C COmms and Spacecraft
            
            unsigned int sequenceFlags : 2;
            // d)	‘11’ if the Space Packet contains unsegmented User Data.
            
            unsigned int packetSequence : 14;
            // Increment by 1 and start over once reach a certin value
            
            unsigned int packetDataLength : 16;
            // C = (Total Number of Octets in the Packet Data Field) – 1
        } header_struct;
        char bytes[6];
    };

    // Constructor
    Message_External(unsigned int applicationProcessID, MessageID iden) {
        header.header_struct.applicationProcessID = applicationProcessID;
        header.header_struct.packetVersionNumber = 0;
        header.header_struct.secondaryHeader = 0;
        header.header_struct.sequenceFlags = 3;
        this->iden = iden;
    }
    
    void printHeader() {
        printMessageID(iden);
        std::cout << "Printing Message Header:" << std::endl;
        std::cout << "packetVersionNumber = " << header.header_struct.packetVersionNumber << std::endl;
        std::cout << "PacketType = " << header.header_struct.packetType << std::endl;
        std::cout << "SecondaryHeader = " << header.header_struct.secondaryHeader << std::endl;
        std::cout << "ApplicationProcessID = " << header.header_struct.applicationProcessID << std::endl;
        std::cout << "SequenceFlags = " << header.header_struct.sequenceFlags << std::endl;
        std::cout << "PacketSequence = " << header.header_struct.packetSequence << std::endl;
        std::cout << "PacketDataLength = " << header.header_struct.packetDataLength << std::endl;
        
        std::cout<< std::endl << std::endl;
    }
    
    // Data Members
    Header_Union header;
    
    // Message ID
    MessageID iden;

    
};


#endif

 
 
 
 
 
 
 
 
 
 
 
 
