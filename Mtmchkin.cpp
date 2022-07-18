#include "Mtmchkin.h"
#include <iostream>
#include <fstream>
#include <memory>

std::map< std::string ,CardsName> Mtmchkin::createCardMap ()
{
    std::map< std::string ,CardsName> CardMap;
    CardMap["Barfight"]=CardsName::Barfight;
    CardMap["Dragon"]= CardsName::Dragon;
    CardMap["Fairy"]=CardsName::Fairy;
    CardMap["Goblin"]=CardsName::Goblin;
    CardMap["Merchant"]=CardsName::Merchant;
    CardMap["Pitfall"]=CardsName::Pitfall;
    CardMap["Treasure"]=CardsName::Treasure;
    CardMap["Vampire"]=CardsName::Vampire;
    CardMap["Gang"]=CardsName::Gang;
    return CardMap;
}

std::map< std::string ,PlayersName> Mtmchkin::createPlayerMap ()
{
    std::map< std::string ,PlayersName> PlayerMap;
    PlayerMap["Fighter"]=PlayersName::Fighter;
    PlayerMap["Rogue"]= PlayersName::Rogue;
    PlayerMap["Wizard"]=PlayersName::Wizard;
    return PlayerMap;
}
std::unique_ptr<Card> Mtmchkin::createCard (CardsName cardName, int line)
{
    switch (cardName)
    {
        case CardsName::Barfight:
            return std::unique_ptr<Barfight>(new Barfight());
            break;

        case CardsName::Dragon:
            return std::unique_ptr<Dragon>(new Dragon());
            break;
        
        case CardsName::Fairy:
            return std::unique_ptr<Fairy>(new Fairy());
            break;
        
        case CardsName::Goblin:
            return std::unique_ptr<Goblin>(new Goblin());
            break;

        case CardsName::Merchant:
            return std::unique_ptr<Merchant>(new Merchant());
            break;

        case CardsName::Pitfall:
            return std::unique_ptr<Pitfall>(new Pitfall());
            break;

        case CardsName::Treasure:
            return std::unique_ptr<Treasure>(new Treasure());
            break;

        case CardsName::Vampire:
            return std::unique_ptr<Vampire>(new Vampire());
            break;

        case CardsName::Gang:
            return std::unique_ptr<Gang>(new Gang());
            break;

        default :
            throw DeckFileFormatError(line);
    }

}

std::unique_ptr<Card> Mtmchkin::matchAndCreateCard (std::string type, int lineNumber)
{
    std::map< std::string ,CardsName> CardMap=createCardMap();
    std::map<std::string ,CardsName>::iterator it;
	it = CardMap.find(type);
    if (it != CardMap.end())
	{
        return createCard(it->second,lineNumber);
    }
    else
    {
        throw DeckFileFormatError(lineNumber);
    }
}

std::unique_ptr<Player> Mtmchkin::matchAndCreatePlayer (std::string type, std::string name)
{
    std::map< std::string ,PlayersName> PlayerMap=createPlayerMap();
    switch (PlayerMap[type])
    {
        case PlayersName::Fighter:
            return std::unique_ptr<Fighter>(new Fighter(name));
            break;
        case PlayersName::Rogue:
            return std::unique_ptr<Rogue>(new Rogue(name)); 
            break;
        
        default:
            return std::unique_ptr<Wizard>(new Wizard(name));
            break;    

    }
}


bool Mtmchkin::validateName (std::string name)
{   
    for (const char single : name) 
    {
        if (!isalpha(single))
        {
            return false;
        }
    }
    if (name.length()>NAME_MAX_LENGTH)
    {
        return false;
    }
    return true;

}
bool Mtmchkin::validateClass (std::string className)
{
    if (className== "Fighter" || className== "Rogue" || className== "Wizard")
    {
        return true;
    }
    return false;
}


std::vector<std::string> Mtmchkin::splitString (std::string input)
{
    std::stringstream test(input);
    std::string spaceString;
    std::vector<std::string> splitString;
    while(std::getline(test, spaceString, ' '))
    {
        splitString.push_back(spaceString);
    }
    return splitString;
}

void Mtmchkin::getNameAndClass (std::string *name, std::string *className)
{
    std::string input;
    std::getline(std::cin, input);
    *name=(splitString(input))[0];
    *className=(splitString(input))[1];
    while (!validateName(*name) || !validateClass(*className))
    {
        if (validateName(*name)==false)
        {
            printInvalidName();
        }
        else
        {
            printInvalidClass();
        }
        std::string input;
        std::getline(std::cin, input);
        *name=(splitString(input))[0];
        *className=(splitString(input))[1];   
    }

}

bool Mtmchkin::isNumber(const std::string& input)
{
    if(input=="")
    {
        return false;
    }
    int stringSize=input.length();
    for (int i = 0; i < stringSize; i++)
    {
        if (isdigit(input[i]) == false)
        {
            return false;
        }     
    }
    return true;
}

bool Mtmchkin::validateSize (std::string size)
{
    int number;
    bool isValid=true;
    if(isNumber(size)==true)
    {
        number = std::stoi(size);
        if (number>6 || number<2)
        {
            isValid=false;
        }	
    }
    else
    {
        isValid=false;
    }
    if(isValid==false)
    {
        printInvalidTeamSize();
        printEnterTeamSizeMessage();
        return isValid;
    }
    return isValid;

}

void Mtmchkin::playMerchant(Merchant &merchantCard, Player &player)
{
    printMerchantInitialMessageForInteractiveEncounter(std::cout, player.getName(), player.getCoins());
    std::string mode;
    std::getline(std::cin, mode);
    while (mode.size()!=1||!isNumber(mode)|| std::stoi(mode)<0 || std::stoi(mode)>2)
    {
        printInvalidInput();
        std::getline(std::cin, mode);
    }
    int numberMode=std::stoi(mode);
    merchantCard.setMode(numberMode);
    int beforeCoins=player.getCoins();
    merchantCard.applyEncounter(player);
    int cost=beforeCoins-(player).getCoins();
    if (cost==0 && numberMode!=0)
    {
        printMerchantInsufficientCoins(std::cout);
        merchantCard.setMode(0);
    }
    printMerchantSummary(std::cout,(player).getName(),numberMode,cost);

}

void Mtmchkin::createGang (Card& newCard, Gang* gang , int line)
{
    
    const Gang* gangCard= dynamic_cast<const Gang*>(&newCard);
    if(gangCard!=nullptr)
    {
        throw DeckFileFormatError(line+gang->gangSize());
    }
    const Dragon* dragon= dynamic_cast<const Dragon*>(&newCard);
    if (dragon!=nullptr)
    {
        gang->addElements(std::unique_ptr<Dragon>(new Dragon()));
        return;
    }
    const Goblin* goblin= dynamic_cast<const Goblin*>(&newCard);
    if (goblin!=nullptr)
    {
        gang->addElements(std::unique_ptr<Goblin>(new Goblin()));
        return;
    }
    const Vampire* vampire= dynamic_cast<const Vampire*>(&newCard);
    if (vampire!=nullptr)
    {
        gang->addElements(std::unique_ptr<Vampire>(new Vampire()));
        return;
    }
    else
    {
        throw DeckFileFormatError(line+gang->gangSize());
    }
    
    
}

void Mtmchkin::bufferIsFull(char* array, int line)
{
    int numberOfChars = 0;
    while (*array++)
    {
        numberOfChars++;
    }
    if(numberOfChars==BUFFER-1)
    {
        throw DeckFileFormatError(line);
    }
   
}

void Mtmchkin::fromFileToCards (std::deque <std::unique_ptr<Card>> &cardsArray, const std::string fileName)
{
    std::ifstream sourceFile(fileName);
    bool gangMode=false;
    if (!sourceFile)
    {
        throw DeckFileNotFound();
    }
    char line [BUFFER];
    std::unique_ptr<Gang> gang;
    while (sourceFile.getline(line, sizeof(line)))
    {
        std::string check(line);
        if (check=="EndGang")
        {
            if(gangMode==false)
            {
                throw DeckFileFormatError(cardsArray.size()+1);
            }
            else
            {
                gangMode=false;
                cardsArray.push_back(std::move(gang));
                continue;
            }
        }
        std::unique_ptr<Card> newCard=matchAndCreateCard(line, cardsArray.size()+1);
        if(gangMode!=true)
        {
            
            Card* temp=(newCard.get())->clone();
            Gang* gangCast = dynamic_cast<Gang*>(temp);
            if (gangCast!=nullptr)
            {
                gangMode=true;
                gang = std::unique_ptr<Gang>(new Gang());
                
            }
            else
            {
                cardsArray.push_back(std::move(newCard));
            }
            delete temp;
                
        }
        else
        {
            createGang((*newCard.get()),gang.get(),cardsArray.size()+1);
        }
        
    }
    bufferIsFull(line,cardsArray.size()+1);
    if(gangMode==true)
    {
        throw DeckFileFormatError(cardsArray.size()+1+gang->gangSize());
    }

}

Mtmchkin::Mtmchkin(const std::string fileName): m_numberOfRound(1)
{
    printStartGameMessage();
    std::ifstream source(fileName);
    fromFileToCards(m_cardsArray,fileName);
    if (m_cardsArray.size()<MINIMUM_CARDS)
    {
        throw DeckFileInvalidSize(); 
    }
    printEnterTeamSizeMessage();
    std::string input;
    do
    {
        std::getline(std::cin, input);
    } 
    while (!validateSize(input));
    m_numberOfPlayers=std::stoi(input);
    std::string playerName;
    std::string playerClass;
    for (int i = 0; i < m_numberOfPlayers; i++)
    {
        printInsertPlayerMessage();
        getNameAndClass(&playerName, &playerClass);
        std::unique_ptr<Player> newPlayer=matchAndCreatePlayer(playerClass,playerName);
        m_playerArray.push_back(std::move(newPlayer));
    }
  
}
void Mtmchkin::playRound()
{
    printRoundStartMessage(m_numberOfRound);
    std::vector<std::unique_ptr<Player>>::iterator i=m_playerArray.begin();
    while( i !=m_playerArray.end())
    {
        printTurnStartMessage((**i).getName());
        Card* temp=((m_cardsArray.front()).get())->clone();
        Merchant* merchantCast= dynamic_cast<Merchant*>(temp);
        if (merchantCast!=nullptr)
        {
            playMerchant(*merchantCast,**i);
        }
        else
        {
            m_cardsArray.front()->applyEncounter(**i);
        }
        delete temp;
         
        if((*i)->getLevel()==WIN_LEVEL)
        {
            m_winnerArray.push_back(std::move(*i));
            m_playerArray.erase(i);
        }
        else if((*i)->isKnockedOut()==true)
        {
            m_looserArray.insert(m_looserArray.begin(),std::move(*i));
            m_playerArray.erase(i);
        }
        else
        {
            ++i;
        }
        m_cardsArray.push_back(std::move(m_cardsArray.front()));
        m_cardsArray.pop_front();
    }
    if (Mtmchkin::isGameOver()==true)
    {
        printGameEndMessage();
    }
    else
    {
        m_numberOfRound++;
    }


}

int Mtmchkin::getNumberOfRounds() const
{
    return m_numberOfRound-1;
}


void Mtmchkin::printLeaderBoard() const
{
    printLeaderBoardStartMessage();
    int rank=1;
    for (std::vector<std::unique_ptr<Player>>::const_iterator it=m_winnerArray.begin(); it !=m_winnerArray.end(); ++it)
    {
        printPlayerLeaderBoard(rank, **it);
        rank++;
    }
    for (std::vector<std::unique_ptr<Player>>::const_iterator it=m_playerArray.begin(); it !=m_playerArray.end(); ++it)
    {
        printPlayerLeaderBoard(rank, **it);
        rank++;
    }
    for (std::vector<std::unique_ptr<Player>>::const_iterator it=m_looserArray.begin(); it !=m_looserArray.end(); ++it)
    {
        printPlayerLeaderBoard(rank, **it);
        rank++;
    }
}

bool Mtmchkin::isGameOver() const
{
    int outPlayers=m_looserArray.size()+m_winnerArray.size();
    if(outPlayers==m_numberOfPlayers)
    {
        return true;
    }
    return false;

}
