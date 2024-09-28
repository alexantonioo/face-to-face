#include <vector>
#include <memory>
#include "Boxer.hpp"


class ComboNode 
{
public:
    ComboNode(std::function<void(Boxer&)> action) 
        : left(nullptr),right(nullptr),action(action)  {}

    std::shared_ptr<ComboNode> left;   
    std::shared_ptr<ComboNode> right;  
    std::function<void(Boxer&)> action;

    bool is_leaf() const 
        {
        return !left && !right;
    }
};

class ComboTree 
    {
public:
    ComboTree();

    void execute_combo(Boxer& boxer, const std::vector<std::string>& moves);

private:

    std::shared_ptr<ComboNode> root;

    std::shared_ptr<ComboNode> advance(std::shared_ptr<ComboNode> node, const std::string& move);
};