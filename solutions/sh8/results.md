### Task 1

The pull request addresses the issue of false sharing in the Vulkan Validation Layers code. False sharing occurs when multiple threads inadvertently use the same cache line, leading significantly lower performance. 

In the project padding for structs was done by arrays of bytes but the PR recommends using alignas to ensure proper alignment preventing false sharing by making sure variables of different structs are not allocated in the same cache line

the code was updated with this ````class alignas(get_hardware_destructive_interference_size())```` to use alignas and a get the right alignments with the cache lines of the target hardware, previously from what it seems to me they were using an array of a fixed size to add padding


### Task 2

https://github.com/redpanda-data/redpanda/pull/18499

The pull request on the Redpanda repository replaces the absl::btree_map with a chunked_hash_map in the kvstore component, the following points were considered when making the decision:

- he chunked_hash_map supports fragmented data structures, which can improve memory management and reduce fragmentation
- Hash maps typically offer better average case performance for insertions, deletions, and lookups compared to tree map
- the code does not rely on the ordered properties of btree_map, making the transition straightforward
