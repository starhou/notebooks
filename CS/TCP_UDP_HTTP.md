# 应用层

## 超文本传输协议 (HTTP)

## TCP

### TCP的流量控制
TCP的流量控制算法是为了防止接受方的接收缓存溢出。所以TCP通过让发送方维护一个接受窗口的变量来提供流量控制。定义两个变量
* LastByteRead: 已读取数据的最大编号
* LastByteRevd: 已收到数据的最大编号

则接受窗口rwnd可以表示为
    rwnd = RcvBuffer - [LastByteRevd - LastByteRead]

服务器每次会将rwnd的大小返回客户端，客户端会维护两个变量，LastByteSent和LastByteAcked, 则客户端会保持未确认的数据量的大小在rwnd之内，
        LastByteSent - LastByteAcked <= rwnd

边界条件
当主机B的接收窗口为0时，主机A继续发送只有一个字节数据的报文段。这些报文段将会被接受方确认。最终缓存将开始清空，并且确认报文里将包含一个非0的rwnd值。
### TCP的拥塞控制原理

为了解决网络的拥塞。

为什么网络拥塞不好？

1. 当分组的到达速率接近链路容量时，分组经历巨大的排队时延。
2. 发送方在遇到大时延时所进行的不必要重传会引起路由器利用其链路带宽来转发不必要的分组副本
3. 发送方必须执行重传以补偿因缓存溢出的而丢弃的分组。
4. 当一个分组沿一条路径被丢弃，每个上游路由器用于转发该分组到丢弃该分组而使用的传输容量最终被浪费掉了。

拥塞控制的方法

* 端到端拥塞控制。 TCP采用这种方式。
* 网络辅助的拥塞控制

其实就是如何获取网络是否拥塞这个信息，第一种端到端的想法是通过TCP报文的丢失来反应，比如3次报文的丢失。或者使用增加往返时延值作为网络拥塞程度的指示。第二种方法路由器向发送方提供关于网络中拥塞状态的显示反馈信息。

TCP会限制发送方的发送流量。TCP连接包含了发送缓存，接收缓存和几个变量。发送方除了维护接收窗口cwnd外，还会维护一个拥塞窗口rwnd。需满足,

$$
    LastByteSent - LastByteAcked <= \min{cwnd, rwnd}
$$

TCP拥塞控制算法

* 慢启动
TCP一开始设置cwnd为1MSS，传输速率位MSS/RTT，一般MSS比较小，例如500字节。当上次发送的分组被确认后，cwnd大小指数增长，直到丢包，ssthresh设置为cwnd/2, cwnd设为1。下次到了ssthresh的时候，转为拥塞避免算法。另外，如果检测到3个冗余的ACK，则快重传快恢复算法。

* 拥塞避免算法
线性增长MSS,当出现超时时候，ssthresh设置为cwnd/2, 当丢包时候， cwnd设为1。当检测到3个冗余ACK，将ssthresh设置为cwnd/2，则快重传快恢复算法。

* 快恢复算法

最新版本，ssthresh设置为cwnd/2, cwnd = 0.5*cwnd + k个冗余， 然后转拥塞避免算法。 

（借图，侵权删）
![](https://pic3.zhimg.com/80/v2-f7db63b1f00cbd8170e1435616e06216_720w.jpg)

