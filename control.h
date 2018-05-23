#ifndef CONTROL_H
#define CONTROL_H

#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<sstream>
#include"myinclude.h"

class my_fs
{
public:
    void myshell();
    void run();
    my_fs();

private:
    superblock sp;
    Inode cur_dir_node;
    sector_dir cur_dir;
}
#endif // CONTROL_H
