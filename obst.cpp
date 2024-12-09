#include <bits/stdc++.h>
#include <string>
using namespace std;


int sum(int freq[], int i, int j);
std::string intToString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

int optimalSearchTree(vector<int>& keys, vector<int>& freq, int n, vector<vector<int> >& root) 
{ 
	  int cost[n][n];

    
    root.assign(n, vector<int>(n, -1));

    
    for (int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
        root[i][i] = i; 
    }


    for (int L = 2; L <= n; L++) {
        
        for (int i = 0; i <= n - L; i++) {
            
            int j = i + L - 1;
            cost[i][j] = INT_MAX;
            int off_set_sum = sum(freq.data(), i, j);

            
            for (int r = i; r <= j; r++) {
                
                int c = ((r > i) ? cost[i][r - 1] : 0) + 
                        ((r < j) ? cost[r + 1][j] : 0) + 
                        off_set_sum;

                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;  
                }
            }
        }
    }

    return cost[0][n - 1];
}

// A utility function to get sum of array elements freq[i] to freq[j]
int sum(int freq[], int i, int j) 
{ 
    int s = 0; 
    for (int k = i; k <= j; k++)
        s += freq[k]; 
    return s; 
}


void UserInput(vector<int>& keys, vector<int>& freq) {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;
    
    keys.resize(n);
    cout << "Enter the keys: ";
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }

    freq.resize(n);
    cout << "Enter the frequencies for each key: ";
    for (int i = 0; i < n; i++) {
        cin >> freq[i];
    }
}


void displayOBST(vector<vector<int> >& root, const vector<int>& keys, int i, int j, string parent, bool isLeft) {
    if (i > j) return;

    int r = root[i][j];
    if (parent == "ROOT") {
        cout << "Root: " << keys[r] << endl;
    } else {
        cout << "Child of " << parent << ": " << keys[r] << " (" << (isLeft ? "Left" : "Right") << ")" << endl;
    }

    
 displayOBST(root, keys, i, r - 1, intToString(keys[r]), true);
    displayOBST(root, keys, r + 1, j, intToString(keys[r]), false);
}


int main() 
{ 
    vector<int> keys, freq;
    vector<vector<int> > root; 
    UserInput(keys, freq);  

    int n = keys.size();
    cout << "Cost of Optimal BST is " << optimalSearchTree(keys, freq, n, root) << endl;

    
    cout << "OBST Structure:" << endl;
    displayOBST(root, keys, 0, n - 1, "ROOT", false);

    return 0;
}  
