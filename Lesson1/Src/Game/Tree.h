#pragma once

class Tree;

class TreeState
{
public:
    virtual void Grow(Tree* tree){};
    virtual void Draw(double x, double y) const = 0;
};

class Tree : public DynamicObject
{
public:
    Tree(std::unique_ptr<TreeState> st);
    ~Tree() = default;
    void Draw() const override;
    void Move(uint16_t dt) override;
    void SetState(std::unique_ptr<TreeState> s);

private:
    const float growTime = 5.f;
    float time{};
    std::unique_ptr<TreeState> state;
};

class SmallState : public TreeState
{
public:
    void Grow(Tree* tree) override;
    void Draw(double x, double y) const override;
};

class MiddleState : public TreeState
{
public:
    void Grow(Tree* tree) override;
    void Draw(double x, double y) const override;
};

class BigState : public TreeState
{
public:
    void Draw(double x, double y) const override;
};

