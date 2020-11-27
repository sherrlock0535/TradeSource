# TradeSource
用于二手交易平台的商品溯源智能合约
可在[此处](https://github.com/xuperchain/xupercore/tree/master/contractsdk/cpp/src/xchain)下载xchain相关SDK，也可直接部署到xchian上。  
## 接口介绍
### initialize()
初始化商品  
owner - 商品发布者(string)(address)   
data - 商品信息(json格式string)    
返回值：商品编号    
### transform()  
商品流通  
itemID: 商品编号(int)  
newOwner: 商品的新从属(string)(address)    
tradeID: 发生流通的交易编号    
### queryTrade()  
查询该商品上一次交易
itemID
返回值：交易编号
### queryOwner()
itemID
返回：拥有者地址(string）(address)
### creatOrder()
买家下单  
ItemID: 商品编号(int)  
newOwner: 买家(string)(address)  
data: 购物信息(string)(json)  
返回交易编号  
### finishOrder()  
买家确认交易完成
tradeID
// remerber use transform to change the owner in the app
### queryAhead()
查询该交易的前驱交易
tradeID
返回上一次交易编号（或-1）
//配合queryTrade()使用可以查询一个商品的所有交易
