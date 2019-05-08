# 基于蒙特卡洛树搜索的四子棋对战AI

## 文件版权说明

本人仅保留State.h/State.cpp和Policy.h/Policy.cpp的版权所有，其它文件版权不归本人所有，仅供参考，版权归属已在文件中注明。

## 简介

本对战AI基于蒙特卡洛树搜索算法（Monte Carlo Tree Search），通过应用蒙特卡洛树搜索，在规定时间内给出合适的落子决策，从而实现在四子棋游戏对战中的胜利。

* Strategy工程生成AI的dll文件，UI工程提供对战界面，可在界面中选择生成的dll进行对战

## 算法介绍

* **基础理论**

  蒙特卡洛树搜索算法的基本思想是沿着博弈树进行DFS，每次遍历的路径会从根节点延伸至未完全展开的子节点，即未曾访问过的可能博弈场景，进一步将该节点作为新的根节点继续博弈，在游戏模拟结束时，将模拟的结果以利益值（Profit）的形式反向传播至根节点并为路径上的节点更新访问次数。在限定时间到达时，结束博弈，并通过根节点的最优子节点决定下一步的行动方案。

* **伪码**

  ```python
  def monte_carlo_tree_search(root):
      while resources_left(time, computational power):
          leaf = traverse(root) # leaf = unvisited node 
          simulation_result = rollout(leaf)
          backpropagate(leaf, simulation_result)
      return best_child(root)
  
  def traverse(node):
      while fully_expanded(node):
          node = best_uct(node)
      return pick_univisted(node.children) or node # in case no children are present / node is terminal 
  
  def rollout(node):
      while non_terminal(node):
          node = rollout_policy(node)
      return result(node) 
  
  def rollout_policy(node):
      return pick_random(node.children)
  
  def backpropagate(node, result):
     if is_root(node) return 
     node.stats = update_stats(node, result) 
     backpropagate(node.parent)
  
  def best_child(node):
      pick child with highest number of visits
  ```

* **搜索**

  首先会对根节点进行展开，并进行模拟对战（rollout）和计算其子节点的利益，后反向传播给根节点。当根节点被完全展开后，选取其最优子节点继续展开、模拟、反向传播，直至限定时间到达。

* **模拟对战**

  模拟对战中，会等概率地选取可落子点，并以此为新的根节点，不断对战直至棋局结束，通过棋局的胜负获得利益。

* **最优子节点**

  最优子节点的选取依据为置信上限UCT，根据下述的UCT公式计算子节点的优势，并选取最优子节点。

  $$UCT(v_i,v)=\frac{Q(v_i)}{N(v_i)}+c\sqrt{\frac{log(N(v))}{N(v_i)}}$$

  UCT置信上限为蒙特卡洛树搜索提供了优胜依据，同时对搜索进行了加速。经过多次实验，实现中给出的系数c为2.4

## 代码结构

* **State**

  State类提供了MCTS算法中搜索树的子节点的数据结构，记录了当前对战状态的棋局、优胜状态等。

* **Policy**

  Policy类提供了MCTS算法的实现，并通过`gameDecision`函数给出最终的落子选择。

## 实验效果

在5s的时限内，算法能够以30%左右的胜率战胜90.dll文件提供的AI。对于60及以下的AI基本能够保持完全胜利。时限降至3s内时，算法的胜率出现下降，对于70左右的AI胜率较低，50及以下胜率较高。