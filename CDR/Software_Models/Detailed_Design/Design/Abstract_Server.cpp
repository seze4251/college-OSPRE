




class Server{
public:
    
    Server();
    
    virtual ~Server();

    virtual run() = 0;
    
private:
    MessageHandler message;
    
    
    
};



class SCComms : public Server{
public:
    
    
private:
    
    
    
    
};



class MessageHandler{
public:
    
    
    
private:
    Parser p;
    Creator c;
    ByteBuffer b;
  
};
