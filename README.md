# Quantum Random Data and Coin Toss Services (Windows)

## Overview

This pilot project, designed for the Windows platform, utilizes two software processes: `RGNG.exe` and `QRNG.exe`. The goal of the project is to fetch and process random data from a quantum source and simulate coin tosses to test Dr. Dean Radin's hypothesis that the mind may influence matter, particularly quantum processes. Dr. Radin suggests that true random number generators (TRNGs) might exhibit periods of variability in randomness, influenced by the mind. As a comparison, a high-quality pseudo-random number generator (PRNG) is also used.

## Project Components

- **`QRNG.exe`**: Fetches quantum-generated random data from the Australian National University Quantum Random Number Generator (ANU QRNG) server. The data is streamed to a local datagram socket for `RGNG.exe` to process.
  
- **`RGNG.exe`**: Receives quantum random data from the local datagram socket and simulates coin toss experiments. It calculates Shannon Eta entropy for each experiment and provides statistical analysis, including the mean, standard deviation, minimum, and maximum entropy values across multiple experiment runs.

## Experiment Details

- **Coin Toss Simulation**: The experiment involves a series of 262,144 coin tosses. Each experiment is repeated 256 times (an experiment run). Shannon Eta entropy is calculated for each experiment, and summary statistics (mean, standard deviation, minimum, and maximum entropy) are generated for the entire experiment run.

- **Output**: The processed data is used to generate visualizations via Google Charts in `RGNG.exe`.

## Modularity and Component Design

This project highlights the benefits of modular software components, where each component has a distinct, clearly defined responsibility. For example, in this setup, the random data source was switched from a TRNG based on transistor noise to true quantum randomness from the ANU QRNG, without needing to modify the overall system.

- **`RGNG.exe`** is implemented in C++
- **`QRNG.exe`** is implemented in C#

## Future Considerations

- Further refine the input, output, and core functionality descriptions for each component.
- Use Sandcastle Help File Builder to generate documentation, enabling XML Comments File Generation for C# and exploring options for documenting C++.
- Focus on documenting the design of both C# and C++ services, providing clarity on their architecture, functionality, and interactions.
