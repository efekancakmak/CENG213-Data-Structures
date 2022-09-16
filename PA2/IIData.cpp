#include "IIData.hpp"

IIData::IIData() {

}

IIData::IIData(const std::string &word) {

    this->word = word;
}

std::string &IIData::getWord() {

    return word;
}

std::vector<std::pair<std::string, std::vector<int> > > &IIData::getOccurrences() {

    return occurrences;
}

void IIData::setWord(const std::string &word) {

    this->word = word;
}

void IIData::setOccurrences(const std::vector<std::pair<std::string, std::vector<int> > > &occurrences) {

    this->occurrences = occurrences;
}

void IIData::addOccurrence(const std::string &documentName, int position) {
    int check = 0;
    std::vector<int> ints;
    std::vector<std::pair< std::string, std::vector< int > > >::iterator start = occurrences.begin();
    for( ; start!=occurrences.end(); ++start){
        if(start->first==documentName){
            start->second.push_back(position);
            check = 1;
            break;
        }
        check = 0;
    }
    if(check==0){
        std::pair< std::string, std::vector< int > > nw;
        nw.first = documentName;
        nw.second.push_back(position);
        occurrences.push_back(nw);
        return;
    }
    else if(check==1){
        std::vector<int>::iterator trv = start->second.begin();
        for( ; trv+1 != start->second.end() ; ++trv){
            if(*trv > *(trv+1)){
                int temp = *trv;
                *trv = *(trv+1);
                *(trv+1) = temp;
            }
        }
    }
}
    
void IIData::removeOccurrences(const std::string &documentName) {
    std::vector<std::pair< std::string, std::vector< int > > >::iterator start;
    for (start = occurrences.begin(); start != occurrences.end(); ++start) { 
        if ((*start).first == documentName) { 
            occurrences.erase(start);
            --start;
        } 
    }
}


bool IIData::operator<(const IIData &rhs) const {

    return word < rhs.word;
}

bool IIData::operator>(const IIData &rhs) const {

    return word > rhs.word;
}

bool IIData::operator==(const IIData &rhs) const {

    return word == rhs.word;
}

std::ostream &operator<<(std::ostream &os, const IIData &data) {

    os << "{";
    os << "word: " << data.word << ", ";
    os << "occurrences: [";
    for (unsigned int i = 0 ; i < data.occurrences.size() ; ++i) {
        os << "(";
        os << data.occurrences[i].first << ", ";
        os << "[";
        if (!data.occurrences[i].second.empty()) {
            for (unsigned int j = 0 ; j < data.occurrences[i].second.size() - 1; ++j) {
                os << data.occurrences[i].second[j] << ", ";
            }
            os << data.occurrences[i].second[data.occurrences[i].second.size() - 1];
        }
        os << "]";
        os << ")";
        if (i != data.occurrences.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    os << "}";

    return os;
}
