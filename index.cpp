#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <vector>
using namespace std;

enum PlayOption
{
    None,
    X,
    O
};

string getPlayOptionDescription(PlayOption playOption)
{
    switch (playOption)
    {
    case X:
        return "X";
    case O:
        return "O";
    default:
        return "_";
    };
};

class Board
{
private:
    PlayOption a1 = None;

private:
    PlayOption a2 = None;

private:
    PlayOption a3 = None;

private:
    PlayOption b1 = None;

private:
    PlayOption b2 = None;

private:
    PlayOption b3 = None;

private:
    PlayOption c1 = None;

private:
    PlayOption c2 = None;

private:
    PlayOption c3 = None;

public:
    void printBoard()
    {
        string result;
        result += getPlayOptionDescription(a1) + " | " + getPlayOptionDescription(a2) + " | " + getPlayOptionDescription(a3) + "\n";
        result += getPlayOptionDescription(b1) + " | " + getPlayOptionDescription(b2) + " | " + getPlayOptionDescription(b3) + "\n";
        result += getPlayOptionDescription(c1) + " | " + getPlayOptionDescription(c2) + " | " + getPlayOptionDescription(c3) + "\n";
        cout << result << endl;
    }

public:
    void play(string coordinate, PlayOption play)
    {
        char col = coordinate[0];
        int row = stoi(coordinate.substr(1));

        switch (col)
        {
        case 'a':
            if (row == 1)
            {
                a1 = play;
            }
            else if (row == 2)
            {
                a2 = play;
            }
            else if (row == 3)
            {
                a3 = play;
            }
            break;
        case 'b':
            if (row == 1)
            {
                b1 = play;
            }
            else if (row == 2)
            {
                b2 = play;
            }
            else if (row == 3)
            {
                b3 = play;
            }
            break;
        case 'c':
            if (row == 1)
            {
                c1 = play;
            }
            else if (row == 2)
            {
                c2 = play;
            }
            else if (row == 3)
            {
                c3 = play;
            }
            break;
        default:
            break;
        }
    }

public:
    bool hasWinner()
    {
        if ((a1 != None && a1 == a2 && a2 == a3) ||
            (b1 != None && b1 == b2 && b2 == b3) ||
            (c1 != None && c1 == c2 && c2 == c3) ||
            (a1 != None && a1 == b1 && b1 == c1) ||
            (a2 != None && a2 == b2 && b2 == c2) ||
            (a3 != None && a3 == b3 && b3 == c3) ||
            (a1 != None && a1 == b2 && b2 == c3) ||
            (a3 != None && a3 == b2 && b2 == c1))
        {
            return true;
        }
        return false;
    }

public:
    bool isFull()
    {
        if (a1 != None && a2 != None && a3 != None && b1 != None && b2 != None && b3 != None && c1 != None && c2 != None && c3 != None)
        {
            return true;
        }
        return false;
    }

public:
    string getAvailableMoves(){
        string availableMoves = "";
        if(a1 == None){
            availableMoves += "a1 ";
        }

        if(a2 == None){
            availableMoves += "a2 ";
        }

        if(a3 == None){
            availableMoves += "a3 ";
        }
        
        if(b1 == None){
            availableMoves += "b1 ";
        }

        if(b2 == None){
            availableMoves += "b2 ";
        }

        if(b3 == None){
            availableMoves += "b3 ";
        }
        
        if(c1 == None){
            availableMoves += "c1 ";
        }

        if(c2 == None){
            availableMoves += "c2 ";
        }

        if(c3 == None){
            availableMoves += "c3 ";
        }

        return availableMoves;
    }
};

class Player
{
private:
    string name;

private:
    int score;

public:
    Player(string name)
    {
        this->name = name;
        this->score = 0;
    }

    string getName()
    {
        return name;
    }

    void setName(string name)
    {
        this->name = name;
    }

public:
    int getScore()
    {
        return score;
    }
    void setScore(int score)
    {
        this->score = score;
    }
};

vector<string> splitString(string& str) {
    vector<string> result;
    istringstream iss(str);
    string token;
    while (getline(iss, token, ' ')) {
        if (!token.empty()) {
            result.push_back(token);
        }
    }
    return result;
}

string getComputerInput(string availableMoves)
{
    vector<string> moves = splitString(availableMoves);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, moves.size() - 1);
    int randomIndex = dis(gen);
    return moves[randomIndex];
}

int main()
{
    Player human("Human");
    Player computer("Computer");

    while (true)
    {
        cout << "\nNEW GAME\n" << endl;
        cout << "Type 'exit' to quit" << endl;

        Board board;

        while (true)
        {
            string availableMoves = board.getAvailableMoves();

            cout << "\n" << endl;
            board.printBoard();
            cout << "\n" << endl;
            cout << "Score:" << endl;
            cout << " - Human(X): " << human.getScore() << endl;
            cout << " - Computer(O): " << computer.getScore() << endl;
            cout << "\n" << endl;

            string coordinate;
            cout << "Available moves: " << availableMoves << endl;
            cout << "Input coordinate: ";
            cin >> coordinate;

            if (coordinate == "exit")
            {
                cout << "Bye!" << endl;
                 return 0;
            }

            board.play(coordinate, PlayOption::X);
            if (board.hasWinner())
            {
                human.setScore(human.getScore() + 1);
                cout << "Human won" << endl;
                break;
            }

            string computerPlay = getComputerInput(board.getAvailableMoves());
            cout << "Compuser plays " << computerPlay << endl;
            board.play(computerPlay, PlayOption::O);
            cout << "\n" << endl;
            if (board.hasWinner())
            {
                computer.setScore(computer.getScore() + 1);
                cout << "Computer won" << endl;
                break;
            }

            if (board.isFull())
            {
                cout << "Draw" << endl;
                break;
            }
        }

    }
    return 0;
}
