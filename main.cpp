#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

// LRU with Key Value pair
class LRU
{
public:
    class Node
    {
    public:
        int key, val;
        Node *next, *prev;
        Node(int _key, int _val)
        {
            key = _key;
            val = _val;
            next = NULL;
            prev = NULL;
        }
    };

    Node *head = new Node(-1, -1);
    Node *tail = new Node(-1, -1);
    int cap;
    unordered_map<int, Node *> mp;

    LRU(int capacity)
    {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }

    void addNode(Node *newNode)
    {
        Node *temp = head->next;
        newNode->next = temp;
        newNode->prev = head;
        head->next = newNode;
        temp->prev = newNode;
    }

    void deleteNode(Node *delNode)
    {
        Node *delPrev = delNode->prev;
        Node *delNext = delNode->next;
        delPrev->next = delNext;
        delNext->prev = delPrev;
    }

    int get(int key)
    {
        if (mp.find(key) != mp.end())
        {
            Node *resNode = mp[key];
            int res = resNode->val;
            mp.erase(key);
            deleteNode(resNode);
            addNode(resNode);
            mp[key] = head->next;
            return res;
        }
        return -1;
    }

    void put(int key, int value)
    {
        if (mp.find(key) != mp.end())
        {
            Node *existingNode = mp[key];
            mp.erase(key);
            deleteNode(existingNode);
        }
        if (mp.size() == cap)
        {
            mp.erase(tail->prev->key);
            deleteNode(tail->prev);
        }
        addNode(new Node(key, value));
        mp[key] = head->next;
    }
};

class SetAssociative
{
public:
    int lines, k, cacheMiss, Tsetes;
    vector<LRU *> memory;

    SetAssociative(int _lines, int _k)
    {
        lines = _lines;
        k = _k;
        Tsetes = (lines / k); // Total number of Sets
        cacheMiss = 0;
        memory.resize(Tsetes); // LRU for each Sets
        for (int i = 0; i < Tsetes; i++)
        {
            memory[i] = new LRU(k);
        }
    }

    void addData()
    {
        int key, value;
        cout << "\nEnter Data to be Add into {key,value} pair : ";
        cin >> key >> value;
        int setNo = key % Tsetes;
        int found = searchData(key, value);
        memory[setNo]->put(key, value);
        if (found == -1)
        {
            cout << "Cache Miss !! {" << key << " " << value << "} not found !" << endl;
            cacheMiss++;
        }
        else if (found == 0)
        {
            cout << "Key is updated successfully :) " << endl; // no miss count
        }
        else
        {
            cout << "Cache Hit !! " << "found at line No : " << found << endl;
        }
    }

    int searchData(int key, int value)
    {
        int setNo = key % Tsetes, cnt = 0;
        for (auto datakey : memory[setNo]->mp)
        {
            cnt++;
            if (key == datakey.first)
            {
                if (datakey.second->val == value)
                    return cnt;
                else
                    return 0;
            }
        }
        return -1;
    }

    void totalMiss()
    {
        cout << "\nTotal misses are: " << cacheMiss << "\n";
    }

    void cacheView()
    {
        cout << "\nchache View : \n\n";
        for (int i = 0; i < Tsetes; i++)
        {
            int cnt = 0;
            cout << "Set No: " << i << endl;
            for (auto datakey : memory[i]->mp)
            {
                cnt++;
                cout << "   {" << datakey.first << "," << datakey.second->val << "}" << endl;
            }
            // reaming line are as {0,0}
            for (int j = cnt; j < k; j++)
            {
                cout << "   {" << 0 << "," << 0 << "}" << endl;
            }
        }
        cout << "\n";
    }
};

bool valadity(int val1, int val2)
{
    if (__builtin_popcount(val1) == 1 && __builtin_popcount(val2) == 1 && val1 >= val2) // chceking for exect power of 2 or not
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Set Associative Mapping Mangement System which follows LRU
int main()
{
    try
    {
        cout << "\nNote : Please Enter No of lines and value of k into power of 2 \n\n";
        int total_no_lines, way_k;
        cout << "Enter Total No of Lines : ";
        cin >> total_no_lines;
        cout << "Enter Value of k-th Way Associative : ";
        cin >> way_k;
        // checking valadity of values of k and lines
        if (!valadity(total_no_lines, way_k))
        {
            throw 0;
        }
        SetAssociative obj(total_no_lines, way_k);

    p:
    {
        system("cls");
        int choice, key, value, found;
        cout << "========================================================";
        cout << "\n   SETASSOCIATIVE MAPPING MANAGEMENT SYSTEM (LRU Based) \n";
        cout << "========================================================";
        cout << "\n\n 1. AddData ";
        cout << "\n\n 2. SearchData ";
        cout << "\n\n 3. Total Misses ";
        cout << "\n\n 4. Cache View ";
        cout << "\n\n 5. Exit ";
        cout << "\n\nEnter your Choice  : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            obj.addData();
            break;
        case 2:
            system("cls");
            cout << "Enter a {key,value} pair to be Search : ";
            cin >> value;
            found = obj.searchData(key, value);
            found != -1 ? (found != 0 ? (cout << value << " found on line No : " << found << endl) : (cout << "key is updated , no miss count :) " << endl)) : (cout << "Cache Miss !! NOT FOUND !!");
            break;
        case 3:
            system("cls");
            obj.totalMiss();
            break;
        case 4:
            system("cls");
            obj.cacheView();
            break;
        case 5:
            exit(0);

        default:
            cout << "\n\nInvalid Choice ... Please try again";
        }
    }
        getch();
        goto p;
    }
    catch (...)
    {
        cout << "\n Values are not valid !! \n\n";
    }
    return 0;
}
