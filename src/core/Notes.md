
Circular Buffer Patten


```
Index:    [0] [1] [2] [3] [4] [5] ...
           ^
      writeIndex_ = 0

After pushing 3 values:
Index:    [A] [B] [C] [ ] [ ] [ ] ...
                       ^
              writeIndex_ = 3

After buffer fills and wraps:
Index:    [X] [Y] [Z] [D] [E] [F] ...  <- A, B, C overwritten
           ^
      writeIndex_ = 0 (wrapped)
```

2. Why constexpr?
static constexpr size_t SIZE = 120; is evaluated at compile time
No runtime cost, acts like a constant
Can be used in template parameters and array sizes
3. Why std::array not std::vector?
Fixed size known at compile time → use std::array
No heap allocation, better cache locality, faster
std::vector is for dynamic sizes
4. Why store in milliseconds (float)?
ImGui's PlotLines expects float*
Milliseconds (16.67ms) are more human-readable than seconds (0.01667)
Float precision is sufficient for frametime graphs