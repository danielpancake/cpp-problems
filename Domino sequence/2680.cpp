/* N dominoes are laid out sequentially one after the other. Each domino tile is represented by a pair of any
 * non-negative integers not exceeding 100. You are not allowed to rearrange tiles, but it 
 * is permitted to rotate any number of them. For example, getting a tile with numbers 2 - 5 from 5 - 2.
 * 
 * Output length of the longest domino sequence which can be obtained by rotating tiles. Domino sequence is a
 * sequence of domino tiles in which the second number of the current domino tile is equal to the first number of
 * the next one. 
 * 
 * Input format:
 * Two input files each of which contains the number of pairs N (1 ≤ N ≤ 100000)) in the first line. Each of the
 * following N lines contains two positive integers not exceeding 100.
 * 
 * Expected results:
 * a.txt : 19
 * b.txt : 235
 * 
 * Original: https://kpolyakov.spb.ru/school/ege/gen.php?action=viewTopic&topicId=2680
 */

#include <iostream>
#include <fstream>
#include <vector>

#define FILE 0 // 0 for a.txt and 1 for b.txt

using namespace std;

int main() {
    fstream f;
    f.open(FILE ? "b.txt" : "a.txt");

    int N, a, b, max = 0;
    bool s1, s2; // Checking which side of the tile hasn't been used

    // Read the number of pairs and the first pair
    f >> N >> a >> b;

    /* The first index holds the length of the sequence, while the second holds the second number of the
     * latest domino in the sequence */
    vector <vector <int>> dominoes = { {1, a}, {1, b} };
    for (int i = 1; i < N; i++) {
        f >> a >> b; s1, s2 = false;

        for (int j = 0; j < dominoes.size(); j++) {
            vector <int> * d = &dominoes[j]; // Too lazy to write it every time

            // If two domino tiles can be connected, will do it
            if ((*d)[1] == a) {
                
                (*d)[1] = b; s1 = true;

            } else if ((*d)[1] == b) {
                
                (*d)[1] = a; s2 = true;

            } else {
                
                // If sequesnce can't be continued, will delete it
                // Before doing so, check its length
                if ((*d)[0] > max) {
                    max = (*d)[0];
                }

                dominoes.erase(dominoes.begin() + j);
                j--; continue;
            }

            (*d)[0]++;
        }

        /* Will start a new sequence only if domino tile isn't a part of existsing sequence */
        if (!s1) { dominoes.push_back( {1, b} ); }
        if (!s2) { dominoes.push_back( {1, a} ); }
    }

    // Check lengths of the remaining sequences
    for (int c : dominoes[0]) {
        if (c > max) {
            max = c;
        }
    }

    cout << max;
}
