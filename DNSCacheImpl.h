#ifndef DNS_CACHE_IMPL_H
#define DNS_CACHE_IMPL_H

#include <iostream>
#include <string.h>

class Node;

class DNSCacheImpl
{
  public:
  	DNSCacheImpl();
  	~DNSCacheImpl();
    void insert(std::string& str, std::string& value);
    std::string search(std::string& str);
    void lookup(std::string& str);
  private:
  	void insertIp(std::string& ip, std::string& url);
  	void insertUrl(std::string& url, std::string& ip);
  	std::string searchIp(std::string& str);
  	std::string searchUrl(std::string& str);
  	Node* lookupIp(std::string& str);
  	Node* lookupUrl(std::string& str);

  	Node *m_ipLookup;
  	Node *m_urlLookup;
};

class Node
{
  public:
  	Node();
  	virtual ~Node();
    void setChar(char c);
    char getChar();
    void setEnd(bool value);
    bool getEnd();
    virtual Node* getChild(int index) = 0;
  	virtual void setChild(Node *child, int index) = 0;
  	virtual const char* getIp() {std::cout << "hi" << std::endl;}
  	virtual void setIp(const char* ip) {std::cout << "hi" << std::endl;}
  	virtual const char* getUrl() {std::cout << "hi" << std::endl;}
  	virtual void setUrl(const char* url) {std::cout << "hi" << std::endl;}
  private:
  	char m_character;
  	bool m_endOfString;
};

class IpNode : public Node
{
  public:
  	IpNode();
  	virtual ~IpNode();
	virtual Node* getChild(int index);
	virtual void setChild(Node *child, int index);
	virtual const char* getUrl();
  	virtual void setUrl(const char* url);
  private:
  	char *m_Url;
  	Node *m_children[11];
};

class UrlNode : public Node
{
  public:
  	UrlNode();
  	virtual ~UrlNode();
  	virtual Node* getChild(int index);
  	virtual void setChild(Node *child, int index);
  	virtual const char* getIp();
  	virtual void setIp(const char* ip);
  private:
  	char *m_Ip;
  	Node *m_children[27];
};
#endif
