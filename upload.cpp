#include <iostream>
#include <fstream>
#include <string>

#define BUCKETSAMOUNT 100
#define BUCKETSIZE 10

struct block {
    int head;
};

struct intBlock {
    int head;
};

struct bucket {
    block blocks[BUCKETSIZE - 1];
    intBlock intBlocks;
};

struct bucketArea {
    bucket buckets[BUCKETSAMOUNT];
};

struct offsetBlock {
    int head;
};

void mallocando() {
    bucketArea* area = new bucketArea;

    int count = 0;
    for (int a = 0; a < BUCKETSAMOUNT; a++) {
        for (int b = 0; b < BUCKETSIZE - 1; b++) {
            area->buckets[a].blocks[b].head = count;
            count += 1;
        }
        area->buckets[a].intBlocks.head = count;
        count += 1;
    }

    int offsetArea = (BUCKETSAMOUNT / 8) * (BUCKETSIZE);
    offsetBlock* offset = new offsetBlock[offsetArea];
    for (int a = 0; a < offsetArea; a++) {
        offset[a].head = count;
        count += 1;
    }

    std::cout << "Alocando espaço..." << std::endl;

    std::ofstream output_file("students.data", std::ios::binary);
    output_file.write(reinterpret_cast<char*>(area), sizeof(bucketArea));
    output_file.close();
}

int main() {
    mallocando();
    std::ifstream file("artigo.csv");
    std::cout << "preenchendo hashing e arvore b+" << std::endl;

    if (file.is_open()) {
        std::string line;
        int count = 0;
        while (getline(file, line)) {
            if (count % 50000 == 0) {
                std::cout << "foram salvos " << count << " registros" << std::endl;
            }
        }

        std::cout << count << " Registros Salvos\n";
        file.close();
    }

    return 0;
}
