## 如何使用

在src目录下运行`make`, 要删除make后产生的文件:`make clean`。

数据库预存了一下几个站点

        from	to
    1|station1|station2|
    2|station2|station3|
    3|station2|station4|
    4|station5|station4|
    5|station6|station1|
    6|station6|station2|

原始用户。当然你可以先注册一个再登陆啦。
    
    username passwd
    1|user1|123456
    2|user2|123456
    4|user4|111111
    5|user5|123456

此外还生成了一些订单信息。

## 结构

    .
    |-- client
    |   |-- client.c                    客户端程序入口
    |   |-- core.c                      客户端核心，读取用户输入，显示事务结果。
    |   `-- core.h
    |-- common.h
    |-- connection.c                    连接封装，负责请求和回应的封装和拆卸
    |-- connection.h
    |-- defs.h                          定义了request,response等通用的结构
    |-- error.c                         工具，error模块
    |-- error.h
    |-- fifo.c                          FIFO模块，初始化服务器、客户端FIFO，负责建立连接和关闭连接
    |-- fifo.h
    |-- Makefile
    |-- server
    |   |-- database.c                  数据库模块，负责所有和数据库的交互业务
    |   |-- database.h
    |   |-- server.c                    服务器程序入口，（下一版本将引入多进程）
    |   |-- transaction.c               服务器事务模块，处理所有客户端的请求
    |   `-- transaction.h
    |-- socket.c                        socket模块，同FIFO模块接口类似
    `-- socket.h

## 和版本一的区别

1. 版本二使用socket作为IPC机制（主要更改在socket.c文件中），在服务端也采用了多进程。
2. 完善了订票的功能,使其更符合常理；
3. 修正了少量BUG

## 拓展性

UNIX视一切东西为文件（好吧，almost）。这样的思想在本程序中将得以体现。客户端和服务器将仅仅维护文件描述符。而文件描述符指向的东西到底是FIFO还是socket，这个问题不用关心。他们唯一需要做的就是根据不同的指令，从文件中读，往文件里写。

由于模块分离，单机版向客户端的转变仅需将FIFO模块改成socket模块。其他模块不受影响。

要添加新的功能？ 你需要：

1. 完善数据库；
2. 分别在客户端、服务器的core和transaction添加事务代码，（注意参数解析）
3. complie, link and run

## 不足

在功能上还是比较单一和粗糙，仅是一个学习用的练手玩意。嗯，关注点在IPC和Linux编程，;)

## 体会

* Makefile 尽量不要留空格；
* 写代码，没发现问题前不要总想着优化；
* 好设计谁都要，但不要过度设计；
* FIFO的缓冲很要命，注意清除缓冲；
* 发现问题，多设断点，打印log（谁让我GDB用得不行呢）
* 由于之前的一切都是文件思想，在修改这个版本时几乎没用多少时间（修改+调试，两个小时足矣）。so，设计真的很重要。