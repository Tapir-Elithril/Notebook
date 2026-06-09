from qubit_simulator import QubitSimulator

if __name__ == "__main__":
    simulator = QubitSimulator(num_qubits=5)
    simulator.h(0)
    simulator.cx(1,0) # target, control
    simulator.cx(2,1)
    simulator.cx(3,2)
    simulator.cx(4,3)

    res = simulator.run(shots=1000)
    print(res)
    print(simulator)
    simulator.plot_wavefunction()
