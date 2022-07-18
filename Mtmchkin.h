#ifndef MTMCHKIN_H_
#define MTMCHKIN_H_
#include <iostream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <map>
#include <memory>
#include "utilities.h"
#include "Cards/Card.h"
#include "Cards/Barfight.h"
#include "Cards/Battle.h"
#include "Cards/Dragon.h"
#include "Cards/Fairy.h"
#include "Cards/Merchant.h"
#include "Cards/Goblin.h"
#include "Cards/Pitfall.h"
#include "Cards/Treasure.h"
#include "Cards/Vampire.h"
#include "Cards/Gang.h"
#include "Exception.h"

/*
* enum CardsName class with cards name
*/
enum class CardsName {
    Barfight,
    Dragon,
    Fairy,
    Goblin,
    Merchant,
    Pitfall,
    Treasure,
    Vampire,
    Gang
};

/*
* enum PlayersName class with players name
*/
enum class PlayersName {
    Fighter,
    Rogue,
    Wizard
};


class Mtmchkin{

public:
    
    /*
    * C'tor of Mtmchkin class
    *
    * @param filename - a file which contains the cards of the deck.
    * @return
    *      A new instance of Mtmchkin.
    *      throw DeckFileInvalidSize if the number of cards is smaller than minimum number
    */
    Mtmchkin(const std::string fileName);

    /*
    * delete copy C'tor of Rogue class
    */
    Mtmchkin(const Mtmchkin& mtmchkin) = delete;

    /*
    * delete assignment operator of Rogue class
    */
    Mtmchkin& operator=(const Mtmchkin& other)= delete;
    
    /*
    * Play the next Round of the game - according to the instruction in the exercise document.
    *
    * @return
    *      void
    */
    void playRound();
    
    /*
    * Prints the leaderBoard of the game at a given stage of the game - according to the instruction in the exercise document.
    *
    * @return
    *      void
    */
    void printLeaderBoard() const;
    
    /*
    *  Checks if the game ended:
    *
    *  @return
    *          True if the game ended
    *          False otherwise
    */
    bool isGameOver() const;
    
	/*
    *  Returns the number of rounds played.
    *
    *  @return
    *          int - number of rounds played
    */
    int getNumberOfRounds() const;
    
    private:

    std::deque <std::unique_ptr<Card>> m_cardsArray;
    std::vector <std::unique_ptr<Player>> m_playerArray;
    int m_numberOfRound;
    int m_numberOfPlayers;
    std::vector <std::unique_ptr<Player>> m_winnerArray;
    std::vector <std::unique_ptr<Player>> m_looserArray;
    static const int WIN_LEVEL=10;
    static const int MINIMUM_CARDS=5;
    static const int NAME_MAX_LENGTH=15;
    static const int BUFFER=256;

    /*
    * matchAndCreateCard: create card according to string type 
    *
    * @param type - string with card type
    * @param lineNumber - the line in the file the type came from
    * @return
    *      unique pointer with the new card
    *      throw DeckFileFormatError if the card name is not valid
    */
    static std::unique_ptr<Card> matchAndCreateCard (std::string type, int lineNumber);

    /*
    * validateName: check if player name is made up of no more than 15 english letters 
    *
    * @param name - The name to check
    * @return
    *       true if the name is valid
    *       false if the name is invalid 
    */
    static bool validateName (std::string name);

    /*
    * validateClass: check if player name is made up of no more than 15 english letters 
    *
    * @param className - The class to check
    * @return
    *       true if the name is valid
    *       false if the name is invalid 
    */
    static bool validateClass (std::string className);

    /*
    * matchAndCreatePlayer: create player according to string type 
    *
    * @param type - string with card type
    * @param name - the player name
    * @return
    *      unique pointer with the new player
    */
    static std::unique_ptr<Player> matchAndCreatePlayer (std::string type, std::string name);

    /*
    * getNameAndClass: checking if name and class name of player is valid and getting them
    *                  if not asking the user for new input 
    *
    * @param *name - pointer to name variable
    * @param *className - pointer to class name variable
    * @return
    *      void
    */
    static void getNameAndClass (std::string *name, std::string *className);

    /*
    * validateSize: check if number of players in team is valid 
    *
    * @param size - The number of players in team
    * @return
    *       true if the number is valid
    *       false if the number is invalid 
    */
    static bool validateSize (std::string size);

    /*
    * createCardMap: create map contain string with card name and matched CardsName enum   
    *
    * @return
    *       map contain string with card name and matched CardsName enum
    */
    static std::map<std::string ,CardsName> createCardMap ();

    /*
    * createPlayerMap: create map contain string with player name and matched PlayersName enum   
    *
    * @return
    *       map contain string with player name and matched PlayersName enum
    */
    static std::map< std::string ,PlayersName> createPlayerMap ();

    /*
    * playMerchant: play the merchant card  
    *
    * @param merchantCard - The card to play
    * @param player - The player to play the card on
    * @return
    *       void
    */
    static void playMerchant(Merchant &merchantCard, Player &player);

    /*
    * isNumber: check if string is number 
    *
    * @param input - The string to check
    * @param player - The player to play the card on
    * @return
    *       true if the input is number
    *       false if the input is not number 
    */
    static bool isNumber (const std::string& input);

    /*
    * createCard: create card according to CardsName enum 
    *
    * @param CardsName - CardsName enum with card type
    * @param line - the line with card type
    * @return
    *      unique pointer with the new card
    *      throw DeckFileFormatError if the card name is not valid
    */
    static std::unique_ptr<Card> createCard (CardsName cardName, int line);

    /*
    * createGang: check if card is battle anf if is adding it to card gang
    *
    * @param newCard - the candidate card to add
    * @param gang - the gang to add the card to 
    * @param line - the line with candidate card
    * @return
    *      unique pointer with the new card
    *      throw DeckFileFormatError if the card name is not valid
    */
    static void createGang (Card& newCard, Gang* gang , int line);

    /*
    * fromFileToCards: reading the card file creating the card and adding it to cards array 
    *
    * @param cardsArray - the card deque
    * @param fileName - the file name of the reading file 
    * @return
    *      void
    *      throw DeckFileFormatError if there is end gang without gang or vice versa
    *      throw DeckFileNotFound if can not open the file
    */
    static void fromFileToCards (std::deque <std::unique_ptr<Card>> &cardsArray, const std::string fileName);

    /*
    * splitString: spliting input string into two different strings
    *
    * @param input - the string to split
    * @return
    *      vector with the two strings
    */
    static std::vector<std::string> splitString (std::string input);

    /*
    * bufferIsFull: check if buffer array if full
    *
    * @param array - the buffer array
    * @param array - the read line in the buffer
    * @return
    *      void
    *      throw DeckFileFormatError if the buffer array is full
    */
    static void bufferIsFull(char* array, int line);
};



#endif /* MTMCHKIN_H_ */
