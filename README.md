# Hierarchical Temporal Memory of a smoker

## Modifications

### Temporal memory

#### Bursting
- [x] Modification of bursting unpredicted column. I activate only winner cell
- [x] Fortunately, the model haven't lost its noise resistance.
- [ ] For more statistic confidence of trainability, I plan to add some random in bursting column.
- [ ] Besides, it can make sense to burst all the column while learn = false.


## Module
- [x] Being in the same folder with HTM.so you can import it with
```python
import HTM
```
or
```python
from HTM import temporal_memory
```
### Temporal Memory API:
#### init:
```python
tm = temporal_memory(
    (1, 2), # column_dimensions
    1,      # cells_per_column, default = 32
    1,      # min_threshold, default = 1
    1,      # activation_threshold, default = 2
    0.4,    # initial_permanence, default = 0.21
    0.5,    # connected_permanence, default = 0.5
    0.1,    # permanence_increment, default = 0.1
    0.1,    # permanence_decrement, default = 0.1
    0.05,   # predicted_segment_decrement, default = 0.0
    2,      # max_segments_per_cell, default = 255
    2       # max_synapses_per_segment, default = 255
)
```
#### computation/learning:
```python
tm.compute([[0, 1]], True) # computation of 2-d SDR. The second parameter is learning
```
#### evaluating model:
```python
tm.get_anomaly() 
# the score of unpredicted active cells and wrong predicted inactive cells 
```
