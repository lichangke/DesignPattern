更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

# 介绍

原型模式（Prototype Pattern）是用于创建重复的对象，同时又能保证性能。这种类型的设计模式属于创建型模式，它提供了一种创建对象的最佳方式。

这种模式是实现了一个原型接口，该接口用于创建当前对象的克隆。当直接创建对象的代价比较大时，则采用这种模式。例如，一个对象需要在一个高代价的数据库操作之后被创建。我们可以缓存该对象，在下一个请求时返回它的克隆，在需要的时候更新数据库，以此来减少数据库调用。

## 意图：

**原型模式(Prototype Pattern)：** 使用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。从一个对象再创建另外一个可定制的对象，而且不需要知道任何创建的细节。



## 解决问题：

在运行期建立和删除原型。

## 实现概述：

利用已有的一个原型对象，快速地生成和原型对象一样的实例。

## 要点：

1、实现克隆操作，也就是 clone()

2、能够隔离类对象的使用者和具体类型之间的耦合关系，要求这些具体类型拥有稳定的接口。

## 应用场景：

(1) 创建新对象成本较大（如一些初始化需要较长时间，占用太多的CPU资源或网络资源），并且新的对象可以通过原型模式对已有对象进行复制来获得，如有必要可稍作修改。

(2) 需要避免使用分层次的工厂类来创建分层次的对象，并且类的实例对象只有一个或很少的几个组合状态，通过复制原型对象得到新实例可能比使用构造函数创建一个新实例更加方便。

### 生活中场景

细胞分裂；克隆羊；抄作业

### 软件中场景

JAVA 中的 Object clone() 方法；工作周报、绩效 、邮件等拷贝上次

## 优点：

(1) 当创建新的对象实例较为复杂时，使用原型模式可以简化对象的创建过程，提高新实例的创建效率。

(2) 扩展性较好，模式中提供了抽象原型类，具体原型类可根据需要扩展。

(3) 原型模式提供了简化的创建结构，模式中产品的复制是通过封装在原型类中的克隆方法实现的，无须专门的工厂类来创建产品。

## 缺点：

(1) 需要为每一个类配备一个克隆方法，该克隆方法位于一个类的内部，改造已有类时需要修改源代码，违背开闭原则；

(2) 在实现深克隆时需要编写较为复杂的代码，并且如果对象嵌套很多引用时，为了实现深拷贝每一层嵌套都必须支持深克隆。

# 深拷贝与浅拷贝

**浅拷贝**：只是增加了一个指针指向已存在的内存地址，如果原地址发生改变，那么浅拷贝出来的对象也会相应的改变。相当于一个箱子有多个钥匙，其中某人打开箱子取走箱子里的东西时，其他人再打开箱子看到的都是空箱子。

**深拷贝**：是增加了一个指针并且申请了一个新的内存，使这个增加的指针指向这个新的内存。相当有多个箱子每个箱子对应一个钥匙，一个人取走他的钥匙对应的箱子里的东西时，不会对其他人产生影响。

# 模式结构

- **抽象原型类（AbstractPrototype）**：规定了具体原型对象必须实现的接口（如果要提供深拷贝，则必须具有实现clone的规定）
- **具体原型类（ConcretePrototype）**：从抽象原型派生而来，是客户程序使用的对象，即被复制的对象，需要实现抽象原型角色所要求的接口。
- **客户端（Client）**：客户端中声明一个抽象原型类，根据客户需求clone具体原型类对象实例

![设计模式之原型模式](\upload\设计模式之原型模式\设计模式之原型模式.jpg)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201229221739479.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)

# 代码示例

在已有邮件上修改生成需要发送的新邮件

## GitHub

[Prototype](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E5%8E%9F%E5%9E%8B%E6%A8%A1%E5%BC%8F/Prototype)

## 抽象原型类（AbstractPrototype）

```cpp
/// 抽象原型类（AbstractPrototype）
class AbstractPrototypeMail {
public:
    virtual ~AbstractPrototypeMail() = default;
    virtual AbstractPrototypeMail *clone() = 0;
    virtual void showMail() = 0;
    virtual void changeTitle(std::string title) = 0;
    virtual void changeSender(std::string sender) = 0;
    virtual void changeRecipients(std::string rec) = 0;
    virtual void changeBody(std::string body) = 0;
    virtual void changeAtt(std::string name) = 0;
protected:
    AbstractPrototypeMail() = default;
};
```

## 具体原型类（ConcretePrototype）

```cpp
/// 具体原型类（ConcretePrototype）
class ConcretePrototypeMail : public AbstractPrototypeMail {
public:
    ConcretePrototypeMail(const std::string &title,const std::string &sender,const std::string &rec,const std::string &body, const std::string &nameAtt=""){
        std::cout << "ConcretePrototypeMail Hello" << std::endl;
        mailTitle = title;
        mailSender = sender;
        mailRecipients = rec;
        mailBody = body;
        if (!nameAtt.empty()) {
            mailAtta = new Attachment();
            mailAtta->changeName(nameAtt);
        }
    }
    ~ConcretePrototypeMail() override {
        std::cout << "ConcretePrototypeMail Bye" << std::endl;
        if (mailAtta!= nullptr) {
            delete(mailAtta);
        }
    }
    AbstractPrototypeMail *clone() override {
        auto *newMail = new ConcretePrototypeMail(mailTitle,mailSender,mailRecipients,mailBody,mailAtta->getName());
        return newMail;
    }
    void showMail() override {
        std::cout << "MailTitle: " << mailTitle << std::endl;
        std::cout << "MailSender: " << mailSender << std::endl;
        std::cout << "MailRecipients: " << mailRecipients << std::endl;
        std::cout << "MailBody: " << mailBody << std::endl;
        std::cout << "MailAttachment: " << mailAtta->getName() << std::endl;

    }
    void changeTitle(const std::string title) override {
        mailTitle = title;
    }
    void changeSender(const std::string sender) override {
        mailSender = sender;
    };
    void changeRecipients(const std::string rec) override {
        mailRecipients = rec;
    }
    void changeBody(const std::string body) override {
        mailBody = body;
    }
    void changeAtt(const std::string name) override  {
        if (mailAtta!= nullptr) {
            delete(mailAtta);
        }
        mailAtta = new Attachment();
        mailAtta->changeName(name);
    }

private:
    std::string mailTitle;
    std::string mailSender;
    std::string mailRecipients; /// 按理说 收件人应该有多个 可改为list等其他数据结构，这里采用std::string用于演示
    std::string mailBody;
    Attachment *mailAtta = nullptr;
};   
```

## 附件类

```cpp
/// 附件类
class Attachment {
public:
    Attachment() {
        std::cout << "Attachment Hello" << std::endl;
    }
    ~Attachment() {
        std::cout << "Attachment Bye" << std::endl;
    }
    void changeName(const std::string &name) {
        nameAtt = name;
    };
    std::string getName() {
        return nameAtt;
    }
private:
    std::string nameAtt; /// 附件名
};
```





## 测试

浅拷贝：

```cpp

int main() {
    /// 用于复用的初始邮件创建
    auto *originalMail = new ConcretePrototypeMail("original_title","original_sender","original_rec","original_body","original_attachment");
    std::cout << "originalMail address: "<< originalMail << std::endl;
    originalMail->showMail();
    /// 浅拷贝
    std::cout << "====浅拷贝====" << std::endl;
    auto *copyMail_A = originalMail;
    copyMail_A->changeTitle("copymail_title");
    copyMail_A->changeSender("copymail_sender");
    copyMail_A->changeRecipients("copymail_rec");
    copyMail_A->changeBody("copymail_body");
    copyMail_A->changeAtt("copymail_attachment");
    std::cout << "====copyMail_A====" << std::endl;
    std::cout << "copyMail_A address: "<< copyMail_A << std::endl;
    copyMail_A->showMail();
    std::cout << "====originalMail====" << std::endl;
    originalMail->showMail();
    delete originalMail;
    return 0;
}
```

originalMail的数据也同样被修改了

深拷贝：

```cpp
int main() {
    /// 用于复用的初始邮件创建
    auto *originalMail = new ConcretePrototypeMail("original_title","original_sender","original_rec","original_body");
    originalMail->changeAtt("original_attachment"); 
    std::cout << "originalMail address: "<< originalMail << std::endl;
    originalMail->showMail();
    /// 深拷贝
    std::cout << "====深拷贝====" << std::endl;
    auto *copyMail_A = originalMail->clone();
    copyMail_A->changeTitle("copymail_title");
    copyMail_A->changeSender("copymail_sender");
    copyMail_A->changeRecipients("copymail_rec");
    copyMail_A->changeBody("copymail_body");
    copyMail_A->changeAtt("copymail_attachment");
    std::cout << "====copyMail_A====" << std::endl;
    std::cout << "copyMail_A address: "<< copyMail_A << std::endl;
    copyMail_A->showMail();
    std::cout << "====originalMail====" << std::endl;
    originalMail->showMail();
    delete originalMail;
    delete copyMail_A;
    return 0;
}
```



## 输出

浅拷贝输出：

![image-20201229140523900](\upload\设计模式之原型模式\A_设计模式之原型模式.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201229221803849.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)





深拷贝输出：

![image-20201229140856402](\upload\设计模式之原型模式\B_设计模式之原型模式.png)



![在这里插入图片描述](https://img-blog.csdnimg.cn/20201229221817187.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)

*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

