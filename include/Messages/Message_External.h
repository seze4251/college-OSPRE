//
//  Message_External.h
//  Message_External
//
//  Created by Seth on 02/09/2017.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef MESSAGE_EXTERNAL
#define MESSAGE_EXTERNAL

#include <stdio.h>

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
    
    void printHeader(FILE* logFile) {
        printMessageID(iden, logFile);
        fprintf(logFile, "Printing Message Header:\n");
        fprintf(logFile, "PacketType = %u\n",header.header_struct.packetVersionNumber);
        fprintf(logFile, "SecondaryHeader = %u\n",header.header_struct.secondaryHeader);
        fprintf(logFile, "ApplicationProcessID = %u\n",header.header_struct.applicationProcessID);
        fprintf(logFile, "SequenceFlags = %u\n",header.header_struct.sequenceFlags);
        fprintf(logFile, "PacketSequence = %u\n",header.header_struct.packetSequence);
        fprintf(logFile, "PacketDataLength = %u\n",header.header_struct.packetDataLength );
    }
    
    // Data Members
    Header_Union header;
    
    // Message ID
    MessageID iden;

    
};


#endif

 
 
 
 
 
 
 
 
 
 
 
 
