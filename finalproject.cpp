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
const int ONE_SIZE = 5;
const int TWO_SIZE = 10;
const int THREE_SIZE = 12;
const int FOUR_SIZE = 15;

// Creates a data set of random numbers from 1 to 100
// IN: arr[] - array to store numbers in
// size - size of the array
void createDataSet(vector<int> &v, int size);
int intractable(vector<int> v, int size);
int heuristic(vector<int> v, int size);

int main() {
    srand(time(0));
    vector<int> one;
    vector<int> two;
    vector<int> three;
    vector<int> four;
    createDataSet(one, ONE_SIZE);
    createDataSet(two, TWO_SIZE);
    createDataSet(three, THREE_SIZE);
    createDataSet(four, FOUR_SIZE);
    
    sort(one.begin(), one.end(), greater<int>());
    auto start = std::chrono::high_resolution_clock::now();
    int oneHeuristic = heuristic(one, ONE_SIZE);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << ONE_SIZE << " items, heuristic: " << oneHeuristic << " bins" << endl;
    cout << ONE_SIZE << " items, heuristic: " << elapsed.count() << " microseconds" << endl << endl;

    sort(two.begin(), two.end(), greater<int>());
    start = std::chrono::high_resolution_clock::now();
    int twoHeuristic = heuristic(two, TWO_SIZE);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << TWO_SIZE << " items, heuristic: " << twoHeuristic << " bins" << endl;
    cout << TWO_SIZE << " items, heuristic: " << elapsed.count() << " microseconds" << endl << endl;
    
    sort(three.begin(), three.end(), greater<int>());
    start = std::chrono::high_resolution_clock::now();
    int threeHeuristic = heuristic(three, THREE_SIZE);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << THREE_SIZE << " items, heuristic: " << threeHeuristic << " bins" << endl;
    cout << THREE_SIZE << " items, heuristic: " << elapsed.count() << " microseconds" << endl << endl;
    
    sort(four.begin(), four.end(), greater<int>());
    start = std::chrono::high_resolution_clock::now();
    int fourHeuristic = heuristic(four, FOUR_SIZE);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << FOUR_SIZE << " items, heuristic: " << fourHeuristic << " bins" << endl;
    cout << FOUR_SIZE << " items, heuristic: " << elapsed.count() << " microseconds" << endl;

    cout << endl;

    sort(one.begin(), one.end());
    start = std::chrono::high_resolution_clock::now();
    int oneIntract = intractable(one, ONE_SIZE);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << ONE_SIZE << " items, intractable: " << oneIntract << " bins" << endl;
    cout << ONE_SIZE << " items, intractable: " << elapsed.count() << " microseconds" << endl << endl;

    sort(two.begin(), two.end());
    start = std::chrono::high_resolution_clock::now();
    int twoIntract = intractable(two, TWO_SIZE);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << TWO_SIZE << " items, intractable: " << twoIntract << " bins" << endl;
    cout << TWO_SIZE << " items, intractable: " << elapsed.count() << " microseconds" << endl << endl;

    sort(three.begin(), three.end());
    start = std::chrono::high_resolution_clock::now();
    int threeIntract = intractable(three, THREE_SIZE);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << THREE_SIZE << " items, intractable: " << threeIntract << " bins" << endl;
    cout << THREE_SIZE << " items, intractable: " << elapsed.count() << " microseconds" << endl << endl;

    sort(four.begin(), four.end());
    start = std::chrono::high_resolution_clock::now();
    int fourIntract = intractable(four, FOUR_SIZE);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << FOUR_SIZE << " items, intractable: " << fourIntract << " bins" << endl;
    cout << FOUR_SIZE << " items, intractable: " << elapsed.count() << " microseconds" << endl << endl;
}

void createDataSet(vector<int> &v, int size) {
    for (int i = 0; i < size; i++) {
        v.push_back(1 + (rand() % 10));
    }
}

int intractable(vector<int> v, int size) {
    vector<int> numBins;
    do {
        /* for (int i : v)
            cout << i << " ";
        cout << endl; */
        numBins.push_back(heuristic(v, size));
    } while(next_permutation(v.begin(), v.end()));
    /* cout << endl;
    for (int i : numBins)
        cout << i << endl; */
    return *min_element(numBins.begin(), numBins.end());
}

int heuristic(vector<int> v, int size) {
    vector<int> bins;
    bins.push_back(0);
    bool addedItem = false;
    for (int i = 0; i < size; i++) {
        if (bins[0] + v[i] <= BIN_SIZE) {
            //cout << "added " << i << " to 0" << endl;
            bins[0] += v[i];
            addedItem = true;
        }
        else {
            int j = 1;
            while(!addedItem && j < bins.size()) {
                if (bins[j] + v[i] <= BIN_SIZE) {
                    //cout << "added " << i << " to " << j << endl;
                    bins[j] += v[i];
                    addedItem = true;
                }
                j++;
            }
            if (!addedItem) {
                //cout << "added " << i << " to " << bins.size() << endl;
                bins.push_back(v[i]);
            }
        }
        addedItem = false;
    }
    //cout << endl;
    return bins.size();
}