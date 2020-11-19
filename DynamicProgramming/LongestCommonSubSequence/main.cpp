#include <iostream>
#include <string>

using namespace std;

/*
LCS :
        The longest common subsequence (LCS) problem is the problem of finding the longest subsequence common to all sequences in a set of
    sequences (often just two sequences). It differs from the longest common substring problem: unlike substrings, subsequences are not required
    to occupy consecutive positions within the original sequences.

Explanation :
        We will place two input strings horizontally and vertically respectively along side a table. The table will have one extra column and row at initial position.
    We will fill the extra column and row (table[i][0] and table[0][i]) with 0's to initialize the process. Now we will traverse through the table and fill other cells
    following some conditions.

References :
        Youtube => https://youtu.be/sSno9rV8Rhg?t=903
        Youtube => https://youtu.be/NnD96abizww
        Wikipidea => https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
        Algorithm => https://youtu.be/sSno9rV8Rhg?t=903

*/

string LCS(string str1, string str2, /*Optional*/ bool showTable = false) {
    int table[str2.length() + 1][str1.length() + 1]; //Comparison table
    string output = ""; //Output string
    int h, k;

    //Initializing table with 0's
    for(int i = 0; i < str2.length() + 1; i++) {
        for(int j = 0; j < str1.length() + 1; j++) {
            table[i][j] = 0;
        }
    }

    //Memoization process
    for(int i = 1; i < str2.length() + 1; i++) {
        for(int j = 1; j < str1.length() + 1; j++) {

            if(str1[j - 1] != str2[i - 1]) //If a match is not found between two characters of two strings(Vertical and Horizontal), then we have to choose the character that will contribute mostly in the length of output.
                table[i][j] = max(table[i][j - 1], table[i - 1][j]); //So, we will choose between the vertical and horizontal characters on basis of maximum contribution (Which cell has maximum value).
            else //If a match found between two characters of two strings(Vertical and Horizontal), we have to count this new match. So, we have to increase our previous output length by 1.
                table[i][j] = table[i - 1][j - 1] + 1; //The previous length was recorded at left upper diagonal position of current position. Because at that diagonal position the new character's length was added neither vertically or horizontally. So, the diagonal holds the exact previous output length.
        }
    }

    //Backtracking process to get the string
    for(h = str2.length(), k = str1.length(); h >= 1 && k >= 1; ) { //Starting from the last corner of table we have to take the vertical characters each time we proceed diagonally.
        if(table[h][k] == table[h][k - 1]) { //Along each row we will keep moving backwords till getting same value as next. Because the same value indicates the vertical character had no effect on output string length (Character not included in output).
            k--;
        }
        else { //Moving horizontally if we get on a space from where moving further will decrease the value, then we have to record that character and move diagonally. As decrement in length value indicates before adding this character to output the output length was less (This character is included in output).
            output.push_back(str1[k - 1]);
            h--;
            k--;
        }
    }



    if(showTable) { //Showing the generated table for comparison
        cout << "Comparison table :" << endl;
        cout << "  " << "0" << " ";
        for(int i = 0; i < str1.length(); i++)
            cout << str1[i] << " ";
        cout << "< String A" << endl;
        for(int i = 0; i < str2.length() + 1; i++) {
            (i == 0)? cout << "0" << " " : cout << str2[i - 1] << " ";
            for(int j = 0; j < str1.length() + 1; j++) {
                    cout << table[i][j] << " ";
            }
            cout << endl;
        }
        cout << "^\nString B" << endl;
    }

    return string(output.rbegin(), output.rend()); //Reversing the output string as backtracking gives the output in reversed way.

}

int main()
{
    cout << "Longest Common Subsequence :" << endl;
    cout << LCS("How to be a pp", "to be a pp", true);
    return 0;
}
