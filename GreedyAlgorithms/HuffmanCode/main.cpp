#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
Huffman Code :
        In computer science and information theory, a Huffman code is a particular type of optimal prefix code that is commonly used for
    lossless data compression.

Prefix Code :
        A prefix code or prefix-free-code is a type of code system distinguished by its possession of the "prefix property", which requires that
    there is no whole code word in the system that is a prefix (initial segment) of any other code word in the system. Let's say, a set of characters
    Ch = {a, b, c} is coded as Ch' = {1, 00, 01}. This coding system is prefix-free because, first sequence 1 is not prefix of either 00 or 01.
    Similarly, 00 is not prefix of 1 or 01 and so on. But if the coding was done such that ch' = {00, 10, 1}, it won't be prefix-free. Because,
    here 1 is prefix of 10.
        In the first prefix-free coding system if a machine gets the code 1 instantly it will know that the decoded character will be a. But, in the
    second coding system, getting a 1 can be just 1 or 1 of the sequence 10. So, no instant way of knowing either it is b or c at first encounter.

Explanation :
        This algorithm is used to compress data using its own coding system instead of ASCII which always takes 8 bits to represent a character. Generally
    in everyday life we don't use all 128 ASCII characters in a single file (Commonly we use A-Z, a-z, 0-9, punctuation marks, new line character). So, why
    to use 8 bit ASCII code? Instead in Huffman coding each character of a file is assigned variable or fixed length of bits usually based on their frequency
    of appearance in the file.
        The table (dictionary) which was used to encode data is also included in front of encoded output string to be used for decoding (decompressing data)
    later.

Algorithm :
        HUFFMAN_ENCODE(input[]) :
        //input[] is a array of structure such that
        //input[i].char contains character from input file
        //and input[i].frequency contains frequency the
        //very character in input file
        1. HEAPIFY input[] using a minHeap based on frequency
        2. WHILE HEAP.size >= 2 :
                a. POP 2 nodes, a and b from HEAP TOP (Nodes that contains lowest frequency characters)
                b. CREATE NEW NODE adding their frequencies i.e. c := new input; c.frequency := a.frequency + b.frequency and c.char := null
                c. MAKE a and b children of c ( b <----- c -----> a Tree)
                d. HEAPIFY new node c
           END FORM TREE t whose leaf nodes contain input characters now and HEAP is empty
        3. TRAVERSE each branch of t from root to leaf node (Nodes that contain characters) :
                a. EACH LEFT PATH is ASSIGNED 0
                b. EACH RIGHT PATH is ASSIGNED 1
        4. FOR EACH character in leaf nodes :
                a. GET the string along the path from root to its node
                b. MAP the character to the string

Sample Input :
aaabcc

Sample Output :
Encoded Message :1a00b01c111000101
Mapping chart   :1a00b01c
Encoded output  :111000101

References :
        Youtube => https://youtu.be/co4_ahEDCho
        Wikipidea => https://en.wikipedia.org/wiki/Huffman_coding
        Wikipidea => https://en.wikipedia.org/wiki/Prefix_code

*/


//An structure for nodes
typedef struct character{
    int frequency;  //Frequency of data
    char ch;        //Data
    int left;       //Node's left child link(index)
    int right;      //Node's left child link(index)
    int self;       //Self reference(index)
    int parent;     //Parent's link(index)
};

//Structure for defining operator function for min heap
struct comparator {
    bool operator()(character i, character j) {
        return i.frequency >= j.frequency;
    }
};

//Min heap for always getting nodes with lowest frequency
priority_queue<character, vector<character>, comparator> minHeap;
int frequency[128] = {0};   //Array for counting character frequency in input
character nodes[128];       //Array that is used to form the tree
int top = 0;                //Act as tree root


map<char, string> mp;               //Map for mapping input character to output code string
map<char, string>::iterator itr;    //Map iterator



//For counting frequencies of characters in input string
void frequencyCounter(string str) {
    for(int i = 0; i < str.length(); i++) {
        frequency[str[i]]++;                //Frequency counting
    }

    for(int i = 0; i < 128; i++) {
        if(frequency[i] != 0) {            //Create character object for Characters whose frequencies are not 0's
            char ch = (char)i;
            character ob;                  //Creating the character object
            ob.ch = ch;                    //Assign the character into the object
            ob.frequency = frequency[i];   //Assign the frequency
            ob.left = -1;                  //Currently it has no left child
            ob.right = -1;                 //Currently it has no right child
            ob.parent = -1;                //Currently it has no parent
            ob.self = top;                 //Reference(Index) of current node is where the top of array is currently at. It is recorded for later use
            nodes[top++] = ob;             //Pushing the created character object into the array and increase the top(Similar to stack)
        }
    }

    //Heapify the array. The self index was recorded into respective objects to keep track of their actual position in array even after heapifying used later to form tree.
    for(int i = 0; i < top; i++) {
        minHeap.push(nodes[i]);         //Heapifying the array
    }
}

//Forming the tree from heapified nodes
void formTree() {
    while(minHeap.size() >= 2) {
        character a = minHeap.top();    //Get first node from heap
        minHeap.pop();                  //Pop out the first node
        character b = minHeap.top();    //Get second node from heap
        minHeap.pop();                  //Pop out the second node


        character newNode;                              //Creating new node to make it the popped nodes' parent
        newNode.ch = '\0';                              //This node won't posses a character unlike leaf nodes. So, assign null.
        newNode.frequency = a.frequency + b.frequency;  //Assign sum of the popped out nodes' frequencies as new node's frequency
        newNode.left = a.self;                          //Make the popped out node with lower frequency left child of new node
        newNode.right = b.self;                         //Make the popped out node with lower frequency right child of new node
        nodes[a.self].parent = top;                     //Make the new node parent of popped out node in nodes array (This is where recorded self reference is needed as the nodes[] array is the permanent record of nodes unlike heap. We will form the tree on the nodes[] array)
        nodes[b.self].parent = top;                     //Make the new node parent of popped out node in nodes array (This is where recorded self reference is needed as the nodes[] array is the permanent record of nodes unlike heap. We will form the tree on the nodes[] array)
        newNode.self = top;                             //Assign new node its self reference which is where the array top is currently at
        nodes[top++] = newNode;                         //Push the new node in the nodes[] array at index where top is pointing
        minHeap.push(newNode);                          //Push the new node also into heap
    }
}

//Encode a single character by traversing the branch of the character and picking up 0 or 1 along the path
void encode(int root, char ch) {
    string output = "";
    int currentCharIndex;
    for(int i = 0; i < top; i++) {                      //Getting the reference(index) of the node containing character passed as argument
        if(nodes[i].ch == ch) {
            currentCharIndex = i;
        }
    }

    //The tree is traversed bottom to top(Leaf to root)
    int ptr = currentCharIndex;                        //Initial node
    while(ptr != root) {                               //Till root is reached

        if(ptr == nodes[nodes[ptr].parent].left)       //If current tree node is left child of its parent add 0 in output
            output += "0";
        else if(ptr == nodes[nodes[ptr].parent].right) //If current tree node is right child of its parent add 1 in output
            output += "1";

        ptr = nodes[ptr].parent;                       //Updating node pointer
    }

    reverse(output.begin(), output.end());             //Reverse the output string as we traversed the tree bottom to top but output must be taken from top to bottom(Root to leaf)
    mp.insert(pair<char, string>(ch, output));         //Map the character to the output encoded string
}

//Encode the whole input string
string encodeMsg(string msg, string& mappingChart, string& output) {
    string codedMsg = "";
    string chart="";

    for(int i = 0; i < 128; i++) {
        if(frequency[i] != 0) {
            char ch = (char)i;
            encode(top - 1, ch);                                //Calling encode(root, character) function for each character with non-zero frequency
        }
    }

    for(int i = 0; i < msg.length(); i++) {                     //For each of input character get the mapped encoded string
        for(itr = mp.find(msg[i]); itr != mp.end(); itr++) {
            codedMsg += (itr -> second);
            break;
        }
    }
    output = codedMsg;

    for(itr = mp.begin(); itr != mp.end(); itr++) {             //Form the chart to include it with output for later decoding(decompressing) purpose
        chart += (itr -> second);
        chart.push_back(itr -> first);
    }
    mappingChart = chart;

    codedMsg = chart + codedMsg;
    return codedMsg;

}

int main()
{
    string str, mappingChart, output;
    cout << "Enter your message :" << endl;
    getline(cin, str);

    frequencyCounter(str);
    formTree();

    cout << "Tabulated view of generated tree :" << endl;
    cout << "(C-Character, F-Frequency, L-LeftChildReference, R-RightChildReference, P-ParentReference, S-SelfReference)" << endl;
    for(int i = 0; i < top; i++) {
        cout << "C:" << nodes[i].ch << " F:" << nodes[i].frequency << " L:" << nodes[i].left << " R:" << nodes[i].right << " P:" << nodes[i].parent << " S:" << nodes[i].self << endl;
    }

    cout << "Encoded Message\t:" << encodeMsg(str, mappingChart, output) << endl;
    cout << "Mapping chart\t:" << mappingChart << endl;
    cout << "Encoded output\t:" << output << endl;
    return 0;
}
