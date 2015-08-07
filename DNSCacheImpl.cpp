#include "DNSCacheImpl.h"
#include "log.h"
#include <string.h>
#include <ctype.h>

namespace {
	const int DIGITS_LENGTH = 11;
	const int CHAR_LENGTH = 27;

	int getIpIndex(char c) { return (c == '.')? 10: (c - '0'); }

	int getUrlIndex(char c) { return (c == '.') ? 26 : (c - 'a'); }
} // anonymous namespace

DNSCacheImpl::DNSCacheImpl()
	: m_ipLookup(new IpNode)
	, m_urlLookup(new UrlNode)
{}

DNSCacheImpl::~DNSCacheImpl()
{
	// delete m_ipLookup;
	// delete m_urlLookup;
}

void DNSCacheImpl::insert(std::string& str, std::string& value)
{
	if (isdigit(str[0])) {
		insertIp(str, value);
	} else if (isalpha(str[0])) {
		insertUrl(str, value);
	} else {
		LOG("Enter correct Url");
	}
}

std::string DNSCacheImpl::search(std::string& str)
{
	if (isdigit(str[0])) {
		return searchIp(str);
	} else if (isalpha(str[0])) {
		return searchUrl(str);
	} else {
		LOG("Enter correct Url");
	}
}

void DNSCacheImpl::lookup(std::string& str)
{
	if (isdigit(str[0])) {
		lookupIp(str);
	} else if (isalpha(str[0])) {
		lookupUrl(str);
	} else {
		LOG("Enter correct Url");
	}
}

void DNSCacheImpl::insertIp(std::string& ip, std::string& url)
{
	Node *current = m_ipLookup, *child = NULL;
	int index;
	for (std::string::iterator it = ip.begin(); it != ip.end(); ++it) {
		index = getIpIndex(*it);
        child = current->getChild(index);
        if (child) {
			current = child;
		} else {
			child = new IpNode();
			child->setChar(*it);
			current->setChild(child, index);
			current = child;
		}
	}
	current->setEnd(true);
    current->setUrl(url.c_str());
}

void DNSCacheImpl::insertUrl(std::string& url, std::string& ip)
{
	Node *current = m_urlLookup, *child = NULL;
	int index = 0;
	for (std::string::iterator it = url.begin(); it != url.end(); ++it) {
		index = getUrlIndex(*it);
		if (child = current->getChild(index)) {
			current = child;
		} else {
			child = new UrlNode();
			child->setChar(*it);
			current->setChild(child, index);
			current = child;
		}
	}
	current->setEnd(true);
    current->setIp(ip.c_str());
}

std::string DNSCacheImpl::searchIp(std::string& str)
{
	Node *current = m_ipLookup;
	int index = 0;
	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
		index = getIpIndex(*it);
		if (!(current = current->getChild(index))) {
			return "-1";
		} else {
            if (it == str.end()-1) {
				if (current->getEnd() && current->getUrl()) {
					return current->getUrl();
				} else {
					return "-1";
				}
			}
		}
	}
}

std::string DNSCacheImpl::searchUrl(std::string& str)
{
	Node *current = m_urlLookup;
	int index = 0;
	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
		index = getUrlIndex(*it);
		if (!(current = current->getChild(index))) {
			return "-1";
		} else {
			if (it == str.end()-1) {
				if (current->getEnd() && current->getIp()) {
					return current->getIp();
				} else {
					return "-1";
				}
			}
		}
	}
}

Node* DNSCacheImpl::lookupIp(std::string& str)
{

}

Node* DNSCacheImpl::lookupUrl(std::string& str)
{

}

Node::Node()
	: m_character(' ')
	, m_endOfString(false)
{}

Node::~Node()
{
	
}

void Node::setChar(char c)
{
	m_character = c;
}

char Node::getChar()
{
	return m_character;
}

void Node::setEnd(bool value)
{
	m_endOfString = value;
}

bool Node::getEnd()
{
	return m_endOfString;
}

IpNode::IpNode()
	: Node()
	, m_Url(NULL)
{
	for (int i = 0; i <= 10; ++i) {
		m_children[i] = NULL;
	}
}

IpNode::~IpNode()
{

}

Node* IpNode::getChild(int index)
{
	if (index < 11) {
		return m_children[index];	
	}
	return NULL;
}

void IpNode::setChild(Node *child, int index)
{
	m_children[index] = child;
}

const char* IpNode::getUrl()
{
	return m_Url;
}

void IpNode::setUrl(const char* url)
{
	int len = strlen(url);
	m_Url = new char[len];
	strcpy(m_Url, url);
	
}

UrlNode::UrlNode()
	: Node()
	, m_Ip(NULL)
{
	for (int i = 0; i <= 26; ++i) {
		m_children[i] = NULL;
	}
}

UrlNode::~UrlNode()
{

}

Node* UrlNode::getChild(int index)
{
	if (index < 27) {
		return m_children[index];	
	}
	return NULL;
}

void UrlNode::setChild(Node *child, int index)
{
	m_children[index] = child;
}

const char* UrlNode::getIp()
{
	return m_Ip;
}

void UrlNode::setIp(const char* ip)
{
	int len = strlen(ip);
	m_Ip = new char[len];
	strcpy(m_Ip, ip);
}
