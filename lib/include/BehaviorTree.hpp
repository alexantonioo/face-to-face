#pragma once
#include <vector>
#include <memory>
#include <functional>

enum class NodeStatus { Success, Failure, Running };

// Clase base para todos los nodos
class BehaviorNode {
public:
    virtual ~BehaviorNode() = default;
    virtual NodeStatus tick() = 0;  // método de ejecución principal para cada nodo
};

// Nodo de acción: realiza acciones específicas, como golpear o esquivar
class ActionNode : public BehaviorNode {
public:
    using ActionFunction = std::function<NodeStatus()>;
    
    explicit ActionNode(ActionFunction action) : action_(action) {}
    NodeStatus tick() override { return action_(); }

private:
    ActionFunction action_;
};

// Nodo de secuencia: ejecuta sus hijos en orden hasta que uno falla
class SequenceNode : public BehaviorNode {
public:
    void addChild(std::shared_ptr<BehaviorNode> child) { children_.push_back(child); }
    NodeStatus tick() override;

private:
    std::vector<std::shared_ptr<BehaviorNode>> children_;
};

// Nodo de selección: intenta ejecutar a sus hijos hasta que uno tenga éxito
class SelectorNode : public BehaviorNode {
public:
    void addChild(std::shared_ptr<BehaviorNode> child) { children_.push_back(child); }
    NodeStatus tick() override;

private:
    std::vector<std::shared_ptr<BehaviorNode>> children_;
};