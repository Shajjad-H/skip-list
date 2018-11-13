#ifndef __SKIP_LIST_H__SH_
#define __SKIP_LIST_H__SH_


#include <vector>
#include <stdlib.h>
#include <stack>

typedef size_t tailleDesTabs;

template <typename DataType>
class SkipList;

template <typename DataType>
class Cellule
{
   friend class SkipList<DataType>;
private:
    DataType info;
    std::vector<Cellule *> m_suivants;
public:
    Cellule();
    Cellule(const DataType& info,const tailleDesTabs nb_etage=0);
    tailleDesTabs nb_etages() const;
    Cellule * dernierEtage() const;
    Cellule * etage(const tailleDesTabs n_etage) const;
    void print() const;
    DataType get_info() const;
    
};

template <typename DataType>
class SkipList
{
private:
    Cellule<DataType> * ad;
    void printEtage(const tailleDesTabs etage) const;
    bool tropLoin(const Cellule<DataType>* it,const tailleDesTabs etage, const DataType &info ) const;
    tailleDesTabs get_nb_etage() const;
    std::stack<Cellule<DataType>*> get_cellule_to_link(Cellule<DataType> * it, const DataType & info,bool doublon);
    Cellule<DataType> * insRec(Cellule<DataType> * it,const tailleDesTabs etage, const DataType &e);
    bool egale_s(const Cellule<DataType> * c,const tailleDesTabs etage, const DataType &e) const;
    bool small_s(const Cellule<DataType> * c,const tailleDesTabs etage, const DataType &e) const;
public:
    SkipList();
    SkipList(const SkipList<DataType> & l);
    ~SkipList();
    void print() const;
    void insert(const DataType & e,bool doublon = false);
    /**
     * precondition: aucun
     * postcondition:
     * return nullptr si e n'est pas dans la liste
     * sinon la cellule qui contient e
    */
    Cellule<DataType> * find(const DataType & e) const;
    bool exists(const DataType &e) const;
    void empty();
    void sup_ele(const DataType & e);
    //Cellule<DataType> * insRec(Cellule<DataType> *c, Cellule<DataType> * nc, tailleDesTabs etage);
    void insertRec(const DataType &e);


};



#endif



#include "SkipList.cpp"