/*#include "BehaviorTree.hpp"

NodeStatus SequenceNode::tick() {
    for (auto& child : children_) {
        NodeStatus status = child->tick();
        if (status != NodeStatus::Success) {
            return status;  
        }
    }
    return NodeStatus::Success;
}


NodeStatus SelectorNode::tick() {
    for (auto& child : children_) {
        NodeStatus status = child->tick();
        if (status == NodeStatus::Success) {
            return NodeStatus::Success;  
        } else if (status == NodeStatus::Running) {
            return NodeStatus::Running;  
        }
    }
    return NodeStatus::Failure; 
}*/