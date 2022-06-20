#include <iostream>
#include <memory>
#include <queue>
#include <algorithm>

template<typename DataType>
class Node
{
public:
    using shared_type = std::shared_ptr<Node>;
    using data_type = DataType;

    Node();
    Node(DataType data);
    virtual ~Node();

    shared_type left();
    shared_type right();
    void left(shared_type l);
    void right(shared_type r);

    shared_type parent();
    void parent(shared_type p);

    DataType data();
    void data(DataType const& d);

    int height();
    void height(int h);

private:
    DataType data_;

    int height_;

    shared_type left_;
    shared_type right_;
    shared_type parent_;
};


template<typename DataType>
Node<DataType>::Node()
    : height_(1)
{
}

template<typename DataType>
Node<DataType>::Node(DataType data)
    : data_(data)
    , height_(1)
{
}

template<typename DataType>
Node<DataType>::~Node()
{
}

template<typename DataType>
typename Node<DataType>::shared_type Node<DataType>::left()
{
    return left_;
}

template<typename DataType>
typename Node<DataType>::shared_type Node<DataType>::right()
{
    return right_;
}

template<typename DataType>
void Node<DataType>::left(typename Node<DataType>::shared_type l)
{
    left_ = l;
}

template<typename DataType>
void Node<DataType>::right(typename Node<DataType>::shared_type r)
{
    right_ = r;
}

template<typename DataType>
typename Node<DataType>::shared_type Node<DataType>::parent()
{
    return parent_;
}

template<typename DataType>
void Node<DataType>::parent(shared_type p)
{
    parent_ = p;
}

template<typename DataType>
DataType Node<DataType>::data()
{
    return data_;
}

template<typename DataType>
void Node<DataType>::data(DataType const& d)
{
    data_ = d;
}

template<typename DataType>
int Node<DataType>::height()
{
    return height_;
}

template<typename DataType>
void Node<DataType>::height(int h)
{
    height_ = h;
}

template<typename NodeType>
class AVLTree
{
public:
    using shared_type = std::shared_ptr<AVLTree>;

    using node_type = typename NodeType::shared_type;
    using data_type = typename NodeType::data_type;

    AVLTree();
    AVLTree(node_type r);
    virtual ~AVLTree();

    void insert_node(node_type node);
    void erase_node(data_type data);
    node_type find_node(data_type data);

    void print();

private:
    void rebalance(node_type node);
    int get_height(node_type node);
    void calc_height(node_type node);
    int balance_factor(node_type node);
    node_type ll_rotation(node_type node);
    node_type rr_rotation(node_type node);
    node_type lr_rotation(node_type node);
    node_type rl_rotation(node_type node);

    node_type root_;
};

template<typename NodeType>
AVLTree<NodeType>::AVLTree()
{
}

template<typename NodeType>
AVLTree<NodeType>::AVLTree(node_type r)
    : root_(r)
{
}

template<typename NodeType>
AVLTree<NodeType>::~AVLTree()
{
}

template<typename NodeType>
void AVLTree<NodeType>::print()
{
    std::cout<<"print start===========================================\n";
    if(root_.get() == nullptr)
    {
        std::cout<<"null\n";
        return;
    }

    std::queue<node_type> q;
    q.push(root_);
    
    std::cout<<"root : "<<root_->data()<<" ";

    while(q.empty() == false)
    {
        auto c = q.front();
        q.pop();

        std::cout<<"\n-------------\n";

        if(c->left().get() != nullptr)
        {
            std::cout<<"L : "<<c->left()->data()<<" ";
            if(c->left()->parent().get() != nullptr) std::cout<<"("<<c->left()->parent()->data()<<") ";
            q.push(c->left());
        }
        else std::cout<<"L : null ";

        if(c->right().get() != nullptr)
        {
            std::cout<<"R : "<<c->right()->data()<<" ";
            if(c->right()->parent().get() != nullptr) std::cout<<"("<<c->right()->parent()->data()<<") ";
            q.push(c->right());
        }
        else std::cout<<"R : null ";
    }

    std::cout<<"\n===========================================print end\n";
}

template<typename NodeType>
int AVLTree<NodeType>::get_height(node_type node)
{
    if(node.get() == nullptr) return 0;
    return node->height();
}

template<typename NodeType>
int AVLTree<NodeType>::balance_factor(node_type node)
{
    if(node.get() == nullptr) return 0;
    return get_height(node->left()) - get_height(node->right());
}

template<typename NodeType>
typename AVLTree<NodeType>::node_type AVLTree<NodeType>::ll_rotation(node_type node)
{
    std::cout<<"LL : "<<node->data()<<"\n";
    if(node.get() == nullptr) return {};

    auto parent = node->parent();
    auto current = node;
    auto right_child = node->right();
    auto left_child = node->left();

    if(parent.get() == nullptr) root_ = left_child;
    else
    {
        if(parent->left() == current) parent->left(left_child);
        else parent->right(left_child);
    }

    left_child->parent(parent);

    current->left(left_child->right());
    if(left_child->right().get() != nullptr) left_child->right()->parent(current);
    left_child->right(current);

    current->parent(left_child);

    print();
    return left_child;
}

template<typename NodeType>
typename AVLTree<NodeType>::node_type AVLTree<NodeType>::rr_rotation(node_type node)
{
    std::cout<<"RR : "<<node->data()<<"\n";
    if(node.get() == nullptr) return {};

    auto parent = node->parent();
    auto current = node;
    auto right_child = node->right();
    auto left_child = node->left();

    if(parent.get() == nullptr) root_ = right_child;
    else
    {
        if(parent->left() == current) parent->left(right_child);
        else parent->right(right_child);
    }
    
    right_child->parent(parent);

    current->right(right_child->left());
    if(right_child->left().get() != nullptr) right_child->left()->parent(current);
    right_child->left(current);

    current->parent(right_child);

    print();
    return right_child;
}

template<typename NodeType>
typename AVLTree<NodeType>::node_type AVLTree<NodeType>::lr_rotation(node_type node)
{
    std::cout<<"LR\n";
    if(node.get() == nullptr) return {};
    
    rr_rotation(node->left());    
    return ll_rotation(node);
}

template<typename NodeType>
typename AVLTree<NodeType>::node_type AVLTree<NodeType>::rl_rotation(node_type node)
{
    std::cout<<"RL\n";
    if(node.get() == nullptr) return {};

    ll_rotation(node->right());
    return rr_rotation(node);
}

template<typename NodeType>
void AVLTree<NodeType>::calc_height(node_type node)
{
    while(node.get() != nullptr)
    {
        int l = 0;
        int r = 0;

        if(node->left().get() != nullptr) l = node->left()->height();
        if(node->right().get() != nullptr) r = node->right()->height();

        node->height(std::max(l, r) + 1);
        node = node->parent();
    }
}

template<typename NodeType>
void AVLTree<NodeType>::rebalance(node_type node)
{
    std::cout<<"REBALANCE : "<<node->data()<<"\n";
    if(node.get() == nullptr)
    {
        std::cout<<"rebalance node nullptr\n";
        return;
    }

    calc_height(node);

    while(node.get() != nullptr)
    {
        auto bf = balance_factor(node);
        auto bf_left = balance_factor(node->left());
        auto bf_right = balance_factor(node->right());
        
        std::cout<<"node : "<<node->data()<<"\n";
        std::cout<<"bf : "<<bf<<", bf_left : "<<bf_left<<", bf_right : "<<bf_right<<"\n";

        if(bf == 2)
        {
            node_type r;
            if(bf_left == -1)
            {
                r = lr_rotation(node);
            }
            else if(bf_left == 1)
            {
                r = ll_rotation(node);
            }

            calc_height(node);
        }
        else if(bf == -2)
        {
            node_type r;
            if(bf_right == 1)
            {
                r = rl_rotation(node);
            }
            else if(bf_right == -1)
            {
                r = rr_rotation(node);
            }

            calc_height(node);
        }

        node = node->parent();
    }
}

template<typename NodeType>
void AVLTree<NodeType>::insert_node(node_type node)
{
    std::cout<<"INSERT : "<<node->data()<<"\n";
    if(root_.get() == nullptr)
    {
        root_ = node;
        return;
    }

    node_type current = root_;
    while(current.get() != nullptr)
    {
        if(current->data() > node->data())
        {
            if(current->left().get() != nullptr)
            {
                current = current->left();
            }
            else
            {
                node->parent(current);
                current->left(node);
                break;
            }
        }
        else if(current->data() <= node->data())
        {
            if(current->right().get() != nullptr)
            {
                current = current->right();
            }
            else
            {
                node->parent(current);
                current->right(node);
                break;
            }
        }
    }

    rebalance(current);
}

template<typename NodeType>
void AVLTree<NodeType>::erase_node(data_type data)
{
    std::cout<<"ERASE : "<<data<<"\n";
    auto target = find_node(data);
    if(target.get() == nullptr)
    {
        std::cout<<" > not found : "<<data<<"\n";
        return;
    }
    else std::cout<<" > found : "<<target->data()<<"\n";
    
    auto current = target;
    auto parent = current->parent();
    auto left_child = current->left();
    auto right_child = current->right();

    if(left_child.get() == nullptr && right_child.get() == nullptr)
    {
        std::cout<<"ERASE LR null\n";
        if(parent.get() == nullptr)
        {
            root_.reset();
            parent.reset();
            return;
        }

        if(parent->left() == current) parent->left({});
        if(parent->right() == current) parent->right({});

        current.reset();
        rebalance(parent);
    }
    else if(left_child.get() != nullptr && right_child.get() != nullptr)
    {
        std::cout<<"ERASE LR not null\n";
        node_type find = right_child;
        while(find->left() != nullptr) find = find->left();
        
        if(find->right().get() != nullptr)
        {
            current->data(std::move(find->data()));

            if(find->parent()->left() == find)
            {
                find->parent()->left(find->right());
                find->right()->parent(find->parent());
            }
            else
            {
                find->parent()->right(find->right());
                find->right()->parent(find->parent());
            }
        }
        else
        {
            target->data(std::move(find->data()));
            
            if(find->parent()->left() == find) find->parent()->left({});
            else find->parent()->right({});
        }

        rebalance(find->parent());
        find.reset();
    }
    else
    {
        if(left_child.get() != nullptr)
        {
            std::cout<<"ERASE L not null\n";
            if(parent->left() == current) parent->left(left_child);    
            else parent->right(left_child);

            left_child->parent(parent);
            current.reset();
            rebalance(left_child);
        }

        if(right_child.get() != nullptr)
        {
            std::cout<<"ERASE R not null\n";
            if(parent->left() == current) parent->left(right_child);
            else parent->right(right_child);

            right_child->parent(parent);
            current.reset();
            rebalance(right_child);
        }
    }
}

template<typename NodeType>
typename AVLTree<NodeType>::node_type AVLTree<NodeType>::find_node(data_type data)
{
    if(root_.get() == nullptr) return {};
    
    auto current = root_;
    while(current.get() != nullptr)
    {
        if(current->data() == data) return current;
        else if(current->data() > data) current = current->left();
        else if(current->data() <= data) current = current->right();
    }
    return {};
}

template<typename DataType>
typename Node<DataType>::shared_type create_node(DataType data)
{
    return std::make_shared<Node<DataType>>(data);
}

int main()
{
    auto avl = std::make_shared<AVLTree<Node<int>>>(create_node(10));
    avl->insert_node(create_node(9));
    avl->insert_node(create_node(8));
    avl->insert_node(create_node(7));
    avl->insert_node(create_node(6));
    avl->insert_node(create_node(5));
    avl->insert_node(create_node(4));
    avl->insert_node(create_node(3));
    avl->insert_node(create_node(2));
    avl->insert_node(create_node(1));

    avl->insert_node(create_node(12));
    avl->insert_node(create_node(13));
    avl->insert_node(create_node(14));
    avl->insert_node(create_node(15));
    avl->insert_node(create_node(16));
    avl->insert_node(create_node(17));
    avl->insert_node(create_node(18));

    avl->erase_node(5);
    avl->erase_node(4);
    avl->erase_node(3);
    avl->erase_node(2);
    avl->erase_node(1);
    
    avl->erase_node(16);
    avl->erase_node(17);
    avl->erase_node(18);

    avl->erase_node(12);
    avl->erase_node(8);
    avl->erase_node(14);
    
    avl->print();

    return 0;
}