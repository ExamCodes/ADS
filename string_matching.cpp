#include <iostream>
#include <vector>
#include <string>
using namespace std;


class StringMatching {
public:
    
    vector<int> kmpSearch(const string& text, const string& pattern) {
        int n = text.size();
        int m = pattern.size();
        vector<int> lps = computeLPS(pattern);
        vector<int> occurrences;

        int i = 0, j = 0;
        while (i < n) {
            if (text[i] == pattern[j]) {
                i++;
                j++;
            }

            if (j == m) {
                occurrences.push_back(i - j);
                j = lps[j - 1];
            } else if (i < n && text[i] != pattern[j]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return occurrences;
    }

    
    vector<int> rabinKarp(const string& text, const string& pattern, int prime = 101) {
        int n = text.size();
        int m = pattern.size();
        int d = 256; 
        int h = 1;
        int pHash = 0; 
        int tHash = 0; 
        vector<int> occurrences;

        
        for (int i = 0; i < m - 1; i++)
            h = (h * d) % prime;

        
        for (int i = 0; i < m; i++) {
            pHash = (d * pHash + pattern[i]) % prime;
            tHash = (d * tHash + text[i]) % prime;
        }

        
        for (int i = 0; i <= n - m; i++) {
            
            if (pHash == tHash) {
                if (text.substr(i, m) == pattern) {
                    occurrences.push_back(i);
                }
            }

            
            if (i < n - m) {
                tHash = (d * (tHash - text[i] * h) + text[i + m]) % prime;
                if (tHash < 0)
                    tHash += prime;
            }
        }

        return occurrences;
    }

    
    void menu() {
        while (true) {
            cout << "\nString Matching Algorithms Menu:\n";
            cout << "1. KMP Algorithm\n";
            cout << "2. Rabin-Karp Algorithm\n";
            cout << "3. Exit\n";

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                string text, pattern;
                cout << "Enter the text: ";
                cin.ignore(); 
                getline(cin, text);
                cout << "Enter the pattern: ";
                getline(cin, pattern);
                vector<int> result = kmpSearch(text, pattern);
                if (!result.empty()) {
                    cout << "Pattern found at indices: ";
                    for (int index=0;index<result.size();index++)
                        cout << result[index]<< " ";
                    cout << endl;
                } else {
                    cout << "Pattern not found.\n";
                }
            } else if (choice == 2) {
                string text, pattern;
                cout << "Enter the text: ";
                cin.ignore(); 
                getline(cin, text);
                cout << "Enter the pattern: ";
                getline(cin, pattern);
                vector<int> result = rabinKarp(text, pattern);
                if (!result.empty()) {
                    cout << "Pattern found at indices: ";
                    for (int index=0;index<result.size();index++)
                        cout << result[index] << " ";
                    cout << endl;
                } else {
                    cout << "Pattern not found.\n";
                }
            } else if (choice == 3) {
                cout << "Exiting.\n";
                break;
            } else {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }

private:
    
    vector<int> computeLPS(const string& pattern) {
        int m = pattern.size();
        vector<int> lps(m, 0);
        int length = 0;
        int i = 1;

        while (i < m) {
            if (pattern[i] == pattern[length]) {
                length++;
                lps[i] = length;
                i++;
            } else {
                if (length != 0) {
                    length = lps[length - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }
};

int main() {
    StringMatching sm;
    sm.menu();
    return 0;
}
