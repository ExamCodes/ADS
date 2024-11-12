#include <iostream>
#include <vector>
#include <limits>

using namespace std;
void optimalBST(const std::vector<int>& keys, const std::vector<double>& p, const std::vector<double>& q) {
    int n = keys.size();

    
    vector<vector<double>> cost(n + 1, vector<double>(n + 1, 0));
    vector<vector<int>> root(n + 1, vector<int>(n, 0));
    vector<vector<double>> w(n + 1, vector<double>(n + 1, 0));

    
    for (int i = 0; i <= n; ++i) {
        cost[i][i] = q[i];
        w[i][i] = q[i];
    }

    
    for (int length = 1; length <= n; ++length) {
        for (int i = 0; i <= n - length; ++i) {
            int j = i + length;
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];

            
            cost[i][j] = std::numeric_limits<double>::infinity();

            
            for (int r = i; r < j; ++r) {
                double tempCost = cost[i][r] + cost[r + 1][j] + w[i][j];
                if (tempCost < cost[i][j]) {
                    cost[i][j] = tempCost;
                    root[i][j - 1] = r + 1;  
                }
            }
        }
    }

    
    std::cout << "Cost matrix:" << std::endl;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            std::cout << cost[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    
    std::cout << "\nRoot matrix:" << std::endl;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << root[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    
    std::vector<int> keys = {10, 20, 30};  
    std::vector<double> p = {0.3, 0.2, 0.1}; 
    std::vector<double> q = {0.1, 0.1, 0.1, 0.1}; 

    optimalBST(keys, p, q);

    return 0;
}

