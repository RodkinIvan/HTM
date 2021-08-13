import matplotlib.pyplot as plt
from HTM import temporal_memory


def make_sdrs(bits_array):
    sdrs = []
    for bit in bits_array:
        sdrs.append([[not bool(bit), bool(bit)]])
    return sdrs


tm = temporal_memory(
    (1, 2), # column_dimensions
    4,      # cells_per_column
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
bits_array = [0, 1, 0, 1, 1, 0, 1, 0]
sdrs = make_sdrs(bits_array)
errors = []
for i in range(7):
    for sdr in sdrs:
        tm.compute(sdr, True)
        errors.append(tm.get_anomaly())

plt.plot(range(len(errors)), errors)
plt.show()