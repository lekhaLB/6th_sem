#include <iostream>
#include <string>
#include <cctype>

using namespace std;

char shift(char m, char k, int dir) {
    int a = tolower(m) - 'a';
    int b = tolower(k) - 'a';
    return 'a' + (a + dir * b + 26) % 26;
}

int main() {
    int ch;

    while (true) {
        cout << "Vigenère Cipher\n1 - Encrypt\n2 - Decrypt\n3 - Quit\nChoice: ";
        cin >> ch;
        cin.ignore();  // Clear newline from buffer

        if (ch == 1 || ch == 2) {
            string msg, key, res;
            int mode = (ch == 1) ? 1 : -1;

            cout << "Enter message: ";
            getline(cin, msg);

            cout << "Enter key: ";
            getline(cin, key);

            int klen = key.length();
            int k = 0;

            for (char c : msg) {
                if (isalpha(c)) {
                    char shifted = shift(c, key[k % klen], mode);
                    // Preserve original case
                    if (isupper(c))
                        shifted = toupper(shifted);
                    res += shifted;
                    k++;
                } else {
                    res += c; // Leave non-alphabet characters unchanged
                }
            }

            if (mode == 1)
                cout << "Encrypted message: " << res << "\n\n";
            else
                cout << "Decrypted message: " << res << "\n\n";
        } 
        else if (ch == 3) {
            break;
        } 
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}