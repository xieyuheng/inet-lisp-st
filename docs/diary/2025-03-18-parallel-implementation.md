---
title: parallel implementation
date: 2025-03-18
---

并行编程学的差不多了。
记录一下目前能想到的实现并行 inet 的方案。

# 前提

首先计划使用 lock-free 的 queue，
因为如果不要求 queue 的两端都可以 enqueue 和 dequeue，
而是只要求一端可以 enqueue 另一端可以 dequeue，
并且又只要求两个 thread 在分别调用 enqueue 和 dequeue 时可以并行，
而不要求诸多 enqueue 或诸多 dequeue 之间的并行，
那么 lock-free 的实现就非常简单。
因为虽然 read 的数据重叠了（有 race），
但是 write 的数据没有重叠（没有 race）。

# 划分

设有一个 scheduler thread，和 N 个 worker thread。

scheduler thread 有 N 个 task queue，分别对应 N 个 worker：

- worker 可以 enqueue -- 把新生成的 task 返回给 scheduler。
- scheduler 可以 dequeue -- 把所收集到的 task 取出来，将会分配给某个 worker。

每个 worker thread 有一个 task queue：

- worker 可以 dequeue -- 取出 task 来处理。
- scheduler 可以 enqueue -- 把某个 task 分配给这个 worker。

# 分配

worker 返回给 scheduler 的 task 需要被重新分配给各个 worker，
分配 task 的策略可以多种多样，但是需要保证：

- 分配的速度本身不能太慢，scheduler 不应该卡住诸 worker 之运行。
- 分配要公平，要避免某个 worker 被分配了很多 task，
  而另外的 worker 没有分配 task 的情况。

具体方案如下：

- 首先，scheduler 读所有 worker 的待处理 task 数量，
  所读到的信息对于算法来说是 heuristic 的，
  因此不需要精确的数量，因此不需要 lock，。

- 然后，找到待处理 task 最多的 worker，
  思路是以它所待处理的 task 数量作为基准，
  给其他 worker 补充 task，
  以求把所有 worker 的有待处理的 task 数量补齐。
  假设，有 5 个 worker，
  所读到的待处理 task 数量分别是 [4, 6, 8, 12, 20]，
  最大是 20，因此需要补充的 task 数量分别是 [16, 14, 12, 8, 0]，
  在这个基础上增加一个常数，比如 1，
  以保证所有的 worker 都能分配到新的 task，
  因此需要补充的 task 数量分别是 [17, 15, 13, 9, 1]。

- 然后，scheduler 用 worker 返回给 scheduler 的 task
  去补齐 worker 的待处理 task。
  scheduler 在一个件循环中，
  逐个 dequeue 属于它自己的 N 个 task queue，
  补充到待补充的 worker 中。
  注意，在这个过程中，为了尽量避免某个 worker 没有活干，
  需要用消除俄罗斯方块的方式消除数组 [17, 15, 13, 9, 1]。
  具体效果如下：
  - [17, 15, 13, 9, 1]
  - [16, 14, 12, 8, 0]
  - [15, 13, 11, 7]
  - [14, 12, 10, 6]
  - ...
  - [8, 6, 4, 0]
  - [7, 5, 3]
  - ...

- 当待补齐的数组完全消除时，
  就重新读所有 worker 的待处理 task 数量，再补齐一次。

TODO 算法何时停止？如何开始？
