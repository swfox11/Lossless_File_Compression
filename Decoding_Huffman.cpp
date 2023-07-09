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


string print_decoded_string(string recover_encoded_string, node *root)
{
    string decoded_string = "";
    node *temp = root;
    for (int i = 0; i < recover_encoded_string.size(); i++)
    {

        if (recover_encoded_string[i] == '0')
        {
            temp = temp->left;
        }
        else if (recover_encoded_string[i] == '1')
        {
            temp = temp->right;
        }
        if (temp->left == NULL && temp->right == NULL)
        {
            cout << temp->c;
            decoded_string += temp->c;
            temp = root;
        }
    }
    cout << endl;
    return decoded_string;
}
vector<int> loadVectorData(const string &filename)
{
    vector<int> table;

    ifstream file(filename, ios::binary);
    if (!file)
    {
        cerr << "Error opening file for reading: " << filename << endl;
        return table;
    }

    // Read the size of the vector
    size_t size;
    file.read(reinterpret_cast<char *>(&size), sizeof(size_t));

    // Resize the vector and read the data
    table.resize(size);
    file.read(reinterpret_cast<char *>(table.data()), size * sizeof(int));

    file.close();
    cout << "Vector data loaded from file: " << filename << endl;

    return table;
}


void saveStringToFile(const string& text, const string& filename)
{
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    file << text;
    file.close();

    cout << "String saved to file: " << filename << endl;
}

int main()
{

    string recovered_encoded_string;
    string decoded_string;
    node *root;
    priority_queue<node *, vector<node *>, comp> minheap;
    vector<int> table(128, 0);
    table.clear();

    // LOADING THE TABLE VECTOR DATA FROM THE BIN FILE  ++++++++++++++++++++++++++++++++++++++++++++
    table = loadVectorData("vector_data.bin");
   
    for (int i = 0; i < 128; i++)
    {
        minheap.push(new node((char)i, table[i]));
    }

    bld_huffman_tree(minheap);
    root = minheap.top();
    
    // TAKING INPUT FROM THE BIN FILE STRING INTO BITSEQUENCE*************************************************(START)
    // TAKING INPUT FROM THE BIN FILE STRING INTO BITSEQUENCE*************************************************(START)
    ifstream inFile("Encoded_output.bin", ios::binary);
    vector<bool> bitSequence2;

    unsigned char byte2;
    while (inFile.read(reinterpret_cast<char *>(&byte2), sizeof(byte2)))
    {
        for (int i = 7; i >= 0; --i)
        {
            bool bit = (byte2 >> i) & 1;
            bitSequence2.push_back(bit);
        }
    }

    inFile.close();
    // TAKING INPUT FROM THE BIN FILE STRING INTO BITSEQUENCE*************************************************(END)
    // TAKING INPUT FROM THE BIN FILE STRING INTO BITSEQUENCE*************************************************(END)
    for (int i = 0; i < bitSequence2.size(); i++)// Converts bitstring to bytes of string
    {
        if (bitSequence2[i])
        {
            recovered_encoded_string.push_back('1');
        }
        else
        {
            recovered_encoded_string.push_back('0');
        }   
    }
    decoded_string = print_decoded_string(recovered_encoded_string, root);// Prints the decoded original string
    
    //cout << decoded_string;TO BE REMOVED
    

    saveStringToFile(decoded_string, "Decoded_Output.txt");
    return 0;
}