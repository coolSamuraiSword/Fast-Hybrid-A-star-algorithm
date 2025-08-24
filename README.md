# hybrid-a-star-frontiers

Minimal C++20 skeleton for experimenting with Hybrid A* frontier data structures.

## Frontiers overview

The project implements three interchangeable frontier containers:

- **BinaryHeap** – classic binary heap providing an optimal frontier.
- **WindowedFQueue** – an exact priority queue that remains optimal when the window size `delta` is no larger than the smallest motion cost `c_min` and the heuristic is consistent.
- **BucketHeap** – a bounded-suboptimal structure using `K` buckets to trade search quality for speed; smaller `delta` and larger `K` improve optimality.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Running CLI examples

```bash
./hybrid_astar --frontier=binary
./hybrid_astar --frontier=window --delta=1.0
./hybrid_astar --frontier=bucket --delta=0.5 --K=512
```

## Running benchmarks

```bash
./frontier_bench --seed=1 --rho=0.3 --spread=0.5
```

## Notes

- `WindowedFQueue` is correct when `delta <= c_min` and the heuristic is consistent.
- To experiment with a full Hybrid A* planner, replace the stubs in `src/` (e.g., `main.cpp`) with real successor generation and collision checking logic.

## License

Placeholder license. See [LICENSE](LICENSE) for details.

