#include "TemplateMethodPattern.h"

int main() {

    OnlineMall* shopTaoBao= new TaoBao();
    shopTaoBao->shopping();
    delete shopTaoBao;

    OnlineMall* shopJingDong = new JingDong();
    shopJingDong->shopping();
    delete shopJingDong;

    return 0;
}
