//code by sherrlock0535
#include "xchain/xchain.h"
#include <algorithm>
// 二手交易平台
// 参数由Context提供
class Item{
public:
    // 初始化商品
    // owner - 商品发布者(string)(address)
    // data - 商品信息(json格式string)
    // 返回值：商品编号
    virtual int initialize() = 0;
    // 商品流通
    // itemID: 商品编号(int)
    // newOwner: 商品的新从属(string)(address)
    // tradeID: 发生流通的交易编号
    virtual void transform() = 0;
    // 商品溯源
    // itemID
    // 返回值：商品上一次交易的编号
    virtual int queryTrade() = 0;
    // 商品从属
    // itemID
    // 返回值：商品拥有者(string)(address)
    virtual std::string queryOwner() = 0;
 };
class Trade{
public:
    // 买家下单
    // ItemID: 商品编号(int)
    // newOwner: 买家(string)(address)
    // data: 购物信息(string)(json)
    // 返回交易编号
    virtual int createOrder() = 0;
    // 买家确认交易完成
    // tradeID
    // remerber use transform to change the owner in the app
    virtual void finishOrder() = 0;
    // 该物品上一次交易编号
    // 返回值：
    // 若有上次 返回编号(int)
    // 无上次交易返回 0
    virtual int queryAhead() = 0;
};
struct ItemDemo : public Item, public xchain::Contract{
private:
    const std::string OWNER_KEY = "owner";
    const std::string DATA_KEY = "data";
    const std::string Item_Ahead_KEY = "iahead";
    std::string turnIntoString(int key){
        std::string x='';
        while(key){
            x += char(key % 10 + '0');
            key /= 10;
        }
        reverse(str.begin(), str.end());
        return x;
    }
public:
    int initialize(){
        xchain::Context* ctx = this->context();
        std::string owner = ctx->arg("owner");
        if(owner.empty()){
            ctx->error("missing owner address");
            return 0;
        }
        std::string data = ctx->arg("data");
        int topID=0;
        ctx->get_object("ITEMID", &topID);
        topID++;
        ctx->put_object("ITEMID", topID);
        ctx->put_object(DATA_KEY + '-' + turnIntoString(topID), data);
        ctx->put_object(OWNER_KEY + '-' +turnIntoString(topID), owner);
        ctx->ok("success");
        return topID;
    }
    void transform(){
        xchain::Context* ctx = this->context();
        std::string owner = ctx->arg("newOwner");
        int itemID = ctx->arg("itemID");
        int tradeID = ctx->arg("tradeID");
        ctx->put_object(Item_Ahead_KEY + '-' + turnIntoString(tradeID));
        ctx->put_object(OWNER_KEY+ '-' +turnIntoString(itemID), owner);
    }
    int queryTrade(){
        xchain::Context* ctx = this->context();
        int itemID = ctx->arg("itemID");
        std::string tradeID='-1';
        ctx->get_object(Item_Ahead_KEY + '-' + turnIntoString(itemID), tradeID);
        return tradeID;
    }
    std::string queryOwner(){
        xchain::Context* ctx = this->context();
        int itemID = ctx->arg("itemID");
        std::string owner;
        ctx->get_object(OWNER_KEY + '-' + turnIntoString(itemID), owner);
        return owner;
    }
};
struct Tradedemo:public Trade,public xchain::Contract{
private:
    const std::string OWNER_KEY = "owner";
    const std::string TradeData_KEY = "tradek";
    const std::string ID_KEY = "ID";
    std::string turnIntoString(int key){
        std::string x='';
        while(key){
            x += char(key % 10 + '0');
            key /= 10;
        }
        reverse(str.begin(), str.end());
        return x;
    }
    int queryAhead(int ItemID){
        std::string tradeID='-1';
        ctx->get_object(Item_Ahead_KEY + '-' + turnIntoString(itemID), tradeID);
        return tradeID;
    }
public:
    int creatOrder(){
        xchain::Context* ctx = this->context();
        int ItemID = ctx->arg("ItemID");
        std::string newOwner = ctx->arg("newOwner");
        std::string data = ctx->arg("data");
        int top = 0;
        ctx->get_object("TRADEID", top);
        top++;
        ctx->put_object("TRADEID", top);
        ctx->put_object(ID_KEY + '-' + turnIntostring(top, ItemID));
        ctx->put_object(TradeData_KEY + '-' + turnIntoString(top), data);
        ctx->put_object(Nowner_KEY + '-' + turnIntoString(top), newOwner);
        ctx->put_object(state + '-' + turnIntoString(top), 1);
        return top;
    }
    void finishOrder(){
        xchain::Context* ctx = this->context();
        int tradeID = ctx->arg("tradeID");
        ctx->put_ojbect("AheadID-" + turnIntoString(tradeID), queryAhead);
    }
    int queryAhead(){
        xchain::Context* ctx = this->context();
        int tradeID = ctx->arg("tradeID");
        int aheadID = -1;
        get_object("AheadID-" + turnIntoString(tradeID), aheadID);
        return aheadID;
    }

};
