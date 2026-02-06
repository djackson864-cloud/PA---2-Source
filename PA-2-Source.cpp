#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <random>
#include <numeric>
#include <cmath>

using namespace std;
using namespace std::chrono;

// Merge sort implementation
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }

    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Function to generate Array_i of size n with random integers
vector<int> generateRandomArray(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);

    for (int i = 0; i < n; ++i) {
        arr[i] = dis(gen);
    }

    return arr;
}

//Function to clear existing content inside csv
void csvClearer(const string& filename) {
    ofstream file;
    file.open(filename, ios::trunc);  // ios::trunc = clear existing content

    file << "Input size n for Array_i,Value of n*logn,Time spent(milliseconds),Value of(n*logn)/time" << endl;
    file.close();
}

// Function to generate csv files
void generateCSVFile(const string& filename, int arraySize, int valueNLogN, double timeSpent, double valueNLogTime) {
    ofstream file;
    file.open(filename, ios::app);
    file << arraySize << "," << valueNLogN << ","  << timeSpent << ", " << scientific << setprecision(3)<< valueNLogTime << endl;
    file.close();
}


int main() {
    //Calls function to clear csv before looping
    csvClearer("Mergesort_Time.csv");

    // for loop that asks user to enter size 9 times
    for (int i = 1; i <= 9; ++i) {

        //generate random array of size 1000 with asking amount from user
        int n, array_size;
        cout << "Enter the size of the array(i) to sort(value is 1000 * i)";
        cout << endl;
        cin >> n;
        array_size = n * 1000;
        vector<int> arr = generateRandomArray(array_size);
        cout << "Generated random array with a size of " << array_size << " elements" << endl;

        // Measure time taken by merge sort
        auto start = high_resolution_clock::now();
        mergeSort(arr, 0, array_size - 1);
        auto stop = high_resolution_clock::now();
        chrono::duration<double, milli> duration = stop - start;
        cout << "Time taken for merge sort" << n << ": " << duration.count() << " milliseconds" << endl;

        //Value of n*log(base10)n
        double nlogn = array_size * log10(array_size); 
        
        //Value of n*log(base10)n divided by time
        double value = nlogn / duration.count(); 
        // Write results to CSV
            generateCSVFile("Mergesort_Time.csv", array_size, nlogn, duration.count(), value);
    }
}
