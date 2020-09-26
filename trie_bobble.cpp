#include<bits/stdc++.h>
using namespace std;

struct node {
    unordered_map<char, node*> mp;
    bool endOfWord;
    node() {
        unordered_map<char, node*> temp;
        mp = temp;
        endOfWord = false;
    }
};

typedef struct node node;

class Trie {
    node *root;

    public:
    unordered_map<string, int> cnt;         //Use to store the frequency of words
    vector<string> words;                   //Use to store list of words
    Trie() {
        root = new node();
    }

    void read_csv(string file_name) {
        int t = 0;
        fstream file;
        file.open(file_name, ios::in);

        string row, word;
        while(file.good()) {

            getline(file, row);
            stringstream stream(row);

            getline(stream, word, ',');
            words.push_back(word);            //string extracted

            string temp = word;
            getline(stream, word, ',');
            cnt[temp] = stoi(word);          //frequency extracted
        }
    }

    void build() {

        for(auto ind = 0; ind < words.size(); ind++) {
            node* current = root;
            string vec_word = words[ind];

            for (int i = 0; i < vec_word.size(); i++) {
                char ch = vec_word[i];
                auto temp = current->mp.find(ch);
                node* link;
                if (temp == current->mp.end()) {
                    link = new node();
                    current->mp[ch] = link;
                }
                current = link;
            }

            current->endOfWord = true;              //mark the current nodes endOfWord as true
        }
    }

    bool srch(string word) {
        node* current = root;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            auto temp = current->mp.find(ch);

            if (temp == current->mp.end()) {          //if node does not exist for given char then return false
                return false;
            }
            current = current->mp[ch];
        }

        return current->endOfWord;                  //return true of current's endOfWord is true else return false.
    }
};

int main() {
    Trie obj;
    obj.read_csv("EnglishDictionary.csv");
    obj.build();
    string word_check;
    cin>>word_check;
    if(obj.srch(word_check))
        cout<<"YES";
    else
        cout<<"NO";
}
