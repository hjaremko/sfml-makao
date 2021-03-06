#include <iostream>

#include "PlayingStack.h"

sf::Packet& operator<<( sf::Packet& packet, const Card& card );

Card& PlayingStack::getTop()
{   
    return cards_.back();
}

sf::Packet* PlayingStack::getLastThreeInPacket()
{
    sf::Packet* cardsPacket = new sf::Packet;
    Card temp( "-", "-" );

    if ( cards_.size() >= 3 )
        *cardsPacket << cards_.at( cards_.size() - 3 ) << cards_.at( cards_.size() - 2 ) << cards_.at( cards_.size() - 1 );
    else if ( cards_.size() == 2 )
        *cardsPacket << temp << cards_.at( cards_.size() - 2 ) << cards_.at( cards_.size() - 1 );
    else if ( cards_.size() == 1 )
        *cardsPacket << temp << temp << cards_.at( cards_.size() - 1 );

    return cardsPacket;
}

bool PlayingStack::pushBack( Card card, std::string status, std::string request, Card last, int by, int turn )
{
    std::cout << "Thrown: " << card.get() << std::endl;

    if ( turn == by )
    {
        if ( getTop().getType() == card.getType() )
        {
            cards_.push_back( card );
            return true;
        }
        else
        {
            std::cout << "Wrong card! Same type only." << std::endl;
            return false;
        }
    }
    else
    {
        if ( status == "fight" )
        {

            if ( ( card.getType() == "2" || card.getType() == "3" || ( card.getType() == "K" && ( card.getColor() == "hearts" || card.getColor() == "spades" ) ) ) && getTop() == card )
            {
                cards_.push_back( card );
                return true;
            }
            else
            {
                std::cout << "Wrong card! Fighting cards only. Thrown: " << card.get() << std::endl;
                return false;
            }
        }
        else if ( status == "skip" )
        {
            if ( card.getType() == "4" )
            {
                cards_.push_back( card );
                return true;
            }
            else
            {
                std::cout << "Wrong card! Fours only. Thrown: " << card.getType() << std::endl;
                return false;
            }
        }
        else if ( status == "jack" )
        {
            if ( card.getType() == request || card.getType() == "J" )
            {
                cards_.push_back( card );
                return true;
            }
            else
            {
                std::cout << "Wrong card! Request: " << request << " Thrown: " << card.getType() << std::endl;
                return false;
            }
        }
        else
        {
            if ( cards_.size() == 0 || getTop() == card || getTop().getType() == "Q" || card.getType() == "Q" )
            {
                cards_.push_back( card );
                return true;
            }
            else
            {
                std::cout << "Wrong card!" << std::endl;
                return false;
            }
        }
    }
}

void PlayingStack::pushForce( Card card )
{   
    cards_.push_back( card );
}
