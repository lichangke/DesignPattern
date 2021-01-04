更多设计模式参看： [设计模式之模式概述(模式汇总)(C++实现)](https://blog.csdn.net/leacock1991/article/details/111713017)

# 介绍



组合模式跟面向对象设计中的“组合关系（通过组合来组装两个类）”，是不同的两码事。这里的“组合模式”，主要是用来处理**树形结构数据**，可以简单理解为一组对象集合。其应用场景的特殊性，数据必须能表示成树形结构

树形结构在软件中随处可见，例如操作系统中的目录结构、应用软件中的菜单、办公系统中的公司组织结构等等，这样的组织形式的特点在于：叶子节点不再包含成员对象，而容器节点可以包含成员对象，这些对象可以是叶子节点，也可以是容器节点。



## 意图：

**组合模式(Composite Pattern)：** 组合多个对象形成树形结构以表示具有“整体—部分”关系的层次结构。组合模式对单个对象（即叶子对象）和组合对象（即容器对象）的使用具有一致性，组合模式又可以称为“整体—部分”(Part-Whole)模式，它是一种对象结构型模式。



## 解决问题：

组合模式为处理树形结构提供了一种较为完美的解决方案，它描述了如何将容器和叶子进行递归组合，使得用户在使用时无须对它们进行区分，可以一致地对待容器和叶子。

## 实现概述：

树型结构的问题中，**模糊了简单元素(叶子节点)和复杂元素的概念(容器节)**，为叶子节点和容器节点提供了公共的抽象构建类，客户端无需关心所操作的对象是叶子节点还是容器节点，只需针对抽象构建类编程处理即可。

## 要点：

组合模式的关键是定义一个公共的抽象构件类，它既可以代表叶子，又可以代表容器，而客户端针对该抽象构件类进行编程，无须知道它到底表示的是叶子还是容器，可以对其进行统一处理。**叶子节点**不再包含成员对象，而**容器节点**可以包含成员对象，这些对象可以是叶子节点，也可以是容器节点。            



## 应用场景： 

在具有**整体和部分的层次结构**中，希望通过一种方式**忽略整体与部分的差异**，客户端可以一致地对待它们。



## 优点：

- 组合模式清楚地定义分层次的复杂对象，表示对象的全部或部分层次结构，让客户端忽略层次的差异；
- 客户端可以一致地对待层次结构中各个层次的对象，而不必关心其具体对象，简化了客户端代码；
- 在组合模式中增加新的叶子构件和容器构件非常方便，易于扩展，符合开闭原则；
- 组合模式为树形结构的面向对象实现提供了一种灵活的解决方案，通过叶子对象和容器对象的递归组合。

## 缺点：

组合模式忽略了层次的差异，很难对容器中的构件类型进行限制，如果希望一个容器中只能有某些特定类型的对象，就必须通过在运行时进行类型检查来处理，这个实现过程较为复杂。

# 模式结构

- **Component（抽象构件）**：可以是接口或抽象类，定义了构件的一些公共接口，这些接口是管理或者访问它的子构件的方法（如果有子构件），具体的实现在叶子构件和容器构件中进行。
- **Leaf（叶子构件）**：它代表树形结构中的叶子节点对象，叶子节点没有子节点，它实现了在抽象构件中定义的行为。对于那些访问及管理子构件的方法（非叶子构件功能，属于容器构件的功能），可以通过抛出异常、提示错误等方式进行处理。
- **Composite（容器构件）** ：表示容器节点对象，容器节点包含子节点，其子节点可以是叶子节点，也可以是容器节点，它提供一个**集合用于存储子节点**，实现了在抽象构件中定义的行为。

根据抽象构件类的定义形式，可将组合模式分为透明组合模式和安全组合模式两种形式。可以简单地看抽象构件类包含的是叶子构件行为和容器构件行为的**并集**还是**交集**。

## 透明组合模式

透明组合模式中，抽象构件类包含叶子构件行为和容器构件行为的**并集**，抽象构件Component中声明了所有用于管理成员对象的方法，包括add()、remove()以及getChild()等方法，这样做的好处是确保所有的构件类都有相同的接口。透明组合模式也是组合模式的标准形式，管理成员对象的方法在叶子构件可见所以是透明的，对于这些方法需要通过抛出异常、提示错误等方式进行处理。

![设计模式之组合模式_透明组合模式](\upload\设计模式之组合模式\设计模式之组合模式_透明组合模式.jpg)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201230213250282.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)

## 安全组合模式

安全组合模式中，抽象构件类包含叶子构件行为和容器构件行为的**交集**，在抽象构件Component中没有声明任何用于管理成员对象的方法，而是在Composite类中声明并实现这些方法。这种做法是安全的，因为根本不向叶子对象提供这些管理成员对象的方法，对于叶子对象，客户端不可能调用到这些方法。

![设计模式之组合模式_安全组合模式](\upload\设计模式之组合模式\设计模式之组合模式_安全组合模式.jpg)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201230213300560.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)

# 代码示例

模拟对文件和文件夹进行杀毒操作

Component（抽象构件）： AbstractFile

Leaf（叶子构件）：ImageFile  TextFile VideoFile

Composite（容器构件）：Folder



## GitHub

[CompositePattern](https://github.com/lichangke/DesignPattern/tree/main/demos/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%E4%B9%8B%E7%BB%84%E5%90%88%E6%A8%A1%E5%BC%8F/CompositePattern)

## 透明组合模式

### Component（抽象构件）

```cpp
/// 透明组合模式
/// Component（抽象构件）： AbstractFile
class AbstractFile {
public:
    virtual ~AbstractFile() = default;
    virtual void add(AbstractFile *file) = 0;
    virtual void remove(AbstractFile *file) = 0;
    virtual void killVirus() = 0;
protected:
    AbstractFile() = default;
};
```



### Leaf（叶子构件）

```cpp
/// Leaf（叶子构件）： ImageFile  TextFile VideoFile
class ImageFile : public AbstractFile {

public:
    explicit ImageFile(const std::string &name) {
        std::cout << "ImageFile Hello " << name << std::endl;
        this->name = name;
    }
    ~ImageFile() override {
        std::cout << "ImageFile Bye " << name << std::endl;
    }
    void add(AbstractFile *file) override {
        std::cout << "不支持该方法！" << std::endl;
    }
    void remove(AbstractFile *file) override {
        std::cout << "不支持该方法！" << std::endl;
    }

    void killVirus() override {
        //模拟杀毒
        std::cout << "---对图像文件: " << name << " 进行杀毒"<< std::endl;
    }
private:
    std::string name;
};

class TextFile : public AbstractFile {

public:
    explicit TextFile(const std::string &name) {
        std::cout << "TextFile Hello " << name << std::endl;
        this->name = name;
    }
    ~TextFile() override {
        std::cout << "TextFile Bye " << name << std::endl;
    }
    void add(AbstractFile *file) override {
        std::cout << "不支持该方法！" << std::endl;
    }
    void remove(AbstractFile *file) override {
        std::cout << "不支持该方法！" << std::endl;
    }

    void killVirus() override {
        //模拟杀毒
        std::cout << "---对文本文件: " << name << " 进行杀毒"<< std::endl;
    }
private:
    std::string name;
};

class VideoFile : public AbstractFile {

public:
    explicit VideoFile(const std::string &name) {
        std::cout << "VideoFile Hello " << name << std::endl;
        this->name = name;
    }
    ~VideoFile() override {
        std::cout << "VideoFile Bye " << name << std::endl;
    }
    void add(AbstractFile *file) override {
        std::cout << "不支持该方法！" << std::endl;
    }
    void remove(AbstractFile *file) override {
        std::cout << "不支持该方法！" << std::endl;
    }
    void killVirus() override {
        //模拟杀毒
        std::cout << "---对视频文件: " << name << " 进行杀毒"<< std::endl;
    }
private:
    std::string name;
};

```



### Composite（容器构件）

```cpp
/// Composite（容器构件）： Folder
class Folder : public AbstractFile {

public:
    explicit Folder(const std::string &name) {
        std::cout << "VideoFile Hello " << name << std::endl;
        this->name = name;
    }
    ~Folder() override {
        std::cout << "Folder Bye " << name << std::endl;
    }
    void add(AbstractFile *file) override {
        fileList.push_back(file);
    }
    void remove(AbstractFile *file) override {
        fileList.remove(file);
    }
    void killVirus() override {
        //模拟杀毒
        std::cout << "***对文件夹: " << name << " 进行杀毒"<< std::endl;
        //递归调用成员构件的killVirus()方法
        for(AbstractFile *obj : fileList) {
            obj->killVirus();
        }
    }
private:
    std::list<AbstractFile *> fileList;
    std::string name;
};
```



### 测试

```cpp
int main() {
    std::cout << "----透明组合模式----" << std::endl;
    //针对抽象构件编程
    AbstractFile *file1,*file2,*file3,*file4,*file5,*folder1,*folder2,*folder3,*folder0;

    folder0 = new Folder("根目录文件夹");
    folder1 = new Folder("图像文件夹");
    folder2 = new Folder("文本文件夹");
    folder3 = new Folder("视频文件夹");

    file1 = new ImageFile("图片01.jpg");
    file2 = new ImageFile("图片02.gif");
    file3 = new TextFile("文本01.txt");
    file4 = new TextFile("文本02.doc");
    file5 = new VideoFile("视频01.rmvb");

    folder1->add(file1);
    folder1->add(file2);
    folder2->add(file3);
    folder2->add(file4);
    folder3->add(file5);
    
    folder0->add(folder1);
    folder0->add(folder2);
    folder0->add(folder3);

    //从 根目录文件夹 节点开始进行模拟杀毒操作
    folder0->killVirus();
    std::cout << "----叶子构件调用管理成员对象的方法----" << std::endl;
    file1->add(file2);
    file3->remove(file4);

    delete file1;
    delete file2;
    delete file3;
    delete file4;
    delete file5;
    delete folder0;
    delete folder1;
    delete folder2;
    delete folder3;

    return 0;
}
```



### 输出

![image-20201230171053902](\upload\设计模式之组合模式\A_设计模式之组合模式.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201230213319733.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)



## 安全组合模式

### Component（抽象构件）

```cpp
/// 安全组合模式
/// Component（抽象构件）： AbstractFile
class AbstractFile {
public:
    virtual ~AbstractFile() = default;
    virtual void killVirus() = 0;
protected:
    AbstractFile() = default;
};
```



### Leaf（叶子构件）

```cpp
/// Leaf（叶子构件）： ImageFile  TextFile VideoFile
class ImageFile : public AbstractFile {

public:
    explicit ImageFile(const std::string &name) {
        std::cout << "ImageFile Hello " << name << std::endl;
        this->name = name;
    }
    ~ImageFile() override {
        std::cout << "ImageFile Bye " << name << std::endl;
    }

    void killVirus() override {
        //模拟杀毒
        std::cout << "---对图像文件: " << name << " 进行杀毒"<< std::endl;
    }
private:
    std::string name;
};

class TextFile : public AbstractFile {

public:
    explicit TextFile(const std::string &name) {
        std::cout << "TextFile Hello " << name << std::endl;
        this->name = name;
    }
    ~TextFile() override {
        std::cout << "TextFile Bye " << name << std::endl;
    }
    void killVirus() override {
        //模拟杀毒
        std::cout << "---对文本文件: " << name << " 进行杀毒"<< std::endl;
    }
private:
    std::string name;
};

class VideoFile : public AbstractFile {

public:
    explicit VideoFile(const std::string &name) {
        std::cout << "VideoFile Hello " << name << std::endl;
        this->name = name;
    }
    ~VideoFile() override {
        std::cout << "VideoFile Bye " << name << std::endl;
    }
    void killVirus() override {
        //模拟杀毒
        std::cout << "---对视频文件: " << name << " 进行杀毒"<< std::endl;
    }
private:
    std::string name;
};

```



### Composite（容器构件）

```cpp
/// Composite（容器构件）： Folder
class Folder : public AbstractFile {

public:
    explicit Folder(const std::string &name) {
        std::cout << "VideoFile Hello " << name << std::endl;
        this->name = name;
    }
    ~Folder() override {
        std::cout << "Folder Bye " << name << std::endl;
    }
    void add(AbstractFile *file) {
        fileList.push_back(file);
    }
    void remove(AbstractFile *file) {
        fileList.remove(file);
    }
    void killVirus() override {
        //模拟杀毒
        std::cout << "***对文件夹: " << name << " 进行杀毒"<< std::endl;
        //递归调用成员构件的killVirus()方法
        for(AbstractFile *obj : fileList) {
            obj->killVirus();
        }
    }
private:
    std::list<AbstractFile *> fileList;
    std::string name;
};

```



### 测试

```cpp

int main() {
    std::cout << "----安全组合模式----" << std::endl;
    //针对抽象构件编程
    AbstractFile *file1,*file2,*file3,*file4,*file5;
    Folder *folder1,*folder2,*folder3,*folder0;

    folder0 = new Folder("根目录文件夹");
    folder1 = new Folder("图像文件夹");
    folder2 = new Folder("文本文件夹");
    folder3 = new Folder("视频文件夹");

    file1 = new ImageFile("图片01.jpg");
    file2 = new ImageFile("图片02.gif");
    file3 = new TextFile("文本01.txt");
    file4 = new TextFile("文本02.doc");
    file5 = new VideoFile("视频01.rmvb");

    folder1->add(file1);
    folder1->add(file2);
    folder2->add(file3);
    folder2->add(file4);
    folder3->add(file5);
    
    folder0->add(folder1);
    folder0->add(folder2);
    folder0->add(folder3);

    //从 根目录文件夹 节点开始进行模拟杀毒操作
    folder0->killVirus();

    delete file1;
    delete file2;
    delete file3;
    delete file4;
    delete file5;
    delete folder0;
    delete folder1;
    delete folder2;
    delete folder3;

    return 0;
}
```



### 输出

![image-20201230171328600](\upload\设计模式之组合模式\B_设计模式之组合模式.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201230213337169.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlYWNvY2sxOTkx,size_16,color_FFFFFF,t_70)

*个人能力有限，如有错误之处或者其他建议，敬请告知欢迎探讨，谢谢!*

