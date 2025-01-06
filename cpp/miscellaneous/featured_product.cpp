#include <string>
#include <vector>
#include <map>
#include <iostream>
/*
An e-commerce site tracks the purchases made each day. The product that is purchased 
the most on one day is the featured product for the following day. If there is a tie 
for the product purchased most frequently, those product names are ordered alphabetically 
ascending, and the last name in the list is chosen.

Example
Input: products = ['redShirt', 'greenPants', 'redShirt', 'orangeShoes', 'blackPants', 'blackPants']
    - greenPants and orangeShoes were purchased once.
    - redShirt and blackPants were each purchased 2 times on the given day.
    - After ordering the products alphabetically ascending, redShirt is the last product listed.
Output: redShirt is the featured product for the following day.
*/

std::string featuredProduct(std::vector<std::string> products) {
    std::map<std::string, int> productMap;
    std::string featProduct;
    int featProductSales = 0;

    for (const auto &product : products) {
        productMap[product] += 1;
    }
    

    for (const auto &pair : productMap) {
        std::string product = pair.first;
        int sales = pair.second;

        if (sales >= featProductSales) {
            featProduct = product;
            featProductSales = sales;
        }
        std::cout << pair.first << ": " << pair.second << '\n';
    }
    return featProduct;

}

int main() {

    std::vector<std::vector<std::string>> testcases = {
        {"apple", "banana", "apple", "orange", "banana", "banana"},
        {"yellowShirt", "redHat", "blackShirt", "bluePants", "redHat", "yellowShirt", "greenPants", "pinkHat", "blackShirt", "greenPants"},
        {"phone", "laptop", "tablet", "tablet", "laptop", "phone", "phone"},
        {"camera"}
        };
    
    for (int i=0 ; i<testcases.size() ; i++) {
        std::cout << "\nTestcase #" << i << '\n';
        std::cout << "Featured Product: " << featuredProduct(testcases[i]) << std::endl;
    }
    return 0;
}