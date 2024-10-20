# Quantum Random Data and Coin Toss Services (Windows)

## Overview

This project, designed for the Windows platform, uses two software processes: `RGNG.exe` and `QRNG.exe`. Its goal is to fetch and process random data from a quantum source and simulate coin tosses to test [Dr. Dean Radin](https://en.wikipedia.org/wiki/Dean_Radin)'s hypothesis that the mind may influence matter, particularly quantum processes. Dr. Radin suggests that true random number generators (TRNGs) might exhibit variability in randomness, potentially influenced by the mind. As a comparison, the project also utilizes a high-quality pseudo-random number generator (PRNG).

The quantum random data is retrieved from the [Australian National University Quantum Random Number Generator (ANU QRNG)](https://qrng.anu.edu.au/) server, which generates true random numbers based on quantum fluctuations.

## Falsifying Dr. Radin�s Hypothesis with BitBabbler TRNG

Initially, the project sought to validate or falsify Dr. Radin's claim using a **BitBabbler White TRNG** (based on transistor noise, also manufactured in Australia). By performing extensive statistical calculations, I found that **Shannon Eta entropy** results falling within the range of minus 9 to 12 sigma (a measure of statistical deviation) occurred far more frequently than expected if one assumes a **normal distribution** of the entropy values.

- **Minus 9 to 12 sigma**: In a normal distribution, events that fall outside this range would be considered highly improbable, leading one to expect them to occur very rarely (perhaps once in hundreds of years). However, with the **BitBabbler White TRNG**, such extreme events appeared much more often�roughly once every half a day�which aligned with brute-force statistical calculations.

This suggests that the assumption of normal distribution is wrong in this context and that both the TRNG and PRNG behaved as expected statistically. Thus, **Dr. Radin�s hypothesis was falsified**, at least when using the BitBabbler White TRNG.

**Note**: These results were specific to the **BitBabbler White TRNG** based on transistor noise. The tests with the **QRNG** (Quantum Random Number Generator) from ANU have not been thoroughly performed yet to reach similar conclusions.

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
