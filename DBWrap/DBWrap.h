/*
 * DBWrap.h
 *
 *  Created on: Jun 11, 2015
 *      Author: young
 */

#ifndef WESTATUSSERVER_DBWRAP_H_
#define WESTATUSSERVER_DBWRAP_H_

#include <stdint.h>

#include <string>
#include <vector>
using std::string;
using std::vector;

class DBWrap
{
public:
    DBWrap(){}
    virtual ~DBWrap(){}

    virtual void Init()=0;
    virtual bool Put(uint32_t key, string &value)=0;
    virtual bool Get(uint32_t key, string &value)=0;
    virtual vector<bool> Get(vector<uint32_t> &key, vector<string> &value)=0;
    virtual bool Del(uint32_t key_list)=0;
};


#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
class RocksDBWrap:public DBWrap
{
public:
    RocksDBWrap(string &db_path):m_DBPath(db_path), m_DB(NULL){}
    ~RocksDBWrap(){delete m_DB;}

    void Init();
    bool Put(uint32_t key, string &value);
    bool Get(uint32_t key, string &value);
    vector<bool> Get(vector<uint32_t> &key, vector<string> &value);
    bool Del(uint32_t key);



    static void ToDBKey(vector<uint32_t> &key_list0, vector<rocksdb::Slice> &key_list1)
    {
        char buff[128];
        for(uint32_t i=0; i<key_list0.size(); ++i)
        {
            snprintf(buff, 128, "%d", key_list0[i]);
            rocksdb::Slice s(buff, strlen(buff));
            key_list1.push_back(s);
        }
    }
private:
    string m_DBPath;
    rocksdb::DB* m_DB;
};

inline
void RocksDBWrap::Init()
{
    rocksdb::Options options;
    // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
    options.IncreaseParallelism();
    options.OptimizeLevelStyleCompaction();
    // create the DB if it's not already present
    options.create_if_missing = true;

    // open DB
    rocksdb::Status s = rocksdb::DB::Open(options, m_DBPath, &m_DB);
    assert(s.ok());
}

inline
bool RocksDBWrap::Put(uint32_t key, string &value)
{
    char buff[128];
    snprintf(buff, 128, "%d", key);
    rocksdb::Slice key_(buff, strlen(buff));

    rocksdb::Status s = m_DB->Put(rocksdb::WriteOptions(), key_, value);
    return s.ok()?true:false;
}

inline
bool RocksDBWrap::Get(uint32_t key, string &value)
{
    char buff[128];
    snprintf(buff, 128, "%d", key);
    rocksdb::Slice key_(buff, strlen(buff));

    rocksdb::Status s = m_DB->Get(rocksdb::ReadOptions(), key_, &value);
    return s.ok()?true:false;
}

inline
vector<bool> RocksDBWrap::Get(vector<uint32_t> &key, vector<string> &value)
{
    vector<rocksdb::Slice> key_list_;
    ToDBKey(key, key_list_);
    vector<rocksdb::Status> s = m_DB->MultiGet(rocksdb::ReadOptions(), key_list_, &value);

    vector<bool> ret;
    for(uint32_t i=0; i<s.size(); ++i)
    {
        ret.push_back(s[i].ok()?true:false);
    }
    return ret;
}

inline
bool RocksDBWrap::Del(uint32_t key)
{
    char buff[128];
    snprintf(buff, 128, "%d", key);
    rocksdb::Slice key_(buff, strlen(buff));

    rocksdb::Status s = m_DB->Delete(rocksdb::WriteOptions(), key_);
    return s.ok()?true:false;
}

#endif /* WESTATUSSERVER_DBWRAP_H_ */
