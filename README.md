# English-translation-Chinese-dictiory

## 功能：  

* 基于插入中英文的增加  
* 基于英文的查找  
* 基于英文的删除  
* 将英文和中文写入到txt文件中  
* 将txt文件读入到所构造的数据结构中  


## 所用到的数据结构：  

* 普通二叉搜索树 （由于插入的数据高度有序，会导致效率非常的低下）
* 红黑树  


## 增强方案：  

* 用QT进行GUI的编写

**现在还有一个很严重的问题，就是Qt代码中使用了大量的std代码，应该用Qt库的代码进行重写，比如string改为Qstring标准IO改为Qt的IO流。**

## 如何使用：

### Console  

用codeblock打开即可  

### Qt  

用Qt Creater打开 .pro文件即可（当然需要下载全部文件）  

## 存在问题  

IO流的打开关闭问题  
