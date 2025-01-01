#ifndef GOODS_TRANSACTION_HPP
#define GOODS_TRANASCTION_HPP

#include <iostream>
#include <string>

using namespace std;

class GoodsTransaction {
    public:
        static const int MAX_GOODS_TRANSACTION = 200;
        int goodsTransactionCount;

        GoodsTransaction();
        void AddGoodsTransaction(const std::string& good, int alter, std::string& desc);
        void ViewGoodsTransaction(int currentPage, int pageSize);

    private:
        int ids[MAX_GOODS_TRANSACTION];
        string date[MAX_GOODS_TRANSACTION];
        string time[MAX_GOODS_TRANSACTION];
        string goods[MAX_GOODS_TRANSACTION];
        int alteration[MAX_GOODS_TRANSACTION];
        string description[MAX_GOODS_TRANSACTION];

        string getCurrentDate();
        string getCurrentTime();
};

#endif