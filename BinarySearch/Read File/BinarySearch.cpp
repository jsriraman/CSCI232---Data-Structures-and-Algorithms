#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;


int binarySearch(string arr[], int left, int right, string input) {
    cout << "--------------------------------------------------------" << endl;
    // Start timer for search
    auto start3 = high_resolution_clock::now();

    int count = 0;
    cout << "Searching for word: " << input << endl;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        // Check if middle element is correct
        if (arr[mid] == input) {

            // Stop timer for search when found
            auto stop3 = high_resolution_clock::now();

            auto duration3 = duration_cast<microseconds>(stop3 - start3);
            cout << "Time taken to search: " << duration3.count() << " microseconds" << endl << endl;
            cout << "Item found at position " << mid << endl << endl;
            cout << "Search took " << count << " comparisons." << endl << endl;
            cout << "--------------------------------------------------------" << endl;

            return mid;
        }
        // Otherwise
        if (arr[mid] < input) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
        count += 1;
    }
    cout << "Item not in dictionary" << endl << endl;
    // Stop timer for search if not found
    auto stop3 = high_resolution_clock::now();

    auto duration3 = duration_cast<microseconds>(stop3 - start3);

    cout << "Time taken to search: " << duration3.count() << " microseconds" << endl << endl;

    cout << "Search took " << count << " comparisons." << endl << endl;

    cout << "--------------------------------------------------------" << endl;

    return -1;
        
    
}


int main()
{
    // Start timer for reading in the text file
    auto start1 = high_resolution_clock::now();

    ifstream file("dictionary.txt");

    string myArray[10000];

    if (file.is_open())
    {


        for (int i = 0; i < 10000; ++i)
        {
            file >> myArray[i];
        }
    }
    // Stop timer for reading text file
    auto stop1 = high_resolution_clock::now();

    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    // After reading in the file, print each word
    // Start timer for printing dictionary
    auto start2 = high_resolution_clock::now();

    for (int i = 0; i < 10000; i++) {
        cout << myArray[i] << "\n";
    }
    // Stop timer for reading text file
    auto stop2 = high_resolution_clock::now();

    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    cout << endl;
    cout << "Time taken to read file: " << duration1.count() << " microseconds" << endl << endl;

    cout << "Time taken to print entire dictionary: " << duration2.count() << " microseconds" << endl << endl;

    // Accept user input to check if a word is in the dictionary
    string input;

    // Test binary search for performance and comparisons based on where they exist in the array

    cout << "Test the first element in the dictionary" << endl;
    binarySearch(myArray, 0, 10000, "a");

    cout << "Test the last element in the dictionary" << endl;
    binarySearch(myArray, 0, 10000, "zus");

    cout << "Test for the exact middle element" << endl;
    binarySearch(myArray, 0, 10000, "lanka");

    cout << "Test for a word that isn't in the dictionary, but is short" << endl;
    binarySearch(myArray, 0, 10000, "bha");

    cout << "Test for a  word that isn't in the dictionary, but is long" << endl;
    binarySearch(myArray, 0, 10000, "gandienaerljda");

    cout << "Test for a few more words" << endl;
    binarySearch(myArray, 0, 10000, "elbows");
    binarySearch(myArray, 0, 10000, "symptom");
    binarySearch(myArray, 0, 10000, "last");



    while (input != "quitnow") {
        cout << "-------------------------------------------------" << endl << endl;
        cout << "Enter a word to check if it's in the dictionary. To exit, enter 'quitnow'. ";
        cin >> input;

        binarySearch(myArray, 0, 10000, input);

        
    }

 
}