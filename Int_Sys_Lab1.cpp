#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <string>
#include <stack>
#include <set>
#include <unordered_set>

typedef int (*Operation) (int n);

struct op_struct
{
    Operation op;
    std::string str;
};

struct node
{
    node* prev;
    op_struct op;
    int n;
    int c;
};

struct op_struct_bi
{
    Operation op_f;
    Operation op_b;
    std::string str_f;
    std::string str_b;
};

struct node_bi
{
    node_bi* prev;
    op_struct_bi op;
    int n;
    int c;
    bool dir;
};

int add3(int n)
{
    return n + 3;
}

int mult2(int n)
{
    return n * 2;
}

int dec2(int n)
{
    return n - 2;
}

int dec3(int n)
{
    return n - 3;
}

int div2(int n)
{
    return n / 2;
}

void bfs1(int start, int final, std::vector<op_struct> operations)
{
    std::queue<node*> q;
    std::set<int> visited;

    node* start_node = new node;
    start_node->n = start;
    start_node->c = 0;
    start_node->prev = nullptr;

    q.push(start_node);

    while (!q.empty())
    {
        node* cur = q.front();
        q.pop();

        for (op_struct op : operations)
        {
            node* next = new node;
            int n = op.op(cur->n);
            next->op = op;
            next->n = n;
            next->prev = cur;
            next->c = cur->c + 1;

            if (next->n == final)
            {
                std::stack<std::string> steps;
                int c = next->c;
                while (next->prev != nullptr)
                {
                    steps.push(next->op.str);
                    next = next->prev;
                }
                while (!steps.empty())
                {
                    std::cout << steps.top();
                    steps.pop();
                }
                std::cout << std::endl;

                std::cout << "Длина решения: " << c << std::endl;

                return;
            }

            if (visited.find(next->n) == visited.end())
            {
                visited.insert(next->n);
                q.push(next);
            }
        }
    }
}

void bfs2(int start, int final, std::vector<op_struct> operations)
{
    std::queue<node*> q;
    std::set<int> visited;

    node* start_node = new node;
    start_node->n = start;
    start_node->c = 0;
    start_node->prev = nullptr;

    q.push(start_node);

    while (!q.empty())
    {
        node* cur = q.front();
        q.pop();

        for (op_struct op : operations)
        {
            node* next = new node;
            int n = op.op(cur->n);
            next->op = op;
            if (cur->n % 2 != 0 && op.str == operations[1].str)
            {
                continue;
            }
            next->n = n;
            next->prev = cur;
            next->c = cur->c + 1;

            if (next->n == final)
            {
                std::stack<std::string> steps;
                int c = next->c;
                while (next->prev != nullptr)
                {
                    steps.push(next->op.str);
                    next = next->prev;
                }
                while (!steps.empty())
                {
                    std::cout << steps.top();
                    steps.pop();
                }
                std::cout << std::endl;

                std::cout << "Длина решения: " << c << std::endl;

                return;
            }

            if (visited.find(next->n) == visited.end())
            {
                visited.insert(next->n);
                q.push(next);
            }
        }
    }
}

void bi_bfs(int start, int final, std::vector<op_struct_bi> operations)
{
    std::queue<node_bi*> q_f;
    std::queue<node_bi*> q_b;
    std::set<int> visited_f;
    std::set<int> visited_b;

    node_bi* start_node_f = new node_bi;
    start_node_f->n = start;
    start_node_f->c = 0;
    start_node_f->prev = nullptr;

    node_bi* start_node_b = new node_bi;
    start_node_b->n = final;
    start_node_b->c = 0;
    start_node_b->prev = nullptr;

    q_f.push(start_node_f);
    q_b.push(start_node_b);

    while (!q_f.empty() && !q_b.empty())
    {
        node_bi* cur_f = q_f.front();
        q_f.pop();

        node_bi* cur_b = q_b.front();
        q_b.pop();

        for (op_struct_bi op : operations)
        {
            node_bi* next_f = new node_bi;
            next_f->n = op.op_f(cur_f->n);
            next_f->op = op;
            next_f->prev = cur_f;
            next_f->c = cur_f->c + 1;

            node_bi* next_b = new node_bi;
            if (!(cur_b->n % 2 != 0 && op.str_b == operations[1].str_b))
            {
                next_b->op = op;
                next_b->n = op.op_b(cur_b->n);;
                next_b->prev = cur_b;
                next_b->c = cur_b->c + 1;
            }

            if (visited_b.find(next_f->n) != visited_b.end())
            {
                while (cur_b->n != next_f->n)
                {
                    cur_b = q_b.front();
                    q_b.pop();
                }

                std::stack<std::string> steps_f;
                int c = next_f->c;
                while (next_f->prev != nullptr)
                {
                    steps_f.push(next_f->op.str_f);
                    next_f = next_f->prev;
                }
                while (!steps_f.empty())
                {
                    std::cout << steps_f.top();
                    steps_f.pop();
                }

                std::cout << " -><- ";

                c += cur_b->c;
                while (cur_b->prev != nullptr)
                {
                    std::cout << cur_b->op.str_b;
                    cur_b = cur_b->prev;
                }
                std::cout << std::endl;
                std::cout << "Длина решения: " << c << std::endl;

                return;
            }

            if (visited_f.find(next_b->n) != visited_f.end() && next_b->prev != nullptr)
            {
                while (cur_f->n != next_b->n)
                {
                    cur_f = q_f.front();
                    q_f.pop();
                }

                std::stack<std::string> steps_b;
                int c = next_b->c;
                while (next_b->prev != nullptr)
                {
                    steps_b.push(next_b->op.str_b);
                    next_b = next_b->prev;
                }
                while (!steps_b.empty())
                {
                    std::cout << steps_b.top();
                    steps_b.pop();
                }

                std::cout << " -><- ";

                c += cur_f->c;
                while (cur_f->prev != nullptr)
                {
                    std::cout << cur_f->op.str_f;
                    cur_f = cur_f->prev;
                }
                std::cout << std::endl;
                std::cout << "Длина решения: " << c << std::endl;

                return;
            }

            if (visited_f.find(next_f->n) == visited_f.end())
            {
                visited_f.insert(next_f->n);
                q_f.push(next_f);
            }

            if (visited_b.find(next_b->n) == visited_b.end())
            {
                visited_b.insert(next_b->n);
                q_b.push(next_b);
            }

        }
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<op_struct> op_vec;
    std::vector<op_struct> rev_op_vec;
    std::vector<op_struct_bi> bi_op_vec;

    {
        op_struct add3_struct;
        add3_struct.op = add3;
        add3_struct.str = "+3 ";

        op_struct mult2_struct;
        mult2_struct.op = mult2;
        mult2_struct.str = "*2 ";

        op_struct dec2_struct;
        dec2_struct.op = dec2;
        dec2_struct.str = "-2 ";

        op_struct dec3_struct;
        dec3_struct.op = dec3;
        dec3_struct.str = "-3 ";

        op_struct div2_struct;
        div2_struct.op = div2;
        div2_struct.str = "/2 ";

        op_struct_bi add3_struct_bi;
        add3_struct_bi.op_f = add3;
        add3_struct_bi.op_b = dec3;
        add3_struct_bi.str_f = "+3 ";
        add3_struct_bi.str_b = "-3 ";

        op_struct_bi mult2_struct_bi;
        mult2_struct_bi.op_f = mult2;
        mult2_struct_bi.op_b = div2;
        mult2_struct_bi.str_f = "*2 ";
        mult2_struct_bi.str_b = "/2 ";

        op_vec.push_back(add3_struct);
        op_vec.push_back(mult2_struct);
        //op_vec.push_back(dec2_struct);

        rev_op_vec.push_back(dec3_struct);
        rev_op_vec.push_back(div2_struct);

        bi_op_vec.push_back(add3_struct_bi);
        bi_op_vec.push_back(mult2_struct_bi);
    }


    int start;
    int final;

    std::cout << "Введите начальное значение:" << std::endl;
    std::cin >> start;

    std::cout << "Введите конечное значение:" << std::endl;
    std::cin >> final;

    std::cout << " === от " << start << " до " << final << " === " << std::endl << std::endl;
    {
        std::cout << "-- Прямое решение --" << std::endl;
        auto start_time = std::chrono::steady_clock::now();
        bfs1(start, final, op_vec);
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "Время выполнения: " << elapsed_ns.count() << " ms\n";
        std::cout << std::endl;
    }

    {
        std::cout << "-- Обратное решение --" << std::endl;
        auto start_time = std::chrono::steady_clock::now();
        bfs2(final, start, rev_op_vec);
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "Время выполнения: " << elapsed_ns.count() << " ms\n";
        std::cout << std::endl;
    }

    {
        std::cout << "--Двунаправленное  решение --" << std::endl;
        auto start_time = std::chrono::steady_clock::now();
        bi_bfs(start, final, bi_op_vec);
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "Время выполнения: " << elapsed_ns.count() << " ms\n";
    }
    
    system("pause");
}