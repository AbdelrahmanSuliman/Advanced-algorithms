#include<iostream>
#include <algorithm>


bool isAngaram(std::string x, std::string y) {
    if (x.size() != y.size()) {
        return false;
    }
    std::sort(x.begin(), x.end());
    std::sort(y.begin(), y.end());
    return x == y;
}

void coins(int arr[], int size) {
    int first = arr[0];
    int second = arr[1];
    if (first == second) {
        if (arr[2] > first) {
            std::cout << "Coin is heavier";
        }
        else {
            std::cout << "Coin is lighter";
        }
    }
    else {
        int fakeCoin = (first > second) ? first : second;
        if (arr[2] == fakeCoin)
            std::cout << "Coin is lighter";
        else
            std::cout << "Coin is heavier";
    }
}        }
    }
    else {
        int fakeCoin = (first > second) ? first : second;
        if (arr[2] == fakeCoin)
            std::cout << "Coin is lighter";
        else
            std::cout << "Coin is heavier";
    }
}


int main() {

    std::string str1 = "listen";
    std::string str2 = "silent";
    if (isAngaram(str1, str2)) {
        std::cout << str1 << " and " << str2 << " are anagrams.\n";
    }
    else {
        std::cout << str1 << " and " << str2 << " are not anagrams.\n";
    }

    int coinsArr1[] = { 5, 5, 6 }; 
    int coinsArr2[] = { 7, 3, 7 };  
    std::cout << "Test 1: ";
    coins(coinsArr1, 3);  
    std::cout << "\nTest 2: ";
    coins(coinsArr2, 3); 

    return 0;
}