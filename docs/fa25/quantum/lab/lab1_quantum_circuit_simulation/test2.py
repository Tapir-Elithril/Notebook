import random
import time
from qubit_simulator import QubitSimulator
import matplotlib.pyplot as plt

def apply_circuit(circuit, n):
    circuit.reset()
    circuit.h(n - 1)
    for qubit in range(n - 1):
        circuit.cu(qubit, qubit + 1, random.random() * 3.14, random.random() * 3.14, random.random() * 3.14)

qubit_counts = list(range(2,15 + 1)) # from 2 to 15
execution_times = []

for n_qubits in qubit_counts:
    simulator = QubitSimulator(n_qubits)

    t = time.time()
    apply_circuit(simulator, n_qubits)
    execution_time = time.time() - t
    print(f"n_qubits = {n_qubits}:{execution_time}s")
    execution_times.append(execution_time)
    simulator.run(shots=1000)

plt.figure(figsize=(10, 6))
plt.plot(qubit_counts, execution_times, 'bo-', linewidth=2, markersize=6, label='real execution time')
plt.xlabel('n_qubits', fontsize=12)
plt.ylabel('execution time(s)', fontsize=12)
plt.title('QubitSimulator Benchmark', fontsize=14)
plt.grid(True, alpha=0.3)
plt.legend()
plt.yscale('log') 
plt.tight_layout()
plt.show()