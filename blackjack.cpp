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

        bool isEmpty(){
            return worth == 0;
        }

        std::string name(){
            return card;
        }

        void printCard(){  // Prints the name and worth of the card, will be replaced by the __str__() equivilant once I learn how it works
            std::cout << card << "; " << worth << '\n';
        }
};
class Deck{  // Class for the deck
    private:
        static const int valuesSize = 13;  // Number of Values
        static const int suitsSize = 4;  // Number of Suits
        static const int deckAmount = 6;
        static const int standardDeckSize = valuesSize * suitsSize;
        static const int deckSize = deckAmount * standardDeckSize;
        std::string values[valuesSize] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};  // Gives me an error when I input the above variable instead of the 13
        std::string suits[suitsSize] = {"S", "H", "D", "C"};  // Same problem as above, if someone finds a nicer/cleaner solution for this feel free to message me about it
        Card deck[deckSize]; 

        int cardWorth(std::string name){  // Method for calculating a cards value based on its name
            for(int i = 0; i < 9; i++){  // If the names value is between A-9, then its worth is just the index + 1, obv not 100% true for aces, however not nec to calc rn
                if(name.at(0) + values[i] == name){
                    return i + 1;
                }
            }
            return 10;  // Otherwise, its value is 10
        };

        void createDeck(){  // Creates a deck with a specified amount of standard decks, without shuffling
            for(int i = 0; i < deckAmount; i++){
                for(int j = 0; j < suitsSize; j++){
                    for(int k = 0; k < valuesSize; k++){
                        std::string name = suits[j] + values[k];  // Creates a variable name combining the suit and value
                        int worth = cardWorth(name);  // Calculates the cards worth
                        Card card(name, worth);  // Initialises the card with the previously found name and worth
                        deck[(i * valuesSize * suitsSize) + (j * valuesSize) + k] = card;  // Adds card to the deck
                    }
                }
            }
            shuffleDeck();
        }


    public:

        void shuffleDeck(){  // Using the Fisher–Yates shuffle Algorithm, O(n^2), shuffles the deck
            for(int i = deckSize - 1; i > 0; i--){  // Goes through every index in the deck
                int j = rand() % (i + 1);  // Gets a random value between 0 and the current i
                Card tmp = deck[i];
                deck[i] = deck[j];
                deck[j] = tmp;
                // Switches the cards at index i and j
            }
        }

        Card cardAt(int i){
            return deck[i];
        }

        void printDeck(){  // Prints every card in the deck. Will be replaced with __str__ eqiv. once i learn how thats done
            for(int i = 0; i < deckSize; i++){
                deck[i].printCard();
            }
        }

        Deck(){  // Deck init asking for the amount of standard decks to be used for this deck
            createDeck();  // Adds actual cards to the deck
        }
};

// The below Human, Dealer and Player classes might be modified/removed, depending on how I decide to go through with it

class Human{  // Not yet implemented. Will store everything important to both the players and the dealer
    private:
        Card held[22];  // Creates a Card array of cards that will the human will hold. The reason for the 22 placeholders is that that is the max number of cards you would need for a bust
        int minimumPoints;  // Will store the minimum amount of points held
        int maximumPoints;  // Will store the maximum amount of points held
    
    public:

        std::string cardsList(){
            calculatePoints();
            std::string cards = held[0].name();
            int i = 1;
            while(!held[i].isEmpty()){
                cards += ", " + held[i].name();
                i++;
            }
            std::string extra = "";
            if (minimumPoints == maximumPoints){
                extra = " (" + std::to_string(minimumPoints) + ")";
            }
            else{
                extra = " (" + std::to_string(minimumPoints) + ", " + std::to_string(minimumPoints) + ")";
            }
            return cards + extra;
        }

        void addCard(Card card){
            int i = 0;
            while(!held[i].isEmpty()){
                i++;
            }
            held[i] = card;
        }

        bool bust(int points){
            return points > 21;
        }
        
        int maxPoints(){
            return maximumPoints;
        }

        int minPoints(){
            return minimumPoints;
        }

        Card cardAt(int i){
            return held[i];
        }

        void calculatePoints(){
            int min = 0;
            bool hasAce = false;
            for(Card card : held){
                min += card.worth;
                if (!hasAce and card.worth == 1){
                    hasAce = true;
                }
            }
            int max = min;
            if (hasAce and !bust(max + 10)){
                max += 10;
            }
            this-> minimumPoints = min;
            this-> maximumPoints = max;
        }
        
        Human(){
            
        }
};


class Dealer : public Human{  // Not yet implemented. Will store everything important to the dealer
    private:

    public:
        Dealer(){

        }

        bool isNatural(){
            return maxPoints() == 21;
        }
};

class Player : public Human{  // Not yet implemented. Will store everything important to the players
    private:
        std::string name;
        int money;
        int currentBet = 0;
    
    public:
        Player(){

        }

        Player(std::string name, int money){
            this->name = name;
            this->money = money;
        }

        void setBet(int bet){
            this->currentBet = bet;
        }

        int moneyCount(){
            return money;
        }

        void printPlayer(){
            std::cout << "Name: " << name << "\n" << "Money: €" << money << "\n";
        }

        int bet(){
            return currentBet;
        }
};

class BlackJack{
    private:
        Dealer dealer;
        Deck deck;
        Player player;
        int cardPos = 0;
    public:

    BlackJack(){
        this-> player = askInfo();
        do
        {
            playRound();
        } while (askIfAnother());
    }

    void playRound(){
        player.setBet(bet());
        
        draw();
        /*
        if (dealer.isNatural()){
            insurance();
        }
        else{
            player.plays();
            dealer.plays();
        }
        finishRound();
        */
    }

    void draw(){
        while(dealer.cardAt(1).isEmpty()){
            player.addCard(deck.cardAt(cardPos));
            cardPos++;
            dealer.addCard(deck.cardAt(cardPos));
            cardPos++;
        }
        std::cout << repeat("*", 15) << "\n";
        std::cout << "Dealer: " << dealer.cardsList() << "\n";
        std::cout << "You: " << player.cardsList() << "\n";
        std::cout << "Your bet: €" << player.bet() << "\n";
    }

    int bet(){
        std::string betToMake;
        int iBet;
        std::string sBet;
        do
        {
            do
            {
                std::cout << "Current Balance: €" << player.moneyCount() << "\n";
                std::cout << "How much do you wish to bet? (Must be a Natural Number): ";
                std::getline(std::cin, betToMake);
            } while (!isDigit(betToMake));
            iBet = std::atoi(betToMake.c_str());
            if (iBet > player.moneyCount()){
                iBet = player.moneyCount();
            }
            sBet = std::to_string(iBet);
        } while (!confirm("Are you sure you want to bet €" + sBet + "? (y/n): "));

        return iBet;
    }

    std::string repeat(std::string str, int amount){
        std::string finalStr = "";
        for (int i = 0; i < amount; i++){
            finalStr += str;
        }
        return finalStr;
    }

    bool askIfAnother(){
        std::string text = "Do you wish to play another round? (y/n): ";
        return confirm(text);
    }

    Player askInfo(){
        bool askAgain;
        std::cout << repeat("*", 10) << "\n";
        std::string name;
        std::string sMoney;
        int money;
        do
        {
            askAgain = false;
            std::cout << "What is your name?: ";
            std::getline(std::cin, name);
            do
            {
                std::cout << "What is your buy in? (Natural Numbers Only): ";
                std::getline(std::cin, sMoney);
            } while (!isDigit(sMoney));

            money = std::atoi(sMoney.c_str());
            sMoney = std::to_string(money);

            std::string text = "Name: " + name + "\n" + "Money: €" + sMoney + "\n" + "Is this correct? (y/n)" + "\n";

            if(!confirm(text)){
                askAgain = true;
            }

        } while (askAgain);


        return Player(name, money);
    }

    bool confirm(std::string text){
        std::string response;
        do
        {
            std::cout << text;
            std::getline(std::cin, response);
        } while (response != "y" && response != "n");
        return response == "y";
    }

    bool isDigit(std::string number){
        for (int i = 0; i < number.length(); i++){
            if (number.at(i) < '0' || number.at(i) > '9'){
                return false;
            }
        }
        return true;
    }

};

int main() {
    srand(time(NULL));  // Creates random seed based on time


    BlackJack bj;
}
