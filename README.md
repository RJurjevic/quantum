# Quantum Random Data and Coin Toss Services (Windows)

## Overview

This project, designed for the Windows platform, uses two software processes: `RGNG.exe` and `QRNG.exe`. Its goal is to fetch and process random data from a quantum source and simulate coin tosses to test [Dr. Dean Radin](https://en.wikipedia.org/wiki/Dean_Radin)'s hypothesis that the mind may influence matter, particularly quantum processes. Dr. Radin suggests that true random number generators (TRNGs) might exhibit variability in randomness, potentially influenced by the mind. As a comparison, the project also utilizes a high-quality pseudo-random number generator (PRNG).

The quantum random data is retrieved from the [Australian National University Quantum Random Number Generator (ANU QRNG)](https://qrng.anu.edu.au/) server, which generates true random numbers based on quantum fluctuations.

## Project Components

- **`QRNG.exe`**: Fetches quantum-generated random data from the ANU QRNG server. The data is written to a local file `data.bin` for `RGNG.exe` to process.
  
- **`RGNG.exe`**: Reads the quantum random data from the local file `data.bin` and simulates coin toss experiments. It calculates [Shannon Eta entropy](https://en.wikipedia.org/wiki/Entropy_(information_theory)) for each experiment and performs statistical analysis, including mean, standard deviation, minimum, and maximum entropy values across multiple experiment runs.

## Experiment Details

- **Coin Toss Simulation**: The experiment involves a series of 8192 coin tosses. Each experiment is repeated 16 times (forming an experiment run). Shannon Eta entropy is calculated for each experiment, and summary statistics (mean, standard deviation, minimum, and maximum entropy) are generated for the entire experiment run.

- **Output**: The processed data is used to generate visualizations via Google Charts in `RGNG.exe`.
