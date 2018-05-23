#include "myinclude.h"

Buffer::Buffer()
{
    disk.open(DISK, std::fstream::in | std::fstream::out | std::fstream::binary);
    if(disk.is_open())
        cout << "文件已打开" << endl;
    else
        cout << "文件未打开" << endl;
}

Buffer::~Buffer()
{
    disk.close();
}

bool Buffer::write_disk(const BufferNode &node)
{
    assert(node.sec_num >= 0 && node.sec_num < MAX_SEC);
    int i;
    i = has_sec(node.sec_num);
    if(i >= 0)
    {
        cout << "write disk: 缓存中存在该扇区" << endl;
        cache[i].update(node);
        return true;
    }

    i = is_full();
    if(i >= 0)
    {
        cout << "write disk: 缓存已满，替换第" << i << "号缓存" << endl;
        real_disk_write(cache[i]);
        cache.erase(cache.begin() + i);
    }
    cache.push_back(node);
    cout << "write disk: 数据已写入缓存中" << endl;
    return true;
}

bool Buffer::read_disk(int sec_num, BufferNode &node)
{
    assert(sec_num >= 0 && sec_num < MAX_SEC);

    int i;
    i = has_sec(sec_num);

    if(i >= 0)
    {
        cout << "read disk: 缓存中存在该扇区" << endl;
        node.update(cache[i]);
        return true;
    }

    i = is_full();
    if(i >= 0)
    {
        cout << "read disk: 缓存已满，替换第" << i << "号缓存" << endl;
        real_disk_write(cache[i]);
        cache.erase(cache.begin() + i);
        real_disk_read(sec_num, node);
        node.init(sec_num);
        cache.push_back(node);
    }
    else
    {
        real_disk_read(sec_num, node);
        node.init(sec_num);
        cache.push_back(node);
        cout << "read disk: 缓存未满，磁盘扇区已存入缓存" << endl;
    }
    return true;
}

bool Buffer::real_disk_write(const BufferNode &node)
{
    assert(node.sec_num >= 0 && node.sec_num < MAX_SEC);
    cout << "read disk write 写回第" << node.sec_num << "号扇区" << endl;
    disk.seekg(sec_num * SEC_SIZE, disk.beg);
    disk.read(node.buffer, SEC_SIZE);
    node.buffer[SEC_SIZE] = '\0';
    node.sec_num = sec_num;
    return true;
}

int Buffer::has_sec(int sec_number)
{
    for(int i = 0; i < cache.size(); i++)
    {
        if(cache[i].sec_num == sec_number)
            return i;
    }
    return -1;
}

int Buffer::is_full()
{
    if(cache.size() == 15)
    {
        int min = 9999;
        int min_i = 0;
        for(int i = 0; i < cache.size(); i++)
        {
            if(cache[i].pri < min)
            {
                min = cache[i].pri;
                min_i = i;
            }
        }
        return min_i;
    }
    else
    {
        return -1;
    }
}
