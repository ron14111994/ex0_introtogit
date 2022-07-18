#ifndef Exception_H_
#define Exception_H_
#include <iostream>
#include <exception> 

/*
* DeckFileNotFound exception
*/
class DeckFileNotFound : public std::exception
{
    public:
    /*
    * what: return exception error 
    *
    * @return
    *      char* with exception error
    */
    const char* what() const noexcept override
    {
        return "Deck File Error: File not found";
    }
};

/*
* DeckFileFormatError exception
*/
class DeckFileFormatError : public std::exception  
{
    public:
    /*
    * C'tor of DeckFileFormatError class
    *
    * @param line - The line with the error.
    * @return
    *      A new instance of DeckFileFormatError.
    */
    DeckFileFormatError(int line):m_line(line)
    {
        m_error="Deck File Error: File format error in line ";
        m_error+=std::to_string(m_line);
    }

    /*
    * what: return exception error 
    *
    * @return
    *      char* with exception error
    */
    const char* what() const noexcept override 
    {
        return m_error.c_str(); 
    }

    private:
    int m_line;
    std::string m_error;
};

/*
* DeckFileInvalidSize exception
*/
class DeckFileInvalidSize :public std::exception 
{
    public:
    /*
    * what: return exception error 
    *
    * @return
    *      char* with exception error
    */
    const char* what() const noexcept override
    {
        return "Deck File Error: Deck size is invalid";
    }

};

/*
* PlayerInvalidName exception
*/
class PlayerInvalidName :public std::exception 
{
    public:
    /*
    * what: return exception error 
    *
    * @return
    *      char* with exception error
    */
    const char* what() const noexcept override
    {
        return "Player Name Error: Name is invalid";
    }

};

#endif //EX4_Exception_H
