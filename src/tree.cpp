#include "tree.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int counter[1000000]; //pinakas gia ton ari8mo twn links tou ka8e kombou
bool done;
int i = 0;
node *temp;
int key;
node *temp2;
node *parent;
node *temp3;



ClassInvertedIndex::ClassInvertedIndex()
{
    root = NULL;
}



int ClassInvertedIndex::height(node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}



int ClassInvertedIndex::difference(node *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int sum = l_height - r_height;
    return sum;
}



node *ClassInvertedIndex::balance(node *temp)
{
    int diff = difference(temp);
    if (diff > 1)
    {
        if (difference(temp->left)>0)
            temp = l_rotation(temp);
        else
            temp = lr_rotation(temp);
    }
    else if (diff < -1)
    {
        if (difference(temp->right) > 0)
            temp = rl_rotation(temp);
        else
            temp = r_rotation(temp);
    }
    return temp;
}



//left rotation
node *ClassInvertedIndex::l_rotation(node *parent)
{
    node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}



//right rotation
node *ClassInvertedIndex::r_rotation(node *parent)
{
    node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}



//right-left rotation
node *ClassInvertedIndex::rl_rotation(node *parent)
{
    node *temp;
    temp = parent->right;
    parent->right = l_rotation(temp);
    return r_rotation(parent);
}



//left-right rotation
node *ClassInvertedIndex::lr_rotation(node *parent)
{
    node *temp;
    temp = parent->left;
    parent->left = r_rotation(temp);
    return l_rotation(parent);
}



node *ClassInvertedIndex::insert(node *root,int x,int b)
{
    i = x;
    //dhmiourgia kombou an den yparxei
    if (root == NULL)
    {
        root = new node;
        root->data = x;
        root->left = NULL;
        root->right = NULL;
        root->linked = NULL;
        cout<<root->data<<endl;
        root = link(b,root);
        return root;
    }

    if(x < root->data)
    {
        root->left = insert(root->left,x,b);
        root = balance(root);
    }
    else if(x > root->data)
    {
        root->right = insert(root->right,x,b);
        root = balance(root);
    }
    else if (x == root->data)
    {
        root = link(b,root);
    }
    return root;
}



node *ClassInvertedIndex::link(int b,node *temp)
{
    //dhmiourgia dentrou avl gia tous geitones, se periptwsh pou den yparxei
    if (temp->linked == NULL)
    {
        counter[i]++;
        temp->linked = new node;
        temp->linked->left = NULL;
        temp->linked->right = NULL;
        temp->linked->data = b;
        return temp;
    }
    else
    {
        temp->linked = link2(b,temp->linked);
        return temp;
    }
}



node *ClassInvertedIndex::link2(int b,node *temp)
{
    if (temp == NULL)
    {
        counter[i]++;
        temp = new node;
        temp->left = NULL;
        temp->right = NULL;
        temp->data = b;
        return temp;
    }
    if (b > temp->data)
    {
        temp->right = link2(b,temp->right);
        temp = balance(temp);
    }
    else if (b < temp->data)
    {
        temp->left = link2(b,temp->left);
        temp = balance(temp);
    }
    else
    {
        return temp;
    }
}



void ClassInvertedIndex::READ_DATA(char text[20])
{
    ifstream f;
    f.open(text, ios::in);
    if (f == NULL)
    {
        cout << "Error";
        return;
    }

    //diabasma kombou kai geitona apo to arxeio
    while (true)
    {
        int a;
        int b;
        f >> a;
        f >> b;
        root = insert(root,a,b);
        if (f.eof())
        {
            break;
        }
    }
    f.close();
}



void inorder2(node *root,ofstream& k)
{
    if (root == NULL)
    {
        return;
    }

    inorder2(root->left,k);

    //katagrafh geitonwn
    if (done == false)
    {
        k<<"Arithmos Geitonwn"<<counter[i]<< " ";
        done = true;
    }
    k<<root->data<<" ";

    inorder2(root->right,k);
}



void inorder(node *root,char text[20])
{
    if (root==NULL)
    {
        return;
    }

    inorder(root->left,text);

    ofstream k;
    k.open(text,ios::app);
    k<<root->data<<" ";
    done = false;
    i = root->data;

    inorder2(root->linked, k);

    k<< endl<<endl;
    k.close();
    i++;

    inorder(root->right,text);
}



void ClassInvertedIndex::WRITE_INDEX(char text[20])
{
    inorder(root,text);
}



void ClassInvertedIndex::INSERT_LINK(int a, int b)
{
    insert(root,a,b);
}



void ClassInvertedIndex::DELETE_LINK(int x,int y)
{
    deleter(root,x,y);
}



void ClassInvertedIndex::deleter (node *root,int x,int y)
{
    temp = root;
    root = finder(root,x);
    if (root == 0)
    {
        return ;
    }

    temp2 = root->linked;
    root->linked = finder(root->linked,y);
    if (root->linked == 0)
    {
        return ;
    }

    cout << root->linked->data;

    if (root->linked->right == NULL && root->linked->left == NULL)
    {
        parent = new node;
        parent = find_parent(temp2,y);

        if (parent->right->data == y)
        {
            root->linked = parent;
            root->linked->right = NULL;
            counter[root->data]--;
            root->linked = temp2;
            root->linked = balance(root->linked);
        }
        else if (parent->left->data == y)
        {
            root->linked = parent;
            root->linked->left = NULL;
            counter[root->data]--;
            root->linked = temp2;
            root->linked = balance(root->linked);
        }
        else
        {
            counter[root->data]--;
        }

        root = temp;
        root->linked = balance(root->linked);
    }
    else if (((root->linked->right == NULL) || (root->linked->left == NULL)) && ((root->linked->right != NULL) || (root->linked->left != NULL)))
    {
        parent = new node;
        parent = find_parent(temp2,y);
        if (root->linked->right != NULL)
        {
            if (root->linked->data < parent->data)
            {
                root->linked = parent;
                root->linked->left = root->linked->left->right;
                root->linked = temp2;
                root->linked = balance(root->linked);
                counter[root->data]--;
            }
            else
            {
                root->linked = parent;
                root->linked->right = root->linked->right->right;
                root->linked = temp2;
                root->linked = balance(root->linked);
                counter[root->data]--;
            }
        }
        else if (root->linked->left != NULL)
        {
            if (root->linked->data < parent->data)
            {
                root->linked = parent;
                root->linked->left = root->linked->left->left;
                root->linked = temp2;
                root->linked = balance(root->linked);
                counter[root->data]--;
            }
            else
            {
                root->linked = parent;
                root->linked->right = root->linked->right->left;
                root->linked = temp2;
                root->linked = balance(root->linked);
                counter[root->data]--;
            }
        }
        root = temp;
        root->linked = balance(root->linked);
    }
    else
    {
        parent = new node;
        parent = find_parent(temp2,y);

        if (root->linked->data < parent->data)
        {
            temp3 = new node;
            temp3 = root->linked;
            root->linked = parent;
            root->linked->left = root->linked->left->right;
            root->linked->left->left = temp3->left;
            root->linked = temp2;
            root->linked = balance(root->linked);
        }
        else
        {
            temp3 = new node;
            temp3 = root->linked;
            root->linked = parent;
            root->linked->right = root->linked->right->left;
            root->linked->right->right = temp3->right;
            root->linked = temp2;
            root->linked = balance(root->linked);
        }

        counter[root->data]--;
        root = temp;
        root->linked = balance(root->linked);
    }

}



node *ClassInvertedIndex::finder(node *root,int x)
{
    if (root->data == x)
    {
        return root;
    }
    else if (root->data < x)
    {
        if (root->right == NULL)
        {
            return 0;
        }

        finder(root->right,x);
    }
    else if (root->data > x)
    {
        if (root->left == NULL)
        {
            return 0;
        }

        finder(root->left,x);
    }
}



node *ClassInvertedIndex::find_parent(node *root,int x)
{
    if (root->data == x)
    {
        delete root;
        return 0;
    }
    else if (root->right == NULL && root->left != NULL)
    {
        if (root->left->data == x )
        {
            return root;
        }
    }
    else if (root->left == NULL && root->left != NULL)
    {
        if (root->right->data == x)
        {
            return root;
        }
    }
    else if (root->left != NULL && root->right != NULL)
    {
        if (root->right->data == x || root->left->data == x)
        {
            return root;
        }
    }

    if (root->data > x)
    {
        root = root->left;
    }
    else if (root->data < x)
    {
        root = root->right;
    }
}
