#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <bitset>
using namespace std;

class node
{
public:
    char c;
    int freq;
    node *left;
    node *right;

    node(char c, int freq)
    {
        this->c = c;
        this->freq = freq;
        this->left = this->right = NULL;
    }
};
struct comp
{
    bool operator()(node *a, node *b)
    {
        return a->freq > b->freq;
    }
};
void frequency_table(string str, vector<int> &table)
{

    for (int i = 0; i < str.size(); i++)
    {
        table[str[i]]++;
    }
}
void bld_huffman_tree(priority_queue<node *, vector<node *>, comp> &minheap)
{
    node *left, *right, *top;
    while (minheap.size() != 1)
    {
        left = minheap.top();
        minheap.pop();
        right = minheap.top();
        minheap.pop();
        top = new node('^', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minheap.push(top);
    }
}
void print_and_storecode(node *root, string str2, unordered_map<char, string> &m1)
{
    if (root == NULL)
    {
        return;
    }
    if (root->c != '^' && root->freq != 0)
    {

        m1[root->c] = str2;
        cout << "Huffman Code for " << root->c << " is: " << str2 << endl;
    }
    print_and_storecode(root->left, str2+ "0", m1);
    print_and_storecode(root->right, str2 + "1", m1);
    
    return;
}
string print_encoded_string(string str, unordered_map<char, string> m1)
{
    string encodedstring = "";
    cout << "THE ENCODED STRING :";
    cout << endl;
    cout << endl;
    for (int i = 0; i < str.size(); i++)
    {
        cout << m1[str[i]];
        encodedstring += m1[str[i]];
    }
    cout << endl;
    cout << endl;
    cout << endl;

    return encodedstring;
}
string print_redecoded_string(string encoded_string, node *root)
{
    string redecoded_string = "";
    node *temp = root;
    cout << "THE REDECODED STRING :";
    cout << endl;
    cout << endl;
    for (int i = 0; i < encoded_string.size(); i++)
    {

        if (encoded_string[i] == '0')
        {
            temp = temp->left;
        }
        else if (encoded_string[i] == '1')
        {
            temp = temp->right;
        }
        if (temp->left == NULL && temp->right == NULL)
        {
            cout << temp->c;
            redecoded_string += temp->c;
            temp = root;
        }
    }
    cout << endl;
    cout << endl;
    cout << endl;
    return redecoded_string;
}

void storeVectorData(const vector<int> &table, const string &filename)
{
    ofstream file(filename, ios::binary);
    if (!file)
    {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    // Write the size of the vector as the first element
    size_t size = table.size();
    file.write(reinterpret_cast<const char *>(&size), sizeof(size_t));

    // Write the vector data
    file.write(reinterpret_cast<const char *>(table.data()), size * sizeof(int));

    file.close();
    cout << "Vector data saved to file: " << filename << endl;
}

int main()
{ // TAKING INPUT FROM TXT FILE**************************************************(START)
  // TAKING INPUT FROM TXT FILE**************************************************(START)
    ifstream file;
    // intput text file opened

    //*************************************PUT THE NAME OF THE INPUT TEXT FILE HERE IN THE STRING**************************
    file.open("text1.txt");
    //*************************************PUT THE NAME OF THE INPUT TEXT FILE HERE IN THE STRING**************************
    if (file.fail())
    {
        cout << "File failed to open!" << endl;
        return 1;
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string str = buffer.str(); // input text file is taken as input
    file.close();              // input text file is closed
    // TAKING INPUT FROM TXT FILE**************************************************(END)
    // TAKING INPUT FROM TXT FILE**************************************************(END)

    string str2 = "";
    node *root;
    priority_queue<node *, vector<node *>, comp> minheap;
    vector<int> table(128, 0);
    unordered_map<char, string> m1;
    string encoded_string;
    string redecoded_string;
    
    frequency_table(str, table);

    for (int i = 0; i < 128; i++)
    {
        minheap.push(new node((char)i, table[i]));
    }

    bld_huffman_tree(minheap);
    root = minheap.top();
    print_and_storecode(root, str2, m1);
    encoded_string = print_encoded_string(str, m1);
    redecoded_string = print_redecoded_string(encoded_string, root);

    

    // STORING THE TABLE VECTOR DATA AND GENERATING BIN FILE  ++++++++++++++++++++++++++++++++++++++++++++
    storeVectorData(table, "vector_data.bin");

    //   GENERATING THE OUTPUT BIN FILE....(START)***************************************************
    //   GENERATING THE OUTPUT BIN FILE....(START)***************************************************
    ofstream outFile("Encoded_output.bin", ios::binary);
    vector<bool> bitSequence; // Use std::vector<bool> for efficient storage of bits
    for (int i = 0; i < encoded_string.size(); i++)
    {
        if (encoded_string[i] == '1')
        {
            bitSequence.push_back(true);
        }
        else
        {
            bitSequence.push_back(false);
        }
    }

    // Add your bit sequence to the vector
    // bitSequence.push_back(true);  // Example: Adding a '1' bit
    // bitSequence.push_back(false); // Example: Adding a '0' bit
    // ...

    // Pack the bits into bytes and write them to the file
    unsigned char byte = 0; // Start with an empty byte
    int bitCount = 0;       // Count the number of bits packed into the byte

    for (bool bit : bitSequence)
    {
        byte = (byte << 1) | static_cast<unsigned char>(bit);
        bitCount++;

        if (bitCount == 8)
        {
            outFile.write(reinterpret_cast<char *>(&byte), sizeof(byte));
            byte = 0;
            bitCount = 0;
        }
    }

    // Write any remaining bits (if not a multiple of 8)
    if (bitCount > 0)
    {
        byte <<= (8 - bitCount);
        outFile.write(reinterpret_cast<char *>(&byte), sizeof(byte));
    }

    outFile.close();
    //   GENERATING THE OUTPUT BIN FILE....(END)******************************************************
    //   GENERATING THE OUTPUT BIN FILE....(END)******************************************************

    return 0;
}
