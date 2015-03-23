/*
Cody Krauskopf
Cross Reference Index
362 Spring 15

*/


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>;
using namespace std;
//data contains the word lines contain the line numbers that word appears at
struct Node{
    string word;
    vector<int> lines;
    Node* left;
    Node* right;
};
//insert new word into binary tree
 Node* Insert(string word, Node* rootPtr, int counter ){
    //if root is NULL
    if(rootPtr == NULL){
    Node* newNode = new Node();
    newNode->word=word;
    newNode->lines.push_back(counter);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
    }
    //go left
    else if(word< rootPtr->word){
        rootPtr->left = Insert(word,rootPtr->left,counter);

    }
    //go right
    else if( word > rootPtr->word) {
        rootPtr->right = Insert(word, rootPtr->right,counter);

    }
    //if word is already in tree add line it is located on
    else if(word == rootPtr->word){

        rootPtr->lines.push_back(counter);
    }


return rootPtr;
}
//print out tree
 void inorderTraversal( Node* rootPtr ){

    if( rootPtr == NULL ){
        return;
    }
    inorderTraversal( rootPtr->left );
    int size = rootPtr->lines.size();
    cout << setw (10) << left << rootPtr->word;
    //loop through multiples of any word and print the line they occur on
    for(int i = 0; i < size; i++){
        cout << "   " << rootPtr->lines.at(i);
    }
    cout << endl;
    inorderTraversal( rootPtr->right );
}


int main() {
    string word;
    ifstream inFile;
    Node* rootPtr = NULL;
    //open file
    inFile.open("test.txt");
    if (!inFile) {
        cout << "Unable to open text file";
    }

    string line;
    int counter = 1;
    //get file line by line
    while(getline(inFile, line)){
            istringstream iss(line);

            //loop through each word in the line
              while (iss >> word) {

                if (word == "#"){
                    break;
                }

                else{
                    // get substr max 10 chars
                    word = word.substr(0,10);
                    int length = word.length();
                    //get char at end of substr and check if it is punctuation
                    char c =  word.at(length-1);
                    if(ispunct(c)){
                        word = word.substr(0,length-1);

                    }
                    //insert word into binary search tree
                    rootPtr = Insert(word,rootPtr, counter );

                }

            }
        //increment line counter
        counter ++;

    }
    //close file
    inFile.close();
    //print tree
    inorderTraversal(rootPtr);


}
