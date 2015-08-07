#ifndef DNS_CACHE_H
#define DNS_CACHE_H

#include <iostream>
#include <string.h>

class DNSCacheImpl;
typedef DNSCacheImpl* DNSCacheImplPtr;

class DNSCache
{
  public:
  	static DNSCache* create()
  	{
  		return new DNSCache;
  	}
  	void insert(std::string str, std::string value);
  	std::string search(std::string str);
    void lookup(std::string str);
    ~DNSCache();
  private:
  	DNSCache();

    DNSCacheImplPtr m_impl;
};

#endif