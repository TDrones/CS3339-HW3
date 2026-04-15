#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Cache line structure
struct CacheLine {
    bool valid;
    int tag;
};

// Cache Simulator
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: ./cache_sim <num_entries> <associativity> <input_memory_reference_file>" << endl;
        return 1;
    }

    // Parses command line arguments
    int num_entries = stoi(argv[1]);
    int associativity = stoi(argv[2]);
    string input_file = argv[3];
    int num_sets = num_entries / associativity;

    ifstream infile(input_file);

    // Checks if the input file is opened successfully
    if (!infile.is_open()) {
        cout << "Error opening file: " << input_file << endl;
        return 1;
    }

    ofstream outfile("cache_sim_output");

    // Checks if the output file is opened successfully
    if (!outfile.is_open()) {
        cout << "Error opening output file: cache_sim_output" << endl;
        return 1;
    }

    int cache_hits = 0;
    int cache_misses = 0;
    int address;

    vector<vector<CacheLine>> cache(num_sets, vector<CacheLine>(associativity));

    //Initializes the cache lines
    for (int i = 0; i < num_sets; i++) {
        for (int j = 0; j < associativity; j++) {
            cache[i][j].valid = false;
            cache[i][j].tag = -1;
        }
    }

    vector<int> next_replace(num_sets, 0);

    // Process memory references
    while (infile >> address) {
        int set_index = address % num_sets;
        int tag = address / num_sets;

        bool hit = false;
        for (int i = 0; i < associativity; i++) {
            if (cache[set_index][i].valid && cache[set_index][i].tag == tag) {
                hit = true;
                break;
            }
        }

        if (hit) {
            cache_hits++;
            outfile << address << " : HIT" << endl; //reports hit
        } else {
            cache_misses++;
            outfile << address << " : MISS" << endl; //reports miss

            // Updates the cache line
            bool inserted = false;
            for (int i = 0; i < associativity; i++) {
                if (!cache[set_index][i].valid) {
                    cache[set_index][i].valid = true;
                    cache[set_index][i].tag = tag;
                    inserted = true;
                    break;
                }
            }

            if (!inserted) {
                int replace_index = next_replace[set_index];

                cache[set_index][replace_index].valid = true;
                cache[set_index][replace_index].tag = tag;

                next_replace[set_index] = (next_replace[set_index] + 1) % associativity;
            }

        }
    }

    infile.close();
    outfile.close();
    return 0;
}