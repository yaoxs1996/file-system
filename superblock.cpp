#include"myinclude.h"

superblock::superblock()
{
    memset(inode_bitmap, 0, sizeof(inode_bitmap));
    memset(block_bitmap, 0, sizeof(block_bitmap));
}

int superblock::remain_inode()
{
    int count = 0;
    for(int i = 0; i < INODE_NUM; i++)
    {
        if(!inode_bitmap[i])
        {
            count++;
        }
    }
    return count;
}

int superblock::remain_sec()
{
    int count = 0;
    for(int i = 0; i < INODE_NUM; i++)
    {
        if(!block_bitmap[i])
        {
            count++;
        }
    }
    return count;
}

int superblock::get_new_inode()
{
    for(int i = 0; i < INODE_NUM; i++)
    {
        if(!inode_bitmap[i])
        {
            inode_bitmap[i] = true;
            return i;
        }
    }
    return -1;
}

int superblock::get_new_sec()
{
    for(int i = 0; i < BLOCK_NUM; i++)
    {
        if(!block_bitmap[i])
        {
            block_bitmap[i] = true;
            return i + INODE_BEGIN / 512 + (INODE_NUM * sizeof(Inode)) / 512;
        }
    }
    return -1;
}

bool superblock::recv_inode(int inode_num)
{
    assert(inode_num >= 0 && inode_num < INODE_NUM);
    inode_bitmap[inode_num] = false;
    return true;
}

bool superblock::recv_sec(int sec_num)
{
    assert(sec_num >= 0 && sec_num < BLOCK_NUM);
    block_bitmap[sec_num] = false;
    return true;
}

bool superblock::init()
{
    memset(inode_bitmap, 0, sizeof(inode_bitmap));
    memset(inode_bitmap, 0, sizeof(block_bitmap));
    return true;
}
