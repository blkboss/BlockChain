#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <ctime>

class Block {
public:
    std::string previous_hash;
    std::string data;
    std::time_t timestamp;
    size_t hash;

    Block(std::string data, std::string previousHash)
        : data(data), previous_hash(previousHash), timestamp(std::time(nullptr)) {
        hash = calculateHash();
    }

    size_t calculateHash() {
        std::stringstream ss;
        ss << previous_hash << timestamp << data;
        return std::hash<std::string>{}(ss.str());
    }
};

class Blockchain {
public:
    std::vector<Block> chain;

    Blockchain() {
        chain.emplace_back("Genesis Block", "0");
    }

    void addBlock(std::string data) {
        std::string previousHash = std::to_string(chain.back().hash);
        chain.emplace_back(data, previousHash);
    }

    void displayChain() {
        for (const auto& block : chain) {
            char buffer[26]; // Buffer for the date string
            ctime_s(buffer, sizeof(buffer), &block.timestamp); // Convert timestamp to string

            std::cout << "Hash: " << block.hash << "\n"
                << "Previous Hash: " << block.previous_hash << "\n"
                << "Data: " << block.data << "\n"
                << "Timestamp: " << buffer // Use the buffer with the formatted time
                << "------------------------------\n";
        }
    }
};

int main() {
    Blockchain blockchain;

    blockchain.addBlock("Block 1 Data");
    blockchain.addBlock("Block 2 Data");

    blockchain.displayChain();

    return 0;
}
