//
//  OSPRE_Exceptions.h
//  OSPRE_Exceptions
//
//  Created by Seth on 2/14/2017.
//  Copyright © 2017 Seth. All rights reserved.
//


#ifndef OSPREEXCEPTIONS_H
#define OSPREEXCEPTIONS_H

#include <string>
#include <exception> // for std::exception

class CannotLocateBodyInImage : public std::exception {
public:
    CannotLocateBodyInImage(std::string error) : m_error() {}
    
    
    const char* what() { return m_error.c_str(); } // return the std::string as a const C-style string
    
private:
    std::string m_error;
}


// Link to all std::exceptions
// http://en.cppreference.com/w/cpp/error/exception

void pretendMain() {
    // Example Throws:
    try {
        //Throw Exception Class
        throw CannotLocateBodyInImage("Earth is not in Image");
        
        // Throw defualt std::exception
        throw std::runtime_error("Error Case hit");
        
    } catch (CannotLocateBodyInImage &e) {
        std::cout << "Catches only CannotLocateBodyInImage Exception";
        std::cerr << "Prints String With Expecion: (" << e.what() << ")\n";
    } catch (std::exception &e) {
        std::cout << "Catchs All std::exception exceptions";
        std::cerr << "Prints String With Expecion: (" << e.what() << ")\n";
        
    } catch (...) {
        std::cout << "Catchs Any Error and Re-Throws it using throw; command";
        throw;
    }
    
}

#endif
