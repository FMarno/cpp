#include <nod/nod.hpp>

#include <iostream>
#include <memory>

class Tree;
class Branch;
class Node
{
public:
    nod::signal<void()> OnEnter;
    nod::signal<void()> OnCancel;
    nod::signal<void()> OnUp;
    nod::signal<void()> OnDown;

    virtual void SetTree(Tree* menu) = 0;
};
class Tree
{
    friend Branch;
    std::unique_ptr<Node> m_root;
    Node* m_active;

public:
    Tree(std::unique_ptr<Node> root) : m_root(std::move(root))
    {
        m_active = m_root.get();
        m_active->SetTree(this);
    }
    void Enter()
    {
        m_active->OnEnter();
    }
    void Cancel()
    {
        m_active->OnCancel();
    }
    void Up()
    {
        m_active->OnUp();
    }
    void Down()
    {
        m_active->OnDown();
    }
    bool IsActive(Node* node)
    {
        return m_active == node;
    }
};


class Branch : public Node
{
    std::vector<std::unique_ptr<Node>> m_children;
    std::size_t m_index;

public:
    Branch()
    {
        OnUp.connect([this]() { --m_index; });
        OnDown.connect([this]() { ++m_index; });
    }
    void AddNode(std::unique_ptr<Node> node)
    {
        m_children.push_back(std::move(node));
    }

    void SetTree(Tree* menu) override

    {
        std::for_each(m_children.begin(), m_children.end(), [this, menu](auto& nodeptr) {
            nodeptr->OnCancel.connect([this, menu]() { menu->m_active = this; });
            nodeptr->SetTree(menu);
        });
        OnEnter.connect(
            [this, menu]() { menu->m_active = m_children[m_index].get(); });
    }
};

class Leaf : public Node
{
public:
    void SetTree(Tree* menu) override
    {
    }
};

int main()
{
    auto root = std::make_unique<Branch>();
    auto rootptr = root.get();
    auto a = std::make_unique<Branch>();
    auto aptr = a.get();
    auto one = std::make_unique<Leaf>();
    auto two = std::make_unique<Leaf>();
    auto twoptr = two.get();
    a->AddNode(std::move(one));
    a->AddNode(std::move(two));
    auto b = std::make_unique<Leaf>();
    auto c = std::make_unique<Leaf>();
    root->AddNode(std::move(a));
    root->AddNode(std::move(b));
    root->AddNode(std::move(c));
    Tree tree(std::move(root));
    std::cout << tree.IsActive(rootptr) << '\n';
    tree.Enter();
    std::cout << tree.IsActive(aptr) << '\n';
    tree.Down();
    tree.Enter();
    std::cout << tree.IsActive(twoptr) << '\n';
    tree.Cancel();
    std::cout << tree.IsActive(aptr) << '\n';
    tree.Cancel();
    std::cout << tree.IsActive(rootptr) << '\n';
    tree.Cancel();
    std::cout << tree.IsActive(rootptr) << '\n';
}
