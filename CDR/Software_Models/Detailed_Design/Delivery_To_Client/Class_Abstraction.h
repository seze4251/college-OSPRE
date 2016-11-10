
class Server {
public:
    // Constructor
    Server();
    
    // Destructor
    virtual ~Server();
    
    // Will be implemented
    virtual void run() = 0;
    
private:
    Selector sel;
    Builder build;
    Parser parse;
    ByteBuffer bread;
    ByteBuffer bwrite;
    
    // Will Be implemented here
    int init();
    int openServerSocket();
    int connectToServer();
};


class Selector {
public:
    Selector();
    ~Selector();
    
    int select();
    int select(timeval* timeout);
    int selectNow();
    
private:
};


class ByteBuffer {
public:
    //Constructor
    ByteBuffer(int capacity);
    
    //Destructor
    ~ByteBuffer();
    
    void clear();
    
    void compact();
    
    void flip();
    
    int position();
    
    int limit();
    
    int getInt();
    void putInt(int i);
    
    char get();
    void put(char c);
    
private:
    char *buf;
    int length;
    char *head;
    char *tail;
};

class Builder {
public:
   
    
private:
    
};

class Parser {
public:
    
    
private:
};

class Parser_Sc : public Parser {
    
};

class Builder_Sc : public Builder_Sc {
    
};


class SCComms : public Server {
public:
    SCComms();
    ~SCComms();
    void run();
    
private:
    Builder_Sc build_sc;
    Parser_Sc parser_sc;
    
};


