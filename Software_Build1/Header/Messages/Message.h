//
//  Messages.h
//  Messages
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef MESSAGES_H
#define MESSAGES_H



class Message {
public:
    clock_t timestamp;
};


class PointingRequest : public Message {
public:
    bool pointAtEarth; // If true point towards Earth, If False point towards moon
    
    PointingRequest(bool point) {
        pointAtEarth = point;
    }
};

//Need to find the copy vector method!!
class SolutionMessage : public Message {
public:
    std::vector <double> position;
    std::vector <double> positionError;
    std::vector <double> velocity;
    std::vector <double> velocityError;
    double earthScMoonAngle;
    
    SolutionMessage(std::vector position, std::vector positionError, std::vector velocity,
                    std::vector velocityError, double earthScMoonAngle) {
        this -> position = position;
        this -> positionError = positionError;
        this -> velocity = velocity;
        this -> velocityError = velocityError;
        this -> earthScMoonAngle = earthScMoonAngle;
    }
};

// Not quite sure how ephemris is going to be passed to us!
class EphemerisMessage : public Message {
public:
    char * ephem;
    
    EphemerisMessage(char * ephem) {
        ephem = new sizeof(*ephem);
        strcpy(ephem, this -> ephem, sizeof(*ephem));
    }
    
    ~EphemerisMessage() {
        free(ephem);
    }
};

class SpacecraftStatus : public Message {
public:
    std::vector <double> quat;
    std::vector <double> angularVelocity;
    double sunAngle;
    clock_t time;
    bool active;
    
    SpacecraftStatus(bool active, bool healthy, char * message) {
        this -> active = active;
        this -> healthy = healthy;
        this -> message = new sizeof(*message);
        strcpy(message, this -> message, sizeof(*message));
    }
    
    ~SpacecraftStatus() {
        free(message);
    }
};


class ProccessHealthAndStatusResponse : public Message {
public:
    bool healthy;
    ErrorCode error;
    
    ProccessHealthAndStatusResponse(bool active, bool healthy, ErrorCode error) {
        this -> healthy = healthy;
        this -> error = error;
    }
};

// Small and tight
class ProccessHealthAndStatusRequest : public Message {
public:
    ProccessHealthAndStatusRequest(bool active, bool healthy, char * message) {
        
    }
};

class ImageMessage : public Message {
public:
    bool active; // True if On, False if Off
    bool healthy; // True if Healthy, False if sick
    char * message;
    
    ImageMessage(bool active, bool healthy, char * message) {
        this -> active = active;
        this -> healthy = healthy;
        this -> message = new sizeof(*message);
        bcopy(message, this -> message, sizeof(*message));
    }
    
    ~ImageMessage() {
        free(message);
    }
};


class ImageAdjustment : public Message {
public:
    
    ImageAdjustment() {
      
    }
};

class CaptureImageRequest : public Message {
public:
    
    CaptureImageRequest() {
       
    }
};



#endif
