---
title: parallel implementation
date: 2025-03-18
---

并行编程学的差不多了。
记录一下目前能想到的实现并行 inet 的方案。

首先计划使用 lock-free 的 queue，
因为如果不要求 queue 的两端都可以 enqueue 和 dequeue，
而是只要求一端可以 enqueue 另一端可以 dequeue，
并且又只要求两个 thread 在分别调用 enqueue 和 dequeue 时可以并行，
而不要求诸多 enqueue 或诸多 dequeue 之间的并行，
那么 lock-free 的实现就非常简单。
因为虽然 read 的数据重叠了（有 race），
但是 write 的数据没有重叠（没有 race）。

设有一个 scheduler thread，和 N 个 worker thread。

scheduler thread 有 N 个 task queue，分别对应 N 个 worker：

- scheduler 可以 dequeue -- 把所收集到的 task 取出来，将会分配给某个 worker。
- worker 可以 enqueue -- 把新生成的 task 返回给 scheduler。

每个 worker thread 有一个 task queue：

- scheduler 可以 enqueue -- 把某个 task 分配给这个 worker。
- worker 可以 dequeue -- 取出 task 来处理。

TODO
