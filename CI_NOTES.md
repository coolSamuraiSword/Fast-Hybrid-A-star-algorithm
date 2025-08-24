# CI Notes

Recommended continuous integration checks:

- Build Debug and Release configurations on Linux and macOS with both GCC and Clang.
- Run all tests and benchmarks.
- Enable `-DFRONTIER_COLLECT_STATS` in one job to gather frontier statistics.
- Use AddressSanitizer (`-fsanitize=address,undefined`) for Debug builds.
- Cache CMake configuration and build artifacts.

