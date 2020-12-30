//
// Created by leacock on 2020/12/30.
//

#ifndef COMPOSITEPATTERN01_COMPOSITEPATTERN01_H
#define COMPOSITEPATTERN01_COMPOSITEPATTERN01_H

#include <iostream>
#include <list>

/// 安全组合模式
/// Component（抽象构件）： AbstractFile
class AbstractFile {
public:
    virtual ~AbstractFile() = default;
    virtual void killVirus() = 0;
protected:
    AbstractFile() = default;
};


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


#endif //COMPOSITEPATTERN01_COMPOSITEPATTERN01_H
