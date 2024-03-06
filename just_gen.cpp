// much thanks to Mathis for the skeleton of the generator code
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> 
#include <bits/stdc++.h>
using namespace std;

const string PROBLEM_NAME = "just";

const int RANDOM_CASES = 10;
const int MAX_WORD_LEN = 2000;
const pair<int, int> LEN_BOUNDS = {1, 2000};
const pair<int, int> STRING_LEN_BOUNDS = {1, 2000};
typedef vector<string> Case;
typedef long long ll;

int findEnd(int start, string target, string &str)
{
    int t = 0, s = start;
    while(s < str.size() && t < target.size())
    {
        if(str[s] == target[t])
        {
            t++;
            if(t >= target.size()) return s;    // found the last letter
            s++;
        }

        else
        {
            s++;
        }
    }

    return s;
}

int getVal(int idx, vector<int> &arr)
{
    if(idx >= arr.size()) return 0;
    return arr[idx];
}

int solve(Case &problem)
{
    string str = problem[0];
    vector<int> memo (str.size());

    for(int i = str.size() - 1; i >= 0; i--)
    {
        memo[i] = (i == str.size() - 1 ? 0 : memo[i+1]);
        int last = str.size();
        
        for(int w = 1; w < problem.size(); w++)
        {
            if(str[i] == problem[w][0])
            {
                last = findEnd(i, problem[w], str);
                if(last != str.size())
                    memo[i] = max(memo[i], 1 + getVal(last + 1, memo));
            }
        }
    }

    return memo[0];
}

int solveAndVerify(Case &problem)
{
    if(problem.size() - 1 > LEN_BOUNDS.second || problem.size() - 1 < LEN_BOUNDS.first) cerr << "input size out of bounds (size = " << problem.size() << ")" << endl;
    if(problem[0].size() > STRING_LEN_BOUNDS.second || problem[0].size() < STRING_LEN_BOUNDS.first) cerr << "sentence size out of bounds (size = " << problem[0].size() << ")" << endl; 

    int len = 0, count = 0;
    for(int i = 1; i < problem.size(); i++)
    {
        len += problem[i].size();
        for(char c : problem[i]) if((c < 'a' || c > 'z') && c != ' ') cerr << "bad input; used character " << c << endl;
    }

    cerr << "len = " << len << endl;
    if(len > LEN_BOUNDS.second) 
        cerr << "too many characters: (total=" << len << ")" << endl;

    return solve(problem);
}

int main() {

    srand(420420420);
    // sample cases
    vector<Case> samples = {
        {"justified justice on jupiters moon thebe", "just"},

        {
            "simon says please jump and sing take on me",
            "just",
            "simple"
        }      
    };

    // custom cases
    vector<Case> custom = {
        {"t", "toxic"},
        {"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", "just", "trivial", "simple"},
        {"space spacewalk spacewear   spaceshoot  spacesuit    spaceshuttle     spacespacespacespace space space", "space"},
        {"space spacewalk spacewear   spaceshoot  spacesuit    spaceshuttle     spacespacespacespace space space", "escapespacewalk"},

        {string (2000 / 5, 's') + string ( 2000 / 5, 'p') + string (2000 / 5, 'a') + string (2000 / 5, 'c') + string (2000 / 5, 'e'), "space"},

        {"nike just do it    lays betcha cant eat just one",
        "just", "simple", "trivial"
        },

        {"just", "just", "simple", "trivial"},
        {"trivial", "just", "simple", "trivial"},
        {"simple", "just", "simple", "trivial"},
        {"just trivial simple", "just", "simple", "trivial"},
        {"just trivial simply really", "just", "simple", "trivial"},
        {"theyre toxic because they trivialize your struggles and its funny because its an inside joke", "trivial", "toxic", "funnyjoke"},
        {"you just lost the game", "yjltge"}
    };

    // justsimpletrivial until reached character limit
    // custom generated cases
    vector<string> toxic = {"just", "simple", "trivial"};
    vector<vector<int>> perm = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

    for(int p = 0; p < perm.size(); p++) // don't need to test all of these
    {
        if(rand() % 3 != 0) continue;
        string word = "";
        int w = 0;
        while(word.size() < MAX_WORD_LEN)
        {
            word += toxic[perm[p][w]];
            w = (w + 1) % 3;
        }
        word = word.substr(0, MAX_WORD_LEN);
        custom.push_back({word, toxic[0], toxic[1], toxic[2]});
    }

    // all z's as sentence and all z's as word
    string all_a (MAX_WORD_LEN, 'z');
    string half_a (MAX_WORD_LEN / 2, 'z');

    custom.push_back({all_a, all_a});

    custom.push_back({all_a, half_a});

    custom.push_back(vector<string> (2001, "z"));
    custom.back().front() = all_a;

    custom.push_back({all_a, half_a + 'z'});

    custom.push_back({all_a, "z"});
    custom.push_back({all_a, "a"});

    custom.push_back(vector<string> (2000 / 4 + 1, "just"));
    custom.back().front() = "justjustjustjustjustjustjustjust";

    // random cases x15 (toxic std dict)
    vector<Case> random;
    for (size_t tc = 0; tc < RANDOM_CASES; ++tc) {
        string str = "";

        // add toxic words
        int numToxicWords = rand() % 250;

        while(numToxicWords--)
            str += toxic[rand() % 3];
        
        int len = tc == RANDOM_CASES - 1 ? MAX_WORD_LEN : (rand() % (MAX_WORD_LEN - str.size() + 1)) + str.size();

        while(str.size() < len)
        {
            str.insert(str.begin() + (int) (rand() % (str.size() + 1)), (char) ((rand() % 26) + 'a'));
        }
        
        random.push_back({str, toxic[0], toxic[1], toxic[2]});
    }

    // random cases (all random)
    for (size_t tc = 0; tc < RANDOM_CASES; ++tc) {
        string sentence = "";

        for(int i = 0; i < MAX_WORD_LEN; i++)
            sentence += (char) ( (rand() % 26) + 'a');
        random.push_back({sentence});

        int left = MAX_WORD_LEN;
        while(left)
        {
            int len = (rand() % left) + 1;
            string word = "";
            for(int i = 0; i < len ;i++)
                word += (char) ((rand() % 26) + 'a');
            random.back().push_back(word);

            left -= len;
        }

    }

    // putting it all together
    vector<Case> all;
    all.insert(end(all), begin(samples), end(samples));
    all.insert(end(all), begin(custom), end(custom));
    all.insert(end(all), begin(random), end(random));

    for (size_t tc = 0; tc < all.size(); tc++) {
        Case current_case = all[tc];

        stringstream file_prefix;
        file_prefix << PROBLEM_NAME << setw(3) << setfill('0') << (tc + 1);

        ofstream in(file_prefix.str() + ".in");
        ofstream out(file_prefix.str() + ".out");

        in << current_case.size() - 1 << "\n";
        for (string word: current_case)
            in << word << "\n";

        out << solve(current_case) << "\n";

        in.close();
        out.close();
    }

    return 0;
}