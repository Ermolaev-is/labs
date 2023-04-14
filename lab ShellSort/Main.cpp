#include <iostream>
#include <vector>
#include <cmath>
#include "StackArray.h"
#include <chrono>

using namespace std;

void shellGapShell(vector<int>& arr, int n);
void shellGapHibbard(vector<int>& arr, int n);
void shellGapSedgwick(vector<int>& arr, int n);
void printArray(vector<int>& arr, int n);
bool isSorted(vector<int>& arr, int n);
void getTimeShell(vector<int>& arr, int n);
void getTimeHibbard(vector<int>& arr, int n);
void getTimeSedgwick(vector<int>& arr, int n);
vector<int> getBest(int maxSize);
vector<int> getWorst(int maxSize);
vector<int> getAverage(int maxSize);



int main()
{
    int maxSize;
    cout << "Enter the length of the array: ";
    cin >> maxSize;
    try
    {
        if (cin.peek() != '\n')
        {
            throw runtime_error("The length of the array must be a non-negative integer");
        }
    }
    catch (exception const& e) 
    {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

   
    cout << "\n" <<"========== BEST CASE ==========" << "\n\n";
    vector<int>arr = getBest(maxSize);
    getTimeShell(arr, arr.size());
    cout << "\n";
    
    arr = getBest(maxSize);
    getTimeHibbard(arr, arr.size());
    cout << "\n";

    arr = getBest(maxSize);
    getTimeSedgwick(arr, arr.size());
    cout << "\n";

    cout << "\n" << "========== AVERAGE CASE ==========" << "\n\n";
    arr = getAverage(maxSize);
    getTimeShell(arr, arr.size());
    cout << "\n";

    arr = getAverage(maxSize);
    getTimeHibbard(arr, arr.size());
    cout << "\n";

    arr = getAverage(maxSize);
    getTimeSedgwick(arr, arr.size());
    cout << "\n";

    cout << "\n" << "========== WORST CASE ==========" << "\n\n";
    arr = getWorst(maxSize);
    getTimeShell(arr, arr.size());
    cout << "\n";

    arr = getWorst(maxSize);
    getTimeHibbard(arr, arr.size());
    cout << "\n";

    arr = getWorst(maxSize);
    getTimeSedgwick(arr, arr.size());
    cout << "\n";

    return 0;
}


void shellGapShell(vector<int>& arr, int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void shellGapHibbard(vector<int>& arr, int n)
{
    int gap = 0;
    while (gap < n)
    {
        gap = 2 * gap + 1;
    }
    while (gap > 0)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
        gap = (gap - 1) / 2;
    }
}

void shellGapSedgwick(vector<int>& arr, int n)
{
    StackArray<int> stack(n);
    int gap = 0;
    stack.push(1);
    while (pow(4, gap + 1) + 3 * pow(2, gap) + 1 < n)
    {
        stack.push(pow(4, gap + 1) + 3 * pow(2, gap) + 1);
        gap++;
    }
    gap = stack.pop();

    while (gap > 0)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }

        if (gap > 1)
        {
            gap = stack.pop();
        }
        else
        {
            break;
        }
    }
}

void printArray(vector<int>& arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

bool isSorted(vector<int>& arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

void getTimeShell(vector<int>& arr, int n)
{
    cout << "Sorted array using Shell's method: ";
    auto start = chrono::steady_clock::now();
    shellGapShell(arr, arr.size());
    auto end = chrono::steady_clock::now();
    cout << (isSorted(arr, arr.size()) ? "Is sorted" : "Is not sorted") << "\n";
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << "\n";
}

void getTimeHibbard(vector<int>& arr, int n)
{
    cout << "Sorted array using Hibbard's method: ";
    auto start = chrono::steady_clock::now();
    shellGapHibbard(arr, arr.size());
    auto end = chrono::steady_clock::now();
    cout << (isSorted(arr, arr.size()) ? "Is sorted" : "Is not sorted") << "\n";
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << "\n";
}

void getTimeSedgwick(vector<int>& arr, int n)
{
    cout << "Sorted array using Sedgwick's method: ";
    auto start = chrono::steady_clock::now();
    shellGapSedgwick(arr, arr.size());
    auto end = chrono::steady_clock::now();
    cout << (isSorted(arr, arr.size()) ? "Is sorted" : "Is not sorted") << "\n";
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << "\n";
}

vector<int> getBest(int maxSize)
{
    vector<int> best(maxSize);
    for (int i = 0; i < maxSize; i++) {
        best[i] = i + 1;
    }
    return best;
}

vector<int> getWorst(int maxSize)
{
    vector<int> worst(maxSize);
    for (int i = 0; i < maxSize; i++) {
        worst[i] = maxSize - i;
    }
    return worst;
}

vector<int> getAverage(int maxSize)
{
    srand(time(NULL));
    vector<int> average(maxSize);
    for (int i = 0; i < maxSize; i++)
    {
        average[i] = rand() % 10;
    }
    return average;
}
