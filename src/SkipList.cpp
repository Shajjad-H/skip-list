#ifndef __SKIP_LIST_CPP__SH_
#define __SKIP_LIST_CPP__SH_

#include "SkipList.h"
#include <iostream>

// inplementation of Cellule
template <typename DataType>
Cellule<DataType>::Cellule()
{
    // m_suivants.push_back(nullptr);
}

template <typename DataType>
Cellule<DataType>::Cellule(const DataType &info, const tailleDesTabs nb_etage)
{
    this->info = info;
    m_suivants.resize(nb_etage, nullptr);
}

template <typename DataType>
void Cellule<DataType>::print() const
{
    std::cout << info << " ";
}

template <typename DataType>
DataType Cellule<DataType>::get_info() const
{
    return info;
}

template <typename DataType>
tailleDesTabs Cellule<DataType>::nb_etages() const
{
    return m_suivants.size();
}
template <typename DataType>
Cellule<DataType> *Cellule<DataType>::dernierEtage() const
{
    return m_suivants.back();
}

template <typename DataType>
Cellule<DataType> *Cellule<DataType>::etage(const tailleDesTabs n_etage) const
{
    if (m_suivants.size() > n_etage)
        return m_suivants[n_etage];
    return dernierEtage();
}

/* 
--------------------------------------------
    inplementation of SkipList
--------------------------------------------
*/
template <typename DataType>
SkipList<DataType>::SkipList()
{
    ad = new Cellule<DataType>;
    ad->m_suivants.push_back(nullptr);
}
template <typename DataType>
SkipList<DataType>::~SkipList()
{
    empty();
}

template <typename DataType>
void SkipList<DataType>::print() const
{
    tailleDesTabs etages = ad->nb_etages();

    do
    {
        printEtage(etages - 1);
        etages--;

    } while (etages != 0);
}

template <typename DataType>
void SkipList<DataType>::printEtage(const tailleDesTabs n_etage) const
{
    Cellule<DataType> *it = ad->m_suivants[n_etage];
    std::cout << "n_etage: " << n_etage << std::endl;
    while (it != nullptr)
    {
        it->print();
        it = it->m_suivants[n_etage];
    }
    std::cout << std::endl;
}

template <typename DataType>
bool SkipList<DataType>::egale_s(const Cellule<DataType> *c,const tailleDesTabs etage, const DataType &e) const
{
    if (c->m_suivants[etage - 1] == nullptr)
        return false;
    if (c->m_suivants[etage - 1]->info != e)
        return false;
    return true;
}

template <typename DataType>
bool SkipList<DataType>::small_s(const Cellule<DataType> *c,const tailleDesTabs etage, const DataType &e) const
{
    if (c->m_suivants[etage - 1] == nullptr)
        return false;

    if (c->m_suivants[etage - 1]->info < e)
        return true;

    return false;
}

// codesign -s gdbcert /usr/local/bin/gdb

template <typename DataType>
Cellule<DataType> *SkipList<DataType>::insRec(Cellule<DataType> *it,const tailleDesTabs etage, const DataType &e)
{
    //std::cout << "etage " << etage << " entry" << std::endl;

    if (egale_s(it, etage, e))
        return nullptr;

    //std::cout << "etage " << etage << " after 1st if" << std::endl;

    if (tropLoin(it, etage, e))
    {

        if (etage == 1)
        {

            //std::cout << "etage " << etage << " time to insert" << std::endl;
            //std::cout << "info " << e << " inserting" << std::endl;

            Cellule<DataType> *nc = new Cellule<DataType>(e, get_nb_etage());
            nc->m_suivants[etage - 1] = it->m_suivants[etage - 1];
            it->m_suivants[etage - 1] = nc;
            return nc;
        }

        //std::cout << "etage " << etage << " etage--" << std::endl;

        Cellule<DataType> *res = insRec(it, etage - 1, e);
        if (res == nullptr)
            return nullptr;

        if (etage <= res->nb_etages())
        {
            //std::cout << "etage " << etage << " linking" << std::endl;
            res->m_suivants[etage - 1] = it->m_suivants[etage - 1];
            it->m_suivants[etage - 1] = res;
        }
        return res;
    }

    //std::cout << "etage " << etage << " going forward" << std::endl;

    while (small_s(it, etage, e) /*it->m_suivants[etage]->info < e*/)
    {
        it = it->m_suivants[etage - 1];
    }
    return insRec(it, etage, e);
}

/*
template <typename DataType>
Cellule<DataType> * SkipList<DataType>::insRec(Cellule<DataType> *c, Cellule<DataType> * nc, tailleDesTabs etage)
{
    if(etage == 0)
        return c;

    if(tropLoin(c,etage,nc->info))
    {
        if(etage <= nc->nb_etages())
        {
            Cellule<DataType> * tmp = insRec(c,nc,etage--);
            nc->m_suivants[etage-1] = tmp->m_suivants[etage-1];
            tmp->m_suivants[etage-1] = nc;

        }
        if(etage == 1)
            return c;
    }
    return insRec(nc->m_suivants[etage-1],nc,etage);
}
*/

template <typename DataType>
void SkipList<DataType>::insertRec(const DataType &e)
{
    Cellule<DataType> *nc = insRec(ad, ad->nb_etages(), e);
    if (nc == nullptr)
        return;
    for (tailleDesTabs i = ad->nb_etages(); i < nc->nb_etages(); i++)
        ad->m_suivants.push_back(nc);
}

template <typename DataType>
std::stack<Cellule<DataType> *> SkipList<DataType>::get_cellule_to_link(Cellule<DataType> *it, const DataType &info, bool doublon)
{
    std::stack<Cellule<DataType> *> p;
    tailleDesTabs etage = it->nb_etages();
    do
    {
        // on ne met pas des doublons
        if (!doublon)
            if (egale_s(it, etage, info))
                return std::stack<Cellule<DataType> *>(); // rien faire on quitte
        /*
            if (it->m_suivants[etage - 1] != nullptr)
                if (it->m_suivants[etage - 1]->info == info)
                    return std::stack<Cellule<DataType> *>(); // rien faire on quitte
            */

        if (tropLoin(it, etage, info))
        {

            //if (etage <= newCellule->nb_etages())
            p.push(it);
            if (etage > 1)
            {
                etage--;
                continue;
            }
            else
                break;
        }
        it = it->m_suivants[etage - 1];

    } while (etage > 0);
    return p;
}

template <typename DataType>
void SkipList<DataType>::insert(const DataType &info, bool doublon)
{
    Cellule<DataType> *it = ad;

    std::stack<Cellule<DataType> *> p = get_cellule_to_link(it, info, doublon);
    /*
    do
    {
        // on ne met pas doublons
        if (!doublon)
            if (it->m_suivants[etage - 1] != nullptr)
                if (it->m_suivants[etage - 1]->info == info)
                {
                    delete newCellule;
                    return; // rien faire on quitte
                }

        if (tropLoin(it, etage, info))
        {

            if (etage <= newCellule->nb_etages())
                p.push(it);
            if (etage > 1)
            {
                etage--;
                continue;
            }
            else
                break;
        }
        it = it->m_suivants[etage - 1];
    } while (etage > 0);
    */
    //std::cout << "first ad size " << ad->m_suivants.size() << std::endl;
    if (p.empty())
    {
        return;
    }

    Cellule<DataType> *newCellule = new Cellule<DataType>(info, get_nb_etage());
    it = nullptr;
    tailleDesTabs etage = 0;
    while (!p.empty() && etage < newCellule->nb_etages())
    {
        it = p.top();
        newCellule->m_suivants[etage] = it->m_suivants[etage];
        it->m_suivants[etage] = newCellule;
        etage++;
        p.pop();
    }
    // p = std::stack<Cellule<DataType> *>();
    //std::cout << "after stack " << etage << std::endl;
    //std::cout << "newCelulle->nb_etage() " << newCellule->nb_etages() << std::endl;
    while (etage < newCellule->nb_etages())
    {
        ad->m_suivants.push_back(newCellule);
        etage++;
    }
    /*std::cout << "inserted " << newCellule->info << std::endl
              << "now printing" << std::endl;
    std::cout << "first ad size " << ad->m_suivants.size() << std::endl;
    print();*/
}
template <typename DataType>
tailleDesTabs SkipList<DataType>::get_nb_etage() const
{
    //return 3;
    tailleDesTabs nb_etage = 1;
    while (rand() % 2)
        nb_etage++;
    return nb_etage;
}
template <typename DataType>
bool SkipList<DataType>::tropLoin(const Cellule<DataType> *it,
                                  const tailleDesTabs etage,
                                  const DataType &info) const
{

    if (it->etage(etage - 1) == nullptr)
        return true;
    if (it->m_suivants[etage - 1]->info > info)
        return true;

    return false;
}
template <typename DataType>
Cellule<DataType> *SkipList<DataType>::find(const DataType &e) const
{
    Cellule<DataType> *it = ad;
    tailleDesTabs etage = it->nb_etages();
    while (it->etage(etage - 1) != nullptr || etage > 1)
    {
        if (it->etage(etage - 1)->info == e)
        {
            return it->etage(etage - 1);
        }
        else if (tropLoin(it, etage, e))
        {
            etage--;
            if (etage == 0)
                return nullptr;
        }
        else
            it = it->etage(etage - 1);
    }

    return nullptr;
}

template <typename DataType>
bool SkipList<DataType>::exists(const DataType &e) const
{
    return find(e) != nullptr;
}

template <typename DataType>
void SkipList<DataType>::empty()
{
    Cellule<DataType> *it = ad;
    Cellule<DataType> *tmp;
    while (it != nullptr)
    {
        tmp = it;
        it = it->etage(0);
        delete tmp;
    }
    ad = new Cellule<DataType>;
    ad->m_suivants.push_back(nullptr);
}

template <typename DataType>
void SkipList<DataType>::sup_ele(const DataType &e)
{
    
}

#endif