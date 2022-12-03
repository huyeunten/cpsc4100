// CPSC 4100 Final Project
// Haley Uyeunten
// December __, 2022

#include <iostream>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;

const int BIN_SIZE = 15;

// Creates a data set of random numbers from 1 to 100
// IN: arr[] - array to store numbers in
// size - size of the array
void createDataSet(vector<int> &v, int size);
int intractable(vector<int> v, int size);
int heuristic(vector<int> v, int size);

int main() {
    srand(time(0));
    vector<int> ten;
    vector<int> hundred;
    vector<int> thousand;
    vector<int> tenThousand;
    createDataSet(ten, 10);
    createDataSet(hundred, 100);
    createDataSet(thousand, 1000);
    createDataSet(tenThousand, 10000);
    sort(ten.begin(), ten.end(), greater<int>());
    sort(hundred.begin(), hundred.end(), greater<int>());
    sort(thousand.begin(), thousand.end(), greater<int>());
    sort(tenThousand.begin(), tenThousand.end(), greater<int>());

    auto start = std::chrono::high_resolution_clock::now();
    int tenHeuristic = heuristic(ten, 10);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "10 items, heuristic: " << tenHeuristic << " bins" << endl;
    cout << "10 items, heuristic: " << elapsed.count() << " microseconds" << endl << endl;

    sort(ten.begin(), ten.end());
    start = std::chrono::high_resolution_clock::now();
    int tenIntract = intractable(ten, 10);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "10 items, intractable: " << tenIntract << " bins" << endl;
    cout << "10 items, intractable: " << elapsed.count() << " microseconds" << endl << endl;
    
    /* start = std::chrono::high_resolution_clock::now();
    int hundredHeuristic = heuristic(hundred, 100);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "100 items, heuristic: " << hundredHeuristic << " bins" << endl;
    cout << "100 items, heuristic: " << elapsed.count() << " microseconds" << endl << endl;
    
    start = std::chrono::high_resolution_clock::now();
    int thousandHeuristic = heuristic(thousand, 1000);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "1000 items, heuristic: " << thousandHeuristic << " bins" << endl;
    cout << "1000 items, heuristic: " << elapsed.count() << " microseconds" << endl << endl;
    
    start = std::chrono::high_resolution_clock::now();
    int tenThousandHeuristic = heuristic(tenThousand, 10000);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "10000 items, heuristic: " << tenThousandHeuristic << " bins" << endl;
    cout << "10000 items, heuristic: " << elapsed.count() << " microseconds" << endl; */
}

void createDataSet(vector<int> &v, int size) {
    for (int i = 0; i < size; i++) {
        v.push_back(1 + (rand() % 10));
    }
}

int intractable(vector<int> v, int size) {
    vector<int> numBins;
    do {
        for (int i : v)
            cout << i << " ";
        cout << endl;
        numBins.push_back(heuristic(v, size));
    } while(next_permutation(v.begin(), v.end()));
    cout << endl;
    for (int i : numBins)
        cout << i << endl;
    return *min_element(numBins.begin(), numBins.end());
}

int heuristic(vector<int> v, int size) {
    vector<int> bins;
    bins.push_back(0);
    bool addedItem = false;
    for (int i = 0; i < size; i++) {
        if (bins[0] + v[i] <= BIN_SIZE) {
            cout << "added " << i << " to 0" << endl;
            bins[0] += v[i];
            addedItem = true;
        }
        else {
            int j = 1;
            while(!addedItem && j < bins.size()) {
                if (bins[j] + v[i] <= BIN_SIZE) {
                    cout << "added " << i << " to " << j << endl;
                    bins[j] += v[i];
                    addedItem = true;
                }
                j++;
            }
            if (!addedItem) {
                cout << "added " << i << " to " << bins.size() << endl;
                bins.push_back(v[i]);
            }
        }
        addedItem = false;
    }
    cout << endl;
    return bins.size();
}