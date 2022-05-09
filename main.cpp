#include <iostream>
#include <string>
#include <tree.h>
#include <stdlib.h>

using namespace std;

int main()
{
    ClassInvertedIndex(test);
    ifstream p;
    p.open("commands.txt",ios::in);
    //anoigei reyma eisodou gia to commands.txt

    //str1 kai str2 aparaithta gia na xrhsimopoihsoyme th find
    string str1 = "INSERT_LINK";
    string str2 = "DELETE_LINK";

    //metablhtes aparaithtes gia thn anagnwsh tou commands.txt
    string a;
    char b[20];
    int c;

    while (true)
    {
        p>>a;
        p>>b;

        if (a == "READ_DATA")
        {
            test.READ_DATA(b);
        }
        else if (a == "WRITE_INDEX")
        {
            test.WRITE_INDEX(b);
        }
        else if (a.find(str1) != string::npos)
        {
            p>>c;
            int ib = atoi(b);
            test.INSERT_LINK (ib,c);
        }
        else if (a.find(str2) != string::npos)
        {
            p>>c;
            int ib = atoi(b);
            test.DELETE_LINK (ib,c);
        }
        if (p.eof())
        {
            break;
        }
    }
    p.close();

}
