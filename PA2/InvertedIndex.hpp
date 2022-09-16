#ifndef INVERTEDINDEX_HPP
#define INVERTEDINDEX_HPP

#include "BST.hpp"
#include "IIData.hpp"

class InvertedIndex {
public: // DO NOT CHANGE THIS PART.
    InvertedIndex();
    InvertedIndex(const InvertedIndex &obj);

    ~InvertedIndex();

    BST<IIData> &getInvertedIndex();

    InvertedIndex &addDocument(const std::string &documentName);
    InvertedIndex &removeDocument(const std::string &documentName);
    InvertedIndex &searchWord(const std::string &word);
    InvertedIndex &printInvertedIndex();

    InvertedIndex &operator=(const InvertedIndex &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    BSTNode<IIData>* finder(BSTNode<IIData>* root,std::string docname);

private: // DO NOT CHANGE THIS PART.
    BST<IIData> invertedIndex;
};

#endif //INVERTEDINDEX_HPP
