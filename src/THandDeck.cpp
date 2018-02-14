#include "THandDeck.h"

THandDeck::THandDeck()
{

} //ctor

THandDeck::THandDeck( int orientation ) : orientation_( orientation )
{

} //ctor

void THandDeck::show( sf::RenderWindow& window )
{   
    int i = 0;
    int j = ( 720 - ( ( size() - 1 ) * 30 + 100 ) ) / 2;
    int k = ( 520 - ( ( size() - 1 ) * 30 + 175 ) ) / 2;
    
    for ( TextureCard& card : cards_ )
    {
        card.assignTexture();

        if ( orientation_ == 0 )
            card.sprite.move( sf::Vector2f( j + ( i * 30 ), 350 ) );
        else if ( orientation_ == 1 )
            card.sprite.move( sf::Vector2f( 50, k + ( i * 30 ) ) );
        else if ( orientation_ == 2 )
            card.sprite.move( sf::Vector2f( j + ( i * 30 ), 10 ) );
        else if ( orientation_ == 3 )
            card.sprite.move( sf::Vector2f( 570, k + ( i * 30 ) ) );

        card.draw( window );
        i++;
    }
}

bool THandDeck::containsMouse( int i, sf::Event& turn )
{
    return cards_[ i ].sprite.getGlobalBounds().contains( turn.mouseButton.x, turn.mouseButton.y );
}
