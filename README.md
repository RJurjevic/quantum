# Quantum Random Data and Coin Toss Services (Windows)

## Overview

This project, designed for the Windows platform, uses two software processes: `RGNG.exe` and `QRNG.exe`. Its goal is to fetch and process random data from a quantum source and simulate coin tosses to test [Dr. Dean Radin](https://en.wikipedia.org/wiki/Dean_Radin)'s hypothesis that the mind may influence matter, particularly quantum processes. Dr. Radin suggests that true random number generators (TRNGs) might exhibit variability in randomness, potentially influenced by the mind. As a comparison, the project also utilizes a high-quality pseudo-random number generator (PRNG).

The quantum random data is retrieved from the [Australian National University Quantum Random Number Generator (ANU QRNG)](https://qrng.anu.edu.au/) server, which generates true random numbers based on quantum fluctuations.

### Investigating the Hypothesis

Initially, I believed that seeing Shannon Eta entropy events in the range of minus 9 to 12 sigma clearly indicated that the TRNG was influenced, as such events should be extremely rare. However, after performing brute force statistical calculations using Mathematica, I discovered that these events are not as rare as expected.

The behavior of the TRNG was found to be statistically normal. A parallel comparison with a good pseudo-random number generator (PRNG) revealed similar behavior between the TRNG and PRNG. Therefore, my conclusion is that both generators behaved exactly as predicted by statistical models, which falsifies Dr. Radin's claim that the mind may influence TRNGs.

#### Brute Force Statistical Analysis

Shannon Eta entropy depends only on the number of 1s in the binary representation of 8192 bits. I calculated the entropy for specific numbers of 1s and used a formula to compute how many permutations with that number of 1s exist. From there, I calculated the probability of that Shannon Eta entropy occurring in the experiment.

The brute force calculation shows that events with minus 9 to 12 sigma occur far more frequently than normal distribution assumptions would suggest. In fact, my results show that these events, which would occur once every hundred years under a normal distribution assumption, actually happen much more often—roughly once every half a day in my experiments.

> "This project demonstrates a well-structured approach to both random number generation and data analysis, using two independent software components to compare the behavior of quantum-based true random number generators (TRNG) with high-quality pseudo-random number generators (PRNG). Through robust statistical analysis, including Shannon Eta entropy calculations, the results show that both TRNG and PRNG behave consistently with statistical expectations, falsifying Dr. Radin's hypothesis that the mind may influence TRNGs." — ChatGPT

### Project Components

- **`QRNG.exe`**: Fetches quantum-generated random data from the ANU QRNG server. The data is written to a local file `data.bin` for `RGNG.exe` to process.
  
- **`RGNG.exe`**: Reads the quantum random data from the local file `data.bin` and simulates coin toss experiments. It calculates [Shannon Eta entropy](https://en.wikipedia.org/wiki/Entropy_(information_theory)) for each experiment and performs statistical analysis, including mean, standard deviation, minimum, and maximum entropy values across multiple experiment runs.

## Experiment Details

- **Coin Toss Simulation**: The experiment involves a series of 8192 coin tosses. Each experiment is repeated 16 times (forming an experiment run). Shannon Eta entropy is calculated for each experiment, and summary statistics (mean, standard deviation, minimum, and maximum entropy) are generated for the entire experiment run.

- **Output**: The processed data is used to generate visualizations via Google Charts in `RGNG.exe`.

## How to Run the Project

1. First, run `QRNG.exe` to start fetching quantum random data from the ANU QRNG server. Wait for the first batch of data to be fetched, which will create a `data.bin` file containing 1024 bytes of random data.
2. Once the `data.bin` file has been created, start `RGNG.exe` in a separate command prompt to begin processing the random data.
3. Open two command prompts (or use Windows Terminal available on Windows 11 or Windows 10), and run each `.exe` in its own window. The two processes will work in harmony, with `QRNG.exe` continuously writing new random data to the `data.bin` file, and `RGNG.exe` processing it.
4. Both `QRNG.exe` and `RGNG.exe` should be left running to conduct the experiments. The experiment results will be displayed on the screen by `RGNG.exe` and also written to files:
   - `PRNG.txt` contains the results from the pseudo-random number generator (PRNG) experiments.
   - `TRNG.txt` contains the results from the quantum random number generator (TRNG) experiments.
5. The data in the `.txt` files is formatted and ready to be inputted into Google Charts `.html` files for visualization. Please refer to `PTest-sample.html` for the PRNG data and `QTest-sample.html` for the TRNG data.
