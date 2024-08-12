//
// Created by Wenjie Dong on 2023-10-16.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include "Homework_4.cpp"

using namespace std;

#ifndef CODE_Experiment_4_H
#define CODE_Experiment_4_H

class Experiment_4 {
public:
    // Exp4.1 find first match position - brute force
    int bruteForce(const string& s = "abccabaccaba", const string& t = "aba") {
        string news = " " + s;
        string newt = " " + t;
        int n = s.size(), m = t.size();
        
        for (int i = 1; i <= n - m + 1; i++) {
            int j = 1;
            for (int k = i; j <= m; j++, k++) {
                if (news[k] != newt[j]) {
                    break;
                }
            }
            if (j == m + 1) {
                return i - 1;
            }
        }
        
        return -1;
    }
    
    
    // Exp4.1 find first match position - KMP original
    int originalKMP(const string& s = "abccabaccaba", const string& t = "aba") {
        string news = " " + s;
        string newt = " " + t;
        int n = s.size(), m = t.size();
        
        Homework_4 obj;
        vector<int> ne = obj.getNext(newt);
        
        for (int i = 1, j = 0; i <= n; i++) {
            if (j && news[i] != newt[j + 1]) {
                j = ne[j];
            }
            if (news[i] == newt[j + 1]) {
                j++;
            }
            if (j == m) {
                return i - m;
            }
        }
        
        return -1;
    }
    
    
    // Exp4.1 find first match position - KMP optimized
    int optimizedKMP(const string& s = "abccabaccaba", const string& t = "aba") {
        string news = " " + s;
        string newt = " " + t;
        int n = s.size(), m = t.size();
        
        Homework_4 obj;
        vector<int> ne = obj.getNext(newt);
        
        for (int i = 1, j = 0; i <= n; i++) {
            while (j && news[i] != newt[j + 1]) {
                j = ne[j];
            }
            if (news[i] == newt[j + 1]) {
                j++;
            }
            if (j == m) {
                return i - m;
            }
        }
        
        return -1;
    }
    
    
    // Exp4.2 caesar cipher
    void caesarCipher(string in = "Exp4_T4_in.txt", string out = "Exp4_T4_cipher.txt", int dx = 3) {
        string cwd = std::filesystem::current_path().string() + "\\Code\\chapter4\\";
        
        ifstream fin(cwd + in);
        ofstream fout(cwd + out);
        
        string s;
        while (getline(fin, s)) {
            string trans;
            for (char ch: s) {
                if (islower(ch)) {
                    trans += (ch - 'a' + dx) % 26 + 'a';
                } else if (isupper(ch)) {
                    trans += (ch - 'A' + dx) % 26 + 'A';
                } else {
                    cerr << "invalid character\n";
                    exit(1);
                }
            }
            fout << trans << "\n";
        }
        
        fin.close();
        fout.close();
    }
    
    
    // Exp4.2 caesar decipher
    void caesarDecipher(string cipher = "Exp4_T4_cipher.txt", string decipher = "Exp4_T4_decipher.txt", int dx = 3) {
        caesarCipher(cipher, decipher, 26 - dx);
    }
};

#endif //CODE_Experiment_4_H