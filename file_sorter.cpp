#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

void print_file_list(int group_num, int n_groups, std::vector<char*> files);
std::vector<int> get_group_inds(int group_num, int n_groups, int n_files);

int main(int argc, char* argv[]){
    if(argc < 4){
        std::cerr << "usage: " << argv[0] << " group_num n_groups files...\n";
        std::cerr << "  You must provide a list of files, the\n"
                     " number of groups to divide the files into,\n"
                     " and the group number that this instance should print.\n";
        return 1;
    }

    int group_num = atoi(argv[1]);
    int n_groups = atoi(argv[2]);

    if(group_num < 0 || group_num >= n_groups){
        std::cerr << " Error: group_num must be between 0 and (n_groups-1)!" << std::endl;
        return 1;
    }

    std::vector<char*> files(argv + 3, argv + argc);
    print_file_list(group_num, n_groups, files);
    return 0;
}

void print_file_list(int group_num, int n_groups, std::vector<char*> files){
    std::vector<int> inds = get_group_inds(group_num, n_groups, files.size());
    for(int i=inds[0]; i<inds[1]; i++){
        std::cout << files[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<int> get_group_inds(int group_num, int n_groups, int n_files){
    // Since integer division truncates, assume that every group needs an extra file (i.e. round up)
    int n_files_per_group = n_files / n_groups + 1;
    int first_ind = (group_num) * n_files_per_group;
    int last_ind = std::min((group_num+1) * n_files_per_group, n_files);
    std::vector<int> inds{first_ind, last_ind};
    return inds;
}
