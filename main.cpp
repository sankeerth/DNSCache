#include "DNSCache.h"
#include "DNSCacheImpl.h"

int main()
{
    DNSCache *dns = DNSCache::create();
    dns->insert("107.108.219.69", "www.samsung.com");
    std::string str = dns->search("107.108.219.69");
    std::cout << str << std::endl;
	return 0;
}
