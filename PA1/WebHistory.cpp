#include "WebHistory.hpp"

WebHistory::WebHistory()
{
    // Does nothing.
}

WebHistory::WebHistory(std::string historyText)
{
	// history = url timestamp | url timestamp | url timestamp...
    // urls are string and timestamps are non-negative integers.
    std::string delimiter = " | ";

	std::string tabInfo;
    std::string url;
    std::string timestamp;
    size_t pos = 0;

    while (true)
	{
        pos = historyText.find(delimiter);

        bool breakTheLoop = (pos == std::string::npos);

        tabInfo = historyText.substr(0, pos);
        historyText.erase(0, pos + delimiter.length());

        pos = tabInfo.find(" ");
        
        url = tabInfo.substr(0, pos);
        timestamp = tabInfo.substr(pos + 1, tabInfo.length() - pos);

		Node<Tab> *newPage = new Node<Tab>(Tab(url, std::atoi(timestamp.c_str())), NULL, NULL);
        insertInOrder(newPage);

        if (breakTheLoop)
		{
			break;
		}
    }
}

void WebHistory::printHistory()
{
	std::cout << "Your web history:" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << std::endl;
	if (history.getHead()->next == history.getTail())
	{
		std::cout << "History is empty." << std::endl;
		std::cout << std::endl;
	}
	else
	{
		Node<Tab> *node = history.getFirstNode();
		
		while (node != history.getTail())
		{
		    std::cout << "Page: " << node->element.getUrl() << std::endl;
			std::cout << "Last Visited: " << node->element.getTimestamp() << std::endl;
			std::cout << std::endl;
		    node = node->next;
		}
	}
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << std::endl;
}

WebHistory::WebHistory(std::string url, int timestamp)
{
    Tab nw;
    nw.setUrl(url);
    nw.setTimestamp(timestamp);
    history.insertAtTheFront(nw);
}

WebHistory::~WebHistory()
{
	history.removeAllNodes();
}

void WebHistory::insertInOrder(Node<Tab> *newPage)
{
	Node<Tab> *trv = history.getHead();
	Node<Tab> *ftail = history.getTail();
	Node<Tab> *fhead = history.getHead();
	if(trv->next==ftail){
		fhead->next = newPage;
		ftail->prev = newPage;
		newPage->prev = fhead;
		newPage->next = ftail;
		return;
	}
	trv=trv->next;
	if(trv->element <= newPage->element){
	    fhead->next = newPage;
	    trv->prev = newPage;
	    newPage->next= trv;
	    newPage->prev= fhead;
	    return;
	}
	while(trv!=ftail){
		if(trv->next==ftail){
			newPage->next = ftail;
			newPage->prev = trv;
			trv->next = newPage;
			ftail->prev = newPage;
			break;
		}
		if(trv->element.getTimestamp() > newPage->element.getTimestamp() && trv->next->element <= newPage->element){
			newPage->next = trv->next;
			newPage->prev = trv;
			trv->next = newPage;
			newPage->next->prev = newPage;
			break;
		}
		trv = trv->next;
	}
}


void WebHistory::goToPage(std::string url, int timestamp)
{
	Node<Tab> *ft = history.getTail();
	Node<Tab> *fh = history.getHead();
	Tab nw;
	nw.setUrl(url);
	nw.setTimestamp(timestamp);
	Node<Tab> *trv = fh;
	if(trv->next==ft){
		history.insertAtTheEnd(nw);
		return;
	}
	trv=trv->next;
	if(trv->element.getTimestamp() <= timestamp){
	    history.insertAtTheFront(nw);
	    return;
	}
	while(trv!=ft){
		if(trv->next==ft){
			history.insertAtTheEnd(nw);
			break;
		}
		if(trv->element.getTimestamp() > timestamp && trv->next->element.getTimestamp() <= timestamp){
			history.insertAfterGivenNode(nw,trv);
			break;
		}
		trv = trv->next;
	}

}


void WebHistory::clearHistory()
{
	history.removeAllNodes();
}

void WebHistory::clearHistory(int timestamp)
{
	Node<Tab> *trv = history.getHead();
	Node<Tab> *ftail = history.getTail();
	if(trv->next==ftail)
		return;
	trv = trv->next;
	if(timestamp >= trv->element.getTimestamp()){
		clearHistory();
		return;
	}
	while(trv->element.getTimestamp() > timestamp){
		if(trv->next!=ftail)
			trv=trv->next;
		else
			return;
	}
	while(trv!=ftail){
		history.removeNode(trv);
		trv=trv->next;
	}
}

WebHistory WebHistory::operator+(const WebHistory &rhs) const
{
	WebHistory result;
	result.history = history;
	Node<Tab> *trv = rhs.history.getHead();
	Node<Tab> *ftail = rhs.history.getTail();
	if(trv->next==ftail)
		return result;
	trv=trv->next;
	while(trv!=ftail){
		result.goToPage(trv->element.getUrl(),trv->element.getTimestamp());
		trv=trv->next;
	}
	return result;
}

int WebHistory::timesVisited(std::string pageName)
{
	int sum=0;
	Node<Tab> *fh= history.getHead();
	Node<Tab> *ft= history.getTail();
	if(fh->next==ft)
		return sum;
	fh=fh->next;
	while(fh!=ft){
		if(fh->element.getWebSite() == pageName)
			sum++;
		fh=fh->next;
	}
	return sum;
}


std::string WebHistory::mostVisited()
{
	Node<Tab> *trv = history.getHead();
	Node<Tab> *cur = history.getHead();
	Node<Tab> *ft = history.getTail();
	std::string temp;
	std::string result;
	int count=0;
	int lastcount=0;
	if(trv->next==ft)
		return "";
	trv=trv->next;
	cur=trv;
	temp = trv->element.getWebSite();
	while(trv!=ft){
		temp = trv->element.getWebSite();
		count=0;
		while(cur!=ft){
			if(cur->element.getWebSite() == temp)
				count++;
			cur=cur->next;
		}
		if(count > lastcount){
			lastcount = count;
			result = trv->element.getWebSite();
		}
		trv=trv->next;
		cur = trv;
	}
	return result;
}