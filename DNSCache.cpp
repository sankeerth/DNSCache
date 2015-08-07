#include "DNSCache.h"
#include "DNSCacheImpl.h"

DNSCache::DNSCache()
    : m_impl(new DNSCacheImpl)
{}

DNSCache::~DNSCache()
{
	delete m_impl;
}

void DNSCache::insert(std::string str, std::string value)
{
	m_impl->insert(str, value);
}

std::string DNSCache::search(std::string str)
{
	return m_impl->search(str);
}

void DNSCache::lookup(std::string str)
{
	m_impl->lookup(str);
}
