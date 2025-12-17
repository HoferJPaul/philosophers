# Philosophers — 42 Project

An implementation of the classic **Dining Philosophers** concurrency problem, developed as part of the 42 curriculum.

This project focuses on **correctness under concurrency**, precise timing, and robustness against race conditions and starvation — including edge cases that appear only under high contention and tight timing constraints.

---

## Overview

Each philosopher is represented by a thread that must:
- take two forks (mutexes)
- eat
- sleep
- think

The simulation ends when:
- a philosopher dies (fails to eat within `time_to_die`), or
- all philosophers have eaten the required number of times (optional argument)

The implementation strictly follows:
- POSIX threads (`pthread`)
- mutex-based synchronization
- 42 Norminette constraints

---

## Features

- Deadlock prevention via fork acquisition ordering
- Accurate death detection using timestamps (not sleep timing)
- Non-overlapping, thread-safe logging
- Starvation handling with controlled desynchronization
- Robust behavior under extreme and adversarial timing scenarios
- Clean shutdown and resource cleanup
- Passes common 42 philosophers testers, including hardcore edge cases

---

## Usage

### Compilation
```bash
make
```

### Execution
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Example
```bash
./philo 5 800 200 200
./philo 5 800 200 200 3
```

---

## Implementation Notes

### Synchronization
- Forks are protected by individual mutexes.
- Shared state (death flag, meal counters, timestamps) is protected by a dedicated mutex.
- Output is serialized to prevent interleaved logs.

### Death Detection
- A monitor loop continuously checks the time since each philosopher’s last meal.
- Death is detected using real timestamps (`gettimeofday`-based), not delays.
- Death messages are printed exactly once.

### Starvation & Fairness
- Small philosopher counts use intentional desynchronization to prevent phase-lock starvation.
- Large philosopher counts disable fairness heuristics to ensure deterministic death when expected.
- This balance allows the simulation to behave correctly in both “should survive” and “should die” test scenarios.

## Constraints & Compliance

- No global variables
- No busy waiting
- No data races
- No overlapping output
- Norminette compliant (≤25 lines per function)
