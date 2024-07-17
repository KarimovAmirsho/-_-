#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <map>
using namespace std;


class Gallows
{
    ifstream input;
    const string word;
    map<char, vector<size_t>> posMap;
    string searchWord;

    static const vector<string> images;

    enum steps : size_t
    {
        BEGIN,
        ONE, TWO, THREE, FOR, FIVE, SIX, SEVEN,
        END
    } m_step = BEGIN;

    enum result : size_t
    {
        LOSE, WIN
    } m_res = LOSE;

    void FillMap()
    {
        size_t pos{};
        for (char ch :word)
            posMap[ch].emplace_back(pos++);
    }

    char getChar()
    {
        cout << "Enter one character: ";
        char ch{}; cin >> ch;

        return posMap.find(ch) != posMap.cend() ? ch : '\0';
    }

    friend steps& operator++(steps&);
public:
    Gallows(const string& filename = "words.txt") :
        input(filename),
       word(
            istream_iterator<char>(input),
            istream_iterator<char>()
        ),
        searchWord(word.size(), '*')
    {
        FillMap();
    };

    void Play()
    {
        while (m_step != END)
        {
            system("cls");
            cout << "Your word is: " << searchWord << '\n' << endl;
            cout << images[m_step] << endl;

            if (char ch{ getChar() })
            {
                const vector<size_t>& vec{ posMap[ch] };
                for (size_t i{}, end{ vec.size() }; i < end; ++i)
                    searchWord[vec[i]] = ch;

                posMap.erase(ch);

                if (searchWord.find('*') == string::npos)
                    m_step = END, m_res = WIN;
            }
            else
                ++m_step;
        }

        system("cls");
        cout << "\nThe word is: " <<word << endl;
        cout << "You are " << (m_res == WIN ? "winner.\n" : "loser.\n") << endl;
    }
};

Gallows::steps& operator++(Gallows::steps&);

int main()
{
    Gallows game;
    game.Play();

    system("pause");
}

Gallows::steps& operator++(Gallows::steps& st)
{
    size_t tmp = st;
    return st = static_cast<Gallows::steps>(++tmp);
}

const vector<string> Gallows::images
{
    {   },
    {
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        O             $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        O             $\n"
        "      /   \\           $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        O             $\n"
        "      / | \\           $\n"
        "        |             $\n"
        "                      $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    },
    {
        "        $$$$$$$$$$$$$$$\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        |             $\n"
        "        O             $\n"
        "      / | \\           $\n"
        "        |             $\n"
        "       / \\            $\n"
        "                      $\n"
        "                      $\n"
        " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
        " $                          $\n"
    }
};
