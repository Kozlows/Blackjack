#include <iostream>


class Card{  // Class for the cards
    private:
        std::string card; // Init for cards name, ex. HA for Ace of Hearts, S9 for 9 of Spades

    public:
        int worth; // Init for cards worth, for ex. a 5 has a worth of 5, a J (Jack) has a worth of 10

        Card(){  // Default Card init for creating placeholders for a card, for arrays or other reasons
            this->card = "Empty";
            this-> worth = 0;
        }

        Card(std::string card, int worth){  //Init function for the Card class, asks for card name and cards worth as input
            this-> card = card;  // Sets the cards name
            this-> worth = worth;  // Sets the cards worth
        }

        void printCard(){  // Prints the name and worth of the card, will be replaced by the __str__() equivilant once I learn how it works
            std::cout << card << "; " << worth << '\n';
        }
};
class Deck{  // Class for the deck
    private:
        int valuesSize = 13;  // Number of Values
        int suitsSize = 4;  // Number of Suits
        std::string values[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};  // Gives me an error when I input the above variable instead of the 13
        std::string suits[4] = {"S", "H", "D", "C"};  // Same problem as above, if someone finds a nicer/cleaner solution for this feel free to message me about it
        Card *pDeck = NULL;  // Creates a pointer to a card class variable, this will be a Card array storing every card using dynamic memory
        int deckSize = valuesSize * suitsSize;  // Creates a variable which will mention the deck size, being 52 on init

        int cardWorth(std::string name){  // Method for calculating a cards value based on its name
            for(int i = 0; i < 9; i++){  // If the names value is between A-9, then its worth is just the index + 1, obv not 100% true for aces, however not nec to calc rn
                if(name.at(0) + values[i] == name){
                    return i + 1;
                }
            }
            return 10;  // Otherwise, its value is 10
        };

        void createDeck(int amountOfDecks){  // Creates a deck with a specified amount of standard decks, without shuffling
            for(int i = 0; i < amountOfDecks; i++){
                for(int j = 0; j < suitsSize; j++){
                    for(int k = 0; k < valuesSize; k++){
                        std::string name = suits[j] + values[k];  // Creates a variable name combining the suit and value
                        int worth = cardWorth(name);  // Calculates the cards worth
                        Card card(name, worth);  // Initialises the card with the previously found name and worth
                        pDeck[(i * valuesSize * suitsSize) + (j * valuesSize) + k] = card;  // Adds card to the deck
                    }
                }
            }
        }

        void shuffleDeck(){  // Using the Fisher–Yates shuffle Algorithm, O(n^2), shuffles the deck
            for(int i = deckSize - 1; i > 0; i--){  // Goes through every index in the deck
                int j = rand() % (i + 1);  // Gets a random value between 0 and the current i
                Card tmp = pDeck[i];
                pDeck[i] = pDeck[j];
                pDeck[j] = tmp;
                // Switches the cards at index i and j
            }
        }

    public:

        void deleteDeck(){  // Method to be called when finished playing blackjack, as pDeck uses dynamic memory
            delete[] pDeck;
        }

        void printDeck(){  // Prints every card in the deck. Will be replaced with __str__ eqiv. once i learn how thats done
            for(int i = 0; i < deckSize; i++){
                pDeck[i].printCard();
            }
        }

        

        Deck(){  // Default init for deck incase I will need a placeholder for setting up an array

        }

        Deck(int amountOfDecks){  // Deck init asking for the amount of standard decks to be used for this deck
            this->deckSize *= amountOfDecks;  // Updates deck size
            pDeck = new Card[amountOfDecks * 52];  // Sets the deck variable into a Card variable using dynamic memory
            createDeck(amountOfDecks);  // Adds actual cards to the deck
            shuffleDeck();  // Shuffles the deck
        }
};

// The below Human, Dealer and Player classes might be modified/removed, depending on how I decide to go through with it

class Human{  // Not yet implemented. Will store everything important to both the players and the dealer
    private:
        Card held[22];  // Creates a Card array of cards that will the human will hold. The reason for the 22 placeholders is that that is the max number of cards you would need for a bust
        int minPoints = 0;  // Will store the minimum amount of points held
        int maxPoints = 0;  // Will store the maximum amount of points held
    /*
    // Below methods might be removed/moved to a different class
    public:
        void hit(){

        }

        void stand(){

        }

        void split(){

        }

        void doubleDown(){

        }
    */
};

/*
class Dealer : private Human{  // Not yet implemented. Will store everything important to the dealer
};
/*
class Player : private Human{  // Not yet implemented. Will store everything important to the players

};
class Blackjack{  // Not yet implemented. Will be the main program for the game

};
*/

int main() {
    srand(time(NULL));  // Creates random seed based on time


    Deck deck(3);  // Creates a deck the size of 3 standard decks, 3 * 52, and shuffles them
    deck.printDeck();  // Prints every card in this deck


    deck.deleteDeck();  // Deletes dynamic memory usage
}
