#include <iostream>
#include <vector>
//#include <chrono>
//#include <thread>

struct branch_segment {
    int m;
    int n;
    int result = -1;
    int parent = -1;
    int center_child = -1;
    int m_child = -1;
    int n_child = -1;
};

int main(int argc, char *argv[]) {
    std::vector<branch_segment * > tree;
    
    branch_segment * root = new branch_segment;
    
    root->m = 4;
    root->n = 1;
    
    tree.push_back(root);
    size_t i = 0; // gives loop context
    
    std::cout << "Starting loop... " << std::endl;
    
    if (!(0 > -1)) return 1;
    
    #define t tree[i]
    while (!(tree[0]->result > -1))
    { /*
        std::cout << "========================" << std::endl;
        std::cout << "Size: " << tree.size() << std::endl;
        std::cout << "Parent: " << t->parent << std::endl;
        std::cout << "Current index: " << i << std::endl; */
        if (t->m == 0) 
        {
            t->result = t->n + 1;
            
            if ((tree[i]->parent) > -1)
            {
                i = t->parent;
            }
            
        } 
        else if (t->n == 0) 
        {            
            // center path;
            if (t->center_child != -1) // already calculated child
            {
                t->result = tree[t->center_child]->result;
                
                if (t->parent != -1) i = t->parent;
                
            } else 
            {// child not calculated yet
                branch_segment * new_branch = new branch_segment;
                new_branch->m = t->m - 1;
                new_branch->n = 1;
                new_branch->parent = i;
                tree.push_back(new_branch);
                t->center_child = tree.size() - 1;
                i = tree.size() - 1;
            }
            
        } 
        else
        {
            if (t->n_child != -1)
            { // sub-branch already calculated
                if (t->center_child != -1)
                { // center branch already calculated 
                    t->result = tree[t->center_child]->result;
                    
                    if (t->parent != -1) i = t->parent;
                }
                else
                {
                    branch_segment * new_branch = new branch_segment;
                    new_branch->m = t->m - 1;
                    new_branch->n = tree[t->n_child]->result;
                    new_branch->parent = i;
                    tree.push_back(new_branch);
                    t->center_child = tree.size() - 1;
                    i = tree.size() - 1;
                }
            }
            else
            { // n child not created yet
                branch_segment * new_branch = new branch_segment;
                new_branch->m = t->m;
                new_branch->n = t->n - 1;
                new_branch->parent = i;
                tree.push_back(new_branch);
                t->n_child = tree.size() - 1;
                i = tree.size() - 1;
            }
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    std::cout << "Completed." << std::endl;
    std::cout << "\nResult: A(" << root->m << ", " << root->n << ") = " << root->result << std::endl;
    
    while (tree.size() > 0) {
        branch_segment * a = tree.back();
        tree.pop_back();
        delete a;
    }
    
    return 0;
}
