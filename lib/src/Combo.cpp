#include "Combo.hpp"
#include <iostream> 

ComboTree::ComboTree() 
{
    root = std::make_shared<ComboNode>(nullptr);

    
    root->left = std::make_shared<ComboNode>([](Boxer& boxer) 
        {
        //boxer.jab_left();
    });
    
    root->right = std::make_shared<ComboNode>([](Boxer& boxer) 
        {
        //boxer.jab_right();
    });
    
    root->left->left = std::make_shared<ComboNode>([](Boxer& boxer) 
        {
        boxer.hook(); 
    });

    
    root->right->right = std::make_shared<ComboNode>([](Boxer& boxer) 
        {
        boxer.uppercut(); 
    });
}
//more hits

void ComboTree::execute_combo(Boxer& boxer, const std::vector<std::string>& moves) 
{
    std::shared_ptr<ComboNode> current_node = root;
    
    for (const auto& move : moves) 
        {
        current_node = advance(current_node, move);
        if (!current_node) 
            {
            std::cout << "Combo incompleto." << std::endl;
            return;  
        }

        if (current_node->is_leaf()) 
            {
            current_node->action(boxer);  
            return;
        }
    }
}

// Advance through the combo tree based on movement
std::shared_ptr<ComboNode> ComboTree::advance(std::shared_ptr<ComboNode> node, const std::string& move) 
    {

    if (move == "jab_left") 
        {
        return node->left;
    } 

    else if (move == "jab_right") 
        {
        return node->right;
    }

    return nullptr;  
}  

