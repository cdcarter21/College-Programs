#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "guess.h"
using namespace std;

int main()
{
    ifstream fs("phrases.txt");
    int phrase_count = 0;
    string phrases[1000];
    while (getline(fs,phrases[phrase_count]))
        phrase_count++;
    
    string snowmen[] = {
        "      _\n    _|_|_\n    ('_')\n+--(  :  )--+\n  (_______)\n",
        "\n     ___\n    ('_')\n+--(  :  )--+\n  (_______)\n",
        "\n     ___\n    ('_')\n+--(  :  )\n  (_______)\n",
        "\n     ___\n    ('_')\n   (  :  )\n  (_______)\n",
        "\n\n     ___\n    ('_')\n   (_____)\n",
        "\n\n\n     ___\n    ('_')\n",
    };

    std::default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    int winner = generator() % phrase_count;
    GuessingGame game(phrases[winner]);

    while (!game.isComplete() && game.getMistakes() < 6) {
        cout << snowmen[game.getMistakes()];
        cout << "Movie: " << game.getRevealed() << "\n";
        cout << "\nGuess a letter: ";
        char letter;
        cin >> letter;
        game.makeGuess(letter);
    }

    if (game.isComplete())
        cout << "\nCongratulations!\nYou got " << game.getAnswer() << " with only " << game.getMistakes() << " mistakes.\n";
    else
        cout << "\nSorry, your snowman melted\nThe answer was " << game.getAnswer() << "\n";
}