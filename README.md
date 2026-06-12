# CSP4CMSIS Hello World Demo for NUCLEO-G474RE

A minimal demonstration of the **CSP (Communicating Sequential Processes)** library using CMSIS‑RTOS v2 on an STM32G474RE microcontroller. This project shows a single process that prints "Hello world" repeatedly – the simplest possible Communicating Sequential Processes (CSP) network. The corresponding formal CSP model can be found [here](https://github.com/OliverFaust/CSP4CMSIS-shake-detection-NUCLEO-F401RE-/tree/main/Formal%20model).

## Features

- **FreeRTOS** with CMSIS‑RTOS v2 API  
- **CSP4CMSIS** library for process‑based concurrency  
- **Zero‑heap** static memory allocation – all processes reside in `.data`/`.bss`  
- **Serial console output** via USART1 (115200 baud)  
- **Infinite loop** with a 1‑second delay to avoid console flooding

## Hardware Requirements

- STM32 Nucleo‑G474RE board  
- USB cable for power, programming, and serial communication  
- No external components required

## Software Requirements

- STM32CubeIDE (or any ARM GCC toolchain)  
- CSP4CMSIS library (included as a git submodule or directly in `lib/`)

## Serial Configuration

| Parameter   | Value          |
|-------------|----------------|
| Baud Rate   | 115200         |
| Data Bits   | 8              |
| Stop Bits   | 1              |
| Parity      | None           |
| Flow Control| None           |

## Building with STM32CubeIDE

1. **Clone this repository** (do not place it inside your STM32CubeIDE workspace directory).  
2. Open STM32CubeIDE.  
3. Go to `File → Import → Existing Projects into Workspace`.  
4. Select the cloned directory.  
5. Build the project (default configuration `Debug` or `Release`).  
6. Flash the binary to your Nucleo board.

## Project Structure
```text
├── Core/ # Main application code (main.c, application.cpp)
├── Drivers/ # STM32 HAL drivers
├── lib/CSP4CMSIS/ # CSP library (static, zero‑heap)
├── Middlewares/ # FreeRTOS + CMSIS‑RTOS v2
├── .gitignore # Excludes build artefacts
└── README.md
```


## How It Works

1. **Process**: `HelloProcess` inherits from `CSProcess` and overrides the `run()` method.  
2. **Infinite loop**: Inside `run()`, the process prints `"Hello world"` and then delays for 1000 ms using `vTaskDelay`.  
3. **Parallel composition**: `InParallel(hello)` starts the single process.  
4. **Static network**: `ExecutionMode::StaticNetwork` ensures no dynamic memory allocation after startup.

Because there is only one process, no channels are needed – the process runs independently.

## Example Console Output

```text
Welcome to STM32 world !
=== STM32 FreeRTOS + CSP4CMSIS bootstrap ===

--- Single Hello World Process ---
Hello world
Hello world
Hello world
...
```

## Key CSP4CMSIS Concepts Demonstrated
* **Process** – creating a custom process by inheriting from CSProcess.
* **Run** – the process entry point.
* **InParallel** – composing one or more processes.
* **Static network** – no dynamic memory allocation after startup.
* **CSP scheduling** – processes are scheduled by the RTOS.

## Troubleshooting
* **No output on serial**: Verify the baud rate (115200) and that the correct COM port is used.
* **Program hangs**: Ensure vTaskDelay is used; without it, the loop would run as fast as possible, possibly starving other tasks (though there are none).
* **Heap usage warning**: CSP4CMSIS uses zero heap – all memory is static. If you see heap allocations, check that you are not using new/malloc elsewhere.

## License

MIT License – see `LICENSE` file (if included) or refer to the CSP4CMSIS library license.

## Acknowledgments

- STMicroelectronics for the STM32 HAL and CMSIS‑RTOS v2
- The FreeRTOS team
- [CSP4CMSIS](https://oliverfaust.github.io/CSP4CMSIS/) library by Oliver Faust
