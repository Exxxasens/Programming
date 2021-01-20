#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

enum Element {
    FIRE,
    WATER,
    EARTH,
    AIR
};

struct Weapon {
    int damage;
    int critical;
    int durability;
};

struct Armor {
    int guard;
    int durability;
};

struct Coin {
    int count;
};

struct Rune {
    int level;
    Element element;
};
enum ItemType {
    COIN,
    RUNE,
    WEAPON,
    ARMOR
};
struct Item {
    ItemType type;
    union {
        Coin coin;
        Rune rune;
        Weapon weapon;
        Armor armor;
    };
};

struct ItemWeight {
    double weight;
    Item value;
};

double randd() {
    return (double)rand() / (RAND_MAX + 1.0);
}

typedef std::vector<Item> LootBox;

Item drop_random_item() {
    std::vector<ItemWeight> itemWeightList = {
        { 50, { ItemType::COIN } },
        { 14, { ItemType::RUNE} },
        { 13, { ItemType::RUNE} },
        { 7, { ItemType::RUNE} },
        { 6, { ItemType::RUNE} },
        { 2.8, { ItemType::ARMOR } },
        { 1.4, { ItemType::WEAPON } },
        { 1.4, { ItemType::WEAPON } },
        { 1.4, { ItemType::RUNE } },
        { 1.3, { ItemType::RUNE } },
        { 0.7, { ItemType::RUNE } },
        { 0.6, { ItemType::RUNE } },
        { 0.14, { ItemType::RUNE } },
        { 0.13, { ItemType::RUNE } },
        { 0.07, { ItemType::RUNE } },
        { 0.06, { ItemType::RUNE } }

    };

    itemWeightList[0].value.coin = { 12000 };
    itemWeightList[1].value.rune = { 1, Element::AIR };
    itemWeightList[2].value.rune = { 1, Element::WATER };
    itemWeightList[3].value.rune = { 1, Element::EARTH };
    itemWeightList[4].value.rune = { 1, Element::FIRE };
    itemWeightList[5].value.armor = { 50, 100 };
    itemWeightList[6].value.weapon = { 100, 0, 100 };
    itemWeightList[7].value.weapon = { 75, 50, 100 };
    itemWeightList[8].value.rune = { 5, Element::AIR };
    itemWeightList[9].value.rune = { 5, Element::WATER };
    itemWeightList[10].value.rune = { 5, Element::EARTH };
    itemWeightList[11].value.rune = { 5, Element::FIRE };
    itemWeightList[12].value.rune = { 10, Element::AIR };
    itemWeightList[13].value.rune = { 10, Element::WATER };
    itemWeightList[14].value.rune = { 10, Element::EARTH };
    itemWeightList[15].value.rune = { 10, Element::FIRE };

    double total = 0, currentWeight = 0;

    for (int i = 0; i < itemWeightList.size(); i++) {
        total += itemWeightList[i].weight;
    }

    double randomWeight = (rand() / (RAND_MAX / 1.0)) * double(total);

    for (int i = 0; i < itemWeightList.size(); i++) {
        currentWeight += itemWeightList[i].weight; // Прибавляем вес текущего элемента массива к временной переменной
        if (currentWeight >= randomWeight) // Прерываем генерацию и возвращаем букву
            return itemWeightList[i].value;
    }
    return Item{};
}

LootBox& operator << (LootBox& box, Item i) {
    box.push_back(i);
    return box;
}

LootBox generateLootBox() {
    LootBox box;

    for (int i = 0; i < 3; i++) {
        box << drop_random_item();
    }

    return box;
}

std::ostream& operator<< (std::ostream& out, Item i) {
    if (i.type == ItemType::COIN) {

        out << "Монета, номинал: " << i.coin.count << std::endl;

    }
    else if (i.type == ItemType::RUNE) {

        if (i.rune.element == Element::FIRE) {
            out << "Руна огня";
        }
        else if (i.rune.element == Element::WATER) {
            out << "Руна воды";
        }
        else if (i.rune.element == Element::EARTH) {
            out << "Руна земли";
        }
        else if (i.rune.element == Element::AIR) {
            out << "Руна воздуха";
        }
        out << ", " << i.rune.level << " lvl" << std::endl;

    }
    else if (i.type == ItemType::ARMOR) {
        out << "Броня" << std::endl;
    }
    else if (i.type == ItemType::WEAPON) {
        out << "Меч, " << i.weapon.damage << " единиц атаки" << std::endl;
    }

    return out;
}

std::ostream& operator<< (std::ostream& out, LootBox box) {
    for (int i = 0; i < box.size(); i++) {
        out << box[i];
    }
    return out;
}


int main() {

    setlocale(LC_ALL, "Rus");

    srand(time(NULL));

    std::string in;

    do {
        std::cout << "Открыть лутбокс? Yes/No" << std::endl;
        std::cin >> in;
        transform(in.begin(), in.end(), in.begin(), ::tolower);

        if (in.compare("y") == 0 || in.compare("yes") == 0) {
            std::cout << generateLootBox();
        }

    } while (!(in.compare("n") == 0) || (in.compare("no") == 0));
}
