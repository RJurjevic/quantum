# Quantum Random Data and Coin Toss Services (Windows)

## Overview

This project, designed for the Windows platform, uses two software processes: `RGNG.exe` and `QRNG.exe`. Its goal is to fetch and process random data from a quantum source and simulate coin tosses to test [Dr. Dean Radin](https://en.wikipedia.org/wiki/Dean_Radin)'s hypothesis that the mind may influence matter, particularly quantum processes. Dr. Radin suggests that true random number generators (TRNGs) might exhibit variability in randomness, potentially influenced by the mind. As a comparison, the project also utilizes a high-quality pseudo-random number generator (PRNG).

The quantum random data is retrieved from the [Australian National University Quantum Random Number Generator (ANU QRNG)](https://qrng.anu.edu.au/) server, which generates true random numbers based on quantum fluctuations.

## **Falsifying Dr. Radin’s Hypothesis with BitBabbler TRNG**

Initially, I suspected that **Shannon Eta entropy** values in the range of **-9σ to -12σ** indicated a significant deviation from randomness—suggesting that the **TRNG was influenced** by an external factor. Given how rare such events should be under a **normal distribution**, I expected them to occur far less frequently than observed, making their presence seem anomalous.

However, after conducting a **brute-force statistical analysis** using **Mathematica**, I found that these extreme entropy deviations were **not rare at all** when modeled correctly using **binomial statistics**. The key realization was that **assuming a normal distribution was incorrect**, and once the correct statistical framework was applied, the observed behavior of the TRNG was **entirely expected**.

To verify this further, I ran a high-quality **pseudo-random number generator (PRNG)** in parallel with the **BitBabbler White TRNG**. The **PRNG exhibited similar entropy fluctuations**, reinforcing the conclusion that both **TRNG and PRNG behaved as expected** according to statistical theory.

### **Conclusion:**
- The presence of **extreme entropy deviations (-9σ to -12σ)** does **not** indicate an anomaly but is a **statistical expectation** under the correct probability model.
- Both the **TRNG and PRNG** followed the same statistical behavior, confirming that no unusual external influence was at play.
- As a result, **Dr. Radin’s claim that mind may influence TRNGs was falsified**, at least in the case of this experiment.

**Note**: These results are specific to the **BitBabbler White TRNG**, which is based on **transistor noise**. Additional tests with the **ANU QRNG** have yet to be conducted in the same manner to determine whether the findings hold for quantum-based randomness.

## Project Components

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
