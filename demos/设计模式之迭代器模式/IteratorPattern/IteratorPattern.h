//
// Created by leacoder on 2021/1/6.
//

#ifndef ITERATORPATTERN_ITERATORPATTERN_H
#define ITERATORPATTERN_ITERATORPATTERN_H

#include <iostream>
#include <cassert>
#include <vector>

/// Iterator（抽象迭代器）：Iterator
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual void nextChannel() = 0; // 下一个电视台节目
    virtual void preChannel() = 0; // 上一个电视台节目
    virtual void chooseChannel(int i) = 0; // 选择具体哪个台
    virtual int getChannel() = 0; // 获取当前频道
protected:
    Iterator() = default;
};

/// Aggregate（抽象聚合类）：Aggregate
class Aggregate {
public:
    virtual ~Aggregate()= default;
    virtual Iterator* createIterator() = 0;
    virtual void play(int i) = 0;
protected:
    Aggregate()= default;
};

/// ConcreteAggregate（具体聚合类）：Television
class Television : Aggregate{

public:
    explicit Television(const std::vector<std::string> &vector) {
        std::cout << "Television Hello" << std::endl;
        channelVector = vector;
    }
    ~Television() override {
        std::cout << "Television Bye" << std::endl;
    }

    // 实现创建迭代器
    Iterator* createIterator() override;

    void play(int i) override{
        std::cout << "现在播放： " <<  channelVector[i] << std::endl;
    }

    int getTotalChannelCount() { // 获取频道总数
        return channelVector.size();
    }
    void addChannel(const std::string& channel) { // 补充添加频道
        std::cout << "补充添加节目频道： " <<  channel << std::endl;
        channelVector.emplace_back(channel);
    }

private:
    std::vector<std::string> channelVector; //
};

/// ConcreteIterator（具体迭代器）：TVRemote
class TVRemote : public  Iterator {
public:
    TVRemote() {
        tv = nullptr;
        cursor = -1;
        totalCount = -1;
        boundTV = false;
        std::cout << "TVRemote Hello" << std::endl;
    }
    ~TVRemote() override {
        std::cout << "TVRemote Bye" << std::endl;
    }

    void bindTV(Television *television) { // 绑定 遥控器和TV
        this->tv = television;
        cursor = 0;
        boundTV = true;
        totalCount = tv->getTotalChannelCount();
    }

    // 下一个电视台节目
    void nextChannel() override {
        assert(boundTV);
        totalCount = tv->getTotalChannelCount();
        cursor++;
        if(cursor > totalCount - 1) {
            cursor = 0;
        }
        std::cout << "TVRemote next channel, current = " << cursor << std::endl;
        tv->play(cursor);
    }

    // 上一个电视台节目
    void preChannel() override {
        assert(boundTV);
        totalCount = tv->getTotalChannelCount();
        cursor--;
        if(cursor < 0) {
            cursor = totalCount - 1;
        }
        std::cout << "TVRemote pre channel, current = " << cursor << std::endl;
        tv->play(cursor);
    }
    // 选择具体哪个台
    void chooseChannel(int i) override {
        assert(boundTV);
        totalCount = tv->getTotalChannelCount();
        if (i > totalCount - 1) {
            cursor = totalCount - 1;
        } else if (i < 0) {
            cursor = 0;
        } else {
            cursor = i;
        }
        std::cout << "TVRemote choose channel = " << cursor << std::endl;
        tv->play(cursor);
    }

    int getChannel() override {
        return cursor;
    }
private:
    bool boundTV; // 是否绑定TV
    Television *tv; // 绑定的电视TV
    int cursor; // 游标
    int totalCount; // 最大 频道数目
};

// 由于 在一个文件中 所以 此函数 放在 TVRemote 类后
Iterator *Television::createIterator() {
    // 实现创建迭代器
    auto *iter = new TVRemote();
    iter->bindTV(this);
    return iter;
}

#endif //ITERATORPATTERN_ITERATORPATTERN_H
