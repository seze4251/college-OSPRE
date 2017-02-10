//
//  Message_External.h
//  Message_External
//
//  Created by Seth on 02/09/2017.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef MESSAGE_EXTERNAL
#define MESSAGE_EXTERNAL

class Message_External {
public:
    

    
    Messege_External(unsigned int applicationProcessID) : applicationProcessID(applicationProcessID) {
        packetVersionNumber = 0;
        secondaryHeader = 0;
        sequenceFlags = 3;
    }
    
    union foo{
        struct Header {
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
        };
        char bytes[6];
    };
};


#endif


/*
 int c;
 
 //c = 0;
 c = 0xFF00FF00;
 
 10101011 110001101010101111
 FC D# A9 32
 
 Header hdr;
 hdr.packetVersionNUmber = 3;
 hd.packetType = 1
 
 
 short oct1  = 0;
 0000 0000 0000 0000
 
 oct1 = 0xE << 12;
 1110 0000 0000 0000
 oct1 = 0x7;
0000 0000 0000 0111
 oct1 <<= 13;
 1110 0000 0000 0000
 
 short temp = oct1 >> 13
 0000 0000 0000 0111
 printf((%d\n, temp);
\
 
 
 
 
 
 oct1 = 0x7;
 oct1 <<= 13;
 1110 0000 0000 0000
 
 short tmep = oct1 & 0x1FFF;
 0001 1111 1111 1111
 
 0000 0000 0000
 
 short temp2 = oct1 & 0xEFFF;
 
 
 
 
 
 
 
 Byte Buffer::
 (Message HEADER >> MESSAGE ID >> MESSAGE DATA)
 
 */
 
 
 
 
 
 
 
 
 
 
 
 
 
