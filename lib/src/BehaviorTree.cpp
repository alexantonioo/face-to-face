#include "BehaviorTree.hpp"

// Implementación del nodo de secuencia
NodeStatus SequenceNode::tick() {
    for (auto& child : children_) {
        NodeStatus status = child->tick();
        if (status != NodeStatus::Success) {
            return status;  // Si algún hijo falla o está corriendo, detenemos la secuencia
        }
    }
    return NodeStatus::Success;
}

// Implementación del nodo de selección
NodeStatus SelectorNode::tick() {
    for (auto& child : children_) {
        NodeStatus status = child->tick();
        if (status == NodeStatus::Success) {
            return NodeStatus::Success;  // Retorna éxito si algún hijo tiene éxito
        } else if (status == NodeStatus::Running) {
            return NodeStatus::Running;  // Retorna corriendo si algún hijo está en ejecución
        }
    }
    return NodeStatus::Failure;  // Falla si todos los hijos fallan
}