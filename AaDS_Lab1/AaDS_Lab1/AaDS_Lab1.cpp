#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

void shellsorting(int arr[], int length)
{
    int p = 0; //operator (couldn't be asigned inside of a loop since its used outside of it later)
    for (int gap = length / 2; gap > 0; gap = gap / 2)
    {
        for (int o = gap; o < length; o++)
        {
            int compv = arr[o]; //value compared to our starting value
            for (p = o; p >= gap && arr[p - gap] > compv; p -= gap)
            {
                arr[p] = arr[p - gap];
            }
            arr[p] = compv;
        }
    }
}

void quicksort(int arr[], int l, int r)
{
    if (l < r)
    {
        int pivot = arr[l];
        int s = l;
        for (int i = l + 1; i <= r; i++)
        {
            if (arr[i] < pivot)
            {
                s++;
                swap(arr[s], arr[i]);
            }
        }
        swap(arr[s], arr[l]);
        quicksort(arr, l, s - 1);
        quicksort(arr, s + 1, r);
    }
}

void stringshellsorting(string arr[], int length)
{
    int p = 0; //operator (couldn't be asigned inside of a loop since its used outside of it later)
    for (int gap = length / 2; gap > 0; gap = gap / 2)
    {
        for (int o = gap; o < length; o++)
        {
            string compv = arr[o]; //value compared to our starting value
            for (p = o; p >= gap && arr[p - gap] > compv; p -= gap)
            {
                arr[p] = arr[p - gap];
            }
            arr[p] = compv;
        }
    }
}
int main()
{
    int n = 60000; //---
    string myarr[60000];
    string line;
    ifstream fin("numbers.txt"); //---

    for (int o = 0; o < n; o++)
    {
        getline(fin, line);
        myarr[o] = line;
    }
    fin.close();


    int myintarr[60000];

    for (int o = 0; o < n; o++)
    {
        myintarr[o] = stoi(myarr[o]);
    }


    cout << "Choose sorting method: " << endl << "1 - Shell." << endl << "2 - (STRING) Shell." << endl;
    int decision;
    cin >> decision;

    auto start = std::chrono::high_resolution_clock::now();

    if (decision == 1)
    {
        shellsorting(myintarr, n);
    }
    else if (decision == 2)
    {
        stringshellsorting(myarr, n);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    for (int o = 0; o < n; o++)
    {
        cout << myintarr[o] << endl;
    }

    cout << "Execution time: " << duration << " ms" << std::endl;

    return 0;
}

//to run the program for integer sorting, all function callings with the name "string" should be commented, and these without string name should be uncommented, as well as the block of code 181-188 (it should be uncommented as well).