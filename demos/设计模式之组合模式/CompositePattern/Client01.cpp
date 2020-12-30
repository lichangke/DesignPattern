#include "CompositePattern01.h"

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
