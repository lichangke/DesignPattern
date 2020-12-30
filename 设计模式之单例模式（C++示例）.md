# 介绍



## 意图：

**单例模式(Singleton Pattern)：**确保某一个类只有一个实例，而且自行实例化并向整个系统提供这个实例，这个类称为单例类，它提供全局访问的方法。单例模式是一种对象创建型模式。

## 解决问题：

一个全局使用的类频繁地创建与销毁。

## 实现概述：

构造函数是私有的，避免外部通过 new 创建实例。 getInstance() 判断系统是否已经有这个单例，如果有则返回，如果没有则创建。

## 要点：

1、单例类只能有一个实例。

2、单例类必须自己创建自己的唯一实例。

3、单例类必须给所有其他对象提供这一实例

## 应用场景：

  (1) 系统只需要一个实例对象，比如，配置信息类，如系统要求提供一个唯一的序列号生成器或资源管理器，或者需要考虑资源消耗太大而只允许创建一个对象。

 (2) 客户调用类的单个实例只允许使用一个公共访问点，除了该公共访问点，不能通过其他途径访问该实例。

### 生活中场景

Windows任务管理器只能启动一个

### 软件中场景

负载均衡器，配置信息类等

## 优点：

- 在内存里只有一个实例，减少了内存的开销，尤其是频繁的创建和销毁实例（比如管理学院首页页面缓存）。
- 避免对资源的多重占用（比如写文件操作）。

## 缺点：

- 没有接口，不能继承，与单一职责原则冲突，一个类应该只关心内部逻辑，而不关心外面怎么样来实例化。

# 模式结构

单例模式是结构最简单的设计模式一，在它的核心结构中只包含一个被称为单例类的特殊类。（下图为单例模式懒汉式结构图）



![设计模式之单例模式](\upload\设计模式之单例模式\设计模式之单例模式.jpg)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201228214804598.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)



# 代码示例

## 饿汉式

只有在第一次用到类实例的时候才实例化。不过，这样的实现方式不支持延迟加载。

由于是一个**static对象**，可以保证对象**只生成一次**，线程安全的。

### GitHub

[EagerSingleton](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E5%8D%95%E4%BE%8B%E6%A8%A1%E5%BC%8F/EagerSingleton)

### 饿汉式单例类

```cpp

class EagerSingleton {
public:

    static EagerSingleton *getInstance(){
        return instance;
    }
    static void delInstance() {
        if(instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }
private:
    EagerSingleton(){
        std::cout << "EagerSingleton Hello" << std::endl;
    };
    ~EagerSingleton() { // 私有化 可以避免 直接 delete s1 ，必须 使用 delInstance
        std::cout << "EagerSingleton Bye" << std::endl;
    }
    // static对象，可以保证对象只生成一次,并且是多线程安全
    static EagerSingleton *instance;
};
// 饿汉模式的关键：初始化即实例化
EagerSingleton *EagerSingleton::instance = new EagerSingleton();
```

### 测试

```cpp
int main() {
    EagerSingleton *s1 = EagerSingleton::getInstance();
    EagerSingleton *s2 = EagerSingleton::getInstance();

    std::cout << "s1 address = " << s1 << std::endl;
    std::cout << "s2 address = " << s2 << std::endl;

    EagerSingleton::delInstance();

    getchar();
    return 0;
}
```

### 输出

![image-20201228110635926](\upload\设计模式之单例模式\A_设计模式之单例模式.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020122821482372.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)

## 懒汉式

懒汉式单例在第一次调用getInstance()方法时实例化，在类加载时并不自行实例化，这种技术又称为**延迟加载*(Lazy Load)***技术，即需要的时候再加载实例，为了避免多个线程同时调用getInstance()方法，我们可以使用锁或者static变量

### GitHub

懒汉式单例类+双检查锁: [LazySingleton01](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E5%8D%95%E4%BE%8B%E6%A8%A1%E5%BC%8F/LazySingleton01)

懒汉式单例类+static变量: [LazySingleton02](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E5%8D%95%E4%BE%8B%E6%A8%A1%E5%BC%8F/LazySingleton02)



### 懒汉式单例类+双检查锁

```cpp
class LazySingleton {
public:
    static LazySingleton *getInstance() {
        //第一个检查，如果只是读操作，就不许用加锁
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lck(m_mutex);
            //第二个检查，保证只有一个
            if (instance == nullptr) {
                instance = new LazySingleton;
            }
        }
        return instance;
    }
    static void delInstance() {
        if(instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }
private:
    LazySingleton(){
        std::cout << "LazySingleton Hello" << std::endl;
    };
    ~LazySingleton() { // 私有化 可以避免 直接 delete s1 ，必须 使用 delInstance
        std::cout << "LazySingleton Bye" << std::endl;
    }
    
    static LazySingleton *instance;
    static std::mutex m_mutex;
};

LazySingleton* LazySingleton::instance = nullptr;
std::mutex LazySingleton::m_mutex;
```



### 懒汉式单例类+static变量

```cpp
class LazySingleton {
public:
    static LazySingleton *getInstance() {
        static LazySingleton instance;
        return &instance;
    }

private:
    LazySingleton(){
        std::cout << "LazySingleton Hello" << std::endl;
    };
    ~LazySingleton() { // 私有化 可以避免 直接 delete s1 ，必须 使用 delInstance
        std::cout << "LazySingleton Bye" << std::endl;
    }
};
```

1、C++11中可以保证static变量时**多线程安全**的，在底层实现了加锁操作，所以不需要像以前那样自己写加锁操作。

2、由于是一个**static对象**，可以保证对象**只生成一次**；

3、在程序结束的时候，系统会**调用对应的析构函数**；如果是new出来的对象，程序结束的时候，系统不会自动调用析构函数。



### 测试

懒汉式单例类+双检查锁

```cpp
int main() {
    LazySingleton *s1 = LazySingleton::getInstance();
    LazySingleton *s2 = LazySingleton::getInstance();

    std::cout << "s1 address = " << s1 << std::endl;
    std::cout << "s2 address = " << s2 << std::endl;

    LazySingleton::delInstance();

    getchar();
    return 0;
}
```

懒汉式单例类+static变量

```cpp
int main() {
    LazySingleton *s1 = LazySingleton::getInstance();
    LazySingleton *s2 = LazySingleton::getInstance();

    std::cout << "s1 address = " << s1 << std::endl;
    std::cout << "s2 address = " << s2 << std::endl;
    

    getchar();
    return 0;
}
```



### 输出

懒汉式单例类+双检查锁

![image-20201228115708404](\upload\设计模式之单例模式\B_设计模式之单例模式.png)



![在这里插入图片描述](https://img-blog.csdnimg.cn/20201228214844924.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)

懒汉式单例类+static变量

![image-20201228134847599](\upload\设计模式之单例模式\C_设计模式之单例模式.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201228214853321.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)



*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

