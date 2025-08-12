#pragma once
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
};

// Simple condition node: executes a predicate (no side effects) and returns
// Success if predicate is true, otherwise Failure. Never returns Running.
class ConditionNode : public BehaviorNode {
public:
    using ConditionFunction = std::function<bool()>;
    explicit ConditionNode(ConditionFunction condition) : condition_(std::move(condition)) {}
    NodeStatus tick() override { return condition_() ? NodeStatus::Success : NodeStatus::Failure; }
private:
    ConditionFunction condition_;
};