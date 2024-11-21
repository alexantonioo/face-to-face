/*#pragma once
#include <vector>
#include <memory>
#include <functional>

enum class NodeStatus { Success, Failure, Running };


class BehaviorNode {
public:
    virtual ~BehaviorNode() = default;
    virtual NodeStatus tick() = 0;  
};


class ActionNode : public BehaviorNode {
public:
    using ActionFunction = std::function<NodeStatus()>;
    
    explicit ActionNode(ActionFunction action) : action_(action) {}
    NodeStatus tick() override { return action_(); }

private:
    ActionFunction action_;
};


class SequenceNode : public BehaviorNode {
public:
    void addChild(std::shared_ptr<BehaviorNode> child) { children_.push_back(child); }
    NodeStatus tick() override;

private:
    std::vector<std::shared_ptr<BehaviorNode>> children_;
};


class SelectorNode : public BehaviorNode {
public:
    void addChild(std::shared_ptr<BehaviorNode> child) { children_.push_back(child); }
    NodeStatus tick() override;

private:
    std::vector<std::shared_ptr<BehaviorNode>> children_;
};*/