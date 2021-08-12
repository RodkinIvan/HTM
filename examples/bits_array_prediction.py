import matplotlib.pyplot as plt
from HTM import temporal_memory

tm = temporal_memory(
    (1, 2), # column_dimensions
    1,      # cells_per_column
    1,      # min_threshold
    1,      # activation_threshold
    0.4,    # initial_permanence
    0.5,    # connected_permanence
    0.1,    # permanence_increment
    0.1,    # permanence_decrement
    0.05,   # predicted_segment_decrement
    2,      # max_segments_per_cell
    2       # max_synapses_per_segment
)
errors = []
for i in range(5):
    tm.compute([[0, 1]], True)
    errors.append(tm.get_anomaly())
    tm.compute([[1, 0]], True)
    errors.append(tm.get_anomaly())

plt.plot(range(len(errors)), errors)
plt.show()