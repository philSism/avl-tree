#ifndef CLASSINVERTEDINDEX_H
#define CLASSINVERTEDINDEX_H
#include <iostream>
#include <fstream>

//kataskeyazei tous kombous
struct node
{
    public:
        int data;
        struct node *left;
        struct node *right;
        struct node *linked;
};



class ClassInvertedIndex
{
    public:
        node *root;

        //constructor
        ClassInvertedIndex();

        //eisagwgh
        node* insert(node *,int ,int );

        //epistrefei to ypsos
        int height (node *);

        //epistrefei th diafora
        int difference (node *);

        //deixnei an apaiteitai balancing tou dentrou
        node *balance(node *);

        //rotations gia to balancing tou dentrou, meta apo eisagwges kai diagrafes
        node *r_rotation(node *);
        node *l_rotation(node *);
        node *rl_rotation(node *);
        node *lr_rotation(node *);

        void READ_DATA(char[20]);
        void INSERT_LINK(int , int );
        void DELETE_LINK(int x, int y);
        void WRITE_INDEX(char[20]);

        //eisagwgh enos link
        node *link(int ,node *);
        node *link2(int ,node *);

        //diagrafh enos link
        void deleter (node *,int , int);
        node *finder(node *,int);
        node *find_parent(node *,int);
};

#endif // CLASSINVERTEDINDEX_H
