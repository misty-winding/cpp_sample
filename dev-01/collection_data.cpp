#include <map>
#include <string>
#include <boost/shared_ptr.hpp>


using std::map;
using std::string;
using boost::shared_ptr;


template <class KEY, class VALUE>
class DataCollection
{
public:
    typedef typename std::map<KEY, VALUE>::value_type value_type;
    typedef typename std::map<KEY, VALUE>::iterator iterator;
    typedef typename std::map<KEY, VALUE>::pointer pointer;

    size_t GetNum(void)
    {
        return collection_.size();
    }

    void Add(VALUE p_element)
    {
        int key = p_element->GetKey();
        collection_.insert(value_type(key, p_element));
    }

    VALUE GetValuePtr(KEY key)
    {
        iterator iter;
        iter = collection_.find(key);
        if (iter == collection_.end()) {
            return NULL;
        } else {
            return iter->second;
        }
    }

private:
    map<KEY, VALUE> collection_;
};


class DataCommon
{
public:
    DataCommon(int key) : key_(key) {}
    int GetKey(void) { return key_; }

private:
    int key_;
};


class TopB1 : public DataCommon
{
public:
    TopB1(int key) : DataCommon(key) {}

private:
    static const string name;
};

const string TopB1::name = "TopB1";


class TopB2 : public DataCommon
{
public:
    TopB2(int number) : DataCommon(number) {}

private:
    static const string name;
};

const string TopB2::name = "TopB2";


class TopA1 : public DataCommon
{
public:
    typedef shared_ptr<TopB1> PtrTopB1;
    typedef shared_ptr<TopB2> PtrTopB2;

    TopA1(int key) : DataCommon(key) {}

private:
    static const string name;
    DataCollection<int, PtrTopB1> ap_top_b1_table_;
    DataCollection<int, PtrTopB2> ap_top_b2_table_;
};

const string TopA1::name = "TopA1";


class TopA1Holder
{
public:
    typedef shared_ptr<TopA1> PtrTopA1;
    typedef DataCollection<int, PtrTopA1>* CollectionPtr;

    size_t GetTopA1Num(void)
    {
        return ap_top_a1_table_.GetNum();
    }

    void AddTopA1(PtrTopA1 p_top_a1)
    {
        ap_top_a1_table_.Add(p_top_a1);
    }

    PtrTopA1 GetTopA1Ptr(int key)
    {
        return ap_top_a1_table_.GetValuePtr(key);
    }

    CollectionPtr GetCollectionPtr(void)
    {
        return &ap_top_a1_table_;
    }

private:
    DataCollection<int, PtrTopA1> ap_top_a1_table_;
};

// EOF

