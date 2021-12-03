#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int val;
    Node* l, *r;
};

class BiSearchTree
{
public:
    Node* root;
    BiSearchTree(){}
    BiSearchTree(vector<int> arr)
    {
        this->root = new Node({arr[0], NULL, NULL});
        for(int i = 1; i < arr.size() - 1; i++)
            insert(root, arr[i]);
    }   

    void printTree()
    {
        cout << "Tree: " << endl;
        dfs(this->root);
        puts("");
    }

    void dfs(Node* root)
    {
        if(!root)
            return;
        dfs(root->l);
        cout << root->val << " ";
        dfs(root->r);
    }

    Node* insert(Node* root, int val)
    {
        if(!root)
        {
            root = new Node({val, NULL, NULL});
            return root;
        }
        
        if(root->val > val)
            root->l = insert(root->l, val);
        else
            root->r = insert(root->r, val);
    }

    Node* find(Node* root, int val)
    {
        if(!root)
            return NULL;
        if(root->val == val)
            return root;
        
        if(root->val < val)
            return find(root->r, val);
        else
            return find(root->l, val);
    }

    Node* getParent(Node* root, Node* p)
    {
        if(root->l == p or root->r == p)
            return root;
        if(p->val > root->val)
            return getParent(root->r, p);
        else
            return getParent(root->l, p);
    }

    Node* getMin(Node* root)
    {
        if(root->r)
            return getMin(root->l);
        
        return root;
    }

    void deleteElem(Node* root, int val)
    {
        auto p = find(root, val);
        auto parent = getParent(this->root, p);
        int cnt = !p->l + !p->r;
        if(cnt == 2)
            parent->l == p ? parent->l = NULL : parent->r = NULL;
        else if(cnt == 1)
        {
            if(parent->l == p)
                parent->l = (p->l ? p->l : p->r);
            else
                parent->r = (p->l ? p->l : p->r);
        }
        else
        {
            auto t = getMin(p->r);
            auto v = t->val;
            deleteElem(p->r, v);
            p->val = v;
        }
    }
};

void printUI()
{
    printf("1. ����һ�ö���������\n");
    printf("2. �������������������\n");
    printf("3. ���ң�����һ���ؼ��֣����в���\n");
    printf("4. ���룺����һ���ؼ��֣����в���\n");
    printf("5. ɾ��������һ���ؼ��֣�����ɾ��\n");
    printf("6. �Ӵ�С������������������йؼ��ֲ�С��x������Ԫ��\n");
}

int main(int argc, char const *argv[])
{
    printUI();
    int choice, t = 0, val;
    bool flag = true;
    BiSearchTree tree;
    vector<int> arr{39, 11, 68, 46, 75, 23, 71, 8, 86, 34, -1};
    while(flag)
    {
        cout << "\n������ѡ��: " << endl;
        cin >> choice;
        switch(choice)
        {
        case 1:
            arr.clear();
            t = 0;
            while(t != -1)
            cin >> t, arr.push_back(t);
            tree = BiSearchTree(arr);
            break;
        case 2:
            tree.printTree();
            break;
        case 3:
            cout << "������Ҫ���ҵ�Ԫ��:" << endl;
            cin >> val;
            if(tree.find(tree.root, val))
                cout << "�ҵ�!!!" << endl;
            else
                cout << "δ�ҵ�!!!" << endl;
            break;
        case 4:
            cout << "������Ҫ�����Ԫ��:" << endl;
            cin >> val;
            tree.insert(tree.root, val);
            tree.printTree();
            break;
        case 5:
            cout << "������Ҫɾ����Ԫ��:" << endl;
            cin >> val;
            tree.deleteElem(tree.root, val);
            tree.printTree();
            break;
        case 6:
            cout << "������x:" << endl;
            cin >> val;
            cout << val << " ";
            tree.dfs(tree.find(tree.root, val)->r);
            break;
        default:
            flag = false;
            break;
        }
    }

    cout << "��ӭʹ��!!!" << endl;
}