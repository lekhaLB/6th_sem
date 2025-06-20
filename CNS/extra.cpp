#include <iostream>
#include <algorithm>
using namespace std;

// ---------- Caesar Cipher ----------
string caesarEncrypt(string text, int shift)
{
    string result = "";
    for (char c : text)
    {
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            result += char((c - base + shift) % 26 + base);
        }
        else
        {
            result += c;
        }
    }
    return result;
}

string caesarDecrypt(string text, int shift)
{
    return caesarEncrypt(text, 26 - shift);
}

// ---------- Playfair Cipher ----------
string keyMatrix[5];

void generateKeyMatrix(string key)
{
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // J excluded
    string used = "";

    key.erase(remove(key.begin(), key.end(), 'J'), key.end());
    key += alphabet;

    for (char &c : key)
    {
        c = toupper(c);
        if (isalpha(c) && used.find(c) == string::npos)
        {
            used += c;
        }
    }

    for (int i = 0; i < 5; ++i)
    {
        keyMatrix[i] = used.substr(i * 5, 5);
    }
}

pair<int, int> findPosition(char c)
{
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (keyMatrix[i][j] == c)
                return {i, j};
    return {-1, -1};
}

string playfairEncrypt(string text)
{
    string result = "";
    for (auto &c : text)
    {
        c = toupper(c);
        if (c == 'J')
            c = 'I';
    }

    string cleanText = "";
    for (char c : text)
        if (isalpha(c))
            cleanText += c;

    string processed = "";
    for (size_t i = 0; i < cleanText.length(); i++)
    {
        char a = cleanText[i];
        char b = (i + 1 < cleanText.length()) ? cleanText[i + 1] : 'X';
        if (a == b)
            b = 'X';
        else
            i++;

        auto [r1, c1] = findPosition(a);
        auto [r2, c2] = findPosition(b);

        if (r1 == r2)
            processed += keyMatrix[r1][(c1 + 1) % 5], processed += keyMatrix[r2][(c2 + 1) % 5];
        else if (c1 == c2)
            processed += keyMatrix[(r1 + 1) % 5][c1], processed += keyMatrix[(r2 + 1) % 5][c2];
        else
            processed += keyMatrix[r1][c2], processed += keyMatrix[r2][c1];
    }

    return processed;
}

string playfairDecrypt(string text)
{
    string result = "";
    for (auto &c : text)
    {
        c = toupper(c);
        if (c == 'J')
            c = 'I';
    }

    for (size_t i = 0; i < text.length(); i += 2)
    {
        char a = text[i];
        char b = (i + 1 < text.length()) ? text[i + 1] : 'X';

        auto [r1, c1] = findPosition(a);
        auto [r2, c2] = findPosition(b);

        if (r1 == r2)
            result += keyMatrix[r1][(c1 + 4) % 5], result += keyMatrix[r2][(c2 + 4) % 5];
        else if (c1 == c2)
            result += keyMatrix[(r1 + 4) % 5][c1], result += keyMatrix[(r2 + 4) % 5][c2];
        else
            result += keyMatrix[r1][c2], result += keyMatrix[r2][c1];
    }

    return result;
}

// ---------- Main ----------
int main()
{
    int choice;
    cout << "Select Cipher:\n";
    cout << "1. Caesar Cipher\n";
    cout << "2. Playfair Cipher\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        string text;
        int shift;
        cout << "\nEnter text: ";
        getline(cin, text);
        cout << "Enter shift (number): ";
        cin >> shift;

        string encrypted = caesarEncrypt(text, shift);
        string decrypted = caesarDecrypt(encrypted, shift);

        cout << "\n--- Caesar Cipher ---\n";
        cout << "Encrypted: " << encrypted << endl;
        cout << "Decrypted: " << decrypted << endl;
    }
    else if (choice == 2)
    {
        string key, text;
        cout << "\nEnter key: ";
        getline(cin, key);
        cout << "Enter text to encrypt: ";
        getline(cin, text);

        generateKeyMatrix(key);
        string encrypted = playfairEncrypt(text);
        string decrypted = playfairDecrypt(encrypted);

        cout << "\n--- Playfair Cipher ---\n";
        cout << "Encrypted: " << encrypted << endl;
        cout << "Decrypted: " << decrypted << endl;
    }
    else
    {
        cout << "Invalid choice!\n";
    }

    return 0;
}