#include <iostream>


class Card{  // Class for the cards
    private:
        std::string card; // Init for cards name, ex. HA for Ace of Hearts, S9 for 9 of Spades

    public:
        int worth; // Init for cards worth, for ex. a 5 has a worth of 5, a J (Jack) has a worth of 10
        Card(std::string card, int worth){  //Init function for the Card class, asks for card name and cards worth as input
            this-> card = card;  // Sets the cards name
            this-> worth = worth;  // Sets the cards worth
        }

        void printName(){  // Prints the name of the card, will be replaced by the __str__() equivilant once I learn how it works
            std::cout << card;
        }
};
class Deck{  // Class for the deck, currently does not work
    private:
        int valuesSize = 13;  // Number of Values
        int suitsSize = 4;  // Number of Suits
        std::string values[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};  // Gives me an error when i input the above variable instead of the 13
        std::string suits[4] = {"S", "H", "D", "C"};  // Same problem as above, if someone finds a nicer/cleaner solution for this feel free to message me about it
        Card deck[52];  // Is meant to init an array for the cards of size 52, however i believe this is actually causing me problems and why the deck class does not work rn

        // I dont believe the compiler is smart enough to realise that it can store an empty Card, as Card init requires 2 inputs. This is prob the reason why deck class does not work
        // Overloading might solve this issue, ill work on it when I wake up

        int cardWorth(std::string name){  // Method for calculating a cards value based on its name
            for(int i = 0; i < 9; i++){  // If the names value is between A-9, then its worth is just the index + 1, obv not 100% true for aces, however not nec to calc rn
                if(name.at(0) + values[i] == name){
                    return i + 1;
                }
                return 10;  // Otherwise, its value is 10
            }
        };
    public:
        void initDeck(){  // Method for initialising the Deck, rn below code simply addes every possible card to deck. Randomness will be added later. Does not work yet because of issue mentioned above
            for(int i = 0; i < suitsSize; i++){
                for(int j = 0; j < valuesSize; j++){
                    std::string name = suits[i] + values[j];
                    int worth = cardWorth(name);
                    Card card(suits[i] + values[j], worth);
                    deck[(i * valuesSize) + j] = card;  // Not entierly sure this works, will need to confirm after problem from above gets fixed
                }
            }
        }

        void printCard(int index){  // Prints the name of card at specified index of deck. For debugging purposes
            deck[index].printName();
        }
};
/*
class Human{  // Not yet implemented. Will store everything important to both the players and the dealer

};
class Dealer : public Human{  // Not yet implemented. Will store everything important to the dealer

};
class Player : public Human{  // Not yet implemented. Will store everything important to the players

};
*/

int main() {
    // Below Card code works fine, the Card class seems to have been set up well
    Card card("HA", 1);
    card.printName();
    std::cout << " " << card.worth;

    // Below deck code does not work, whether there exists an init for the Deck or not. Error message does not really give too much of an insight into problem either
    // Except that the Card class is in some way related, which is why I believe line 25 to be the problematic one.

    /*
    Deck deck;  // Calling this did not work no matter what I tried, will try overloading Card class next time I work on this to see if it helps
    deck.initDeck();  // Will be moved into Decks init once problem from above is fixed
    deck.printCard(1);  // Simply put here for debuggging purposes
    return 0;
    */
}
