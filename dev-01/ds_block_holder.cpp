#include <map>
#include <boost/shared_ptr.hpp>


using std::map;
using boost::shared_ptr;


class DsBase
{

};

class DsBlockData : public DsBase
{

};


class DsBlockHolder
{
public:
	typedef shared_ptr<DsBase*> PBlockDataTable;

private:
	map<int, DsBase> ap_block_table_;
};


// EOF
	
