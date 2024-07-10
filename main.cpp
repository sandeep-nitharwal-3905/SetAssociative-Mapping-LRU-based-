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
    int lines, k, cache_miss, total_sets;
    vector<LRU *> v;
    vector<int> lineNo;

    SetAssociative(int _lines, int _k)
    {
        lines = _lines;
        k = _k;
        total_sets = (lines / k);
        cache_miss = 0;
        v.resize(total_sets); // number of sets
        lineNo.resize(total_sets);
        for (int i = 0; i < total_sets; i++)
        {
            v[i] = new LRU(k);
        }
    }

    void addData()
    {
        int value;
        cout << "\nEnter Data to be Add : ";
        cin >> value;
        int setNo = value % total_sets;
        int is_hit = searchData(value);
        if (is_hit != -1)
        {
            v[setNo]->put(is_hit, value);
        }
        else
        {
            v[setNo]->put(lineNo[setNo], value);
            lineNo[setNo] = (++lineNo[setNo]) % k;
        }
    }

    int searchData(int value)
    {
        int setNo = value % total_sets;
        int found = -1;
        for (int i = 0; i < k; i++)
        {
            if (v[setNo]->get(i) == value)
            {
                found = i;
                break;
            }
        }
        if (found==-1)
        {
            cout << "\n\nNot Found! cache miss !!" << endl;
            cache_miss++;
        }
        else
        {
            cout << "\n\nCache Hit!" << endl;
        }
        return found;
    }

    void totalMiss()
    {
        cout << "\nTotal misses are: " << cache_miss << "\n";
    }

    void cacheView()
    {
        cout << "\nchache View : \n\n";
        for (int i = 0; i < total_sets; i++)
        {
            cout << "Set No: " << i << endl;
            for (int j = 0; j < k; j++)
            {
                int value = v[i]->get(j);
                cout << (value != -1 ? value : 0) << " ";
            }
            cout << endl;
        }
        cout << "\n";
    }
};

bool valadity(int val1, int val2)
{
    if (__builtin_popcount(val1) == 1 && __builtin_popcount(val2) == 1 && val1 >= val2)
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
        int choice, value, found;
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
            cout << "Enter a value to be Search : ";
            cin >> value;
            found = obj.searchData(value);
            found != -1 ? (cout << value << " found on line No : " << found << endl) : (cout << "Cache Miss !!");
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
